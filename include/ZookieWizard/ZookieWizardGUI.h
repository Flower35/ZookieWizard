#ifndef H_ZOOKIEWIZARD_GUI
#define H_ZOOKIEWIZARD_GUI

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // Graphical User Interface
    ////////////////////////////////////////////////////////////////

    namespace GUI
    {
        /*** Defines and variables ***/

        #include <ZookieWizard/GUI_defines.h>

        #define TEST_CAMERA_DEFAULT_SPEED 10.0
        #define TEST_CAMERA_DEFAULT_SPEED_TEXT "10.0"

        #define TEST_CAMERA_NEAR_PLANE 1.0
        #define TEST_CAMERA_FAR_PLANE 30000.0

        #define ANIMATION_FRAMERATE_DEFAULT 30
        #define ANIMATION_FRAMERATE_DEFAULT_TEXT "30"

        #define TEST_CAMERA_FOV 45.0

        struct testCameraStruct
        {
            double pos_x;
            double pos_y;
            double pos_z;

            double look_x;
            double look_y;
            double look_z;

            double pitch;
            double yaw;
            double speed[2];

            float culling_normals[6][3];
            float culling_points[6][3];
            double aspect_ratio;

            int16_t mouse_prev_x;
            int16_t mouse_prev_y;
            uint8_t mouse_mode;

            int8_t keyboard_x;
            int8_t keyboard_y;
            int8_t keyboard_z;
            uint8_t object_mode;

            testCameraStruct();
            void reset(float, float, float);
            void calculateFrustum();
        };

        extern HBITMAP myWindowLogo;
        extern HFONT myWindowFont;
        extern HDC openGL_DeviceContext;
        extern HGLRC openGL_RenderingContext;

        extern float backgroundColor[3];
        extern bool isOrthoMode;
        extern testCameraStruct testCamera;

        enum drawFlags
        {
            DRAW_FLAG_OUTLINE = (1 << 0),
            DRAW_FLAG_INVISIBLE = (1 << 1),
            DRAW_FLAG_DRAWPASS1 = (1 << 2),
            DRAW_FLAG_DRAWPASS2 = (1 << 3),
            DRAW_FLAG_DRAWPASS3 = (1 << 4),
            DRAW_FLAG_TEXTURES = (1 << 5),
            DRAW_FLAG_BLENDING = (1 << 6),
            DRAW_FLAG_FRUSTUM = (1 << 7),
            DRAW_FLAG_COLORS = (1 << 8),
            DRAW_FLAG_LIGHTING = (1 << 9),
            DRAW_FLAG_ANIMS = (1 << 10),
            DRAW_FLAG_BOXZONES = (1 << 11),
            DRAW_FLAG_PROXIES = (1 << 12),
            DRAW_FLAG_COLLISION = (1 << 13),
            DRAW_FLAG_SPECIAL = (1 << 14),

            DRAW_FLAG_COUNT = 15
        };

        extern uint32_t myDrawFlags;

        extern LONGLONG timePrevious;
        extern float timeFrameStart;
        extern float timeCurrent;
        extern bool timeUpdate;
        extern int32_t animationID;
        extern int32_t animationFPS;
        extern bool renderingLimitFramerate;

        /*** Functions ***/

        bool createWindows(HINSTANCE hInstance);
        bool prepareRendering();

        bool isAppRunning();
        void render();
        void setPerspective(GLsizei, GLsizei);
        void changeView(bool);

        void moveCameraOrObject(int8_t x, int8_t y, int8_t z, uint8_t movement_mode);
        void getMovedSeletedTransform(void* transform);
        void setMovedSeletedTransform(void* transform);
        void multiplyBySelectedObjectTransform(bool ignore_scale);
        void repositionCamera(bool returning, void* transform);

        bool testWithCameraPlanes
        (
            float min_x, float min_y, float min_z,
            float max_x, float max_y, float max_z
        );

        void renderBoundingBox
        (
            float thickness,
            float color_r, float color_g, float color_b,
            float min_x, float min_y, float min_z,
            float max_x, float max_y, float max_z
        );

        void colorOfMarkedObject(float &color_r, float &color_g, float &color_b);

        void closeWindows();

        void updateNodesList(int32_t, void*);
        void updateArSettingsText(int32_t, const char*);

        LONGLONG timerGet();
        void timerReset();
        float timerGetCurrent();
        float timerGetFrames();
    }
}

#endif
