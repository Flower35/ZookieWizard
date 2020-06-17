#include <ZookieWizard/ZookieWizard.h>
#include <ZookieWizard/WindowsManager.h>

#include <kao2ar/Archive.h>
#include <kao2engine/eNode.h>

namespace ZookieWizard
{
    namespace GUI
    {
        ////////////////////////////////////////////////////////////////
        // Initialize variables
        ////////////////////////////////////////////////////////////////

        HBITMAP myWindowLogo = NULL;
        HFONT myWindowFont = NULL;

        static bool updatingNodeName = false;


        ////////////////////////////////////////////////////////////////
        // List of static functions
        ////////////////////////////////////////////////////////////////

        void menuFunc_SetGameVersion(WPARAM wParam, LPARAM lParam, void* custom_param)
        {
            setGameVersion((int32_t)custom_param);
        }

        void menuFunc_DenisConvert(WPARAM wParam, LPARAM lParam, void* custom_param)
        {
            if (0 == (int32_t)custom_param)
            {
                openDenisLevel();
            }
            else if (1 == (int32_t)custom_param)
            {
                convertDenisLevel();
            }
        }

        void menuFunc_ArOpen(WPARAM wParam, LPARAM lParam, void* custom_param)
        {
            if ((int32_t)custom_param >= 0)
            {
                openOrSaveAr((int32_t)custom_param);
            }
            else if ((-1) == (int32_t)custom_param)
            {
                writeArStructureToTextFile();
            }
            else if ((-2) == (int32_t)custom_param)
            {
                exportArToCollada();
            }
            else if ((-3) == (int32_t)custom_param)
            {
                bulkArchiveConverter();
            }
            else if ((-4) == (int32_t)custom_param)
            {
                generateEmptyScene();
            }
        }

        void buttonFunc_EditBoxTyping(WPARAM wParam, LPARAM lParam, void* custom_param)
        {
            if (EN_CHANGE == HIWORD(wParam))
            {
                GetWindowText((HWND)lParam, (LPSTR)custom_param, 256);
            }
        }

        void buttonFunc_Anim(WPARAM wParam, LPARAM lParam, void* custom_param)
        {
            int32_t i;
            char bufor[8];

            if (EN_CHANGE == HIWORD(wParam))
            {
                GetWindowText((HWND)lParam, bufor, 8);

                i = std::atoi(bufor);

                if (0 == (int32_t)custom_param)
                {
                    if (i < 0) i = 0;

                    if (animationID != i)
                    {
                        animationID = i;
                        timerReset();
                    }
                }
                else if (1 == (int32_t)custom_param)
                {
                    if (i < 1) i = 1;

                    animationFPS = i;
                }
            }
        }

        void buttonFunc_NodesListChild(WPARAM wParam, LPARAM lParam, void* custom_param)
        {
            int32_t a = 0, b;

            switch (HIWORD(wParam))
            {
                case LBN_DBLCLK:
                {
                    a = 1;
                    break;
                }

                case LBN_SELCHANGE:
                case LBN_SELCANCEL:
                {
                    a = 2;
                    break;
                }
            }

            if (0 != a)
            {
                b = SendMessage((HWND)lParam, LB_GETCURSEL, 0, 0);

                switch (a)
                {
                    case 1:
                    {
                        a = (b == LB_ERR) ? NODES_LISTBOX_UPDATE_CURRENT : b;
                        b = 0;
                        break;
                    }

                    case 2:
                    {
                        a = NODES_LISTBOX_SET_MARKED_CHILD;
                        b = (b == LB_ERR) ? (-1) : b;
                        break;
                    }
                }

                myARs[0].changeSelectedObject(a, (void*)b);
            }
        }

        void buttonFunc_NodesListMisc(WPARAM wParam, LPARAM lParam, void* custom_param)
        {
            if (BN_CLICKED == HIWORD(wParam))
            {
                myARs[0].changeSelectedObject((int32_t)custom_param, nullptr);
            }
        }

        void buttonFunc_NodesListObj(WPARAM wParam, LPARAM lParam, void* custom_param)
        {
            if (BN_CLICKED == HIWORD(wParam))
            {
                if (0 == (int32_t)custom_param)
                {
                    exportTrimeshToObj();
                }
                else if (1 == (int32_t)custom_param)
                {
                    importTrimeshFromObj();
                }
                else if (2 == (int32_t)custom_param)
                {
                    importNodesFromTxt();
                }
            }
        }

        void buttonFunc_ResetTimer(WPARAM wParam, LPARAM lParam, void* custom_param)
        {
            if (BN_CLICKED == HIWORD(wParam))
            {
                timerReset();
            }
        }

