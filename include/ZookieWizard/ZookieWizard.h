#ifndef H_ZOOKIEWIZARD
#define H_ZOOKIEWIZARD


////////////////////////////////////////////////////////////////
// LIBRARIES
////////////////////////////////////////////////////////////////

/* Mathematical functions and variables */
#define _USE_MATH_DEFINES
#include <cmath>

/* `std::time` */
#include <ctime>

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
    extern const char* MESSAGE_TITLE_INFO;
    extern const char* MESSAGE_TITLE_ERROR;

    #define LARGE_BUFFER_SIZE 256

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

        bool endOfFileReached();
    };


    ////////////////////////////////////////////////////////////////
    // ERROR MESSAGE THROWER
    ////////////////////////////////////////////////////////////////

    class ErrorMessage
    {
        private:

            char text[2 * LARGE_BUFFER_SIZE];

        public:

            ErrorMessage(const char* message, ...);

            void display();
    };

}


////////////////////////////////////////////////////////////////
// Other headers
////////////////////////////////////////////////////////////////

#include <ZookieWizard/ZookieWizardGUI.h>
#include <ZookieWizard/ZookieWizardMisc.h>
#include <ZookieWizard/ZookieWizardSpecialModels.h>
#include <ZookieWizard/ZookieWizardMaterials.h>


#endif
