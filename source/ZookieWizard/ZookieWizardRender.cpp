#include <ZookieWizard/ZookieWizard.h>
#include <ZookieWizard/WindowsManager.h>

#include <kao2ar/Archive.h>

#ifdef _DEBUG
    #define DEBUG_CAMERA_CULLING
#endif

namespace ZookieWizard
{
    namespace GUI
    {
        ////////////////////////////////////////////////////////////////
        // Initialize variables
        ////////////////////////////////////////////////////////////////

        HDC openGL_DeviceContext = NULL;
        HGLRC openGL_RenderingContext = NULL;

        float backgroundColor[3] = {0, 1.0f, 1.0f};
        bool isOrthoMode = false;
        testCameraStruct testCamera;

        int32_t myDrawFlags = 0;

        LONGLONG timePrevious = 0;
        float timeFrameStart = 0;
        float timeCurrent = 0;
        bool timeUpdate = false;
        int32_t animationID = 0;
        int32_t animationFPS = 1;

        testCameraStruct::testCameraStruct()
        {
            mouse_prev_x = 0;
            mouse_prev_y = 0;
            mouse_mode = 0;

            keyboard_x = 0;
            keyboard_y = 0;
            keyboard_z = 0;
            object_mode = 0;

            speed = TEST_CAMERA_DEFAULT_SPEED;
            reset(0, 0, 0);
        }

        void testCameraStruct::reset(float center_x, float center_y, float center_z)
        {
            pos_x = center_x;
            pos_y = center_y - 1000;
            pos_z = center_z;

            look_x = 0;
            look_y = 1.0;
            look_z = 0;

            pitch = 0;
            yaw = 0;

            aspect_ratio = (4.0 / 3.0);

            calculateFrustum();
        }

        static eSRP selectedObjectNewTransform;
        static float selectedObjectTransposedMatrix[16];


        ////////////////////////////////////////////////////////////////
        // Reposition camera
        ////////////////////////////////////////////////////////////////
        void repositionCamera(bool returning, void* transform)
        {
            float s;
            eSRP* test_srp = (eSRP*)transform;

            if (nullptr != test_srp)
            {
                if (returning)
                {
                    testCamera.pos_x -= test_srp->pos.x;
                    testCamera.pos_y -= test_srp->pos.y;
                    testCamera.pos_z -= test_srp->pos.z;

                    s = test_srp->scale;
                    if (s > 0)
                    {
                        s = (1.0f / s);
                        testCamera.pos_x *= s;
                        testCamera.pos_y *= s;
                        testCamera.pos_z *= s;
                    }
                }
                else
                {
                    s = test_srp->scale;
                    if (s > 0)
                    {
                        testCamera.pos_x *= s;
                        testCamera.pos_y *= s;
                        testCamera.pos_z *= s;
                    }

                    testCamera.pos_x += test_srp->pos.x;
                    testCamera.pos_y += test_srp->pos.y;
                    testCamera.pos_z += test_srp->pos.z;
                }
            }
        }