        void buttonFunc_CameraReset(WPARAM wParam, LPARAM lParam, void* custom_param)
        {
            if (BN_CLICKED == HIWORD(wParam))
            {
                testCamera.reset(0, 0, 0);
            }
        }

        void buttonFunc_CameraSpeed(WPARAM wParam, LPARAM lParam, void* custom_param)
        {
            double i;
            char bufor[8];

            if (EN_CHANGE == HIWORD(wParam))
            {
                GetWindowText((HWND)lParam, bufor, 8);

                i = std::atof(bufor);

                if (i > 0)
                {
                    testCamera.speed = i;
                }
            }
        }

        void buttonFunc_RenderFlags(WPARAM wParam, LPARAM lParam, void* custom_param)
        {
            if (BN_CLICKED == HIWORD(wParam))
            {
                if (BST_CHECKED == SendMessage((HWND)lParam, BM_GETCHECK, 0, 0))
                {
                    if (0 == (int32_t)custom_param)
                    {
                        glPolygonMode(GL_FRONT, GL_LINE);
                    }
                    else if (1 == (int32_t)custom_param)
                    {
                        myDrawFlags |= drawFlags::DRAW_FLAG_OUTLINE;
                    }
                    else if (2 == (int32_t)custom_param)
                    {
                        myDrawFlags |= drawFlags::DRAW_FLAG_INVISIBLE;
                    }
                    else if (3 == (int32_t)custom_param)
                    {
                        myDrawFlags |= drawFlags::DRAW_FLAG_BOXZONES;
                    }
                    else if (4 == (int32_t)custom_param)
                    {
                        myDrawFlags |= drawFlags::DRAW_FLAG_PROXIES;
                    }
                    else if (5 == (int32_t)custom_param)
                    {
                        myDrawFlags |= drawFlags::DRAW_FLAG_ANIMS;
                    }
                    else if (6 == (int32_t)custom_param)
                    {
                        myDrawFlags |= drawFlags::DRAW_FLAG_SPECIAL;
                    }
                }
                else
                {
                    if (0 == (int32_t)custom_param)
                    {
                        glPolygonMode(GL_FRONT, GL_FILL);
                    }
                    else if (1 == (int32_t)custom_param)
                    {
                        myDrawFlags &= (~ drawFlags::DRAW_FLAG_OUTLINE);
                    }
                    else if (2 == (int32_t)custom_param)
                    {
                        myDrawFlags &= (~ drawFlags::DRAW_FLAG_INVISIBLE);
                    }
                    else if (3 == (int32_t)custom_param)
                    {
                        myDrawFlags &= (~ drawFlags::DRAW_FLAG_BOXZONES);
                    }
                    else if (4 == (int32_t)custom_param)
                    {
                        myDrawFlags &= (~ drawFlags::DRAW_FLAG_PROXIES);
                    }
                    else if (5 == (int32_t)custom_param)
                    {
                        myDrawFlags &= (~ drawFlags::DRAW_FLAG_ANIMS);
                    }
                    else if (6 == (int32_t)custom_param)
                    {
                        myDrawFlags &= (~ drawFlags::DRAW_FLAG_SPECIAL);
                    }
                }
            }
        }

        void buttonFunc_NodeType(WPARAM wParam, LPARAM lParam, void* custom_param)
        {
            char bufor[64];
            HWND type_name_window = NULL;

            if (BN_CLICKED == HIWORD(wParam))
            {
                type_name_window = theWindowsManager.getSpecificWindow(3, 1);

                if (NULL != type_name_window)
                {
                    GetWindowText(type_name_window, bufor, 64);

                    if (0x00 == (int32_t)custom_param)
                    {
                        theWindowsManager.displayMessage
                        (
                            WINDOWS_MANAGER_MESSAGE_WARNING,
                            "Changng object type is not supported yet."
                        );
                    }
                    else if (0x01 == (int32_t)custom_param)
                    {
                        myARs[0].changeSelectedObject(NODES_EDITING_INSERT, bufor);
                    }
                }
            }
        }

        void buttonFunc_NodeName(WPARAM wParam, LPARAM lParam, void* custom_param)
        {
            char bufor[256];

            if ((false == updatingNodeName) && (EN_CHANGE == HIWORD(wParam)))
            {
                GetWindowText((HWND)lParam, bufor, 256);

                myARs[0].changeSelectedObject(NODES_EDITING_CHANGE_NAME, bufor);
            }
        }

