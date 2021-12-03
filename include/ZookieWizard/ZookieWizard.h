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


////////////////////////////////////////////////////////////////
// MACROS
////////////////////////////////////////////////////////////////

#define DEG2RAD(angle) ((angle) * (double)M_PI / 180.0)
#define RAD2DEG(angle) ((angle) * 180.0 / (double)M_PI)

#define DEG2RAD_F(angle) ((angle) * (float)M_PI / 180.0f)
#define RAD2DEG_F(angle) ((angle) * 180.0f / (float)M_PI)


////////////////////////////////////////////////////////////////
// PROJECT NAMESPACE
////////////////////////////////////////////////////////////////

namespace ZookieWizard
{
    extern const char* MESSAGE_TITLE_INFO;
    extern const char* MESSAGE_TITLE_ERROR;

    #define LARGE_BUFFER_SIZE  256

    ////////////////////////////////////////////////////////////////
    // FILE OPERATOR STRUCTURE
    ////////////////////////////////////////////////////////////////

    #define FILE_OPERATOR_MODE_READ    (0x01 << 0)
    #define FILE_OPERATOR_MODE_BINARY  (0x01 << 1)

    struct FileOperator
    {
        /*** Properties ***/

        public:

            std::fstream file;
            char* currentPath;

        /*** Methods ***/

        public:

            FileOperator();
            ~FileOperator();

            bool open(const char* filename, int mode);
            void close();

            bool read(void* pointer, int size);
            bool write(void* pointer, int size);
            bool peek(char &next_char);

            void setDir(char* filename);
            bool createDir();

            int getPointer();
            void setPointer(int offset);
            void skip(int size);

            bool endOfFileReached();
    };


    ////////////////////////////////////////////////////////////////
    // ERROR MESSAGE THROWER
    ////////////////////////////////////////////////////////////////

    class ErrorMessage
    {
        /*** Properties ***/

        private:

            char message[2 * LARGE_BUFFER_SIZE];
            bool header;

        /*** Methods ***/

        public:

            ErrorMessage(const char* c_format, ...);

            void appendHeader(const char* c_format, ...);
            bool wasHeaderAppended() const;

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
#include <ZookieWizard/ZookieWizardNodes.h>


#endif