        ////////////////////////////////////////////////////////////////
        // Calculate frustum culling planes for camera
        ////////////////////////////////////////////////////////////////
        void testCameraStruct::calculateFrustum()
        {
            /* Dimensions of the viewing frustum */

            const float test = tanf((float)((TEST_CAMERA_FOV / 180.0f * M_PI) / 2.0f));

            const float near_half_height = (float)(test * TEST_CAMERA_NEAR_PLANE);
            const float near_half_width = (float)(near_half_height * aspect_ratio);

            ePoint3 eyes
            (
                (float)testCamera.pos_x,
                (float)testCamera.pos_y,
                (float)testCamera.pos_z
            );

            ePoint3 look
            (
                (float)testCamera.look_x,
                (float)testCamera.look_y,
                (float)testCamera.look_z
            );

            ePoint3 directions[3] =
            {
                {0, 1, 0}, // forwads [+Y]
                {1, 0, 0}, // right [+X]
                {0, 0, 1}  // upwards [+Z]
            };

            ePoint3 test_point = crossProduct(directions[0], look);

            eQuat rotation =
            {
                test_point.x,
                test_point.y,
                test_point.z,
                (- 1.0f - dotProduct(directions[0], look))
            };

            rotation.normalize();

            /* Special case, when look direction is [0, -1, 0] */
            if (rotation.getLength() <= 0)
            {
                rotation = {0, 0, 1, 0};
            }

            ePoint3 dir_right = (directions[1] * rotation) * near_half_width;
            ePoint3 dir_up = (directions[2] * rotation) * near_half_height;

            /* Near plane */

            culling_points[0][0] = (float)(testCamera.pos_x + (TEST_CAMERA_NEAR_PLANE * testCamera.look_x));
            culling_points[0][1] = (float)(testCamera.pos_y + (TEST_CAMERA_NEAR_PLANE * testCamera.look_y));
            culling_points[0][2] = (float)(testCamera.pos_z + (TEST_CAMERA_NEAR_PLANE * testCamera.look_z));

            culling_normals[0][0] = (float)testCamera.look_x;
            culling_normals[0][1] = (float)testCamera.look_y;
            culling_normals[0][2] = (float)testCamera.look_z;

            /* Far plane */

            culling_points[1][0] = (float)(testCamera.pos_x + (TEST_CAMERA_FAR_PLANE * testCamera.look_x));
            culling_points[1][1] = (float)(testCamera.pos_y + (TEST_CAMERA_FAR_PLANE * testCamera.look_y));
            culling_points[1][2] = (float)(testCamera.pos_z + (TEST_CAMERA_FAR_PLANE * testCamera.look_z));

            culling_normals[1][0] = (float)(-testCamera.look_x);
            culling_normals[1][1] = (float)(-testCamera.look_y);
            culling_normals[1][2] = (float)(-testCamera.look_z);

            /* 4 corners of the viewing frustum (near plane) */

            ePoint4 corners[4];

            for (int a = 0; a < 4; a++)
            {
                corners[a].x = culling_points[0][0];
                corners[a].y = culling_points[0][1];
                corners[a].z = culling_points[0][2];
            }

            corners[0] = corners[0] - dir_right; // left
            corners[0] = corners[0] - dir_up; // bottom

            corners[1] = corners[1] - dir_right; // left
            corners[1] = corners[1] + dir_up; // top

            corners[2] = corners[2] + dir_right; // right
            corners[2] = corners[2] - dir_up; // bottom

            corners[3] = corners[3] + dir_right; // right
            corners[3] = corners[3] + dir_up; // top

            /* Setting up points that are lying on 4 other planes (top, bottom, left, right) */

            for (int a = 0; a < 4; a++)
            {
                int b = 2 + a;
                int c = (a % 2) + 1; // top-left or bottom-right

                culling_points[b][0] = corners[c].x;
                culling_points[b][1] = corners[c].y;
                culling_points[b][2] = corners[c].z;
            }

            /* Vectors from camera center to near-plane-corners */

            for (int a = 0; a < 4; a++)
            {
                corners[a] = corners[a] - eyes;
            }

            /* Information for other planes: two vector IDs for cross product */
            /* All normals are pointing INWARDS (from outside into the camera viewing frustum) */

            const int other_planes_vectors[4][2] =
            {
                {1, 3}, // top plane (top-left x top-right)
                {2, 0}, // bottom plane (bottom-right x bottom-left)
                {0, 1}, // left plane (bottom-left x top-left)
                {3, 2}  // right plane (top-right x bottom-right)
            };

            for (int a = 0; a < 4; a++)
            {
                int b = 2 + a;

                ePoint4 dummy_vector = crossProduct
                (
                    corners[other_planes_vectors[a][0]],
                    corners[other_planes_vectors[a][1]]
                );

                dummy_vector.normalize();

                culling_normals[b][0] = dummy_vector.x;
                culling_normals[b][1] = dummy_vector.y;
                culling_normals[b][2] = dummy_vector.z;
            }
        }


