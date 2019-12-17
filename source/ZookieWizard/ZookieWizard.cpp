#include <ZookieWizard/ZookieWizard.h>

#include <kao2ar/TypeInfo.h>
#include <kao2ar/Archive.h>

#include <kao2ar/StaticPool.h>
#include <kao2engine/Log.h>

namespace ZookieWizard
{

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

    void ErrorMessage::display(HWND window)
    {
        MessageBox(window, text, "KAO2 ERROR", MB_ICONERROR);
    }


    ////////////////////////////////////////////////////////////////
    // Zookie Wizard: Start
    ////////////////////////////////////////////////////////////////

    int32_t Start(HINSTANCE hInstance)
    {
        const char* title = "ZookieWizard: Kao2 editor";

        /********************************/
        /* Prepare Kao2 engine! */

        try
        {
            InterfaceManager.registerInterfaces();

            StaticPool.registerStaticGadgets();
        }
        catch (ErrorMessage &e)
        {
            e.display(0);

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
            .display(NULL);
        }

        memset(&ofn, 0, sizeof(OPENFILENAME));
        ofn.lStructSize = sizeof(OPENFILENAME);
        ofn.lpstrFile = nullptr;
        ofn.nMaxFile = 0;
        ofn.lpstrFilter = "All files (*.*)\0*.*\0";
        ofn.hwndOwner = GUI::myWindows[GUI::windowID::WINDOW_MAIN];
        ofn.hInstance = hInstance;

        if (!GUI::prepareRendering())
        {
            ErrorMessage
            (
                "Could not prepare OpenGL."
            )
            .display(GUI::myWindows[GUI::windowID::WINDOW_MAIN]);
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
            e.display(GUI::myWindows[GUI::windowID::WINDOW_MAIN]);

            return (-1);
        }

        /********************************/
        /* Close application */

        GUI::closeWindows();

        return 0;
    }


    ////////////////////////////////////////////////////////////////
    // miscellaneous: variables
    ////////////////////////////////////////////////////////////////

    int archivesInUse = 0;
    Archive myARs[MAX_OPEN_ARCHIVES];

    OPENFILENAME ofn;

    int currentGameVersion = (-1);
    char currentWorkingDirectory[256] = "";


    ////////////////////////////////////////////////////////////////
    // miscellaneous: functions
    ////////////////////////////////////////////////////////////////

