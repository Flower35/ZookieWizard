#ifndef H_ZOOKIEWIZARD
#define H_ZOOKIEWIZARD


////////////////////////////////////////////////////////////////
// LIBRARIES
////////////////////////////////////////////////////////////////

/* Mathematical functions and variables */
#define _USE_MATH_DEFINES
#include <cmath>

/* Win32 app */
#include <Windows.h>

/* File stream */
#include <fstream>

/* `vsprintf_s()` (for error messages) */
#include <cstdio>
    
/* `std::strcmp()` */
#include <cstring>

/* OpenGL (3D API) */
#pragma comment (lib, "opengl32")
#pragma comment (lib, "glu32")
#include <gl/GL.h>
#include <gl/GLU.h>


namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // FILE OPERATOR STRUCTURE
    ////////////////////////////////////////////////////////////////

    #define FILE_OPERATOR_MODE_READ 0x01
    #define FILE_OPERATOR_MODE_BINARY 0x02

    struct FileOperator
    {
        std::fstream file;
        char* currentPath;

        FileOperator();
        ~FileOperator();

        bool open(const char* filename, int mode);
        void close();

        bool read(void* pointer, int size);
        bool write(void* pointer, int size);

        void setDir(char* filename);
        bool createDir();

        void setPointer(int offset);
    };


    ////////////////////////////////////////////////////////////////
    // ERROR MESSAGE THROWER
    ////////////////////////////////////////////////////////////////

    class ErrorMessage
    {
        public:

            char text[256];

            ErrorMessage(const char* message, ...);

            void display(HWND windows);
    };


    ////////////////////////////////////////////////////////////////
    // GUI
    ////////////////////////////////////////////////////////////////

    namespace GUI
    {
        /*** Properties ***/

            #include <ZookieWizard/GUI_defines.h>

            enum windowID
            {
                WINDOW_MAIN = 0,
                WINDOW_RENDER,

                WINDOWS_COUNT
            };

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

                testCameraStruct();
                void reset();
            };

            extern HWND myWindows[windowID::WINDOWS_COUNT];
            extern HBITMAP myWindowsLogo;
            extern HFONT myWindowsFont;
            extern HDC openGL_DeviceContext;
            extern HGLRC openGL_RenderingContext;

            extern int32_t mousePosAndButton[3];
            extern float backgroundColor[3];
            extern bool isOrthoMode;
            extern testCameraStruct testCamera;

            enum drawFlags
            {
                DRAW_FLAG_INVISIBLE = (1 << 0),
                DRAW_FLAG_BOXZONES = (1 << 1),
                DRAW_FLAG_PROXIES = (1 << 2),

                DRAW_FLAGS_COUNT = 3
            };

            extern int32_t myDrawFlags;

        /*** Methods ***/

            bool createWindows(HINSTANCE hInstance);
            bool prepareRendering();

            LRESULT CALLBACK procedureOfRenderWindow(HWND, UINT, WPARAM, LPARAM);
            LRESULT CALLBACK procedureOfMainWindow(HWND, UINT, WPARAM, LPARAM);

            bool isAppRunning();
            void render();
            void setPerspective(GLsizei, GLsizei);
            void changeView(bool);
            void moveCameraAndLook(int32_t, int32_t);
            
            void closeWindows();
    }

    
    ////////////////////////////////////////////////////////////////
    // miscellaneous
    ////////////////////////////////////////////////////////////////

    class Archive;

    /*** Variables ***/

        static const int MAX_OPEN_ARCHIVES = 2;
        extern int archivesInUse;
        extern Archive myARs[MAX_OPEN_ARCHIVES];

        extern OPENFILENAME ofn;

        extern int currentGameVersion;
        extern char currentWorkingDirectory[256];

    /*** Functions ***/

        void openOrSaveAr(int);
        void setGameVersion(int);

}

#endif
