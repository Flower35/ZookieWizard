#include <ZookieWizard/ZookieWizard.h>
#include <ZookieWizard/WindowsManager.h>

#include <kao2ar/Archive.h>
#include <kao2engine/Log.h>

#include <kao2engine/eScene.h>
#include <kao2engine/eEnvironment.h>
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
        char bufor[256];

        bool skip_creating_new_ar = true;
        bool skip_dialog = true;
        uint8_t open_or_save_dialog = 0;
        int32_t archive_flags = 0;
        DWORD ofn_flags = 0;

        const char* ofn_title = nullptr;
        const char* final_msg = nullptr;

        switch (mode)
        {
            case AR_MODE_READ:
            {
                archive_flags = (AR_MODE_ABSOLUTE_PATH | AR_MODE_READ);
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
                archive_flags = (AR_MODE_ABSOLUTE_PATH | AR_MODE_WRITE);
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

            theLog.print
            (
                "================================\n" \
                "==       ARCHIVE OPENING      ==\n" \
                "==            BEGIN           ==\n" \
                "================================\n"
            );

            /* Clear archive when loading new file */

            if (skip_creating_new_ar)
            {
                myARs[0].setMediaDir(currentWorkingDirectory);
            }
            else
            {
                myARs[0] = Archive(currentWorkingDirectory);
            }

            /* Set target filename or leave directory path */

            if (skip_dialog)
            {
                ar_name = myARs[0].getMediaDir();
            }
            else
            {
                ar_name = bufor;

                if ((2 == open_or_save_dialog) && (false == ar_name.hasExtension("ar")))
                {
                    ar_name += ".ar";
                }
            }

            /* Load or save contents */

            myARs[0].open
            (
                ar_name,
                archive_flags,
                currentGameVersion,
                false,
                0
            );

            myARs[0].close(false);

            theLog.print
            (
                "================================\n" \
                "==       ARCHIVE OPENING      ==\n" \
                "==          FINISHED          ==\n" \
                "================================\n"
            );

            if (AR_MODE_READ == mode)
            {
                myARs[0].changeSelectedObject(NODES_LISTBOX_ROOT, nullptr);
            }

            /* Display message */

            if (false == skip_dialog)
            {
                ar_name = ar_name.getFilename();
            }

            sprintf_s
            (
                bufor, 256,
                final_msg,
                ar_name.getText()
            );

            GUI::theWindowsManager.displayMessage(WINDOWS_MANAGER_MESSAGE_INFO, bufor);
        }
        catch (ErrorMessage &e)
        {
            myARs[0].close(false);

            theLog.print
            (
                "================================\n" \
                "==       ARCHIVE OPENING      ==\n" \
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
                GUI::theWindowsManager.displayMessage
                (
                    WINDOWS_MANAGER_MESSAGE_ERROR,
                    "Invalid engine version! (THIS SHOULD NEVER HAPPEN)"
                );

                return;
            }
        }

        /* Kangurek Kao */

        currentGameVersion = engine_version;

        GUI::theWindowsManager.displayMessage
        (
            WINDOWS_MANAGER_MESSAGE_INFO,
            msg
        );
    }


    ////////////////////////////////////////////////////////////////
    // miscellaneous: Write Ar structure
    ////////////////////////////////////////////////////////////////

    void writeArStructureToTextFile()
    {
        char bufor[256];

        try
        {
            sprintf_s(bufor, 256, "ar.log");

            ofn.lpstrFile = bufor;
            ofn.nMaxFile = 256;
            ofn.lpstrTitle = "Select your destination...";
            ofn.lpstrFilter = "Text files (*.log)\0*.log\0";
            ofn.Flags = OFN_OVERWRITEPROMPT;

            if (0 == GetOpenFileName(&ofn))
            {
                return;
            }

            myARs[0].writeStructureToTextFile(bufor);

            GUI::theWindowsManager.displayMessage(WINDOWS_MANAGER_MESSAGE_INFO, "Text file saved.");
        }
        catch (ErrorMessage &e)
        {
            e.display();
        }
    }


    ////////////////////////////////////////////////////////////////
    // miscellaneous: Bulk Archive Converter
    ////////////////////////////////////////////////////////////////

    void bulkArchiveConverter()
    {
        int32_t i, j, k;
        char bufor[256];

        int params[2][2];

        eString media_dirs[2];
        eString keywords[4];
        Archive dummy_ar;

        FileOperator list;

        try
        {
            /* Show instruction */

            GUI::theWindowsManager.displayMessage
            (
                WINDOWS_MANAGER_MESSAGE_INFO,
                "Select a text file structured in a following way:\n\n" \
                "lines 1 & 2: [game version] [archive version] [media directory]\n" \
                "next lines: file names (in reference to media directories)\n" \
                "\n--------------------------------\n" \
                "    EXAMPLE:\n\n" \
                "[1] 3 144 C:\\Program Files (x86)\\Kangurek Kao - Tajemnica Wulkanu\\media\n" \
                "[2] 1 135 C:\\Program Files (x86)\\Kangurek Kao - Runda 2\\media\n" \
                "[3] build/pc/kao.ar\n" \
                "[4] build/pc/check_point.ar\n" \
                "[5] particle/kao_die_killwater.ar\n"
            );

            /* Try to open a text file */

            bufor[0] = 0x00;

            ofn.lpstrFile = bufor;
            ofn.nMaxFile = 256;
            ofn.lpstrTitle = "Opening a list file..";
            ofn.lpstrFilter = "Text files (*.txt)\0*.txt\0";
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

            for (i = 0; i < 2; i++)
            {
                keywords[3] << list;

                ArFunctions::splitString(keywords[3], keywords, 3);

                /* Engine number and Archive version */

                params[i][0] = std::atoi(keywords[0].getText());

                switch (params[i][0])
                {
                    case GAME_VERSION_KAO2_PL_PC:
                    case GAME_VERSION_KAO2_EUR_PC:
                    case GAME_VERSION_KAO_TW_PC:
                    {
                        break;
                    }

                    default:
                    {
                        throw ErrorMessage
                        (
                            "Error while parsing the beginning of the list:\n" \
                            "Incorrect game version numbers!"
                        );
                    }
                }

                params[i][1] = std::atoi(keywords[1].getText());

                k = j = 0;

                switch (params[i][0])
                {
                    case GAME_VERSION_KAO2_PL_PC:
                    {
                        j = 0x67;
                        k = 0x87;
                        break;
                    }

                    case GAME_VERSION_KAO2_EUR_PC:
                    {
                        j = 0x67;
                        k = 0x89;
                        break;
                    }

                    case GAME_VERSION_KAO_TW_PC:
                    {
                        j = 0x8B;
                        k = 0x90;
                        break;
                    }
                }

                if ((params[i][1] < j) || (params[i][1] > k))
                {
                    throw ErrorMessage
                    (
                        "Error while parsing the beginning of the list:\n" \
                        "Incorrect archive version for engine #%d!",
                        params[i][0]
                    );
                }

                media_dirs[i] = keywords[2];
            }

            /* Begin the conversion... */

            i = 0;

            while (!list.endOfFileReached())
            {
                keywords[0] << list;

                /* "*.ar" */

                if (keywords[0].getLength() > 3)
                {
                    /* Source archive */

                    dummy_ar.setMediaDir(media_dirs[0]);

                    dummy_ar.open
                    (
                        keywords[0],
                        (AR_MODE_ABSOLUTE_PATH | AR_MODE_XREF_PATH | AR_MODE_READ),
                        params[0][0],
                        false,
                        0
                    );

                    dummy_ar.close(false);

                    /* Destination archive */

                    dummy_ar.setMediaDir(media_dirs[1]);

                    dummy_ar.open
                    (
                        keywords[0],
                        (AR_MODE_ABSOLUTE_PATH | AR_MODE_XREF_PATH | AR_MODE_WRITE),
                        params[1][0],
                        false,
                        params[1][1]
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
                bufor, 256,
                "Successfully converted %d KAO2 archives!",
                i
            );

            GUI::theWindowsManager.displayMessage(WINDOWS_MANAGER_MESSAGE_INFO, bufor);
        }
        catch (ErrorMessage &e)
        {
            theLog.print
            (
                "================================\n" \
                "==   BULK ARCHIVE CONVERTER   ==\n" \
                "==            oops!           ==\n" \
                "================================\n"
            );

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
                "==      DENIS LVL OPENING     ==\n" \
                "==            BEGIN           ==\n" \
                "================================\n"
            );

            myDenisLevels[0].destroy();
            myDenisLevels[0] = DenisLevelMap(denisLevelName);

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
                bufor, 256,
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
                "==    DENIS LVL CONVERTING    ==\n" \
                "==            BEGIN           ==\n" \
                "================================\n"
            );

            test_scene = myDenisLevels[0].convertToKao2(file);

            myARs[0].setMyParentScene(test_scene);

            myARs[0].changeSelectedObject(NODES_LISTBOX_ROOT, nullptr);

            theLog.print
            (
                "================================\n" \
                "==    DENIS LVL CONVERTING    ==\n" \
                "==          FINISHED          ==\n" \
                "================================\n"
            );

            sprintf_s
            (
                bufor, 256,
                    "Denis Map has been converted to Kao2 engine!\n\n" \
                    "Now you can save Archive to: \"%s/build/win32/%s.ar\"",
                currentWorkingDirectory,
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


    ////////////////////////////////////////////////////////////////
    // miscellaneous: generate empty scene (custom Kao2 levels)
    ////////////////////////////////////////////////////////////////

    void generateEmptyScene()
    {
        char bufor[256];
        eString compile_strings[2];

        std::time_t current_time;
        std::tm time_info;
        char time_bufor[32];

        eScene* new_scene = nullptr;
        eEnvironment* global_env = nullptr;
        eCollisionMgr* test_collision = nullptr;

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

        global_env = new eEnvironment("global_env");
        global_env->setFlags(0x70000000);

        test_collision = new_scene->getCollisionManager();

        /********************************/
        /* Set scene name and creation details */

        new_scene->setName("$root");

        compile_strings[0] = "Created with ZookieWizard at ";
        compile_strings[0] += time_bufor;
        compile_strings[0] += "\r\n";

        compile_strings[1] = denisLevelName;

        new_scene->setCompileStrings(compile_strings[0], compile_strings[1]);

        /********************************/
        /* Add environment (and update its parent) */

        new_scene->appendChild(global_env);

        /********************************/
        /* Add one collision entry (REQUIRED BY KAO2 ENGINE) */

        test_collision->insertNewItem_seriesA(0);

        /********************************/
        /* Replace current archive */

        myARs[0].setMyParentScene(new_scene);

        myARs[0].changeSelectedObject(NODES_LISTBOX_ROOT, nullptr);

        theLog.print
        (
            "================================\n" \
            "==   GENERATING EMPTY SCENE   ==\n" \
            "==          FINISHED          ==\n" \
            "================================\n"
        );

        sprintf_s
        (
            bufor, 256,
            "Empty scene for Kao2 created!\n\n" \
            "Now you can save Archive to: \"%s/build/win32/%s.ar\"",
            currentWorkingDirectory,
            denisLevelName
        );

        GUI::theWindowsManager.displayMessage(WINDOWS_MANAGER_MESSAGE_INFO, bufor);
    }


    ////////////////////////////////////////////////////////////////
    // miscellaneous: Export Kao2 Archive to COLLADA "*.dae" format
    ////////////////////////////////////////////////////////////////

    void exportArToCollada()
    {
        eString filename;
        char bufor[256];

        try
        {
            bufor[0] = 0x00;

            ofn.lpstrFile = bufor;
            ofn.nMaxFile = 256;
            ofn.lpstrTitle = "Saving COLADA document...";
            ofn.lpstrFilter = "COLLADA document (*.dae)\0*.dae\0";
            ofn.Flags = (OFN_OVERWRITEPROMPT);

            if (0 == GetSaveFileName(&ofn))
            {
                return;
            }

            /* Set filename and save XML document */

            filename = bufor;

            if (false == filename.hasExtension("dae"))
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

            myARs[0].writeStructureToXmlFile(filename);

            theLog.print
            (
                "================================\n" \
                "==    COLLADA DAE EXPORTING   ==\n" \
                "==          FINISHED          ==\n" \
                "================================\n"
            );

            sprintf_s
            (
                bufor, 256,
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

    void exportTrimeshToObj()
    {
        eString filename;
        char bufor[256];

        try
        {
            bufor[0] = 0x00;

            ofn.lpstrFile = bufor;
            ofn.nMaxFile = 256;
            ofn.lpstrTitle = "Saving OBJ document...";
            ofn.lpstrFilter = "Wavefront OBJ document (*.obj)\0*.obj\0";
            ofn.Flags = (OFN_OVERWRITEPROMPT);

            if (0 == GetSaveFileName(&ofn))
            {
                return;
            }

            /* Set filename and save OBJ document */

            filename = bufor;

            if (false == filename.hasExtension("obj"))
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

            myARs[0].writeSelectedObjectToObjFile(filename);

            theLog.print
            (
                "================================\n" \
                "==   WAVEFRONT OBJ EXPORTING  ==\n" \
                "==          FINISHED          ==\n" \
                "================================\n"
            );

            sprintf_s
            (
                bufor, 256,
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

    void importTrimeshFromObj()
    {
        eString filename;
        char bufor[256];

        try
        {
            bufor[0] = 0x00;

            ofn.lpstrFile = bufor;
            ofn.nMaxFile = 256;
            ofn.lpstrTitle = "Opening OBJ document...";
            ofn.lpstrFilter = "Wavefront OBJ document (*.obj)\0*.obj\0";
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

            myARs[0].appendToSelectedObjectFromObjFile(filename);

            theLog.print
            (
                "================================\n" \
                "==   WAVEFRONT OBJ IMPORTING  ==\n" \
                "==          FINISHED          ==\n" \
                "================================\n"
            );

            sprintf_s
            (
                bufor, 256,
                "<\"%s\">\n\nOBJ document imported successfully! :)",
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
    // miscellaneous: Import Kao2 Nodes from "*.txt" file
    ////////////////////////////////////////////////////////////////

    void importNodesFromTxt()
    {
        int32_t result;
        eString filename;
        char bufor[256];

        try
        {
            /* Show instruction */

            GUI::theWindowsManager.displayMessage
            (
                WINDOWS_MANAGER_MESSAGE_INFO,
                "Select a text file structured in a following way:\n\n" \
                "<ClassName> # starts a new object\n" \
                "  name = node name\n" \
                "  pos = X Y Z positions\n" \
                "  rot = X Y Z euler angles\n" \
                "  scl = scale\n" \
                "and other properties...\n" \
                "\n--------------------------------\n" \
                "    EXAMPLE:\n\n" \
                "<eProxy>\n" \
                "  name = foka\n" \
                "  pos = 0 500.0 1000.0\n" \
                "  rot = 0 0 90.0\n" \
                "  scl = 2.0\n" \
                "  link = characters\\fluffs\\bobr\\scripts\\bobr_generic.def\n" \
                "  category = fluff\n"
            );

            /* Try to open a text file */

            bufor[0] = 0x00;

            ofn.lpstrFile = bufor;
            ofn.nMaxFile = 256;
            ofn.lpstrTitle = "Opening a TXT file...";
            ofn.lpstrFilter = "Text files (*.txt)\0*.txt\0";
            ofn.Flags = (OFN_FILEMUSTEXIST | OFN_HIDEREADONLY);

            if (0 == GetOpenFileName(&ofn))
            {
                return;
            }

            filename = bufor;

            theLog.print
            (
                "================================\n" \
                "==  PROXIES FROM TXT IMPORT   ==\n" \
                "==            BEGIN           ==\n" \
                "================================\n"
            );

            result = myARs[0].appendNodesFromTxtFile(filename.getText());

            theLog.print
            (
                "================================\n" \
                "==  PROXIES FROM TXT IMPORT   ==\n" \
                "==          FINISHED          ==\n" \
                "================================\n"
            );

            sprintf_s
            (
                bufor, 256,
                "<\"%s\">\n\n%d proxies successfully added :)",
                filename.getText(),
                result
            );

            GUI::theWindowsManager.displayMessage(WINDOWS_MANAGER_MESSAGE_INFO, bufor);
        }
        catch (ErrorMessage &e)
        {
            theLog.print
            (
                "================================\n" \
                "==  PROXIES FROM TXT IMPORT   ==\n" \
                "==            oops!           ==\n" \
                "================================\n"
            );

            e.display();
        }
    }

}