        ////////////////////////////////////////////////////////////////
        // Check if object is visible in camera
        ////////////////////////////////////////////////////////////////
        bool testWithCameraPlanes
        (
            float min_x, float min_y, float min_z,
            float max_x, float max_y, float max_z
        )
        {
            ePoint4 points[8] =
            {
                {min_x, min_y, min_z, 0},
                {max_x, min_y, min_z, 0},
                {min_x, max_y, min_z, 0},
                {max_x, max_y, min_z, 0},
                {min_x, min_y, max_z, 0},
                {max_x, min_y, max_z, 0},
                {min_x, max_y, max_z, 0},
                {max_x, max_y, max_z, 0}
            };

            for (int a = 0; a < 6; a++)
            {
                ePoint4 plane_point
                (
                    testCamera.culling_points[a][0],
                    testCamera.culling_points[a][1],
                    testCamera.culling_points[a][2],
                    0
                );

                ePoint4 plane_normal
                (
                    testCamera.culling_normals[a][0],
                    testCamera.culling_normals[a][1],
                    testCamera.culling_normals[a][2],
                    0
                );

                bool is_outside_some_plane = true;

                for (int b = 0; (is_outside_some_plane) && (b < 8); b++)
                {
                    if (dotProduct(plane_normal, (points[b] - plane_point)) > 0)
                    {
                        /* At least one point of the bounding box */
                        /* is inside the viewing frustum */
                        is_outside_some_plane = false;
                    }
                }

                if (is_outside_some_plane)
                {
                    /* Every corner of the bounding box is outside ONE of the planes */
                    /* (please notice that it will never be outside ALL of the planes) */

                    #ifdef DEBUG_CAMERA_CULLING
                        glPushMatrix();

                        glLoadIdentity();

                        gluLookAt
                        (
                            testCamera.pos_x, testCamera.pos_y, testCamera.pos_z,
                            (testCamera.pos_x + testCamera.look_x),
                            (testCamera.pos_y + testCamera.look_y),
                            (testCamera.pos_z + testCamera.look_z),
                            0, 0, 1.0
                        );

                        renderBoundingBox(1.0f, 1.0f, 0, 0, min_x, min_y, min_z, max_x, max_y, max_z);

                        glPopMatrix();
                    #endif

                    return false;
                }
            }

            return true;
        }


        ////////////////////////////////////////////////////////////////
        // Prepare OpenGL window
        ////////////////////////////////////////////////////////////////
        bool prepareRendering()
        {
            int pixel_format;
            PIXELFORMATDESCRIPTOR pfd = {0};

            /* Reset global timer */
            timerReset();
            timeUpdate = true;

            /* Reset selected object transform matrix */
            selectedObjectNewTransform.getMatrix().transpose(selectedObjectTransposedMatrix);

            openGL_DeviceContext = GetDC(theWindowsManager.getRenderWindow());

            pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
            pfd.nVersion = 1;
            pfd.iLayerType = PFD_MAIN_PLANE;
            pfd.dwFlags = (PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER);
            pfd.cDepthBits = 32;
            pfd.cColorBits = 24;
            pfd.iPixelType = PFD_TYPE_RGBA;

            pixel_format = ChoosePixelFormat(openGL_DeviceContext, &pfd);

            if (FALSE == SetPixelFormat(openGL_DeviceContext, pixel_format, &pfd))
            {
                return false;
            }

            if (NULL == (openGL_RenderingContext = wglCreateContext(openGL_DeviceContext)))
            {
                return false;
            }

            if (FALSE == wglMakeCurrent(openGL_DeviceContext, openGL_RenderingContext))
            {
                return false;
            }

            /* Triangles cropping */
            glCullFace(GL_FRONT);

            /* Wireframe */
            glPolygonMode(GL_BACK, GL_LINE);

            /* Depth testing */
            glClearDepth(1.0f);
            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LEQUAL);

            /* Transparent textures */
            //// glEnable(GL_BLEND);
            //// glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            //// glBlendEquation(GL_FUNC_ADD);

            /* Default perspective */
            setPerspective(RECT_RENDER_X2, RECT_RENDER_Y2);