        void buttonFunc_NodeFlags(WPARAM wParam, LPARAM lParam, void* custom_param)
        {
            if (BN_CLICKED == HIWORD(wParam))
            {
                if (BST_CHECKED == SendMessage((HWND)lParam, BM_GETCHECK, 0, 0))
                {
                    myARs[0].changeSelectedObject(NODES_EDITING_SET_FLAG, custom_param);
                }
                else
                {
                    myARs[0].changeSelectedObject(NODES_EDITING_UNSET_FLAG, custom_param);
                }
            }
        }


        ////////////////////////////////////////////////////////////////
        // Update ListBox of nodes
        // (-3) set label message
        // (-2) clears listbox
        // (-1) sets listbox selection
        // (0) adds children nodes to the listbox
        // (1) sets current node type
        // (2) sets current node name
        // (3) sets current node flags
        ////////////////////////////////////////////////////////////////
        void updateNodesList(int32_t mode, void* param)
        {
            int32_t a;
            WPARAM b;

            const char* new_text = "";
            HWND label = theWindowsManager.getSpecificWindow(2, 0);
            HWND listbox = theWindowsManager.getSpecificWindow(2, (-1));
            HWND test_hwnd;

            if (((-3) == mode) && (NULL != label))
            {
                if (nullptr != param)
                {
                    new_text = (char*)param;
                }

                SetWindowText(label, new_text);
            }
            else if ((mode <= 0) && (NULL != listbox))
            {
                if ((-2) == mode)
                {
                    SendMessage(listbox, LB_RESETCONTENT, 0, 0);
                }
                else if ((-1) == mode)
                {
                    SendMessage(listbox, LB_SETCURSEL, (WPARAM)param, 0);
                }
                else if (0 == mode)
                {
                    if (nullptr != param)
                    {
                        new_text = (char*)param;
                    }

                    SendMessage(listbox, LB_ADDSTRING, 0, (LPARAM)new_text);
                }
            }
            else if ((1 == mode) || (2 == mode))
            {
                updatingNodeName = true;

                if (nullptr != param)
                {
                    new_text = (char*)param;
                }

                test_hwnd = theWindowsManager.getSpecificWindow(3, (1 == mode) ? 1 : 5);

                if (NULL != test_hwnd)
                {
                    SetWindowText(test_hwnd, new_text);
                }

                updatingNodeName = false;
            }
            else if (3 == mode)
            {
                for (a = 0; a < 32; a++)
                {
                    test_hwnd = theWindowsManager.getSpecificWindow(3, (7 + a));

                    if (NULL != test_hwnd)
                    {
                        b = ((0x01 << a) & (int32_t)param) ? BST_CHECKED : BST_UNCHECKED;

                        SendMessage(test_hwnd, BM_SETCHECK, b, 0);
                    }
                }
            }
        }