    void openOrSaveAr(int32_t mode)
    {
        int32_t result;
        eString ar_name;
        char bufor[256];

        bool skip_creating_new_ar = true;
        bool skip_dialog = true;
        uint8_t open_or_save_dialog = 0;
        int32_t archive_flags = 0;
        DWORD ofn_flags = 0;

        const char* title = "ZookieWizard: Kao2 editor";
        const char* ofn_title = nullptr;
        const char* final_msg = nullptr;

        switch (mode)
        {
            case AR_MODE_READ:
            {
                archive_flags = (AR_MODE_ABSOLUTE_PATH | AR_MODE_READ | AR_MODE_DEBUG);
                ofn_flags = (OFN_FILEMUSTEXIST | OFN_HIDEREADONLY);

                ofn_title = "Opening KAO2 Archive...";
                final_msg = "<\"%s\">\n\nArchive reading completed successfully! :)";

                skip_creating_new_ar = false;
                skip_dialog = false;
                open_or_save_dialog = 0x01;

                break;
            }

            case AR_MODE_WRITE:
            {
                archive_flags = (AR_MODE_ABSOLUTE_PATH | AR_MODE_WRITE | AR_MODE_DEBUG);
                ofn_flags = (OFN_OVERWRITEPROMPT);

                ofn_title = "Saving KAO2 Archive...";
                final_msg = "<\"%s\">\n\nArchive saving completed successfully! :)";

                skip_creating_new_ar = true;
                skip_dialog = false;
                open_or_save_dialog = 0x02;

                break;
            }

            case AR_MODE_EXPORT_SCRIPTS:
            {
                archive_flags = (AR_MODE_ABSOLUTE_PATH | AR_MODE_EXPORT_SCRIPTS);

                final_msg = "<\"%s\">\n\nScripts exporting completed successfully! :)";

                skip_creating_new_ar = true;
                skip_dialog = true;
                open_or_save_dialog = 0x02;

                break;
            }

            case AR_MODE_EXPORT_PROXIES:
            {
                archive_flags = (AR_MODE_ABSOLUTE_PATH | AR_MODE_EXPORT_PROXIES);

                final_msg = "<\"%s\">\n\nProxies exporting completed successfully! :)";

                skip_creating_new_ar = true;
                skip_dialog = true;
                open_or_save_dialog = 0x02;

                break;
            }

            default:
            {
                return;
            }

        }

        try
        {
            if (false == skip_dialog)
            {
                bufor[0] = 0x00;

                ofn.lpstrFile = bufor;
                ofn.nMaxFile = 256;
                ofn.lpstrTitle = ofn_title;
                ofn.lpstrFilter = "KAO2 Archive files (*.ar)\0*.ar\0";
                ofn.Flags = ofn_flags;

                if (1 == open_or_save_dialog)
                {
                    result = GetOpenFileName(&ofn);
                }
                else if (2 == open_or_save_dialog)
                {
                    result = GetSaveFileName(&ofn);
                }
                else
                {
                    result = 0;
                }

                if (0 == result)
                {
                    return;
                }
            }

            /* Set filename and open archive */

            theLog.print
            (
                "================================\n" \
                "==            BEGIN           ==\n" \
                "================================\n"
            );

            if (skip_creating_new_ar)
            {
                myARs[0].setMediaDir(currentWorkingDirectory);
                ar_name = myARs[0].getMediaDir();
            }
            else
            {
                ar_name = bufor;
                myARs[0] = Archive(currentWorkingDirectory);
            }

            myARs[0].open
            (
                ar_name,
                archive_flags,
                currentGameVersion
            );

            theLog.print
            (
                "================================\n" \
                "==          FINISHED          ==\n" \
                "================================\n"
            );

            if (false == skip_creating_new_ar)
            {
                ar_name = ar_name.getFilename();
            }

            sprintf_s
            (
                bufor,
                256,
                final_msg,
                ar_name.getText()
            );

            MessageBox(GUI::myWindows[GUI::windowID::WINDOW_MAIN], bufor, title, MB_ICONINFORMATION);
        }
        catch (ErrorMessage &e)
        {
            e.display(GUI::myWindows[GUI::windowID::WINDOW_MAIN]);

            theLog.print
            (
                "================================\n" \
                "==            oops!           ==\n" \
                "================================\n"
            );

            myARs[0].close();
        }
    }

    void setGameVersion(int engine_version)
    {
        const char* msg;

        switch (engine_version)
        {
            case GAME_VERSION_KAO2_PL_PC:
            {
                msg = "Nice, you have selected:\n\n" \
                    "\"Kangurek Kao: Runda 2\" [PL]\n\n" \
                    "ar versions: 0x67 (103) — 0x87 (135)";
                break;
            }

            case GAME_VERSION_KAO2_EUR_PC:
            {
                msg = "Nice, you have selected:\n\n" \
                    "\"Kao the Kangaroo: Round 2\" [EUR/USA]\n\n" \
                    "ar versions: 0x67 (103) — 0x89 (137)";
                break;
            }

            case GAME_VERSION_KAO_TW_PC:
            {
                msg = "Nice, you have selected:\n\n" \
                    "\"Kangurek Kao: Tajemnica Wulkanu\"\n\n" \
                    "ar versions: 0x8B (139) — 0x90 (144)";
                break;
            }

            default:
            {
                MessageBox
                (
                    GUI::myWindows[GUI::windowID::WINDOW_MAIN],
                    "Invalid engine version! (THIS SHOULD NEVER HAPPEN)",
                    "Zookie Wizard — error",
                    (MB_ICONERROR | MB_OK)
                );

                return;
            }
        }

        /* Kangurek Kao */

        currentGameVersion = engine_version;

        MessageBox
        (
            GUI::myWindows[GUI::windowID::WINDOW_MAIN],
            msg,
            "Zookie Wizard — info",
            (MB_ICONINFORMATION | MB_OK)
        );
    }

}


////////////////////////////////////////////////////////////////
// Main
////////////////////////////////////////////////////////////////

int main()
{
    return ZookieWizard::Start(GetModuleHandle(NULL));
}