            return true;
        }


        ////////////////////////////////////////////////////////////////
        // Set OpenGL perspective
        ////////////////////////////////////////////////////////////////
        void setPerspective(GLsizei new_width, GLsizei new_height)
        {
            float p_x = 1.0f;
            float p_y = 1.0f;

            /* DO NOT DIVICE BY ZERO! */
            if (0 == new_width)
            {
                new_width = 1;
            }
            if (0 == new_height)
            {
                new_height = 1;
            }

            /* Set background color for this scene */
            glClearColor
            (
                backgroundColor[0], // Red
                backgroundColor[1], // Green
                backgroundColor[2], // Blue
                1.0 // Alpha
            );

            glViewport(0, 0, new_width, new_height);

            /* Begin with the projection matrix */
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();

            if (isOrthoMode)
            {
                /* Calculate proportions */
                if (new_height > new_width)
                {
                    p_y = (float)new_height / (float)new_width;
                }
                else if (new_height < new_width)
                {
                    p_x = (float)new_width / (float)new_height;
                }

                glOrtho
                (
                    (-p_x), // left
                    p_x, // right
                    (-p_y), // top
                    p_y, // bottom
                    0.0, // zNear
                    1.0 // zFar
                );
            }
            else
            {
                testCamera.aspect_ratio = ((double)new_width / (double)new_height);

                gluPerspective
                (
                    TEST_CAMERA_FOV, // field of view
                    testCamera.aspect_ratio, // aspect ratio
                    TEST_CAMERA_NEAR_PLANE, // zNear
                    TEST_CAMERA_FAR_PLANE // zFar
                );
            }

            /* Finish with the model matrix */
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
        }


        ////////////////////////////////////////////////////////////////
        // Change OpenGL viewing
        ////////////////////////////////////////////////////////////////
        void changeView(bool change_to_perspective_view)
        {
            float to_be_changed = false;
            RECT rc;

            if ((!change_to_perspective_view) && (!isOrthoMode))
            {
                isOrthoMode = true;
                to_be_changed = true;
            }

            if (change_to_perspective_view && isOrthoMode)
            {
                isOrthoMode = false;
                to_be_changed = true;
            }

            if (to_be_changed)
            {
                GetWindowRect(theWindowsManager.getRenderWindow(), &rc);
                setPerspective((rc.right - rc.left), (rc.bottom - rc.top));
            }
        }


        ////////////////////////////////////////////////////////////////
        // Get or Set selected object's new transformation
        ////////////////////////////////////////////////////////////////

        void getMovedSeletedTransform(void* transform)
        {
            eSRP* test_srp_ptr = (eSRP*)transform;

            (*test_srp_ptr) = selectedObjectNewTransform;
        }

        void setMovedSeletedTransform(void* transform)
        {
            eSRP* test_srp_ptr = (eSRP*)transform;

            if (nullptr != test_srp_ptr)
            {
                selectedObjectNewTransform = (*test_srp_ptr);
            }
            else
            {
                selectedObjectNewTransform = eSRP();
            }

            selectedObjectNewTransform.getMatrix().transpose(selectedObjectTransposedMatrix);
        }

        void multiplyBySelectedObjectTransform()
        {
            glMultMatrixf(selectedObjectTransposedMatrix);
        }


