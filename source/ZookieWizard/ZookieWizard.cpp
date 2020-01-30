#include <ZookieWizard/ZookieWizard.h>

#include <kao2ar/TypeInfo.h>

#include <kao2ar/StaticPool.h>

namespace ZookieWizard
{
    const char* MESSAGE_TITLE_INFO = "Zookie Wizard — info";
    const char* MESSAGE_TITLE_ERROR = "Zookie Wizard — error";

    ////////////////////////////////////////////////////////////////
    // File Operator functions
    ////////////////////////////////////////////////////////////////

    FileOperator::FileOperator()
    {
        currentPath = nullptr;
    }

    FileOperator::~FileOperator()
    {
        close();
    }

    bool FileOperator::open(const char* filename, int mode)
    {
        int test = 0;

        if (mode & FILE_OPERATOR_MODE_READ)
        {
            test |= std::ios::in;
        }
        else
        {
            test |= std::ios::out;
        }

        if (mode & FILE_OPERATOR_MODE_BINARY)
        {
            test |= std::ios::binary;
        }

        file.open(filename, test);
        
        if (!file.is_open())
        {
            return false;
        }

        currentPath = (char*)filename;

        return true;
    }

    void FileOperator::close()
    {
        if (file.is_open())
        {
            file.close();
        }
    }

    void FileOperator::setDir(char* filename)
    {
        currentPath = filename;
    }

    bool FileOperator::createDir()
    {
        char* offset;
        char previous_char;
        int test;

        if (nullptr != currentPath)
        {
            offset = currentPath;

            while (0x00 != (*offset))
            {
                switch (*offset)
                {
                    case '/':
                    case '\\':
                    {
                        previous_char = (*offset);
                        (*offset) = 0x00;

                        test = CreateDirectory(currentPath, NULL);

                        (*offset) = previous_char;

                        if (0 == test)
                        {
                            switch (GetLastError())
                            {
                                case ERROR_PATH_NOT_FOUND:
                                {
                                    return false;
                                }
                            }
                        }
                    }
                }

                offset++;
            }

            return true;
        }

        return false;
    }

    void FileOperator::setPointer(int offset)
    {
        file.seekp(offset, std::ios::beg);
    }

    bool FileOperator::read(void* pointer, int size)
    {
        if (file.is_open())
        {
            file.read((char*)pointer, size);

            return file.good();
        }

        return false;
    }

    bool FileOperator::write(void* pointer, int size)
    {
        if (file.is_open())
        {
            file.write((char*)pointer, size);

            return file.good();
        }

        return false;
    }

    bool FileOperator::endOfFileReached()
    {
        return file.eof();
    }


    ////////////////////////////////////////////////////////////////
    // Error Message functions
    ////////////////////////////////////////////////////////////////

    ErrorMessage::ErrorMessage(const char* message, ...)
    {
        va_list args;
        
        va_start(args, message);

        vsprintf_s(text, 256, message, args);

        va_end(args);
    }

    void ErrorMessage::display()
    {
        HWND window = GUI::myWindowsGroupMain[0];

        MessageBox(window, text, MESSAGE_TITLE_ERROR, MB_ICONERROR);
    }


    ////////////////////////////////////////////////////////////////
    // Zookie Wizard: Start
    ////////////////////////////////////////////////////////////////

    int32_t Start(HINSTANCE hInstance)
    {
        /********************************/
        /* Prepare Kao2 engine! */

        try
        {
            InterfaceManager.registerInterfaces();

            StaticPool.registerStaticGadgets();
        }
        catch (ErrorMessage &e)
        {
            e.display();

            return (-1);
        }

        /********************************/
        /* Create GUI windows and prepare OpenGL */

        if (!GUI::createWindows(hInstance))
        {
            ErrorMessage
            (
                "Could not create Windows."
            )
            .display();
        }

        memset(&ofn, 0, sizeof(OPENFILENAME));
        ofn.lStructSize = sizeof(OPENFILENAME);
        ofn.lpstrFile = nullptr;
        ofn.nMaxFile = 0;
        ofn.lpstrFilter = "All files (*.*)\0*.*\0";
        ofn.hwndOwner = GUI::myWindowsGroupMain[0];
        ofn.hInstance = hInstance;

        if (!GUI::prepareRendering())
        {
            ErrorMessage
            (
                "Could not prepare OpenGL."
            )
            .display();
        }

        /********************************/
        /* Enter main loop */

        try
        {
            while (GUI::isAppRunning())
            {
                GUI::render();
            }
        }
        catch (ErrorMessage &e)
        {
            e.display();

            return (-1);
        }

        /********************************/
        /* Close application */

        GUI::closeWindows();

        return 0;
    }

}


////////////////////////////////////////////////////////////////
// Main
////////////////////////////////////////////////////////////////

int main()
{
    return ZookieWizard::Start(GetModuleHandle(NULL));
}
