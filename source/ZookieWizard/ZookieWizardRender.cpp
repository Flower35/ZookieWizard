#include <ZookieWizard/ZookieWizard.h>

#include <kao2ar/Archive.h>

namespace ZookieWizard
{
    namespace GUI
    {
        ////////////////////////////////////////////////////////////////
        // Initialize variables
        ////////////////////////////////////////////////////////////////
        
        HDC openGL_DeviceContext = NULL;
        HGLRC openGL_RenderingContext = NULL;

        int32_t mousePosAndButton[3] = {0, 0, 0};
        float backgroundColor[3] = {0, 1.0f, 1.0f};
        bool isOrthoMode = false;
        testCameraStruct testCamera;

        int32_t myDrawFlags = 0;

        testCameraStruct::testCameraStruct()
        {
            reset();
        }

        void testCameraStruct::reset()
        {
            pos_x = 0;
            pos_y = (-1000);
            pos_z = 0;

            look_x = 0;
            look_y = 1.0;
            look_z = 0;

            pitch = 0;
            yaw = 0;
        }


        ////////////////////////////////////////////////////////////////
        // Renderer window procedure
        ////////////////////////////////////////////////////////////////
        LRESULT CALLBACK procedureOfRenderWindow(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
        {
            switch (Msg)
            {
                case WM_LBUTTONDOWN:
                {
                    mousePosAndButton[0] = LOWORD(lParam);
                    mousePosAndButton[1] = HIWORD(lParam);
                    mousePosAndButton[2] = 1;

                    break;
                }

                case WM_RBUTTONDOWN:
                {
                    mousePosAndButton[0] = LOWORD(lParam);
                    mousePosAndButton[1] = HIWORD(lParam);
                    mousePosAndButton[2] = 2;

                    break;
                }

                case WM_LBUTTONUP:
                case WM_RBUTTONUP:
                {
                    mousePosAndButton[2] = 0;

                    break;
                }

                case WM_MOUSEMOVE:
                {
                    if (mousePosAndButton[2] > 0)
                    {
                        moveCameraAndLook
                        (
                            (LOWORD(lParam) - mousePosAndButton[0]),
                            (HIWORD(lParam) - mousePosAndButton[1])
                        );

                        mousePosAndButton[0] = LOWORD(lParam);
                        mousePosAndButton[1] = HIWORD(lParam);
                    }

                    break;
                }
            }

            return DefWindowProc(hWnd, Msg, wParam, lParam);
        }


        ////////////////////////////////////////////////////////////////
        // Prepare OpenGL window
        ////////////////////////////////////////////////////////////////
        bool prepareRendering()
        {
            int pixel_format;
            PIXELFORMATDESCRIPTOR pfd = {0};

            openGL_DeviceContext = GetDC(myWindowsGroupMain[1]);

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
                gluPerspective
                (
                    45.0, // field of view
                    ((GLfloat)new_width / (GLfloat)new_height), // aspect ratio
                    1.0, // zNear
                    160000.0 // zFar
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
                GetWindowRect(myWindowsGroupMain[1], &rc);
                setPerspective((rc.right - rc.left), (rc.bottom - rc.top));
            }
        }


        ////////////////////////////////////////////////////////////////
        // Try to use mouse to move camera around...
        ////////////////////////////////////////////////////////////////
        void moveCameraAndLook(int32_t x, int32_t y)
        {
            bool calculations = false;

            const double ROTATING_SPEED = 0.01;
            const double STRAFING_SPEED = 100.0;

            if (!isOrthoMode)
            {
                /* 1 (LMB): rotate camera */
                /* 2 (RMB): pan camera */

                switch (mousePosAndButton[2])
                {
                    case 1:
                    {
                        /* Modify "rot_Z" */

                        if (x > 0) // look to the right (ADD)
                        {
                            testCamera.yaw += ((double)x * ROTATING_SPEED);
                        }
                        else if (x < 0) // look to the left (SUBTRACT)
                        {
                            testCamera.yaw -= ((double)(-x) * ROTATING_SPEED);
                        }

                        /* Modify "rot_X" */

                        if (y > 0) // look down (SUBTRACT)
                        {
                            testCamera.pitch -= ((double)y * ROTATING_SPEED);
                        }
                        else if (y < 0) // look up (ADD)
                        {
                            testCamera.pitch += ((double)(-y) * ROTATING_SPEED);
                        }

                        calculations = true;
                        break;
                    }

                    case 2:
                    {
                        if (x > 0) // move to the right
                        {
                            testCamera.pos_x += (testCamera.look_y * STRAFING_SPEED);
                            testCamera.pos_y -= (testCamera.look_x * STRAFING_SPEED);
                        }
                        else if (x < 0) // move to the left
                        {
                            testCamera.pos_x -= (testCamera.look_y * STRAFING_SPEED);
                            testCamera.pos_y += (testCamera.look_x * STRAFING_SPEED);
                        }

                        if (y > 0) // move backwards
                        {
                            testCamera.pos_x -= (testCamera.look_x * STRAFING_SPEED);
                            testCamera.pos_y -= (testCamera.look_y * STRAFING_SPEED);
                            testCamera.pos_z -= (testCamera.look_z * STRAFING_SPEED);
                        }
                        else if (y < 0) // move forwards
                        {
                            testCamera.pos_x += (testCamera.look_x * STRAFING_SPEED);
                            testCamera.pos_y += (testCamera.look_y * STRAFING_SPEED);
                            testCamera.pos_z += (testCamera.look_z * STRAFING_SPEED);
                        }

                        break;
                    }
                }

                /* Get camera direction */

                if (calculations)
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

                /* Load identity before making eye contact... */
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
            }
        }


        ////////////////////////////////////////////////////////////////
        // Render current scene
        ////////////////////////////////////////////////////////////////
        void render()
        {
            glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

            moveCameraAndLook(0, 0);

            myARs[0].renderScene(0, myDrawFlags);

            SwapBuffers(openGL_DeviceContext);
        }

    }
}
