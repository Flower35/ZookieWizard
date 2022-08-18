#include <ZookieWizard/ZookieWizard.h>
#include <ZookieWizard/WindowsManager.h>

#include <ElephantBase/Archive.h>
#include <ElephantEngine/Log.h>

#include <ElephantEngine/eScene.h>
#include <ElephantEngine/eEnvironment.h>
#include <denis/DenisLevelMap.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // miscellaneous: variables
    ////////////////////////////////////////////////////////////////

    int currentArId = 0;
    Archive myARs[MAX_OPEN_ARCHIVES];

    int currentDenisLevelId = 0;
    DenisLevelMap myDenisLevels[MAX_OPEN_DENISLEVELS];

    OPENFILENAME ofn;

    int currentArchiveVersion = ARCHIVE_VERSION_MAX;
    char mediaDirectory[LARGE_BUFFER_SIZE] = "";
    char denisDirectory[LARGE_BUFFER_SIZE] = "";
    char denisLevelName[LARGE_BUFFER_SIZE] = "";

    bool currentWorkingDirectoryStored = false;
    char currentWorkingDirectory[LARGE_BUFFER_SIZE];

    #define ZOOKIE_WIZARD_SETTINGS_FILENAME "ZookieWizard.ini"
    #define ZOOKIE_WIZARD_SETTINGS_COUNT 8

    const char* ZookieWizardSettingNames[ZOOKIE_WIZARD_SETTINGS_COUNT] =
    {
        "ArchiveVersion", "MediaDir", "DenisDir", "LevelName",
        "CameraMovementSpeed", "CameraRotationSpeed",
        "DrawFlags", "BackgroundColor"
    };

    const bool ZookieWizardSettingIsString[ZOOKIE_WIZARD_SETTINGS_COUNT] =
    {
        false, true, true, true,
        false, false,
        false, false
    };


    ////////////////////////////////////////////////////////////////
    // miscellaneous: Get Current Working Directory (Windows)
    ////////////////////////////////////////////////////////////////
    void getCurrentWorkingDirectory(char* large_buffer)
    {
        if (!currentWorkingDirectoryStored)
        {
            GetCurrentDirectory(LARGE_BUFFER_SIZE, currentWorkingDirectory);

            currentWorkingDirectoryStored = true;
        }

        if (nullptr != large_buffer)
        {
            strcpy_s(large_buffer, LARGE_BUFFER_SIZE, currentWorkingDirectory);
        }
    }


    ////////////////////////////////////////////////////////////////
    // miscellaneous: load or save editor settings
    ////////////////////////////////////////////////////////////////

    void loadEditorSettings()
    {
        char bufor[LARGE_BUFFER_SIZE];
        int32_t a, setting_id, line_number = 1;
        FileOperator file;
        eString keywords[3];
        const char* dummy_text;

        try
        {
            bufor[0] = '\0';
            getCurrentWorkingDirectory(bufor);
            keywords[0] = bufor;
            keywords[0] += "/";
            keywords[0] += ZOOKIE_WIZARD_SETTINGS_FILENAME;

            if (!file.open(keywords[0].getText(), FILE_OPERATOR_MODE_READ))
            {
                return;
            }

            while (!file.endOfFileReached())
            {
                keywords[0] << file;

                a = ArFunctions::propertyString(keywords[0], &(keywords[1]), 2, line_number);

                if (a >= 1)
                {
                    setting_id = (-1);

                    for (a = 0; (setting_id < 0) && (a < ZOOKIE_WIZARD_SETTINGS_COUNT); a++)
                    {
                        if (keywords[1].compareExact(ZookieWizardSettingNames[a], true))
                        {
                            setting_id = a;
                        }
                    }

                    if (setting_id >= 0)
                    {
                        if (ZookieWizardSettingIsString[setting_id])
                        {
                            dummy_text = keywords[2].getText();
                            a = keywords[2].getLength();

                            if ((a > 2) && ('"' == dummy_text[0]) && ('"' == dummy_text[a - 1]))
                            {
                                switch (setting_id)
                                {
                                    case 1: // "MediaDir"
                                    {
                                        setting_id = 0;
                                        break;
                                    }

                                    case 2: // "DenisDir"
                                    {
                                        setting_id = 1;
                                        break;
                                    }

                                    case 3: // "LevelName"
                                    {
                                        setting_id = 2;
                                        break;
                                    }

                                    default:
                                    {
                                        setting_id = (-1);
                                    }
                                }

                                if (setting_id >= 0)
                                {
                                    keywords[2] = keywords[2].getSubstring(1, (-2));

                                    GUI::updateArSettingsText(setting_id, keywords[2].getText());
                                }
                            }
                        }
                        else
                        {
                            switch (setting_id)
                            {
                                case 0: // "ArchiveVersion"
                                {
                                    setMaxArchiveVersion(std::atoi(keywords[2].getText()));
                                    sprintf_s(bufor, LARGE_BUFFER_SIZE, "%i", currentArchiveVersion);
                                    keywords[2] = bufor;

                                    setting_id = 7;
                                    break;
                                }

                                case 4: // "CameraMovementSpeed"
                                {
                                    setting_id = 3;
                                    break;
                                }

                                case 5: // "CameraRotationSpeed"
                                {
                                    setting_id = 4;
                                    break;
                                }

                                case 6: // "DrawFlags"
                                {
                                    setting_id = 5;
                                    break;
                                }

                                case 7: // "BackgroundColor"
                                {
                                    setting_id = 6;
                                    break;
                                }

                                default:
                                {
                                    setting_id = (-1);
                                }
                            }

                            if (setting_id >= 0)
                            {
                                GUI::updateArSettingsText(setting_id, keywords[2].getText());
                            }
                        }
                    }
                }

                line_number++;
            }
        }
        catch (ErrorMessage)
        {
            /* Silent mode */
        }
    }

    void saveEditorSettings()
    {
        char bufor[LARGE_BUFFER_SIZE];
        eString dummy_str[2];
        FileOperator file;
        int32_t setting_id;

        bufor[0] = '\0';
        getCurrentWorkingDirectory(bufor);
        dummy_str[0] = bufor;
        dummy_str[0] += "/";
        dummy_str[0] += ZOOKIE_WIZARD_SETTINGS_FILENAME;

        if (!file.open(dummy_str[0].getText(), 0))
        {
            ErrorMessage
            (
                "Could not open the \"%s\" file to save editor settings while closing the application!",
                ZOOKIE_WIZARD_SETTINGS_FILENAME
            )
            .display();

            return;
        }

        for (setting_id = 0; setting_id < ZOOKIE_WIZARD_SETTINGS_COUNT; setting_id++)
        {
            dummy_str[0] = ZookieWizardSettingNames[setting_id];

            if (ZookieWizardSettingIsString[setting_id])
            {
                switch (setting_id)
                {
                    case 1: // "MediaDir"
                    {
                        dummy_str[1] = eString(mediaDirectory).trimWhitespace();
                        break;
                    }

                    case 2: // "DenisDir"
                    {
                        dummy_str[1] = eString(denisDirectory).trimWhitespace();
                        break;
                    }

                    case 3: // "LevelName"
                    {
                        dummy_str[1] = eString(denisLevelName).trimWhitespace();
                        break;
                    }

                    default:
                    {
                        dummy_str[1] = eString();
                    }
                }

                dummy_str[0] += " = \"";
                dummy_str[0] += dummy_str[1];
                dummy_str[0] += "\"\n";
            }
            else
            {
                switch (setting_id)
                {
                    case 0: // "ArchiveVersion"
                    {
                        sprintf_s(bufor, LARGE_BUFFER_SIZE, "%d", currentArchiveVersion);

                        break;
                    }

                    case 4: // "CameraMovementSpeed"
                    {
                        sprintf_s(bufor, LARGE_BUFFER_SIZE, "%.3f", GUI::testCamera.speed[0]);

                        break;
                    }

                    case 5: // "CameraRotationSpeed"
                    {
                        sprintf_s(bufor, LARGE_BUFFER_SIZE, "%.3f", GUI::testCamera.speed[1]);

                        break;
                    }

                    case 6: // "DrawFlags"
                    {
                        sprintf_s(bufor, LARGE_BUFFER_SIZE, "%lu", GUI::myDrawFlags);

                        break;
                    }

                    case 7: // "BackgroundCOlor"
                    {
                        sprintf_s
                        (
                            bufor, LARGE_BUFFER_SIZE,
                            "%d %d %d",
                            (int)(255 * GUI::backgroundColor[0]),
                            (int)(255 * GUI::backgroundColor[1]),
                            (int)(255 * GUI::backgroundColor[2])
                        );

                        break;
                    }

                    default:
                    {
                        bufor[0] = '\0';
                    }
                }

                dummy_str[0] += " = ";
                dummy_str[0] += bufor;
                dummy_str[0] += "\n";
            }

            file << dummy_str[0];
        }
    }


    ////////////////////////////////////////////////////////////////
    // miscellaneous: Get one of the editor strings
    // (timming and checking if empty)
    // (1 = MediaDir, 2 = DenisDir, 3 = LevelName)
    ////////////////////////////////////////////////////////////////
    const char* getEditorString(int32_t id, bool silent)
    {
        char bufor[LARGE_BUFFER_SIZE];

        bool display_warning = true;
        char* result;
        const char* warning_text;

        switch (id)
        {
            case 1:
            {
                result = mediaDirectory;
                warning_text = "MediaDir";
                break;
            }

            case 2:
            {
                result = denisDirectory;
                warning_text = "DenisDir";
                break;
            }

            case 3:
            {
                result = denisLevelName;
                warning_text = "LevelName";
                break;
            }

            default:
            {
                result = nullptr;
                warning_text = "???";
            }
        }

        if (nullptr != result)
        {
            eString dummy_str(result);
            dummy_str.trimWhitespace();

            if (false == (display_warning = dummy_str.isEmpty()))
            {
                switch (id)
                {
                    case 1: // "MediaDir"
                    case 2: // "DenisDir"
                    {
                        dummy_str.assertPath();
                        break;
                    }
                }
            }

            strcpy_s(result, LARGE_BUFFER_SIZE, display_warning ? "" : dummy_str.getText());
        }

        if ((!silent) && display_warning)
        {
            sprintf_s(bufor, LARGE_BUFFER_SIZE, "WARNING: The editor setting \"%s\" is empty!", warning_text);

            GUI::theWindowsManager.displayMessage(WINDOWS_MANAGER_MESSAGE_WARNING, bufor);
        }

        return result;
    }


    ////////////////////////////////////////////////////////////////
    // miscellaneous: Set current archive version
    // (saving, exporting, reimporting, files and scripts)
    ////////////////////////////////////////////////////////////////
    void setMaxArchiveVersion(int32_t ar_version)
    {
        if (ar_version < ARCHIVE_VERSION_MIN)
        {
            ar_version = ARCHIVE_VERSION_MIN;
        }
        else if (ar_version > ARCHIVE_VERSION_MAX)
        {
            ar_version = ARCHIVE_VERSION_MAX;
        }

        currentArchiveVersion = ar_version;
    }


    ////////////////////////////////////////////////////////////////
    // miscellaneous: Check AR extensions
    ////////////////////////////////////////////////////////////////
    bool checkArFilenameExtensions(const char* name, int32_t length)
    {
        if (length > 3)
        {
            name = name + length - 3;

            if ('.' == name[0])
            {
                if (('a' == name[1]) || ('A' == name[1]))
                {
                    return (('r' == name[2]) || ('R' == name[2]));
                }
                else if (('e' == name[1]) || ('E' == name[1]))
                {
                    return (('b' == name[2]) || ('B' == name[2]) || ('m' == name[2]) || ('M' == name[2]));
                }
            }
        }

        return false;
    }


    ////////////////////////////////////////////////////////////////
    // miscellaneous: Open or Save Kao2 Archive
    ////////////////////////////////////////////////////////////////
    void ArMenuOptions_OpenOrSaveAr(const char* auto_path, int32_t mode)
    {
        int32_t test;
        eString ar_name;
        char bufor[LARGE_BUFFER_SIZE];

        bool skip_creating_new_ar = true;
        uint8_t open_or_save_dialog = 0;
        int32_t archive_flags = 0;
        DWORD ofn_flags = 0;

        const char* ofn_title = nullptr;
        const char* final_msg = nullptr;

        HWND listbox = GUI::theWindowsManager.getSpecificWindow(1, 8);

        switch (mode)
        {
            case AR_MODE_READ:
            {
                archive_flags = (AR_MODE_ABSOLUTE_PATH | AR_MODE_READ);
                ofn_flags = (OFN_FILEMUSTEXIST | OFN_HIDEREADONLY);

                ofn_title = "Opening KAO2 Archive...";
                final_msg = "<\"%s\">\n\nArchive reading completed successfully! :)";

                skip_creating_new_ar = false;
                open_or_save_dialog = 0x01;

                break;
            }

            case AR_MODE_WRITE:
            {
                archive_flags = (AR_MODE_ABSOLUTE_PATH | AR_MODE_WRITE);
                ofn_flags = (OFN_OVERWRITEPROMPT);

                ofn_title = "Saving KAO2 Archive...";
                final_msg = "<\"%s\">\n\nArchive saving completed successfully! :)";

                skip_creating_new_ar = true;
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
            bufor[0] = 0x00;

            ofn.lpstrFile = bufor;
            ofn.nMaxFile = LARGE_BUFFER_SIZE;
            ofn.lpstrTitle = ofn_title;
            ofn.lpstrFilter = "KAO2 Archive files (*.ar;*.em;*.eb)\0*.ar;*.em;*.eb\0All files (*.*)\0*.*\0";
            ofn.Flags = ofn_flags;

            if (nullptr == auto_path)
            {
                if (1 == open_or_save_dialog)
                {
                    test = GetOpenFileName(&ofn);
                }
                else if (2 == open_or_save_dialog)
                {
                    sprintf_s(bufor, LARGE_BUFFER_SIZE, "%s.ar", getEditorString(3, false));

                    test = GetSaveFileName(&ofn);
                }
                else
                {
                    test = 0;
                }
            }
            else
            {
                test = (-1);

                strcpy_s(bufor, LARGE_BUFFER_SIZE, auto_path);
            }

            if (0 == test)
            {
                return;
            }

            theLog.print
            (
                "================================\n" \
                "==       ARCHIVE OPENING      ==\n" \
                "==            BEGIN           ==\n" \
                "================================\n"
            );

            /* Clear archive when loading new file */

            if (false == skip_creating_new_ar)
            {
                myARs[currentArId].close(true);
            }

            myARs[currentArId].setMediaDir(getEditorString(1, false));

            /* Set target filename or leave directory path */

            ar_name = bufor;

            if ((2 == open_or_save_dialog) && !checkArFilenameExtensions(ar_name.getText(), ar_name.getLength()))
            {
                ar_name += ".ar";
            }

            /* Load or save contents */

            myARs[currentArId].open
            (
                ar_name,
                archive_flags,
                currentArchiveVersion
            );

            nodesManager_ClearProxies();

            theLog.print
            (
                "================================\n" \
                "==       ARCHIVE OPENING      ==\n" \
                "==          FINISHED          ==\n" \
                "================================\n"
            );

            if (AR_MODE_READ == mode)
            {
                myARs[currentArId].changeSelectedObject(NODES_LISTBOX_ROOT, nullptr);

                eString dummy_name = ar_name.getFilename(true);

                if (checkArFilenameExtensions(dummy_name.getText(), dummy_name.getLength()))
                {
                    dummy_name = dummy_name.getSubstring(0, (-4));
                }

                GUI::updateArSettingsText(2, dummy_name.getText());
            }

            if (NULL != listbox)
            {
                SendMessage(listbox, LB_DELETESTRING, (WPARAM)currentArId, 0);
                SendMessage(listbox, LB_INSERTSTRING, (WPARAM)currentArId, (LPARAM)myARs[currentArId].getBaseFileName().getText());
                SendMessage(listbox, LB_SETCURSEL, (WPARAM)currentArId, 0);
            }

            if (nullptr == auto_path)
            {
                /* Display message */

                sprintf_s
                (
                    bufor, 256,
                    final_msg,
                    ar_name.getText()
                );

                GUI::theWindowsManager.displayMessage(WINDOWS_MANAGER_MESSAGE_INFO, bufor);
            }
        }
        catch (ErrorMessage &err)
        {
            myARs[currentArId].close(false);

            nodesManager_ClearProxies();

            theLog.print
            (
                "================================\n" \
                "==       ARCHIVE OPENING      ==\n" \
                "==            oops!           ==\n" \
                "================================\n"
            );

            err.display();
        }
    }


    ////////////////////////////////////////////////////////////////
    // miscellaneous: Close Kao2 Archive
    ////////////////////////////////////////////////////////////////
    void ArMenuOptions_CloseAr(bool automatic)
    {
        HWND listbox = GUI::theWindowsManager.getSpecificWindow(1, 8);

        if ((!automatic) && myARs[currentArId].isNotEmpty())
        {
            if (false == GUI::theWindowsManager.askQuestion
                (
                    "Are you sure you want to close the current Archive?\n\n" \
                    "Any unsaved changes will be lost!"
                )
            )
            {
                return;
            }
        }

        /****************/

        myARs[currentArId].close(true);

        myARs[currentArId].changeGlobalScene();
        myARs[currentArId].changeSelectedObject(NODES_LISTBOX_UPDATE_CURRENT, nullptr);

        /****************/

        GUI::updateArSettingsText(2, "");

        /****************/

        if (NULL != listbox)
        {
            SendMessage(listbox, LB_DELETESTRING, (WPARAM)currentArId, 0);
            SendMessage(listbox, LB_INSERTSTRING, (WPARAM)currentArId, (LPARAM)"<< EMPTY >>");
            SendMessage(listbox, LB_SETCURSEL, (WPARAM)currentArId, 0);
        }
    }


    ////////////////////////////////////////////////////////////////
    // miscellaneous: generate empty scene (custom Kao2 levels)
    ////////////////////////////////////////////////////////////////
    void ArMenuOptions_GenerateEmptyScene(bool automatic)
    {
        char bufor[LARGE_BUFFER_SIZE];
        eString compile_strings[2];

        std::time_t current_time;
        std::tm time_info;
        char time_bufor[32];

        eScene* new_scene = nullptr;
        eEnvironment* global_env = nullptr;
        eCollisionMgr* test_collision = nullptr;

        HWND listbox = GUI::theWindowsManager.getSpecificWindow(1, 8);

        /********************************/
        /* Check if the name is not empty */

        compile_strings[1] = eString(denisLevelName).trimWhitespace();

        if (compile_strings[1].isEmpty())
        {
            denisLevelName[0] = '\0';

            GUI::theWindowsManager.displayMessage
            (
                WINDOWS_MANAGER_MESSAGE_WARNING,
                "A valid level name has not been set yet!"
            );

            return;
        }

        if (!automatic)
        {
            if (false == GUI::theWindowsManager.askQuestion
                (
                    "You are about to generate a new, empty KAO2 scene.\n\n" \
                    "This action will close the current Archive and any unsaved changes will be lost!\n\n" \
                    "Do you want to continue?"
                )
            )
            {
                return;
            }
        }

        sprintf_s(denisLevelName, LARGE_BUFFER_SIZE, compile_strings[1].getText());

        if (NULL != listbox)
        {
            SendMessage(listbox, LB_DELETESTRING, (WPARAM)currentArId, 0);
            SendMessage(listbox, LB_INSERTSTRING, (WPARAM)currentArId, (LPARAM)denisLevelName);
            SendMessage(listbox, LB_SETCURSEL, (WPARAM)currentArId, 0);
        }

        theLog.print
        (
            "================================\n" \
            "==   GENERATING EMPTY SCENE   ==\n" \
            "==            BEGIN           ==\n" \
            "================================\n"
        );

        /********************************/
        /* Get current time and date */

        std::time(&current_time);
        localtime_s(&time_info, &current_time);

        std::strftime(time_bufor, 32, "%c", &time_info);

        /********************************/
        /* Create new scene and new environment */

        new_scene = new eScene();
        new_scene->setFlags(0x70071000);
        new_scene->rebuildEmptyAnimState(true);

        global_env = new eEnvironment("global_env");
        global_env->setFlags(0x70000000);

        test_collision = new_scene->getCollisionManager();

        /********************************/
        /* Set scene name and creation details */

        new_scene->setName("$root");

        compile_strings[0] = "Created with ZookieWizard at ";
        compile_strings[0] += time_bufor;
        compile_strings[0] += "\r\n";

        new_scene->setCompileStrings(compile_strings[0], compile_strings[1]);

        /********************************/
        /* Add environment (and update its parent) */

        new_scene->appendChild(global_env);

        /********************************/
        /* Replace current archive */

        myARs[currentArId].setMyParentScene(new_scene);

        myARs[currentArId].changeSelectedObject(NODES_LISTBOX_ROOT, nullptr);

        theLog.print
        (
            "================================\n" \
            "==   GENERATING EMPTY SCENE   ==\n" \
            "==          FINISHED          ==\n" \
            "================================\n"
        );

        if (!automatic)
        {
            sprintf_s
            (
                bufor, LARGE_BUFFER_SIZE,
                "Empty scene for Kao2 created!\n\n" \
                "Now you can save Archive to: \"%s/build/win32/%s.ar\"",
                getEditorString(1, true),
                denisLevelName
            );

            GUI::theWindowsManager.displayMessage(WINDOWS_MANAGER_MESSAGE_INFO, bufor);
        }
    }


    ////////////////////////////////////////////////////////////////
    // miscellaneous: Export Scripts from Kao2 Archive
    ////////////////////////////////////////////////////////////////
    void ArMenuOptions_ExportScripts()
    {
        char bufor[LARGE_BUFFER_SIZE];

        theLog.print
        (
            "================================\n" \
            "==  ARCHIVE SCRIPTS EXPORTING ==\n" \
            "==            BEGIN           ==\n" \
            "================================\n"
        );

        try
        {
            myARs[currentArId].setMediaDir(getEditorString(1, false));

            myARs[currentArId].exportScripts();

            theLog.print
            (
                "================================\n" \
                "==  ARCHIVE SCRIPTS EXPORTING ==\n" \
                "==          FINISHED          ==\n" \
                "================================\n"
            );

            sprintf_s
            (
                bufor, 256,
                "Done exporting scripts from current AR to \"%s\".",
                myARs[currentArId].getMediaDir().getText()
            );

            GUI::theWindowsManager.displayMessage(WINDOWS_MANAGER_MESSAGE_INFO, bufor);
        }
        catch (ErrorMessage &err)
        {
            theLog.print
            (
                "================================\n" \
                "==  ARCHIVE SCRIPTS EXPORTING ==\n" \
                "==            oops!           ==\n" \
                "================================\n"
            );

            err.display();
        }
    }


    ////////////////////////////////////////////////////////////////
    // miscellaneous: Export Proxies from Kao2 Archive
    ////////////////////////////////////////////////////////////////
    void ArMenuOptions_ExportProxies()
    {
        char bufor[LARGE_BUFFER_SIZE];

        theLog.print
        (
            "================================\n" \
            "==  ARCHIVE PROXIES EXPORTING ==\n" \
            "==            BEGIN           ==\n" \
            "================================\n"
        );

        try
        {
            myARs[currentArId].setMediaDir(getEditorString(1, false));

            myARs[currentArId].exportProxies(currentArchiveVersion);

            theLog.print
            (
                "================================\n" \
                "==  ARCHIVE PROXIES EXPORTING ==\n" \
                "==          FINISHED          ==\n" \
                "================================\n"
            );

            sprintf_s
            (
                bufor, 256,
                "Done exporting proxies from current AR to \"%s\".",
                myARs[currentArId].getMediaDir().getText()
            );

            GUI::theWindowsManager.displayMessage(WINDOWS_MANAGER_MESSAGE_INFO, bufor);
        }
        catch (ErrorMessage &err)
        {
            theLog.print
            (
                "================================\n" \
                "==  ARCHIVE PROXIES EXPORTING ==\n" \
                "==            oops!           ==\n" \
                "================================\n"
            );

            err.display();
        }
    }


    ////////////////////////////////////////////////////////////////
    // miscellaneous: Reload Proxies in Kao2 Archive
    ////////////////////////////////////////////////////////////////
    void ArMenuOptions_ReloadProxies()
    {
        char bufor[LARGE_BUFFER_SIZE];

        theLog.print
        (
            "================================\n" \
            "==  ARCHIVE PROXIES RELOADING ==\n" \
            "==            BEGIN           ==\n" \
            "================================\n"
        );

        try
        {
            myARs[currentArId].setMediaDir(getEditorString(1, false));

            myARs[currentArId].reloadProxies(currentArchiveVersion);

            theLog.print
            (
                "================================\n" \
                "==  ARCHIVE PROXIES RELOADING ==\n" \
                "==          FINISHED          ==\n" \
                "================================\n"
            );

            sprintf_s
            (
                bufor, 256,
                "Done reloading proxies from \"%s\".",
                myARs[currentArId].getMediaDir().getText()
            );

            GUI::theWindowsManager.displayMessage(WINDOWS_MANAGER_MESSAGE_INFO, bufor);
        }
        catch (ErrorMessage &err)
        {
            theLog.print
            (
                "================================\n" \
                "==  ARCHIVE PROXIES RELOADING ==\n" \
                "==            oops!           ==\n" \
                "================================\n"
            );

            err.display();
        }
    }


    ////////////////////////////////////////////////////////////////
    // miscellaneous: Bulk Archive Converter
    ////////////////////////////////////////////////////////////////
    void ArMenuOptions_BulkArchiveConverter()
    {
        int32_t i, ar_version;
        char bufor[LARGE_BUFFER_SIZE];

        eString input_dir;
        eString keywords[3];
        Archive dummy_ar;

        FileOperator list;

        try
        {
            /* Show instruction */

            GUI::theWindowsManager.displayMessage
            (
                WINDOWS_MANAGER_MESSAGE_INFO,
                "Select a text file structured in a following way:\n\n" \
                "1st line: [input media directory]\n" \
                "2nd line: [target archive version] [output media directory]\n" \
                "next lines: file names (in reference to media directories)\n" \
                "\n--------------------------------\n" \
                "    EXAMPLE:\n\n" \
                "[1] C:\\Program Files (x86)\\Kangurek Kao - Tajemnica Wulkanu\\media\n" \
                "[2] 135 C:\\Program Files (x86)\\Kangurek Kao - Runda 2\\media\n" \
                "[3] build/pc/kao.ar\n" \
                "[4] build/pc/check_point.ar\n" \
                "[5] particle/kao_die_killwater.ar\n"
            );

            /* Try to open a text file */

            bufor[0] = 0x00;

            ofn.lpstrFile = bufor;
            ofn.nMaxFile = LARGE_BUFFER_SIZE;
            ofn.lpstrTitle = "Opening a list file...";
            ofn.lpstrFilter = "Text files (*.txt;*.def;*.log)\0*.txt;*.def;*.log\0All files (*.*)\0*.*\0";
            ofn.Flags = (OFN_FILEMUSTEXIST | OFN_HIDEREADONLY);

            if (0 == GetOpenFileName(&ofn))
            {
                return;
            }

            theLog.print
            (
                "================================\n" \
                "==   BULK ARCHIVE CONVERTER   ==\n" \
                "==            BEGIN           ==\n" \
                "================================\n"
            );

            if (!list.open(bufor, FILE_OPERATOR_MODE_READ))
            {
                throw ErrorMessage("Could not open file: \"%s\".", bufor);
            }

            /* Read first two lines (and validate) */

            input_dir << list;
            input_dir = ArFunctions::removeComment(input_dir, true);

            keywords[2] << list;
            keywords[2] = ArFunctions::removeComment(keywords[2], true);

            if (ArFunctions::splitString(keywords[2], keywords, 2) < 2)
            {
                throw ErrorMessage
                (
                    "Error while parsing the beginning of the list:\n" \
                    "Expected the target archive version and output directory in the 2nd line!"
                );
            }

            ar_version = std::atoi(keywords[0].getText());

            if ((ar_version < ARCHIVE_VERSION_MIN) || (ar_version > ARCHIVE_VERSION_MAX))
            {
                throw ErrorMessage
                (
                    "Error while parsing the beginning of the list:\n" \
                    "Incorrect target archive vesion %i!\n" \
                    "(min.: %i, max.: %i)",
                    ar_version, ARCHIVE_VERSION_MIN, ARCHIVE_VERSION_MAX
                );
            }

            /* Begin the conversion... */

            i = 0;

            while (!list.endOfFileReached())
            {
                keywords[0] << list;
                keywords[0] = ArFunctions::removeComment(keywords[0], true).trimWhitespace();

                /* Minimal length of three characters [*.ar] */

                if (keywords[0].getLength() > 3)
                {
                    /* Source archive */

                    dummy_ar.setMediaDir(input_dir);

                    dummy_ar.open
                    (
                        dummy_ar.getMediaDir() + keywords[0],
                        (AR_MODE_SKIP_PROXIES | AR_MODE_READ),
                        0
                    );

                    dummy_ar.close(false);

                    /* Destination archive */

                    dummy_ar.setMediaDir(keywords[1]);

                    dummy_ar.open
                    (
                        dummy_ar.getMediaDir() + keywords[0],
                        (AR_MODE_WRITE),
                        ar_version
                    );

                    dummy_ar.close(true);

                    i++;
                }
            }

            list.close();

            theLog.print
            (
                "================================\n" \
                "==   BULK ARCHIVE CONVERTER   ==\n" \
                "==          FINISHED          ==\n" \
                "================================\n"
            );

            sprintf_s
            (
                bufor, LARGE_BUFFER_SIZE,
                "Successfully converted %d KAO2 archives!",
                i
            );

            GUI::theWindowsManager.displayMessage(WINDOWS_MANAGER_MESSAGE_INFO, bufor);
        }
        catch (ErrorMessage &err)
        {
            theLog.print
            (
                "================================\n" \
                "==   BULK ARCHIVE CONVERTER   ==\n" \
                "==            oops!           ==\n" \
                "================================\n"
            );

            err.display();
        }
    }


    ////////////////////////////////////////////////////////////////
    // miscellaneous: Dump Ar Tree
    ////////////////////////////////////////////////////////////////
    void ArMenuOptions_WriteTreeToJsonFile()
    {
        char bufor[LARGE_BUFFER_SIZE];
        eString filename;
        bool empty_name;

        try
        {
            filename = eString(denisLevelName).trimWhitespace();
            empty_name = filename.isEmpty();
            sprintf_s(denisLevelName, LARGE_BUFFER_SIZE, empty_name ? "" : filename.getText());

            if (!empty_name)
            {
                sprintf_s(bufor, LARGE_BUFFER_SIZE, "%s.json", denisLevelName);
            }
            else
            {
                sprintf_s(bufor, LARGE_BUFFER_SIZE, "ar.json");
            }

            ofn.lpstrFile = bufor;
            ofn.nMaxFile = LARGE_BUFFER_SIZE;
            ofn.lpstrTitle = "Select your destination...";
            ofn.lpstrFilter = "JSON files (*.json)\0*.json\0All files (*.*)\0*.*\0";
            ofn.Flags = OFN_OVERWRITEPROMPT;

            if (0 == GetSaveFileName(&ofn))
            {
                return;
            }

            filename = bufor;

            if ((1 == ofn.nFilterIndex) && !filename.hasExtension("json"))
            {
                filename += ".json";
            }

            theLog.print
            (
                "================================\n" \
                "==       JSON EXPORTING       ==\n" \
                "==            BEGIN           ==\n" \
                "================================\n"
            );

            myARs[currentArId].writeTreeToJsonFile(filename.getText());

            theLog.print
            (
                "================================\n" \
                "==       JSON EXPORTING       ==\n" \
                "==          FINISHED          ==\n" \
                "================================\n"
            );

            sprintf_s
            (
                bufor, LARGE_BUFFER_SIZE,
                "<\"%s\">\n\nJSON document exported successfully! :)",
                filename.getText()
            );

            GUI::theWindowsManager.displayMessage(WINDOWS_MANAGER_MESSAGE_INFO, bufor);
        }
        catch (ErrorMessage &e)
        {
            e.display();
        }
    }


    ////////////////////////////////////////////////////////////////
    // miscellaneous: Export Kao2 Archive to COLLADA "*.dae" format
    ////////////////////////////////////////////////////////////////
    void ArMenuOptions_ExportArToCollada()
    {
        eString filename;
        char bufor[LARGE_BUFFER_SIZE];

        try
        {
            bufor[0] = 0x00;

            ofn.lpstrFile = bufor;
            ofn.nMaxFile = LARGE_BUFFER_SIZE;
            ofn.lpstrTitle = "Saving COLADA document...";
            ofn.lpstrFilter = "COLLADA document (*.dae)\0*.dae\0All files (*.*)\0*.*\0";
            ofn.Flags = (OFN_OVERWRITEPROMPT);

            if (0 == GetSaveFileName(&ofn))
            {
                return;
            }

            /* Set filename and save XML document */

            filename = bufor;

            if ((1 == ofn.nFilterIndex) && !filename.hasExtension("dae"))
            {
                filename += ".dae";
            }

            theLog.print
            (
                "================================\n" \
                "==    COLLADA DAE EXPORTING   ==\n" \
                "==            BEGIN           ==\n" \
                "================================\n"
            );

            myARs[currentArId].writeTreeToXmlFile(filename);

            theLog.print
            (
                "================================\n" \
                "==    COLLADA DAE EXPORTING   ==\n" \
                "==          FINISHED          ==\n" \
                "================================\n"
            );

            sprintf_s
            (
                bufor, LARGE_BUFFER_SIZE,
                "<\"%s\">\n\nCOLLADA document exported successfully! :)",
                filename.getText()
            );

            GUI::theWindowsManager.displayMessage(WINDOWS_MANAGER_MESSAGE_INFO, bufor);
        }
        catch (ErrorMessage &e)
        {
            theLog.print
            (
                "================================\n" \
                "==    COLLADA DAE EXPORTING   ==\n" \
                "==            oops!           ==\n" \
                "================================\n"
            );

            e.display();
        }
    }


    ////////////////////////////////////////////////////////////////
    // miscellaneous: Export Kao2 Mesh to WAVEFRONT "*.obj" format
    ////////////////////////////////////////////////////////////////
    void ArMenuOptions_ExportTrimeshToObj()
    {
        eString filename;
        char bufor[LARGE_BUFFER_SIZE];

        try
        {
            bufor[0] = 0x00;

            ofn.lpstrFile = bufor;
            ofn.nMaxFile = LARGE_BUFFER_SIZE;
            ofn.lpstrTitle = "Saving OBJ document...";
            ofn.lpstrFilter = "Wavefront OBJ document (*.obj)\0*.obj\0All files (*.*)\0*.*\0";
            ofn.Flags = (OFN_OVERWRITEPROMPT);

            if (0 == GetSaveFileName(&ofn))
            {
                return;
            }

            /* Set filename and save OBJ document */

            filename = bufor;

            if ((1 == ofn.nFilterIndex) && !filename.hasExtension("obj"))
            {
                filename += ".obj";
            }

            theLog.print
            (
                "================================\n" \
                "==   WAVEFRONT OBJ EXPORTING  ==\n" \
                "==            BEGIN           ==\n" \
                "================================\n"
            );

            myARs[currentArId].writeSelectedObjectToObjFile(filename);

            theLog.print
            (
                "================================\n" \
                "==   WAVEFRONT OBJ EXPORTING  ==\n" \
                "==          FINISHED          ==\n" \
                "================================\n"
            );

            sprintf_s
            (
                bufor, LARGE_BUFFER_SIZE,
                "<\"%s\">\n\nOBJ document exported successfully! :)",
                filename.getText()
            );

            GUI::theWindowsManager.displayMessage(WINDOWS_MANAGER_MESSAGE_INFO, bufor);
        }
        catch (ErrorMessage &e)
        {
            theLog.print
            (
                "================================\n" \
                "==   WAVEFRONT OBJ EXPORTING  ==\n" \
                "==            oops!           ==\n" \
                "================================\n"
            );

            e.display();
        }
    }


    ////////////////////////////////////////////////////////////////
    // miscellaneous: Import Kao2 Mesh from WAVEFRONT "*.obj" format
    ////////////////////////////////////////////////////////////////
    void ArMenuOptions_ImportTrimeshFromObj()
    {
        eString filename;
        char bufor[LARGE_BUFFER_SIZE];

        try
        {
            bufor[0] = 0x00;

            ofn.lpstrFile = bufor;
            ofn.nMaxFile = LARGE_BUFFER_SIZE;
            ofn.lpstrTitle = "Opening OBJ document...";
            ofn.lpstrFilter = "Wavefront OBJ document (*.obj)\0*.obj\0All files (*.*)\0*.*\0";
            ofn.Flags = (OFN_FILEMUSTEXIST | OFN_HIDEREADONLY);

            if (0 == GetOpenFileName(&ofn))
            {
                return;
            }

            /* Set filename and read OBJ document */

            filename = bufor;

            theLog.print
            (
                "================================\n" \
                "==   WAVEFRONT OBJ IMPORTING  ==\n" \
                "==            BEGIN           ==\n" \
                "================================\n"
            );

            myARs[currentArId].appendToSelectedObjectFromObjFile(filename);

            theLog.print
            (
                "================================\n" \
                "==   WAVEFRONT OBJ IMPORTING  ==\n" \
                "==          FINISHED          ==\n" \
                "================================\n"
            );

            sprintf_s
            (
                bufor, LARGE_BUFFER_SIZE,
                "<\"%s\">\n\nOBJ document imported successfully! :)\n\n" \
                "Remember to optimize your materials after you adjust them!",
                filename.getText()
            );

            GUI::theWindowsManager.displayMessage(WINDOWS_MANAGER_MESSAGE_INFO, bufor);
        }
        catch (ErrorMessage &e)
        {
            theLog.print
            (
                "================================\n" \
                "==   WAVEFRONT OBJ IMPORTING  ==\n" \
                "==            oops!           ==\n" \
                "================================\n"
            );

            e.display();
        }
    }


    ////////////////////////////////////////////////////////////////
    // miscellaneous: Change Kao2 Nodes with a "*.txt" file
    ////////////////////////////////////////////////////////////////
    void ArMenuOptions_ChangeNodesWithTxt()
    {
        int32_t result;
        char bufor[2][LARGE_BUFFER_SIZE];

        bufor[1][0] = 0x00;

        ofn.lpstrFile = bufor[1];
        ofn.nMaxFile = LARGE_BUFFER_SIZE;
        ofn.lpstrTitle = "Opening a text file...";
        ofn.lpstrFilter = "Text files (*.txt;*.def;*.log)\0*.txt;*.def;*.log\0All files (*.*)\0*.*\0";
        ofn.Flags = (OFN_FILEMUSTEXIST | OFN_HIDEREADONLY);

        if (0 == GetOpenFileName(&ofn))
        {
            return;
        }

        theLog.print
        (
            "================================\n" \
            "==   CHANGE NODES WITH TXT    ==\n" \
            "==            BEGIN           ==\n" \
            "================================\n"
        );

        result = myARs[currentArId].changeNodesWithTxtFile(bufor[1]);

        theLog.print
        (
            "================================\n" \
            "==   CHANGE NODES WITH TXT    ==\n" \
            "==          FINISHED          ==\n" \
            "================================\n"
        );

        if (result >= 0)
        {
            sprintf_s
            (
                bufor[0], LARGE_BUFFER_SIZE,
                "<\"%s\">\n\n%d messages parsed by the \"ArCustomParser\" :)",
                bufor[1],
                result
            );

            GUI::theWindowsManager.displayMessage(WINDOWS_MANAGER_MESSAGE_INFO, bufor[0]);
        }
    }


    ////////////////////////////////////////////////////////////////
    // miscellaneous: Open or Save Denis Level Map
    ////////////////////////////////////////////////////////////////
    void DenisMenuOptions_OpenDenisLevel()
    {
        char bufor[LARGE_BUFFER_SIZE];

        DenisFileOperator file(getEditorString(2, false));

        try
        {
            theLog.print
            (
                "================================\n" \
                "==      DENIS LVL OPENING     ==\n" \
                "==            BEGIN           ==\n" \
                "================================\n"
            );

            myDenisLevels[0].destroy();
            myDenisLevels[0] = DenisLevelMap(getEditorString(3, false));

            myDenisLevels[0].openAndSerialize(file);

            theLog.print
            (
                "================================\n" \
                "==      DENIS LVL OPENING     ==\n" \
                "==          FINISHED          ==\n" \
                "================================\n"
            );

            sprintf_s
            (
                bufor, LARGE_BUFFER_SIZE,
                "<\"%s\">\n\nDenis Level Map loaded successfully! :)",
                myDenisLevels[0].getName().getText()
            );

            GUI::theWindowsManager.displayMessage(WINDOWS_MANAGER_MESSAGE_INFO, bufor);
        }
        catch (ErrorMessage &e)
        {
            myDenisLevels[0].destroy();

            theLog.print
            (
                "================================\n" \
                "==      DENIS LVL OPENING     ==\n" \
                "==            oops!           ==\n" \
                "================================\n"
            );

            e.display();
        }
    }


    ////////////////////////////////////////////////////////////////
    // miscellaneous: Convert loaded Denis Level to Kao2 Archive
    ////////////////////////////////////////////////////////////////
    void DenisMenuOptions_ConvertDenisLevel()
    {
        char bufor[LARGE_BUFFER_SIZE];

        DenisFileOperator file(getEditorString(2, false));

        eScene* test_scene;

        try
        {
            theLog.print
            (
                "================================\n" \
                "==    DENIS LVL CONVERTING    ==\n" \
                "==            BEGIN           ==\n" \
                "================================\n"
            );

            test_scene = myDenisLevels[0].convertToKao2(file);

            myARs[currentArId].setMyParentScene(test_scene);

            myARs[currentArId].changeSelectedObject(NODES_LISTBOX_ROOT, nullptr);

            theLog.print
            (
                "================================\n" \
                "==    DENIS LVL CONVERTING    ==\n" \
                "==          FINISHED          ==\n" \
                "================================\n"
            );

            sprintf_s
            (
                bufor, LARGE_BUFFER_SIZE,
                    "Denis Map has been converted to Kao2 engine!\n\n" \
                    "Now you can save Archive to: \"%s/build/win32/%s.ar\"",
                getEditorString(1, true),
                myDenisLevels[0].getName().getText()
            );

            GUI::theWindowsManager.displayMessage(WINDOWS_MANAGER_MESSAGE_INFO, bufor);
        }
        catch (ErrorMessage &e)
        {
            e.display();

            theLog.print
            (
                "================================\n" \
                "==    DENIS LVL CONVERTING    ==\n" \
                "==            oops!           ==\n" \
                "================================\n"
            );
        }
    }

}