        ////////////////////////////////////////////////////////////////
        // Use mouse or keyboard to move camera around (or update position and rotation)
        ////////////////////////////////////////////////////////////////
        void moveCameraOrObject(int8_t x, int8_t y, int8_t z, uint8_t movement_mode)
        {
            bool angle_calculations = false;
            bool frustum_calculations = false;
            float dir_x, dir_y, dir_z, dummy_angle;
            eQuat test_quaternion;
            ePoint3 test_direction;

            const double ROTATING_SPEED = (0.05 / (TEST_CAMERA_DEFAULT_SPEED / 2.0));
            const double STRAFING_SPEED = (100.0 / TEST_CAMERA_DEFAULT_SPEED);

            if ((0 != x) || (0 != y) || (0 != z))
            {
                dir_x = float(x > 0) - float(x < 0);
                dir_y = float(y > 0) - float(y < 0);
                dir_z = float(z > 0) - float(z < 0);

                if ((false == isOrthoMode) && (0 == testCamera.object_mode))
                {
                    /* [0] default, keyboard movement -> [2] */
                    /* [1] (LMB) ROTATE CAMERA */
                    /* [2] (RMB) PAN CAMERA */

                    if (1 == movement_mode)
                    {
                        /* Modify "rot_Z" from "x" (horizontal) parameter */
                        /* (x > 0) look to the right (ADD) */
                        /* (x < 0) look to the left (SUBTRACT) */

                        testCamera.yaw += (dir_x * ROTATING_SPEED * (testCamera.speed / 2.0));

                        /* Modify "rot_X" from "z" (vertical) parameter */
                        /* (z > 0) look up (ADD) */
                        /* (z < 0) look down (SUBTRACT) */

                        testCamera.pitch += (dir_z * ROTATING_SPEED * (testCamera.speed / 2.0));

                        angle_calculations = true;
                        frustum_calculations = true;
                    }
                    else if ((0 == movement_mode) || (2 == movement_mode))
                    {
                        /* (x > 0) move to the right */
                        /* (x < 0) move to the left */

                        if (0 != x)
                        {
                            testCamera.pos_x += (dir_x * testCamera.look_y * STRAFING_SPEED * testCamera.speed);
                            testCamera.pos_y -= (dir_x * testCamera.look_x * STRAFING_SPEED * testCamera.speed);

                            frustum_calculations = true;
                        }

                        /* (y > 0) move forwards */
                        /* (y < 0) move backwards */

                        if (0 != y)
                        {
                            testCamera.pos_x += (dir_y * testCamera.look_x * STRAFING_SPEED * testCamera.speed);
                            testCamera.pos_y += (dir_y * testCamera.look_y * STRAFING_SPEED * testCamera.speed);
                            testCamera.pos_z += (dir_y * testCamera.look_z * STRAFING_SPEED * testCamera.speed);

                            frustum_calculations = true;
                        }

                        /* (z > 0) move uprawds */
                        /* (z < 0) move downwards */

                        if (0 != z)
                        {
                            testCamera.pos_z += (dir_z * STRAFING_SPEED * testCamera.speed);

                            frustum_calculations = true;
                        }
                    }
                }
                else if (1 == testCamera.object_mode)
                {
                    /* [X/Y/Z] MOVING */

                    if (0 != x)
                    {
                        selectedObjectNewTransform.pos.x += float(dir_x * testCamera.look_y * STRAFING_SPEED * testCamera.speed);
                        selectedObjectNewTransform.pos.y -= float(dir_x * testCamera.look_x * STRAFING_SPEED * testCamera.speed);
                    }

                    if (0 != y)
                    {
                        selectedObjectNewTransform.pos.x += float(dir_y * testCamera.look_x * STRAFING_SPEED * testCamera.speed);
                        selectedObjectNewTransform.pos.y += float(dir_y * testCamera.look_y * STRAFING_SPEED * testCamera.speed);
                    }

                    if (0 != z)
                    {
                        selectedObjectNewTransform.pos.z += float(dir_z * STRAFING_SPEED * testCamera.speed);
                    }

                    selectedObjectNewTransform.getMatrix().transpose(selectedObjectTransposedMatrix);
                }
                else if (2 == testCamera.object_mode)
                {
                    /* ARBITRARY ROTATION */

                    if (0 != x)
                    {
                        /* Rotate countner-clockwise around "Z-axis" (the user drags the object) */
                        dummy_angle = (float)((-dir_x) * ROTATING_SPEED * testCamera.speed * 10.0);
                        test_quaternion.fromEulerAngles(false, 0, 0, (float)(M_PI * dummy_angle / 180.0f));

                        selectedObjectNewTransform.rot = selectedObjectNewTransform.rot * test_quaternion;
                    }

                    if (0 != y)
                    {
                        /* Get a vector that is perpendicular to "Look Direction" around "Z-axis" */
                        test_direction = {(float)testCamera.look_y, (float)(- testCamera.look_x), 0};

                        /* If camera is pointing "Y-forwards", the rotation will occur around "X-axis" */
                        dummy_angle = (float)(dir_y * ROTATING_SPEED * testCamera.speed * 10.0);
                        test_quaternion.fromAxisAngle(test_direction, (float)(M_PI * dummy_angle / 180.0f));

                        selectedObjectNewTransform.rot = selectedObjectNewTransform.rot * test_quaternion;
                    }

                    if (0 != z)
                    {
                        /* Get "Look Direction" vector */
                        test_direction = {(float)testCamera.look_x, (float)testCamera.look_y, (float)testCamera.look_z};

                        /* If camera is pointing "Y-forwards", the rotation will occur around "Y-axis" */
                        dummy_angle = (float)(dir_z * ROTATING_SPEED * testCamera.speed * 10.0);
                        test_quaternion.fromAxisAngle(test_direction, (float)(M_PI * dummy_angle / 180.0f));

                        selectedObjectNewTransform.rot = selectedObjectNewTransform.rot * test_quaternion;
                    }

                    selectedObjectNewTransform.getMatrix().transpose(selectedObjectTransposedMatrix);
                }
            }

            /* Get camera direction */

            if (angle_calculations)
            {
                if (testCamera.pitch > (M_PI / 2.0 - 0.0001))
                {
                    testCamera.pitch = (M_PI / 2.0 - 0.0001);
                }
                else if (testCamera.pitch < - (M_PI / 2.0 - 0.0001))
                {
                    testCamera.pitch = - (M_PI / 2.0 - 0.0001);
                }

                if ((testCamera.yaw > (2.0 * M_PI)) || (testCamera.yaw < (- 2.0 * M_PI)))
                {
                    testCamera.yaw = 0;
                }

                testCamera.look_x = cos(testCamera.pitch) * sin(testCamera.yaw);
                testCamera.look_y = cos(testCamera.pitch) * cos(testCamera.yaw);
                testCamera.look_z = sin(testCamera.pitch);
            }

            /* Update viewing frustum */

            if (frustum_calculations)
            {
                testCamera.calculateFrustum();
            }
        }


