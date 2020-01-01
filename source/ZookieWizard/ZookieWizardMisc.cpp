#include <ZookieWizard/ZookieWizard.h>

#include <kao2ar/Archive.h>
#include <kao2engine/Log.h>

#include <kao2engine/eScene.h>
#include <denis/DenisLevelMap.h>

namespace ZookieWizard
{
    
    ////////////////////////////////////////////////////////////////
    // miscellaneous: variables
    ////////////////////////////////////////////////////////////////

    int archivesInUse = 0;
    Archive myARs[MAX_OPEN_ARCHIVES];

    int denisLevelsInUse = 0;
    DenisLevelMap myDenisLevels[MAX_OPEN_DENISLEVELS];

    OPENFILENAME ofn;

    int currentGameVersion = (-1);
    char currentWorkingDirectory[256] = "";
    char denisDirectory[256] = "";
    char denisLevelName[256] = "";


    ////////////////////////////////////////////////////////////////
    // miscellaneous: Open or Save Kao2 Archive
    ////////////////////////////////////////////////////////////////

    void openOrSaveAr(int32_t mode)
    {
        int32_t result;
        eString ar_name;
        eScene* test_scene = nullptr;
        char bufor[256];

        bool skip_creating_new_ar = true;
        bool skip_dialog = true;
        uint8_t open_or_save_dialog = 0;
        int32_t archive_flags = 0;
        DWORD ofn_flags = 0;

        const char* title = "ZookieWizard — info";
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

                skip_creating_new_ar = false;
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

                myARs[0].copySceneFromMe(&test_scene);
                myARs[0] = Archive(currentWorkingDirectory);
                myARs[0].setMyParentScene(test_scene);

                test_scene->decRef();
                test_scene = nullptr;
            }

            myARs[0].open
            (
                ar_name,
                archive_flags,
                currentGameVersion
            );

            myARs[0].close(false);

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

            MessageBox(GUI::myWindowsGroupMain[0], bufor, MESSAGE_TITLE_INFO, MB_ICONINFORMATION);
        }
        catch (ErrorMessage &e)
        {
            myARs[0].close(true);

            theLog.print
            (
                "================================\n" \
                "==            oops!           ==\n" \
                "================================\n"
            );

            e.display();
        }
    }


    ////////////////////////////////////////////////////////////////
    // miscellaneous: Set Kao2 game engine version
    ////////////////////////////////////////////////////////////////

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
                    GUI::myWindowsGroupMain[0],
                    "Invalid engine version! (THIS SHOULD NEVER HAPPEN)",
                    MESSAGE_TITLE_ERROR,
                    (MB_ICONERROR | MB_OK)
                );

                return;
            }
        }

        /* Kangurek Kao */

        currentGameVersion = engine_version;

        MessageBox
        (
            GUI::myWindowsGroupMain[0],
            msg,
            MESSAGE_TITLE_INFO,
            (MB_ICONINFORMATION | MB_OK)
        );
    }


    ////////////////////////////////////////////////////////////////
    // miscellaneous: Write Ar structure
    ////////////////////////////////////////////////////////////////

    void writeArStructureToTextFile()
    {
        try
        {
            myARs[0].writeStructureToTextFile();

            MessageBox(GUI::myWindowsGroupMain[0], "Text file saved.", MESSAGE_TITLE_INFO, MB_ICONINFORMATION);
        }
        catch (ErrorMessage &e)
        {
            e.display();
        }
    }


    ////////////////////////////////////////////////////////////////
    // miscellaneous: Open or Save Denis Level Map
    ////////////////////////////////////////////////////////////////

    void openDenisLevel()
    {
        char bufor[256];

        DenisFileOperator file(denisDirectory);
        
        try
        {
            theLog.print
            (
                "================================\n" \
                "==            BEGIN           ==\n" \
                "================================\n"
            );

            myDenisLevels[0].destroy();
            myDenisLevels[0] = DenisLevelMap(denisLevelName);

            myDenisLevels[0].openAndSerialize(file);

            theLog.print
            (
                "================================\n" \
                "==          FINISHED          ==\n" \
                "================================\n"
            );

            sprintf_s
            (
                bufor,
                256,
                "<\"%s\">\n\nDenis Level Map loaded successfully! :)",
                myDenisLevels[0].getName().getText()
            );

            MessageBox(GUI::myWindowsGroupMain[0], bufor, MESSAGE_TITLE_INFO, MB_ICONINFORMATION);
        }
        catch (ErrorMessage &e)
        {
            myDenisLevels[0].destroy();

            theLog.print
            (
                "================================\n" \
                "==            oops!           ==\n" \
                "================================\n"
            );

            e.display();
        }
    }


    ////////////////////////////////////////////////////////////////
    // miscellaneous: Convert loaded Denis Level to Kao2 Archive
    ////////////////////////////////////////////////////////////////

    void convertDenisLevel()
    {
        char bufor[256];

        DenisFileOperator file(denisDirectory);

        eScene* test_scene;

        try
        {
            theLog.print
            (
                "================================\n" \
                "==            BEGIN           ==\n" \
                "================================\n"
            );

            test_scene = myDenisLevels[0].convertToKao2(file);

            myARs[0].setMyParentScene(test_scene);

            sprintf_s
            (
                bufor,
                256,
                    "Denis Map has been converted to Kao2 engine! \n\n" \
                    "Now you can save Archive to: \"%s/build/win32/%s.ar\"",
                currentWorkingDirectory,
                myDenisLevels[0].getName().getText()
            );
        
            MessageBox(GUI::myWindowsGroupMain[0], bufor, MESSAGE_TITLE_INFO, MB_ICONINFORMATION);
        }
        catch (ErrorMessage &e)
        {
            e.display();

            theLog.print
            (
                "================================\n" \
                "==            oops!           ==\n" \
                "================================\n"
            );
        }
    }

}