        ////////////////////////////////////////////////////////////////
        // Create windows
        ////////////////////////////////////////////////////////////////
        bool createWindows(HINSTANCE hInstance)
        {
            int32_t a, b;
            char bufor[64];
            HMENU menu_bar, test_menu;
            HWND main_window, scroll_window;

            const int WINDOW_HEIGHT = 24;
            const int WINDOW_PADDING = 16;
            const int WINDOW_PADDING_SMALL = 8;
            const int TOP_OFFSET = 8;

            const char* WELCOME_MESSAGE = \
                "Camera movement:\n" \
                " - LMB for rotation\n" \
                " - RMB or [W][A][S][D] for strafing\n" \
                "\n" \
                "This project is in alpha stage.";

            /********************************/
            /* Prepare manager (1/2) */

            theWindowsManager.reset();
            theWindowsManager.setCurrentModuleInstance(hInstance);

            /********************************/
            /* Load fonts and resources */

            myWindowLogo = LoadBitmap(hInstance, MAKEINTRESOURCE(IDM_BITMAP));

            if (NULL == myWindowLogo)
            {
                return false;
            }

            myWindowFont = CreateFont
            (
                16, 0, 0, 0,
                FW_NORMAL,
                FALSE, FALSE, FALSE,
                DEFAULT_CHARSET,
                OUT_DEFAULT_PRECIS,
                CLIP_DEFAULT_PRECIS,
                DEFAULT_QUALITY,
                (DEFAULT_PITCH | FF_SWISS),
                "Verdana"
            );

            if (NULL == myWindowFont)
            {
                return false;
            }

            /********************************/
            /* Prepare manager (2/2) */

            if (false == theWindowsManager.createMainWindows())
            {
                return false;
            }

            main_window = theWindowsManager.getMainWindow();
            scroll_window = theWindowsManager.getScrollWindow();

            theWindowsManager.setCurrentParent(scroll_window);
            theWindowsManager.setCurrentPadding(0, 0);

            /********************************/
            /* [MENU BAR] */

            menu_bar = CreateMenu();

            test_menu = CreateMenu();
            AppendMenu(test_menu, MF_STRING, (UINT_PTR)theWindowsManager.addStaticFunction(menuFunc_DenisConvert, (void*)0), "&Open level");
            AppendMenu(test_menu, MF_STRING, (UINT_PTR)theWindowsManager.addStaticFunction(menuFunc_DenisConvert, (void*)1), "&Convert level");
            AppendMenu(menu_bar, MF_POPUP, (UINT_PTR)test_menu, "Denis the Kangaroo");

            test_menu = CreateMenu();
            AppendMenu(test_menu, MF_STRING, (UINT_PTR)theWindowsManager.addStaticFunction(menuFunc_SetGameVersion, (void*)GAME_VERSION_KAO2_PL_PC), "&1) Kangurek Kao: Runda 2 [PL]");
            AppendMenu(test_menu, MF_STRING, (UINT_PTR)theWindowsManager.addStaticFunction(menuFunc_SetGameVersion, (void*)GAME_VERSION_KAO2_EUR_PC), "&2) Kao the Kangaroo: Round 2 [EU]");
            AppendMenu(test_menu, MF_STRING, (UINT_PTR)theWindowsManager.addStaticFunction(menuFunc_SetGameVersion, (void*)GAME_VERSION_KAO_TW_PC), "&3) Kao: Tajemnica Wulkanu");
            AppendMenu(menu_bar, MF_POPUP, (UINT_PTR)test_menu, "Game &version");

            test_menu = CreateMenu();
            AppendMenu(test_menu, MF_STRING, (UINT_PTR)theWindowsManager.addStaticFunction(menuFunc_ArOpen, (void*)AR_MODE_READ), "&Open Archive");
            AppendMenu(test_menu, MF_STRING, (UINT_PTR)theWindowsManager.addStaticFunction(menuFunc_ArOpen, (void*)AR_MODE_WRITE), "&Save Archive");
            AppendMenu(test_menu, MF_STRING, (UINT_PTR)theWindowsManager.addStaticFunction(menuFunc_ArOpen, (void*)(-4)), "Generate &empty scene");
            AppendMenu(test_menu, MF_STRING, (UINT_PTR)theWindowsManager.addStaticFunction(menuFunc_ArOpen, (void*)AR_MODE_EXPORT_SCRIPTS), "Export S&cripts");
            AppendMenu(test_menu, MF_STRING, (UINT_PTR)theWindowsManager.addStaticFunction(menuFunc_ArOpen, (void*)AR_MODE_EXPORT_PROXIES), "Export &proxies");
            AppendMenu(test_menu, MF_STRING, (UINT_PTR)theWindowsManager.addStaticFunction(menuFunc_ArOpen, (void*)(-3)), "&Bulk archive converter");
            AppendMenu(test_menu, MF_STRING, (UINT_PTR)theWindowsManager.addStaticFunction(menuFunc_ArOpen, (void*)(-1)), "Export &readable structure");
            AppendMenu(test_menu, MF_STRING, (UINT_PTR)theWindowsManager.addStaticFunction(menuFunc_ArOpen, (void*)(-2)), "Export COLLADA &dae");
            AppendMenu(menu_bar, MF_POPUP, (UINT_PTR)test_menu, "Kao the Kangaroo: Round 2");

            SetMenu(main_window, menu_bar);

            /********************************/
            /* [PAGE 0] */

            theWindowsManager.addPage("Render settings");

            theWindowsManager.setCurrentPosition(RECT_TABS_X1, TOP_OFFSET);
            theWindowsManager.updateReturningPosition();

            /********************************/
            /* [PAGE 0] (0 – 6) Create checkboxes */

            theWindowsManager.setCurrentClassName("BUTTON");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | BS_AUTOCHECKBOX);

            const char* render_flags_names[7] =
            {
                "Draw WIREFRAME", "Outline SELECTED", "Draw INVISIBLE MESHES", "Draw BOX ZONES", "Draw PROXIES", "Update ANIMATIONS", "Render SPECIAL HELPERS"
            };

            for (a = 0; a < 7; a++)
            {
                if (0 == theWindowsManager.addWindow(render_flags_names[a], RECT_TABS_X2, WINDOW_HEIGHT, buttonFunc_RenderFlags, (void*)a, 0x01))
                {
                    return false;
                }
            }

            theWindowsManager.offsetCurrentPosition(0, WINDOW_PADDING);

            /********************************/
            /* [PAGE 0] (7) Create line decoration */

