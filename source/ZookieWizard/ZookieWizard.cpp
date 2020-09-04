#include <ZookieWizard/ZookieWizard.h>
#include <ZookieWizard/WindowsManager.h>

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

    int FileOperator::getPointer()
    {
        return (int)file.tellp();
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

    bool FileOperator::peek(char &next_char)
    {
        if (file.is_open())
        {
            next_char = file.peek();

            return (file.good() && (!file.eof()));
        }

        return false;
    }

    bool FileOperator::endOfFileReached()
    {
        return file.eof();
    }

    void FileOperator::skip(int size)
    {
        file.seekp(size, std::ios_base::cur);
    }


    ////////////////////////////////////////////////////////////////
    // Error Message functions
    ////////////////////////////////////////////////////////////////

    ErrorMessage::ErrorMessage(const char* message, ...)
    {
        va_list args;

        va_start(args, message);

        vsprintf_s(text, 512, message, args);

        va_end(args);
    }

    void ErrorMessage::display()
    {
        GUI::theWindowsManager.displayMessage(WINDOWS_MANAGER_MESSAGE_ERROR, text);
    }


    ////////////////////////////////////////////////////////////////
    // Zookie Wizard: Start
    ////////////////////////////////////////////////////////////////

    int32_t Start(HINSTANCE hInstance)
    {
        int32_t test_value = 0;
        bool prepared_special_models = false;
        bool prepared_materials_viewer = false;

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

            test_value = (-1);
        }

        /********************************/
        /* Create GUI windows and prepare OpenGL */

        if (0 == test_value)
        {
            GUI::myWindowLogo = NULL;
            GUI::myWindowFont = NULL;

            if (false == GUI::createWindows(hInstance))
            {
                ErrorMessage
                (
                    "FATAL ERROR!\n" \
                    "Could not create Windows."
                )
                .display();

                test_value = (-1);
            }
        }

        if (0 == test_value)
        {
            memset(&ofn, 0, sizeof(OPENFILENAME));
            ofn.lStructSize = sizeof(OPENFILENAME);
            ofn.lpstrFile = nullptr;
            ofn.nMaxFile = 0;
            ofn.lpstrFilter = "All files (*.*)\0*.*\0";
            ofn.hwndOwner = GUI::theWindowsManager.getMainWindow();
            ofn.hInstance = hInstance;

            if (!GUI::prepareRendering())
            {
                ErrorMessage
                (
                    "FATAL ERROR!\n" \
                    "Could not prepare OpenGL."
                )
                .display();

                test_value = (-1);
            }
        }

        if (0 == test_value)
        {
            if (!GUI::prepareMaterialsManager())
            {
                ErrorMessage
                (
                    "FATAL ERROR!\n" \
                    "Could not prepare materials manager."
                )
                    .display();

                test_value = (-1);
            }

            prepared_materials_viewer = true;
        }

        if (0 == test_value)
        {
            if (!GUI::prepareSpecialModels())
            {
                ErrorMessage
                (
                    "FATAL ERROR!\n" \
                    "Could not prepare special models."
                )
                    .display();

                test_value = (-1);
            }

            prepared_special_models = true;
        }

        if (0 == test_value)
        {
            loadEditorSettings();
        }

        /********************************/
        /* Enter main loop */

        if (0 == test_value)
        {
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

                test_value = (-1);
            }
        }

        /********************************/
        /* Close application */

        if (prepared_materials_viewer)
        {
            GUI::clearMaterialsManager();
        }

        if (prepared_special_models)
        {
            GUI::clearSpecialModels();
        }

        GUI::closeWindows();

        saveEditorSettings();

        return test_value;
    }

}


////////////////////////////////////////////////////////////////
// Main
////////////////////////////////////////////////////////////////

int main()
{
    return ZookieWizard::Start(GetModuleHandle(NULL));
}