        ////////////////////////////////////////////////////////////////
        // Render bounding box
        ////////////////////////////////////////////////////////////////
        void renderBoundingBox
        (
            float thickness,
            float color_r, float color_g, float color_b,
            float min_x, float min_y, float min_z,
            float max_x, float max_y, float max_z
        )
        {
            glBindTexture(GL_TEXTURE_2D, 0);

            glColor3f(color_r, color_g, color_b);
            glLineWidth(thickness);
            glBegin(GL_LINES);

            /* Cube Front */

            glVertex3f(min_x, min_y, min_z);
            glVertex3f(max_x, min_y, min_z);

            glVertex3f(max_x, min_y, min_z);
            glVertex3f(max_x, min_y, max_z);

            glVertex3f(max_x, min_y, max_z);
            glVertex3f(min_x, min_y, max_z);

            glVertex3f(min_x, min_y, max_z);
            glVertex3f(min_x, min_y, min_z);

            /* Cube Back */

            glVertex3f(min_x, max_y, min_z);
            glVertex3f(max_x, max_y, min_z);

            glVertex3f(max_x, max_y, min_z);
            glVertex3f(max_x, max_y, max_z);

            glVertex3f(max_x, max_y, max_z);
            glVertex3f(min_x, max_y, max_z);

            glVertex3f(min_x, max_y, max_z);
            glVertex3f(min_x, max_y, min_z);

            /* Cube Left */

            glVertex3f(min_x, max_y, max_z);
            glVertex3f(min_x, min_y, max_z);

            glVertex3f(min_x, max_y, min_z);
            glVertex3f(min_x, min_y, min_z);

            /* Cube Right */

            glVertex3f(max_x, max_y, max_z);
            glVertex3f(max_x, min_y, max_z);

            glVertex3f(max_x, max_y, min_z);
            glVertex3f(max_x, min_y, min_z);

            /* Stop drawing lines */

            glEnd();
            glColor3f(1.0f, 1.0f, 1.0f);
            glLineWidth(1.0f);
        }


