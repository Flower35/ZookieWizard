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

        static const int32_t nodesList_ButtonsCount = 16;
        static const int32_t nodesList_ActionsCount = 5;
        int32_t nodesList_CurrentAction;
        static HWND nodesList_Windows[1 + nodesList_ButtonsCount];
        static uint8_t nodesList_ActionIds[nodesList_ButtonsCount];

        static const char* nodesList_ActionNames[nodesList_ActionsCount] =
        {
            "Browsing the Archive", "Moving Nodes", "Deleting Nodes", "Modifying 3D meshes", "Parsing instructions"
        };


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
                GetWindowText((HWND)lParam, (LPSTR)custom_param, LARGE_BUFFER_SIZE);
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

        void func_NodesListSwitchPage(int32_t direction)
        {
            char bufor[32];

            if (direction < 0)
            {
                nodesList_CurrentAction--;
            }
            else if (direction > 0)
            {
                nodesList_CurrentAction++;
            }

            if (nodesList_CurrentAction < 0)
            {
                nodesList_CurrentAction = 0;
            }
            else if (nodesList_CurrentAction >= nodesList_ActionsCount)
            {
                nodesList_CurrentAction = nodesList_ActionsCount - 1;
            }

            for (int32_t i = 0; i < nodesList_ButtonsCount; i++)
            {
                bool show_button = (nodesList_CurrentAction == nodesList_ActionIds[i]);

                ShowWindow(nodesList_Windows[1 + i], show_button ? SW_SHOW : SW_HIDE);
            }

            sprintf_s(bufor, 32, "Actions: %s", nodesList_ActionNames[nodesList_CurrentAction]);

            SetWindowText(nodesList_Windows[0], bufor);
        }

        void menuFunc_NodesListEnter()
        {
            func_NodesListSwitchPage(0);
        }

        void buttonFunc_NodesListSwitchPage(WPARAM wParam, LPARAM lParam, void* custom_param)
        {
            if (BN_CLICKED == HIWORD(wParam))
            {
                func_NodesListSwitchPage((int32_t)custom_param);
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
                else if (3 == (int32_t)custom_param)
                {
                    changeNodesWithTxt();
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
            int32_t id = (int32_t)custom_param;
            double new_speed;
            char bufor[8];

            if ((EN_CHANGE == HIWORD(wParam)) && (id >= 0) && (id < 2))
            {
                GetWindowText((HWND)lParam, bufor, 8);

                new_speed = std::atof(bufor);

                if (new_speed > 0)
                {
                    testCamera.speed[id] = new_speed;
                }
                else
                {
                    testCamera.speed[id] = TEST_CAMERA_DEFAULT_SPEED;
                }
            }
        }

        void buttonFunc_RenderFlags(WPARAM wParam, LPARAM lParam, void* custom_param)
        {
            if (BN_CLICKED == HIWORD(wParam))
            {
                int32_t index = (int32_t)custom_param;

                if (BST_CHECKED == SendMessage((HWND)lParam, BM_GETCHECK, 0, 0))
                {
                    if (0 == index)
                    {
                        renderingLimitFramerate = true;
                    }
                    else if (1 == index)
                    {
                        glPolygonMode(GL_FRONT, GL_LINE);
                    }
                    else if ((index >= (2 + 0)) && (index < (2 + drawFlags::DRAW_FLAG_COUNT)))
                    {
                        myDrawFlags |= (1 << (index - 2));
                    }
                }
                else
                {
                    if (0 == index)
                    {
                        renderingLimitFramerate = false;
                    }
                    else if (1 == index)
                    {
                        glPolygonMode(GL_FRONT, GL_FILL);
                    }
                    else if ((index >= (2 + 0)) && (index < (2 + drawFlags::DRAW_FLAG_COUNT)))
                    {
                        myDrawFlags &= (~ (1 << (index - 2)));
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
            char bufor[LARGE_BUFFER_SIZE];

            if ((false == updatingNodeName) && (EN_CHANGE == HIWORD(wParam)))
            {
                GetWindowText((HWND)lParam, bufor, LARGE_BUFFER_SIZE);

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
        // WindowsManager: overriden ListBox key dispatch
        ////////////////////////////////////////////////////////////////
        LRESULT WindowsManager::overriddenListboxKeyDispatch(HWND listbox_window, uint16_t keycode) const
        {
            int32_t a;

            if (getSpecificWindow(2, (-1)) == listbox_window)
            {
                switch (keycode)
                {
                    case VK_RETURN:
                    {
                        a = SendMessage(listbox_window, LB_GETCURSEL, 0, 0);

                        a = (LB_ERR == a) ? NODES_LISTBOX_UPDATE_CURRENT : a;

                        myARs[0].changeSelectedObject(a, nullptr);

                        return (-2);
                    }

                    case VK_BACK:
                    {
                        myARs[0].changeSelectedObject(NODES_LISTBOX_PARENT, nullptr);

                        return (-2);
                    }
                }
            }

            /* Default action */
            return (-1);
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
        // Update EditBoxes with specific text
        // (0) "MediaDir"
        // (1) "DenisDir"
        // (2) "LevelName"
        // (3) "CameraMovementSpeed"
        // (4) "CameraRotationSpeed"
        ////////////////////////////////////////////////////////////////
        void updateArSettingsText(int32_t id, const char* new_text)
        {
            HWND dummy_window;
            int32_t page_id, window_id;

            switch (id)
            {
                case 0: // "MediaDir"
                {
                    page_id = 1;
                    window_id = 1;
                    break;
                }

                case 1: // "DenisDir"
                {
                    page_id = 1;
                    window_id = 3;
                    break;
                }

                case 2: // "LevelName"
                {
                    page_id = 1;
                    window_id = 5;
                    break;
                }

                case 3: // "CameraMovementSpeed"
                {
                    page_id = 0;
                    window_id = 20;
                    break;
                }

                case 4: // "CameraRotationSpeed"
                {
                    page_id = 0;
                    window_id = 21;
                    break;
                }

                default:
                {
                    return;
                }
            }

            dummy_window = theWindowsManager.getSpecificWindow(page_id, window_id);

            if (NULL != dummy_window)
            {
                SetWindowText(dummy_window, new_text);
            }
        }


        ////////////////////////////////////////////////////////////////
        // Create windows
        ////////////////////////////////////////////////////////////////
        bool createWindows(HINSTANCE hInstance)
        {
            int32_t a, b, x, y;
            char bufor[64];
            HMENU menu_bar, test_menu;
            HWND main_window, scroll_window, dummy_window;

            const int WINDOW_HEIGHT = 24;
            const int NODES_BUTTON_HEIGHT = (int)(2.25 * WINDOW_HEIGHT);
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
            AppendMenu(test_menu, MF_STRING, (UINT_PTR)theWindowsManager.addStaticFunction(menuFunc_SetGameVersion, (void*)GAME_VERSION_KAO2_PL_PC), "&1) Kangurek Kao: Runda 2 [PL, Retail] [PC]");
            AppendMenu(test_menu, MF_STRING, (UINT_PTR)theWindowsManager.addStaticFunction(menuFunc_SetGameVersion, (void*)GAME_VERSION_KAO2_EUR_PC), "&2) Kao the Kangaroo: Round 2 [EU, Digital] [PC]");
            AppendMenu(test_menu, MF_STRING, (UINT_PTR)theWindowsManager.addStaticFunction(menuFunc_SetGameVersion, (void*)GAME_VERSION_KAO_TW_PC), "&3) Kao: Tajemnica Wulkanu [PC]");
            AppendMenu(test_menu, MF_STRING, (UINT_PTR)theWindowsManager.addStaticFunction(menuFunc_SetGameVersion, (void*)GAME_VERSION_ASTERIX_XXL2_PSP), "&4) Asterix && Obelix XXL 2: Mission Wifix [PSP]");
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

            theWindowsManager.addPage("Render settings", nullptr, nullptr);

            theWindowsManager.setCurrentPosition(RECT_TABS_X1, TOP_OFFSET);
            theWindowsManager.updateReturningPosition();

            /********************************/
            /* [PAGE 0] (0 – 16) Create checkboxes */

            theWindowsManager.setCurrentClassName("BUTTON");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | BS_AUTOCHECKBOX);

            const int RENDER_FLAGS_COUNT = 2 + drawFlags::DRAW_FLAG_COUNT;

            const char* render_flags_names[RENDER_FLAGS_COUNT] =
            {
                "Limit rendering framerate (30 fps)",
                "WIREFRAME MODE",

                "Outline SELECTED NODES",
                "Render INVISIBLE MESHES",
                "DrawPass #1",
                "DrawPass #2",
                "DrawPass #3",
                "Render with TEXTURES",
                "Render with MATERIAL BLENDING",
                "Render with FRUSTUM TESTING",
                "Render with VERTEX COLORS",
                "Render with DYNAMIC LIGHTS",
                "Update ANIMATIONS",
                "Objects: BOX ZONES",
                "Objects: PROXIES",
                "Objects: COLLISION",
                "Objects: SPECIAL HELPERS"
            };

            for (a = 0; a < RENDER_FLAGS_COUNT; a++)
            {
                if (0 == (dummy_window = theWindowsManager.addWindow(render_flags_names[a], RECT_TABS_X2, WINDOW_HEIGHT, buttonFunc_RenderFlags, (void*)a, 0x01)))
                {
                    return false;
                }

                switch (a)
                {
                    case (2 + 2): // "DrawPass #1"
                    case (2 + 3): // "DrawPass #2"
                    case (2 + 5): // "Render with TEXTURES"
                    case (2 + 7): // "Render with FRUSTUM TESTING"
                    {
                        SendMessage(dummy_window,BM_SETCHECK, BST_CHECKED, 0);
                        myDrawFlags |= (1 << (a - 2));

                        break;
                    }
                }
            }

            theWindowsManager.offsetCurrentPosition(0, WINDOW_PADDING);

            /********************************/
            /* [PAGE 0] (17) Create line decoration */

            theWindowsManager.setCurrentClassName("STATIC");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | WS_VISIBLE | SS_ETCHEDHORZ);
            theWindowsManager.getCurrentPosition(nullptr, &y);
            theWindowsManager.setCurrentPosition(0, y);

            if (0 == theWindowsManager.addWindow("", RECT_LOGO_X2, 2, nullptr, 0, 0x01))
            {
                return false;
            }

            theWindowsManager.offsetCurrentPosition(0, (WINDOW_PADDING_SMALL - 2));

            /********************************/
            /* [PAGE 0] (18) Create button */

            theWindowsManager.setCurrentClassName("BUTTON");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | BS_DEFPUSHBUTTON);

            if (0 == theWindowsManager.addWindow("Reset Camera", RECT_TABS_X2, WINDOW_HEIGHT, buttonFunc_CameraReset, nullptr, 0x01))
            {
                return false;
            }

            theWindowsManager.offsetCurrentPosition(0, WINDOW_PADDING);

            /********************************/
            /* [PAGE 0] (19) Create dummy label */

            theWindowsManager.setCurrentClassName("STATIC");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD);

            if (0 == theWindowsManager.addWindow("Camera movement and rotation speed:", RECT_TABS_X2, WINDOW_HEIGHT, nullptr, nullptr, 0x01))
            {
                return false;
            }

            /********************************/
            /* [PAGE 0] (20-21) Create editboxes */

            theWindowsManager.setCurrentClassName("EDIT");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | ES_AUTOHSCROLL);

            a = (RECT_TABS_X2 / 2) - (WINDOW_PADDING / 2);

            theWindowsManager.addEdgesToNextWindow();
            if (0 == theWindowsManager.addWindow(TEST_CAMERA_DEFAULT_SPEED_TEXT, a, WINDOW_HEIGHT, buttonFunc_CameraSpeed, (void*)0, 0))
            {
                return false;
            }

            theWindowsManager.offsetCurrentPosition(WINDOW_PADDING, 0);

            theWindowsManager.addEdgesToNextWindow();
            if (0 == theWindowsManager.addWindow(TEST_CAMERA_DEFAULT_SPEED_TEXT, a, WINDOW_HEIGHT, buttonFunc_CameraSpeed, (void*)1, 0x01))
            {
                return false;
            }

            theWindowsManager.offsetCurrentPosition(0, WINDOW_PADDING);

            /********************************/
            /* [PAGE 0] (22) Create line decoration */

            theWindowsManager.setCurrentClassName("STATIC");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | WS_VISIBLE | SS_ETCHEDHORZ);
            theWindowsManager.getCurrentPosition(nullptr, &y);
            theWindowsManager.setCurrentPosition(0, y);

            if (0 == theWindowsManager.addWindow("", RECT_LOGO_X2, 2, nullptr, 0, 0x01))
            {
                return false;
            }

            theWindowsManager.offsetCurrentPosition(0, (WINDOW_PADDING_SMALL - 2));

            /********************************/
            /* [PAGE 0] (23) Create dummy label */

            theWindowsManager.setCurrentClassName("STATIC");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD);

            if (0 == theWindowsManager.addWindow("Animation ID", RECT_TABS_X2, WINDOW_HEIGHT, nullptr, nullptr, 0x01))
            {
                return false;
            }

            /********************************/
            /* [PAGE 0] (24) Create editbox */

            theWindowsManager.setCurrentClassName("EDIT");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | ES_AUTOHSCROLL);

            theWindowsManager.addEdgesToNextWindow();
            if (0 == theWindowsManager.addWindow("0", RECT_TABS_X2, WINDOW_HEIGHT, buttonFunc_Anim, (void*)0, 0x01))
            {
                return false;
            }

            theWindowsManager.offsetCurrentPosition(0, WINDOW_PADDING);

            /********************************/
            /* [PAGE 0] (25) Create button */

            theWindowsManager.setCurrentClassName("BUTTON");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | BS_DEFPUSHBUTTON);

            if (0 == theWindowsManager.addWindow("Reset Timer", RECT_TABS_X2, WINDOW_HEIGHT, buttonFunc_ResetTimer, nullptr, 0x01))
            {
                return false;
            }

            theWindowsManager.offsetCurrentPosition(0, WINDOW_PADDING);

            /********************************/
            /* [PAGE 0] (26) Create dummy label */

            theWindowsManager.setCurrentClassName("STATIC");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD);

            if (0 == theWindowsManager.addWindow("Frames per second", RECT_TABS_X2, WINDOW_HEIGHT, nullptr, nullptr, 0x01))
            {
                return false;
            }

            /********************************/
            /* [PAGE 0] (27) Create editbox */

            theWindowsManager.setCurrentClassName("EDIT");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | ES_AUTOHSCROLL);

            theWindowsManager.addEdgesToNextWindow();
            if (0 == theWindowsManager.addWindow(ANIMATION_FRAMERATE_DEFAULT_TEXT, RECT_TABS_X2, WINDOW_HEIGHT, buttonFunc_Anim, (void*)1, 0x01))
            {
                return false;
            }

            theWindowsManager.offsetCurrentPosition(0, WINDOW_PADDING);

            /********************************/
            /* [PAGE 0] (28) Create line decoration */

            theWindowsManager.setCurrentClassName("STATIC");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | WS_VISIBLE | SS_ETCHEDHORZ);
            theWindowsManager.getCurrentPosition(nullptr, &y);
            theWindowsManager.setCurrentPosition(0, y);

            if (0 == theWindowsManager.addWindow("", RECT_LOGO_X2, 2, nullptr, 0, 0x01))
            {
                return false;
            }

            theWindowsManager.offsetCurrentPosition(0, (WINDOW_PADDING_SMALL - 2));

            /********************************/
            /* [PAGE 0] (29) Create dummy label */

            theWindowsManager.setCurrentClassName("STATIC");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD);

            if (0 == theWindowsManager.addWindow(WELCOME_MESSAGE, RECT_TABS_X2, (5 * WINDOW_HEIGHT), nullptr, nullptr, 0))
            {
                return false;
            }

            /********************************/
            /* [PAGE 1] */

            theWindowsManager.addPage("theAR + Denis", nullptr, nullptr);

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

            if (0 == theWindowsManager.addWindow("Denis Level Name / New Scene Name\n / Last Ar Name:", RECT_TABS_X2, (2 * WINDOW_HEIGHT), nullptr, nullptr, 0x01))
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

            theWindowsManager.addPage("Nodes list", menuFunc_NodesListEnter, nullptr);

            theWindowsManager.setCurrentPosition(RECT_TABS_X1, TOP_OFFSET);

            /********************************/
            /* [PAGE 2] (0) Create dummy label */

            theWindowsManager.setCurrentClassName("STATIC");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD);

            if (0 == theWindowsManager.addWindow("( no archive loaded yet\n or the parent item is not a node )", RECT_TABS_X2, (4 * WINDOW_HEIGHT), nullptr, nullptr, 0x01))
            {
                return false;
            }

            /********************************/
            /* [PAGE 2] (1) Create line decoration */

            theWindowsManager.setCurrentStyleFlags(WS_CHILD | WS_VISIBLE | SS_ETCHEDHORZ);
            theWindowsManager.getCurrentPosition(nullptr, &y);
            theWindowsManager.setCurrentPosition(0, y);

            if (0 == theWindowsManager.addWindow("", RECT_LOGO_X2, 2, nullptr, 0, 0x01))
            {
                return false;
            }

            theWindowsManager.offsetCurrentPosition(0, (WINDOW_PADDING_SMALL - 2));

            /********************************/
            /* [PAGE 2] (2 – 4) Create action switching buttons */

            nodesList_CurrentAction = 0;

            theWindowsManager.setCurrentClassName("BUTTON");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | BS_DEFPUSHBUTTON);

            theWindowsManager.setCurrentPadding(WINDOW_PADDING_SMALL, WINDOW_PADDING_SMALL);

            if (0 == theWindowsManager.addWindow("<<", 24, 20, buttonFunc_NodesListSwitchPage, (void*)(-1), 0))
            {
                return false;
            }

            if (0 == theWindowsManager.addWindow(">>", 24, 20, buttonFunc_NodesListSwitchPage, (void*)(1), 0))
            {
                return false;
            }

            theWindowsManager.setCurrentClassName("STATIC");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD);

            if (0 == (nodesList_Windows[0] = theWindowsManager.addWindow("", (RECT_TABS_X2 - 2 * (24 + WINDOW_PADDING_SMALL)), WINDOW_HEIGHT, nullptr, nullptr, 0x01)))
            {
                return false;
            }

            theWindowsManager.getCurrentPosition(&x, &y);

            /********************************/
            /* [PAGE 2] (5 – 20) Create buttons */

            theWindowsManager.setCurrentClassName("BUTTON");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | BS_DEFPUSHBUTTON | BS_MULTILINE);

            a = (RECT_TABS_X2 / 2) - (WINDOW_PADDING / 2);

            theWindowsManager.setCurrentPosition(x, y);
            nodesList_ActionIds[0] = 0;
            nodesList_ActionIds[1] = 0;
            nodesList_ActionIds[2] = 0;

            if (0 == (nodesList_Windows[1 + 0] = theWindowsManager.addWindow("^ Back to the\nArchive Root", a, NODES_BUTTON_HEIGHT, buttonFunc_NodesListMisc, (void*)NODES_LISTBOX_ROOT, 0)))
            {
                return false;
            }

            if (0 == (nodesList_Windows[1 + 1] = theWindowsManager.addWindow("^ Back to the\nParent Node", a, NODES_BUTTON_HEIGHT, buttonFunc_NodesListMisc, (void*)NODES_LISTBOX_PARENT, 0x01)))
            {
                return false;
            }

            if (0 == (nodesList_Windows[1 + 2] = theWindowsManager.addWindow("Center the Camera on the Current Node", a, NODES_BUTTON_HEIGHT, buttonFunc_NodesListMisc, (void*)NODES_LISTBOX_CENTER_CAMERA, 0)))
            {
                return false;
            }

            theWindowsManager.setCurrentPosition(x, y);
            nodesList_ActionIds[3] = 1;
            nodesList_ActionIds[4] = 1;
            nodesList_ActionIds[5] = 1;
            nodesList_ActionIds[6] = 1;

            if (0 == (nodesList_Windows[1 + 3] = theWindowsManager.addWindow("Move Higlighted Node UP", a, NODES_BUTTON_HEIGHT, buttonFunc_NodesListMisc, (void*)NODES_LISTBOX_MOVE_UP, 0)))
            {
                return false;
            }

            if (0 == (nodesList_Windows[1 + 4] = theWindowsManager.addWindow("Move Higlighted Node DOWN", a, NODES_BUTTON_HEIGHT, buttonFunc_NodesListMisc, (void*)NODES_LISTBOX_MOVE_DOWN, 0x01)))
            {
                return false;
            }

            if (0 == (nodesList_Windows[1 + 5] = theWindowsManager.addWindow("Highlighted Node\nOUTSIDE the Current Group", a, NODES_BUTTON_HEIGHT, buttonFunc_NodesListMisc, (void*)NODES_LISTBOX_MOVE_OUT, 0)))
            {
                return false;
            }

            if (0 == (nodesList_Windows[1 + 6] = theWindowsManager.addWindow("Highlighted Node\nINTO the Group entry ontop", a, NODES_BUTTON_HEIGHT, buttonFunc_NodesListMisc, (void*)NODES_LISTBOX_MOVE_IN, 0x01)))
            {
                return false;
            }

            theWindowsManager.setCurrentPosition(x, y);
            nodesList_ActionIds[7] = 2;
            nodesList_ActionIds[8] = 2;
            nodesList_ActionIds[9] = 2;

            if (0 == (nodesList_Windows[1 + 7] = theWindowsManager.addWindow("Delete Current Node", a, NODES_BUTTON_HEIGHT, buttonFunc_NodesListMisc, (void*)NODES_LISTBOX_DELETE_CURRENT, 0x01)))
            {
                return false;
            }

            if (0 == (nodesList_Windows[1 + 8] = theWindowsManager.addWindow("Delete All Children from the Current Group", a, NODES_BUTTON_HEIGHT, buttonFunc_NodesListMisc, (void*)NODES_LISTBOX_DELETE_CHILDREN, 0)))
            {
                return false;
            }

            if (0 == (nodesList_Windows[1 + 9] = theWindowsManager.addWindow("Delete\nHighlighted Node\n(from the list)", a, NODES_BUTTON_HEIGHT, buttonFunc_NodesListMisc, (void*)NODES_LISTBOX_DELETE_SELECTED, 0x01)))
            {
                return false;
            }

            theWindowsManager.setCurrentPosition(x, y);
            nodesList_ActionIds[10] = 3;
            nodesList_ActionIds[11] = 3;
            nodesList_ActionIds[12] = 3;
            nodesList_ActionIds[13] = 3;

            if (0 == (nodesList_Windows[1 + 10] = theWindowsManager.addWindow("Export 3D Meshes to Wavefront OBJ", a, NODES_BUTTON_HEIGHT, buttonFunc_NodesListObj, (void*)0, 0)))
            {
                return false;
            }

            if (0 == (nodesList_Windows[1 + 11] = theWindowsManager.addWindow("Import 3D Meshes from Wavefront OBJ", a, NODES_BUTTON_HEIGHT, buttonFunc_NodesListObj, (void*)1, 0x01)))
            {
                return false;
            }

            if (0 == (nodesList_Windows[1 + 12] = theWindowsManager.addWindow("Rebuild Collision Data", a, NODES_BUTTON_HEIGHT, buttonFunc_NodesListMisc, (void*)NODES_LISTBOX_COLLISION_REBUILD, 0)))
            {
                return false;
            }

            if (0 == (nodesList_Windows[1 + 13] = theWindowsManager.addWindow("Clear Collision Data", a, NODES_BUTTON_HEIGHT, buttonFunc_NodesListMisc, (void*)NODES_LISTBOX_COLLISION_CLEAR, 0x01)))
            {
                return false;
            }

            theWindowsManager.setCurrentPosition(x, y);
            nodesList_ActionIds[14] = 4;
            nodesList_ActionIds[15] = 4;

            if (0 == (nodesList_Windows[1 + 14] = theWindowsManager.addWindow("Import Nodes from a TXT file", a, NODES_BUTTON_HEIGHT, buttonFunc_NodesListObj, (void*)2, 0)))
            {
                return false;
            }

            if (0 == (nodesList_Windows[1 + 15] = theWindowsManager.addWindow("Change Nodes with a TXT file", a, NODES_BUTTON_HEIGHT, buttonFunc_NodesListObj, (void*)3, 0x01)))
            {
                return false;
            }

            theWindowsManager.setCurrentPosition(x, (y + 2 * (NODES_BUTTON_HEIGHT + WINDOW_PADDING_SMALL)));
            theWindowsManager.setCurrentPadding(0, 0);
            theWindowsManager.offsetCurrentPosition(0, WINDOW_PADDING_SMALL);

            /********************************/
            /* [PAGE 2] (21) Create listbox */

            theWindowsManager.setCurrentClassName("LISTBOX");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | WS_HSCROLL | WS_VSCROLL | LBS_DISABLENOSCROLL | LBS_HASSTRINGS | LBS_NOTIFY | LBS_WANTKEYBOARDINPUT);

            theWindowsManager.addEdgesToNextWindow();
            if (0 == (dummy_window = theWindowsManager.addWindow("", RECT_TABS_X2, 384, buttonFunc_NodesListChild, nullptr, 0x01)))
            {
                return false;
            }

            SendMessage(dummy_window, LB_SETHORIZONTALEXTENT, (WPARAM)512, 0);

            /********************************/
            /* [PAGE 3] */

            theWindowsManager.addPage("Node editing", nullptr, nullptr);

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

            if (false == materialsManager_AddWindows())
            {
                return false;
            }

            /********************************/
            /* [PAGE 5] */

            theWindowsManager.addPage("Object movement", nullptr, nullptr);

            theWindowsManager.setCurrentPosition(RECT_TABS_X1, TOP_OFFSET);

            if (false == theWindowsManager.createObjectMovementWindows())
            {
                return false;
            }

            /********************************/
            /* [PAGE 5] Create line decoration */

            theWindowsManager.setCurrentClassName("STATIC");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | WS_VISIBLE | SS_ETCHEDHORZ);
            theWindowsManager.getCurrentPosition(nullptr, &y);
            theWindowsManager.setCurrentPosition(0, y);

            if (0 == theWindowsManager.addWindow("", RECT_LOGO_X2, 2, nullptr, 0, 0x01))
            {
                return false;
            }

            theWindowsManager.offsetCurrentPosition(0, (WINDOW_PADDING_SMALL - 2));

            /********************************/
            /* [PAGE 0] (18) Create dummy labels */

            theWindowsManager.setCurrentClassName("STATIC");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD);

            a = (RECT_TABS_X2 / 2) - (WINDOW_PADDING / 2);

            if (0 == theWindowsManager.addWindow("PREVIEW", a, WINDOW_HEIGHT, nullptr, nullptr, 0x03))
            {
                return false;
            }

            theWindowsManager.offsetCurrentPosition(0, WINDOW_PADDING_SMALL);

            if (0 == theWindowsManager.addWindow("Position [X Y Z]", a, WINDOW_HEIGHT, nullptr, nullptr, 0))
            {
                return false;
            }

            theWindowsManager.offsetCurrentPosition(WINDOW_PADDING, 0);

            if (0 == theWindowsManager.addWindow("Rotation [X Y Z]", a, WINDOW_HEIGHT, nullptr, nullptr, 0x01))
            {
                return false;
            }

            theWindowsManager.getCurrentPosition(&x, &y);

            theWindowsManager.offsetCurrentPosition(0, 3 * (WINDOW_HEIGHT + WINDOW_PADDING_SMALL));

            if (0 == theWindowsManager.addWindow("Scale", a, WINDOW_HEIGHT, nullptr, nullptr, 0x02))
            {
                return false;
            }

            /********************************/
            /* [PAGE 5] (19-20) Create editboxes */

            theWindowsManager.setCurrentClassName("EDIT");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | ES_AUTOHSCROLL);

            theWindowsManager.setCurrentPadding(WINDOW_PADDING, WINDOW_PADDING_SMALL);

            theWindowsManager.setCurrentPosition(x, y);

            for (b = 0; b < 3; b++)
            {
                theWindowsManager.addEdgesToNextWindow();
                if (0 == theWindowsManager.addWindow("", a, WINDOW_HEIGHT, nullptr, nullptr, 0))
                {
                    return false;
                }

                theWindowsManager.addEdgesToNextWindow();
                if (0 == theWindowsManager.addWindow("", a, WINDOW_HEIGHT, nullptr, nullptr, 0x01))
                {
                    return false;
                }
            }

            theWindowsManager.offsetCurrentPosition(0, WINDOW_HEIGHT);

            theWindowsManager.addEdgesToNextWindow();
            if (0 == theWindowsManager.addWindow("", a, WINDOW_HEIGHT, nullptr, nullptr, 0x03))
            {
                return false;
            }

            theWindowsManager.offsetCurrentPosition(0, WINDOW_PADDING);

            theWindowsManager.setCurrentPadding(0, 0);

            /********************************/
            /* [PAGE 0] (21) Create line decoration */

            theWindowsManager.setCurrentClassName("STATIC");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | WS_VISIBLE | SS_ETCHEDHORZ);
            theWindowsManager.getCurrentPosition(nullptr, &y);
            theWindowsManager.setCurrentPosition(0, y);


            if (0 == theWindowsManager.addWindow("", RECT_LOGO_X2, 2, nullptr, 0, 0x01))
            {
                return false;
            }

            theWindowsManager.offsetCurrentPosition(0, (WINDOW_PADDING_SMALL - 2));

            /********************************/
            /* [PAGE 5] Create buttons */

            theWindowsManager.setCurrentClassName("BUTTON");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | BS_DEFPUSHBUTTON);

            theWindowsManager.setCurrentPadding(WINDOW_PADDING, WINDOW_PADDING_SMALL);

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