            theWindowsManager.setCurrentClassName("STATIC");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | WS_VISIBLE | SS_ETCHEDHORZ);
            theWindowsManager.offsetCurrentPosition((0 - RECT_TABS_X1), 0);

            if (0 == theWindowsManager.addWindow("", RECT_LOGO_X2, 2, nullptr, 0, 0x01))
            {
                return false;
            }

            theWindowsManager.offsetCurrentPosition(0, WINDOW_PADDING);

            /********************************/
            /* [PAGE 0] (8) Create button */

            theWindowsManager.setCurrentClassName("BUTTON");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | BS_DEFPUSHBUTTON);

            if (0 == theWindowsManager.addWindow("Reset Camera", RECT_TABS_X2, WINDOW_HEIGHT, buttonFunc_CameraReset, nullptr, 0x01))
            {
                return false;
            }

            theWindowsManager.offsetCurrentPosition(0, WINDOW_PADDING);

            /********************************/
            /* [PAGE 0] (9) Create dummy label */

            theWindowsManager.setCurrentClassName("STATIC");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD);

            if (0 == theWindowsManager.addWindow("Camera speed multiplier:", RECT_TABS_X2, WINDOW_HEIGHT, nullptr, nullptr, 0x01))
            {
                return false;
            }

            /********************************/
            /* [PAGE 0] (10) Create editbox */

            theWindowsManager.setCurrentClassName("EDIT");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | ES_AUTOHSCROLL);

            theWindowsManager.addEdgesToNextWindow();
            if (0 == theWindowsManager.addWindow(TEST_CAMERA_DEFAULT_SPEED_TEXT, RECT_TABS_X2, WINDOW_HEIGHT, buttonFunc_CameraSpeed, nullptr, 0x01))
            {
                return false;
            }

            theWindowsManager.offsetCurrentPosition(0, WINDOW_PADDING);

            /********************************/
            /* [PAGE 0] (11) Create line decoration */

            theWindowsManager.setCurrentClassName("STATIC");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | WS_VISIBLE | SS_ETCHEDHORZ);
            theWindowsManager.offsetCurrentPosition((0 - RECT_TABS_X1), 0);

            if (0 == theWindowsManager.addWindow("", RECT_LOGO_X2, 2, nullptr, 0, 0x01))
            {
                return false;
            }

            theWindowsManager.offsetCurrentPosition(0, WINDOW_PADDING);

            /********************************/
            /* [PAGE 0] (12) Create dummy label */

            theWindowsManager.setCurrentClassName("STATIC");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD);

            if (0 == theWindowsManager.addWindow("Animation ID", RECT_TABS_X2, WINDOW_HEIGHT, nullptr, nullptr, 0x01))
            {
                return false;
            }

            /********************************/
            /* [PAGE 0] (13) Create editbox */

            theWindowsManager.setCurrentClassName("EDIT");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | ES_AUTOHSCROLL);

            theWindowsManager.addEdgesToNextWindow();
            if (0 == theWindowsManager.addWindow("0", RECT_TABS_X2, WINDOW_HEIGHT, buttonFunc_Anim, (void*)0, 0x01))
            {
                return false;
            }

            theWindowsManager.offsetCurrentPosition(0, WINDOW_PADDING);

            /********************************/
            /* [PAGE 0] (14) Create button */

            theWindowsManager.setCurrentClassName("BUTTON");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | BS_DEFPUSHBUTTON);

            if (0 == theWindowsManager.addWindow("Reset Timer", RECT_TABS_X2, WINDOW_HEIGHT, buttonFunc_ResetTimer, nullptr, 0x01))
            {
                return false;
            }

            theWindowsManager.offsetCurrentPosition(0, WINDOW_PADDING);

            /********************************/
            /* [PAGE 0] (15) Create dummy label */

            theWindowsManager.setCurrentClassName("STATIC");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD);

            if (0 == theWindowsManager.addWindow("Frames per second", RECT_TABS_X2, WINDOW_HEIGHT, nullptr, nullptr, 0x01))
            {
                return false;
            }

            /********************************/
            /* [PAGE 0] (16) Create editbox */

            theWindowsManager.setCurrentClassName("EDIT");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | ES_AUTOHSCROLL);

            theWindowsManager.addEdgesToNextWindow();
            if (0 == theWindowsManager.addWindow("1", RECT_TABS_X2, WINDOW_HEIGHT, buttonFunc_Anim, (void*)1, 0x01))
            {
                return false;
            }

            theWindowsManager.offsetCurrentPosition(0, WINDOW_PADDING);

            /********************************/
            /* [PAGE 0] (17) Create line decoration */

            theWindowsManager.setCurrentClassName("STATIC");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | WS_VISIBLE | SS_ETCHEDHORZ);
            theWindowsManager.offsetCurrentPosition((0 - RECT_TABS_X1), 0);

            if (0 == theWindowsManager.addWindow("", RECT_LOGO_X2, 2, nullptr, 0, 0x01))
            {
                return false;
            }

            theWindowsManager.offsetCurrentPosition(0, WINDOW_PADDING);

            /********************************/
            /* [PAGE 0] (18) Create dummy label */

            theWindowsManager.setCurrentClassName("STATIC");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD);

            if (0 == theWindowsManager.addWindow(WELCOME_MESSAGE, RECT_TABS_X2, (5 * WINDOW_HEIGHT), nullptr, nullptr, 0))
            {
                return false;
            }

            /********************************/
            /* [PAGE 1] */

            theWindowsManager.addPage("theAR + Denis");

            theWindowsManager.setCurrentPosition(RECT_TABS_X1, TOP_OFFSET);

            /********************************/
            /* [PAGE 1] (0) Create dummy label */

            theWindowsManager.setCurrentClassName("STATIC");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD);

            if (0 == theWindowsManager.addWindow("Working directory (\"/media/\"):", RECT_TABS_X2, WINDOW_HEIGHT, nullptr, nullptr, 0x01))
            {
                return false;
            }

            /********************************/
            /* [PAGE 1] (1) Create editbox */

            theWindowsManager.setCurrentClassName("EDIT");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | ES_AUTOHSCROLL);

            theWindowsManager.addEdgesToNextWindow();
            if (0 == theWindowsManager.addWindow("", RECT_TABS_X2, WINDOW_HEIGHT, buttonFunc_EditBoxTyping, (void*)currentWorkingDirectory, 0x01))
            {
                return false;
            }

            theWindowsManager.offsetCurrentPosition(0, WINDOW_PADDING);

            /********************************/
            /* [PAGE 1] (2) Create dummy label */

            theWindowsManager.setCurrentClassName("STATIC");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD);

            if (0 == theWindowsManager.addWindow("Denis game directory:", RECT_TABS_X2, WINDOW_HEIGHT, nullptr, nullptr, 0x01))
            {
                return false;
            }

            /********************************/
            /* [PAGE 1] (3) Create editbox */

            theWindowsManager.setCurrentClassName("EDIT");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | ES_AUTOHSCROLL);

            theWindowsManager.addEdgesToNextWindow();
            if (0 == theWindowsManager.addWindow("", RECT_TABS_X2, WINDOW_HEIGHT, buttonFunc_EditBoxTyping, (void*)denisDirectory, 0x01))
            {
                return false;
            }

            theWindowsManager.offsetCurrentPosition(0, WINDOW_PADDING);

            /********************************/
            /* [PAGE 1] (4) Create dummy label */

            theWindowsManager.setCurrentClassName("STATIC");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD);

            if (0 == theWindowsManager.addWindow("Which level do you want to load?", RECT_TABS_X2, WINDOW_HEIGHT, nullptr, nullptr, 0x01))
            {
                return false;
            }

            /********************************/
            /* [PAGE 1] (5) Create editbox */

            theWindowsManager.setCurrentClassName("EDIT");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | ES_AUTOHSCROLL);

            theWindowsManager.addEdgesToNextWindow();
            if (0 == theWindowsManager.addWindow("", RECT_TABS_X2, WINDOW_HEIGHT, buttonFunc_EditBoxTyping, (void*)denisLevelName, 0x01))
            {
                return false;
            }

            /********************************/
            /* [PAGE 2] */

            theWindowsManager.addPage("Nodes list");

            theWindowsManager.setCurrentPosition(RECT_TABS_X1, TOP_OFFSET);

            /********************************/
            /* [PAGE 2] (0) Create dummy label */

            theWindowsManager.setCurrentClassName("STATIC");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD);

            if (0 == theWindowsManager.addWindow("(no archive loaded yet)", RECT_TABS_X2, (3 * WINDOW_HEIGHT), nullptr, nullptr, 0x01))
            {
                return false;
            }

            /********************************/
            /* [PAGE 2] (1 – 9) Create buttons */

            theWindowsManager.setCurrentClassName("BUTTON");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | BS_DEFPUSHBUTTON | BS_MULTILINE);

            theWindowsManager.setCurrentPadding(WINDOW_PADDING_SMALL, WINDOW_PADDING_SMALL);

            a = (RECT_TABS_X2 / 2) - (WINDOW_PADDING / 2);

            if (0 == theWindowsManager.addWindow("^ Back to\nArchive Root", a, 2 * WINDOW_HEIGHT, buttonFunc_NodesListMisc, (void*)NODES_LISTBOX_ROOT, 0))
            {
                return false;
            }

            if (0 == theWindowsManager.addWindow("^ Back to\nParent Node", a, 2 * WINDOW_HEIGHT, buttonFunc_NodesListMisc, (void*)NODES_LISTBOX_PARENT, 0x01))
            {
                return false;
            }

            if (0 == theWindowsManager.addWindow("Center Camera on Node", a, 2 * WINDOW_HEIGHT, buttonFunc_NodesListMisc, (void*)NODES_LISTBOX_FIND, 0))
            {
                return false;
            }

            if (0 == theWindowsManager.addWindow("Delete Node", a, 2 * WINDOW_HEIGHT, buttonFunc_NodesListMisc, (void*)NODES_LISTBOX_DELETE, 0x01))
            {
                return false;
            }

            if (0 == theWindowsManager.addWindow("Export 3D Meshes to Wavefront OBJ", a, 2 * WINDOW_HEIGHT, buttonFunc_NodesListObj, (void*)0, 0))
            {
                return false;
            }

            if (0 == theWindowsManager.addWindow("Import 3D Meshes from Wavefront OBJ", a, 2 * WINDOW_HEIGHT, buttonFunc_NodesListObj, (void*)1, 0x01))
            {
                return false;
            }

            if (0 == theWindowsManager.addWindow("Rebuild Collision", a, 2 * WINDOW_HEIGHT, buttonFunc_NodesListMisc, (void*)NODES_LISTBOX_COLLISION_REBUILD, 0))
            {
                return false;
            }

            if (0 == theWindowsManager.addWindow("Clear Collision", a, 2 * WINDOW_HEIGHT, buttonFunc_NodesListMisc, (void*)NODES_LISTBOX_COLLISION_CLEAR, 0x01))
            {
                return false;
            }

            if (0 == theWindowsManager.addWindow("Import Nodes from TXT", a, 2 * WINDOW_HEIGHT, buttonFunc_NodesListObj, (void*)2, 0x01))
            {
                return false;
            }

            theWindowsManager.setCurrentPadding(0, 0);
            theWindowsManager.offsetCurrentPosition(0, WINDOW_PADDING_SMALL);

            /********************************/
            /* [PAGE 2] (10) Create listbox */

            theWindowsManager.setCurrentClassName("LISTBOX");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | WS_HSCROLL | WS_VSCROLL | LBS_DISABLENOSCROLL | LBS_HASSTRINGS | LBS_NOTIFY);

            theWindowsManager.addEdgesToNextWindow();
            if (0 == theWindowsManager.addWindow("", RECT_TABS_X2, 384, buttonFunc_NodesListChild, nullptr, 0x01))
            {
                return false;
            }

            /********************************/
            /* [PAGE 3] */

            theWindowsManager.addPage("Node editing");

            theWindowsManager.setCurrentPosition(RECT_TABS_X1, TOP_OFFSET);

            /********************************/
            /* [PAGE 3] (0) Create dummy label */

            theWindowsManager.setCurrentClassName("STATIC");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD);

            if (0 == theWindowsManager.addWindow("\"eNode\" type:", RECT_TABS_X2, WINDOW_HEIGHT, nullptr, nullptr, 0x01))
            {
                return false;
            }

            /********************************/
            /* [PAGE 3] (1) Create editbox */

            theWindowsManager.setCurrentClassName("EDIT");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | ES_AUTOHSCROLL);

            theWindowsManager.addEdgesToNextWindow();
            if (0 == theWindowsManager.addWindow("", RECT_TABS_X2, WINDOW_HEIGHT, nullptr, nullptr, 0x01))
            {
                return false;
            }

            theWindowsManager.offsetCurrentPosition(0, WINDOW_PADDING);

            /********************************/
            /* [PAGE 3] (2 – 3) Create buttons */

            theWindowsManager.setCurrentClassName("BUTTON");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | BS_DEFPUSHBUTTON);

            theWindowsManager.setCurrentPadding(WINDOW_PADDING_SMALL, WINDOW_PADDING_SMALL);

            a = (RECT_TABS_X2 / 2) - (WINDOW_PADDING / 2);

            if (0 == theWindowsManager.addWindow("Change Type", a, WINDOW_HEIGHT, buttonFunc_NodeType, (void*)0x00, 0))
            {
                return false;
            }

            if (0 == theWindowsManager.addWindow("Add New Node", a, WINDOW_HEIGHT, buttonFunc_NodeType, (void*)0x01, 0x01))
            {
                return false;
            }

            theWindowsManager.setCurrentPadding(0, 0);
            theWindowsManager.offsetCurrentPosition(0, WINDOW_PADDING_SMALL);

            /********************************/
            /* [PAGE 3] (4) Create dummy label */

            theWindowsManager.setCurrentClassName("STATIC");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD);

            if (0 == theWindowsManager.addWindow("\"eNode\" name:", RECT_TABS_X2, WINDOW_HEIGHT, nullptr, nullptr, 0x01))
            {
                return false;
            }

            /********************************/
            /* [PAGE 3] (5) Create editbox */

            theWindowsManager.setCurrentClassName("EDIT");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | ES_AUTOHSCROLL);

            theWindowsManager.addEdgesToNextWindow();
            if (0 == theWindowsManager.addWindow("", RECT_TABS_X2, WINDOW_HEIGHT, buttonFunc_NodeName, nullptr, 0x01))
            {
                return false;
            }

            theWindowsManager.offsetCurrentPosition(0, WINDOW_PADDING);

            /********************************/
            /* [PAGE 3] (6) Create dummy label */

            theWindowsManager.setCurrentClassName("STATIC");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD);

            if (0 == theWindowsManager.addWindow("\"eNode\" flags:", RECT_TABS_X2, WINDOW_HEIGHT, nullptr, nullptr, 0x01))
            {
                return false;
            }

            /********************************/
            /* [PAGE 3] (7 – 38) Create checkboxes */

            theWindowsManager.setCurrentClassName("BUTTON");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | BS_AUTOCHECKBOX);

            for (a = 0; a < 32; a++)
            {
                b = (0x01 << a);
                sprintf_s(bufor, 64, "(0x%08X) %s", b, theNodeFlagNames[a]);

                if (0 == theWindowsManager.addWindow(bufor, RECT_TABS_X2, WINDOW_HEIGHT, buttonFunc_NodeFlags, (void*)b, 0x01))
                {
                    return false;
                }
            }

            /********************************/
            /* [PAGE 4] */

            theWindowsManager.addPage("Object movement");

            theWindowsManager.setCurrentPosition(RECT_TABS_X1, TOP_OFFSET);

            if (false == theWindowsManager.createObjectMovementWindows())
            {
                return false;
            }

            /********************************/
            /* [PAGE 4] Create buttons */

            theWindowsManager.setCurrentClassName("BUTTON");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | BS_DEFPUSHBUTTON);

            theWindowsManager.setCurrentPadding(WINDOW_PADDING_SMALL, WINDOW_PADDING_SMALL);

            a = (RECT_TABS_X2 / 2) - (WINDOW_PADDING / 2);

            if (0 == theWindowsManager.addWindow("Reset", a, WINDOW_HEIGHT, buttonFunc_NodesListMisc, (void*)NODES_EDITING_RESET_TRANSFORM, 0))
            {
                return false;
            }

            if (0 == theWindowsManager.addWindow("Apply", a, WINDOW_HEIGHT, buttonFunc_NodesListMisc, (void*)NODES_EDITING_APPLY_TRANSFORM, 0x01))
            {
                return false;
            }

            theWindowsManager.setCurrentPadding(0, 0);
            theWindowsManager.offsetCurrentPosition(0, WINDOW_PADDING_SMALL);

            /********************************/
            /* WinApi creation completed. :) */

            theWindowsManager.switchPage(0);

            ShowWindow(main_window, SW_SHOW);

            return true;
        }


        ////////////////////////////////////////////////////////////////
        // Close windows and unload OpenGL
        ////////////////////////////////////////////////////////////////
        void closeWindows()
        {
            /* Disable OpenGL */

            wglMakeCurrent(NULL, NULL);

            if (NULL != openGL_DeviceContext)
            {
                wglDeleteContext(openGL_RenderingContext);

                ReleaseDC(theWindowsManager.getMainWindow(), openGL_DeviceContext);
            }

            /* Close/Unload others */

            if (NULL != myWindowLogo)
            {
                FreeResource(myWindowLogo);
            }

            if (NULL != myWindowFont)
            {
                DeleteObject(myWindowFont);
            }
        }


        ////////////////////////////////////////////////////////////////
        // Window loop: Is main window still open?
        ////////////////////////////////////////////////////////////////
        bool isAppRunning()
        {
            bool stillActive = true;
            MSG message = {0};

            while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
            {
                if (WM_QUIT == message.message)
                {
                    stillActive = false;
                }

                TranslateMessage(&message);
                DispatchMessage(&message);
            }

            return stillActive;
        }

    }
}