        ////////////////////////////////////////////////////////////////
        // Generate glowing color for selected object
        ////////////////////////////////////////////////////////////////
        void colorOfMarkedObject(float &color_r, float &color_g, float &color_b)
        {
            const float GLOW_INTERVAL = 2.0f; // seconds

            const float tones[2][3] =
            {
                {1.0f, 1.0f, 1.0f}, // white
                {0.5f, 0, 1.0f} // purple
            };

            float time = fmod(timerGetCurrent(), GLOW_INTERVAL);
            float ratio = std::fabs(std::sinf((float)(M_PI * time / GLOW_INTERVAL)));
            float inv_ratio = (1.0f - ratio);

            color_r = ratio * tones[0][0] + inv_ratio * tones[1][0];
            color_g = ratio * tones[0][1] + inv_ratio * tones[1][1];
            color_b = ratio * tones[0][2] + inv_ratio * tones[1][2];
        }


        ////////////////////////////////////////////////////////////////
        // Render current scene
        ////////////////////////////////////////////////////////////////
        void render()
        {
            char bufor[64];
            float time_start, time_elapsed;

            /* Get time at the beginning, measure elapsed time */

            time_start = timerGetCurrent();
            time_elapsed = time_start - timeFrameStart;

            /* Limit rendering to 60 fps */

            //// if (time_elapsed >= (1.0f / 60.0f))
            if (true) // [DEBUG] (makes system unresponsive for no reason)
            {
                /* Remeber current frame starting time */

                timeFrameStart = time_start;

                /* Prepare frame and camera */

                glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

                moveCameraOrObject(testCamera.keyboard_x, testCamera.keyboard_y, testCamera.keyboard_z, 0);

                glLoadIdentity();

                gluLookAt
                (
                    testCamera.pos_x, // eyes X
                    testCamera.pos_y, // eyes Y
                    testCamera.pos_z, // eyes Z
                    (testCamera.pos_x + testCamera.look_x), // center X
                    (testCamera.pos_y + testCamera.look_y), // center Y
                    (testCamera.pos_z + testCamera.look_z), // center Z
                    0, // up X
                    0, // up Y
                    1.0 // up Z
                );

                /* Render one frame */

                myARs[0].renderScene(myDrawFlags);

                SwapBuffers(openGL_DeviceContext);
            }

            /* Update main window title */

            if (time_elapsed > 0)
            {
                sprintf_s(bufor, 64, "Zookie Wizard (%.2f fps)", (1.0f / time_elapsed));
            }
            else
            {
                sprintf_s(bufor, 64, "Zookie Wizard");
            }

            SetWindowText(theWindowsManager.getMainWindow(), bufor);
        }


        ////////////////////////////////////////////////////////////////
        // Timer functions
        ////////////////////////////////////////////////////////////////

        LONGLONG timerGet()
        {
            /* Returns time in miliseconds */

            static LARGE_INTEGER s_frequency;

            if (QueryPerformanceFrequency(&s_frequency))
            {
                LARGE_INTEGER now;
                QueryPerformanceCounter(&now);

                return (1000LL * now.QuadPart / s_frequency.QuadPart);
            }
            else
            {
                return GetTickCount64();
            }
        }

        void timerReset()
        {
            timePrevious = timerGet();
            timeCurrent = 0;
        }

        float timerGetCurrent()
        {
            /* Return time in seconds */

            if (timeUpdate)
            {
                /* Subtract 64-bit integers, then convert to float */

                timeCurrent = (timerGet() - timePrevious) / 1000.0f;
            }

            return timeCurrent;
        }

        float timerGetFrames()
        {
            /* [s] x [frame/s] = [frame] */
            return timerGetCurrent() * animationFPS;
        }

    }
}
