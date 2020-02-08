#include <ZookieWizard/ZookieWizard.h>

#include <kao2ar/Archive.h>

namespace ZookieWizard
{
    namespace GUI
    {
        ////////////////////////////////////////////////////////////////
        // Initialize variables
        ////////////////////////////////////////////////////////////////

        const char* WINDOW_CLASS_NAME_1 = "ZookieWizard::GUI::WindowClassOne";
        const char* WINDOW_CLASS_NAME_2 = "ZookieWizard::GUI::WindowClassTwo";

        HWND myWindowsGroupMain[3] = {NULL};
        HWND myWindowsGroupAr[8] = {NULL};
        HWND myWindowsGroupDenis[4] = {NULL};
        HWND myWindowsGroupAnimation[5] = {NULL};
        HWND myWindowsGroupNodes[9] = {NULL};

        int32_t myWindowsCurrentGroup = 1;


        ////////////////////////////////////////////////////////////////
        // Create windows
        ////////////////////////////////////////////////////////////////
        bool createWindows(HINSTANCE hInstance)
        {
            int32_t i;
            HWND test_hwnd;

            WNDCLASSEX window_classes[2];

            const int WINDOW_HEIGHT = 24;
            const int WINDOW_PADDING = 16;

            /********************************/
            /* Register window classes */

            ZeroMemory(&(window_classes[0]), sizeof(WNDCLASSEX));
            window_classes[0].cbSize = sizeof(WNDCLASSEX);
            window_classes[0].hbrBackground = (HBRUSH)(COLOR_BTNFACE +1);
            window_classes[0].hCursor = LoadCursor(hInstance, IDC_ARROW);
            window_classes[0].hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDM_ICON));
            window_classes[0].hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDM_ICON));
            window_classes[0].hInstance = hInstance;
            window_classes[0].lpfnWndProc = procedureOfMainWindow;
            window_classes[0].lpszClassName = WINDOW_CLASS_NAME_1;
            window_classes[0].lpszMenuName = MAKEINTRESOURCE(IDM_MENU);
            window_classes[0].style = (CS_OWNDC | CS_VREDRAW | CS_HREDRAW);

            ZeroMemory(&(window_classes[1]), sizeof(WNDCLASSEX));
            window_classes[1].cbSize = sizeof(WNDCLASSEX);
            window_classes[1].hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
            window_classes[1].hInstance = hInstance;
            window_classes[1].lpfnWndProc = procedureOfRenderWindow;
            window_classes[1].lpszClassName = WINDOW_CLASS_NAME_2;
            window_classes[1].style = (CS_OWNDC | CS_VREDRAW | CS_HREDRAW);

            if ((!RegisterClassEx(&(window_classes[0]))) || (!RegisterClassEx(&(window_classes[1]))))
            {
                return false;
            }

            /********************************/
            /* Load fonts and resources */

            myWindowsLogo = LoadBitmap(hInstance, MAKEINTRESOURCE(IDM_BITMAP));

            if (NULL == myWindowsLogo)
            {
                return false;
            }

            myWindowsFont = CreateFont
            (
                16,
                0,
                0,
                0,
                FW_NORMAL,
                FALSE,
                FALSE,
                FALSE,
                DEFAULT_CHARSET,
                OUT_DEFAULT_PRECIS,
                CLIP_DEFAULT_PRECIS,
                DEFAULT_QUALITY,
                (DEFAULT_PITCH | FF_SWISS),
                "Verdana"
            );

            if (NULL == myWindowsFont)
            {
                return false;
            }

            /********************************/
            /* [GROUP 0/4] Create main window */

            const DWORD pos_x = ((GetSystemMetrics(SM_CXSCREEN) - RECT_WINDOW_X) / 2);
            const DWORD pos_y = ((GetSystemMetrics(SM_CYSCREEN) - RECT_WINDOW_Y) / 2);

            test_hwnd = CreateWindow
            (
                WINDOW_CLASS_NAME_1,
                "Zookie Wizard",
                (WS_OVERLAPPEDWINDOW),
                pos_x,
                pos_y,
                RECT_WINDOW_X,
                RECT_WINDOW_Y,
                NULL,
                NULL,
                hInstance,
                NULL
            );

            if (0 == test_hwnd)
            {
                return false;
            }

            myWindowsGroupMain[0] = test_hwnd;

            /********************************/
            /* [GROUP 0/4] Create renderer window */

            test_hwnd = CreateWindow
            (
                WINDOW_CLASS_NAME_2,
                NULL,
                (WS_CHILD | WS_VISIBLE),
                RECT_RENDER_X1,
                RECT_RENDER_Y1,
                RECT_RENDER_X2,
                RECT_RENDER_Y2,
                myWindowsGroupMain[0],
                NULL,
                hInstance,
                NULL
            );

            if (0 == test_hwnd)
            {
                return false;
            }

            myWindowsGroupMain[1] = test_hwnd;

            /********************************/
            /* [GROUP 0/4] Create button (previous page) */

            test_hwnd = CreateWindow
            (
                "BUTTON",
                "<<",
                (WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON),
                RECT_TABS_X1 + (0 * 32) + (0 * WINDOW_PADDING),
                RECT_TABS_Y1 + (0 * WINDOW_HEIGHT) + (0 * WINDOW_PADDING),
                32,
                WINDOW_HEIGHT,
                myWindowsGroupMain[0],
                (HMENU)IDM_BUTTON_PAGE_PREV,
                hInstance,
                NULL
            );

            if (0 == test_hwnd)
            {
                return false;
            }

            SendMessage(test_hwnd, WM_SETFONT, (WPARAM)myWindowsFont, FALSE);

            /********************************/
            /* [GROUP 0/4] Create button (next page) */

            test_hwnd = CreateWindow
            (
                "BUTTON",
                ">>",
                (WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON),
                RECT_TABS_X1 + (1 * 32) + (1 * WINDOW_PADDING),
                RECT_TABS_Y1 + (0 * WINDOW_HEIGHT) + (0 * WINDOW_PADDING),
                32,
                WINDOW_HEIGHT,
                myWindowsGroupMain[0],
                (HMENU)IDM_BUTTON_PAGE_NEXT,
                hInstance,
                NULL
            );

            if (0 == test_hwnd)
            {
                return false;
            }

            SendMessage(test_hwnd, WM_SETFONT, (WPARAM)myWindowsFont, FALSE);

            /********************************/
            /* [GROUP 0/4] Create page label */

            test_hwnd = CreateWindow
            (
                "STATIC",
                "",
                (WS_CHILD | WS_VISIBLE),
                RECT_TABS_X1 + (2 * 32) + (2 * WINDOW_PADDING),
                RECT_TABS_Y1 + (0 * WINDOW_HEIGHT) + (0 * WINDOW_PADDING),
                160,
                WINDOW_HEIGHT,
                myWindowsGroupMain[0],
                NULL,
                hInstance,
                NULL
            );

            SendMessage(test_hwnd, WM_SETFONT, (WPARAM)myWindowsFont, FALSE);

            myWindowsGroupMain[2] = test_hwnd;

            /********************************/
            /* [GROUP 1/4] Create dummy label */

            test_hwnd = CreateWindow
            (
                "STATIC",
                "Working directory (\"/media/\"):",
                (WS_CHILD | WS_VISIBLE),
                RECT_TABS_X1,
                RECT_TABS_Y1 + (1 * WINDOW_HEIGHT) + (1 * WINDOW_PADDING),
                RECT_TABS_X2,
                WINDOW_HEIGHT,
                myWindowsGroupMain[0],
                NULL,
                hInstance,
                NULL
            );

            SendMessage(test_hwnd, WM_SETFONT, (WPARAM)myWindowsFont, FALSE);

            myWindowsGroupAr[0] = test_hwnd;

            /********************************/
            /* [GROUP 1/4] Create editbox window */

            test_hwnd = CreateWindowEx
            (
                WS_EX_CLIENTEDGE,
                "EDIT",
                NULL,
                (WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL),
                RECT_TABS_X1,
                RECT_TABS_Y1 + (2 * WINDOW_HEIGHT) + (1 * WINDOW_PADDING),
                RECT_TABS_X2,
                WINDOW_HEIGHT,
                myWindowsGroupMain[0],
                (HMENU)IDM_EDITBOX_MEDIADIR,
                hInstance,
                NULL
            );

            if (0 == test_hwnd)
            {
                return false;
            }

            SendMessage(test_hwnd, WM_SETFONT, (WPARAM)myWindowsFont, FALSE);

            myWindowsGroupAr[1] = test_hwnd;

            /********************************/
            /* [GROUP 1/4] Create button */

            test_hwnd = CreateWindow
            (
                "BUTTON",
                "Reset Camera",
                (WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON),
                RECT_TABS_X1,
                RECT_TABS_Y1 + (3 * WINDOW_HEIGHT) + (2 * WINDOW_PADDING),
                RECT_TABS_X2,
                WINDOW_HEIGHT,
                myWindowsGroupMain[0],
                (HMENU)IDM_BUTTON_RESET_CAMERA,
                hInstance,
                NULL
            );

            if (0 == test_hwnd)
            {
                return false;
            }

            SendMessage(test_hwnd, WM_SETFONT, (WPARAM)myWindowsFont, FALSE);

            myWindowsGroupAr[2] = test_hwnd;

            /********************************/
            /* [GROUP 1/4] Create checkboxes */

            const int checkboxes_ids[drawFlags::DRAW_FLAGS_COUNT] =
            {
                IDM_CHECKBOX_RENDER_INVISIBLE,
                IDM_CHECKBOX_RENDER_BOXZONES,
                IDM_CHECKBOX_RENDER_PROXIES,
                IDM_CHECKBOX_RENDER_ANIMS
            };

            const char* checkboxes_names[drawFlags::DRAW_FLAGS_COUNT] =
            {
                "draw INVISIBLE MESHES",
                "draw BOX ZONES",
                "draw PROXIES",
                "update ANIMATIONS"
            };

            for (i = 0; i < drawFlags::DRAW_FLAGS_COUNT; i++)
            {
                test_hwnd = CreateWindow
                (
                    "BUTTON",
                    checkboxes_names[i],
                    (WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX),
                    RECT_TABS_X1,
                    RECT_TABS_Y1 + ((4 + i) * WINDOW_HEIGHT) + (3 * WINDOW_PADDING),
                    RECT_TABS_X2,
                    WINDOW_HEIGHT,
                    myWindowsGroupMain[0],
                    (HMENU)checkboxes_ids[i],
                    hInstance,
                    NULL
                );

                if (0 == test_hwnd)
                {
                    return false;
                }

                SendMessage(test_hwnd, WM_SETFONT, (WPARAM)myWindowsFont, FALSE);

                myWindowsGroupAr[3 + i] = test_hwnd;
            }

            /********************************/
            /* [GROUP 1/4] Create dummy label */

            test_hwnd = CreateWindow
            (
                "STATIC",
                "Camera movement:\n" \
                " - LMB for rotation\n" \
                " - RMB for strafing\n" \
                "\n" \
                "This project is in alpha stage.",
                (WS_CHILD | WS_VISIBLE),
                RECT_TABS_X1,
                RECT_TABS_Y1 + ((drawFlags::DRAW_FLAGS_COUNT + 4) * WINDOW_HEIGHT) + (4 * WINDOW_PADDING),
                RECT_TABS_X2,
                (5 * WINDOW_HEIGHT),
                myWindowsGroupMain[0],
                NULL,
                hInstance,
                NULL
            );

            SendMessage(test_hwnd, WM_SETFONT, (WPARAM)myWindowsFont, FALSE);

            myWindowsGroupAr[3 + drawFlags::DRAW_FLAGS_COUNT] = test_hwnd;

            /********************************/
            /* [GROUP 2/4] Create dummy label */

            test_hwnd = CreateWindow
            (
                "STATIC",
                "Denis game directory:",
                (WS_CHILD),
                RECT_TABS_X1,
                RECT_TABS_Y1 + (1 * WINDOW_HEIGHT) + (1 * WINDOW_PADDING),
                RECT_TABS_X2,
                WINDOW_HEIGHT,
                myWindowsGroupMain[0],
                NULL,
                hInstance,
                NULL
            );

            SendMessage(test_hwnd, WM_SETFONT, (WPARAM)myWindowsFont, FALSE);

            myWindowsGroupDenis[0] = test_hwnd;

            /********************************/
            /* [GROUP 2/4] Create editbox window */

            test_hwnd = CreateWindowEx
            (
                WS_EX_CLIENTEDGE,
                "EDIT",
                NULL,
                (WS_CHILD | ES_AUTOHSCROLL),
                RECT_TABS_X1,
                RECT_TABS_Y1 + (2 * WINDOW_HEIGHT) + (1 * WINDOW_PADDING),
                RECT_TABS_X2,
                WINDOW_HEIGHT,
                myWindowsGroupMain[0],
                (HMENU)IDM_EDITBOX_DENIS_DIR,
                hInstance,
                NULL
            );

            if (0 == test_hwnd)
            {
                return false;
            }

            SendMessage(test_hwnd, WM_SETFONT, (WPARAM)myWindowsFont, FALSE);

            myWindowsGroupDenis[1] = test_hwnd;


            /********************************/
            /* [GROUP 2/4] Create dummy label */

            test_hwnd = CreateWindow
            (
                "STATIC",
                "Which level do you want to load?",
                (WS_CHILD),
                RECT_TABS_X1,
                RECT_TABS_Y1 + (3 * WINDOW_HEIGHT) + (2 * WINDOW_PADDING),
                RECT_TABS_X2,
                WINDOW_HEIGHT,
                myWindowsGroupMain[0],
                NULL,
                hInstance,
                NULL
            );

            SendMessage(test_hwnd, WM_SETFONT, (WPARAM)myWindowsFont, FALSE);

            myWindowsGroupDenis[2] = test_hwnd;

            /********************************/
            /* [GROUP 2/4] Create editbox window */

            test_hwnd = CreateWindowEx
            (
                WS_EX_CLIENTEDGE,
                "EDIT",
                NULL,
                (WS_CHILD | ES_AUTOHSCROLL),
                RECT_TABS_X1,
                RECT_TABS_Y1 + (4 * WINDOW_HEIGHT) + (2 * WINDOW_PADDING),
                RECT_TABS_X2,
                WINDOW_HEIGHT,
                myWindowsGroupMain[0],
                (HMENU)IDM_EDITBOX_DENIS_LVL,
                hInstance,
                NULL
            );

            if (0 == test_hwnd)
            {
                return false;
            }

            SendMessage(test_hwnd, WM_SETFONT, (WPARAM)myWindowsFont, FALSE);

            myWindowsGroupDenis[3] = test_hwnd;

            /********************************/
            /* [GROUP 3/4] Create dummy label */

            test_hwnd = CreateWindow
            (
                "STATIC",
                "Animation ID",
                (WS_CHILD),
                RECT_TABS_X1,
                RECT_TABS_Y1 + (1 * WINDOW_HEIGHT) + (1 * WINDOW_PADDING),
                RECT_TABS_X2,
                WINDOW_HEIGHT,
                myWindowsGroupMain[0],
                NULL,
                hInstance,
                NULL
            );

            SendMessage(test_hwnd, WM_SETFONT, (WPARAM)myWindowsFont, FALSE);

            myWindowsGroupAnimation[0] = test_hwnd;

            /********************************/
            /* [GROUP 3/4] Create editbox window */

            test_hwnd = CreateWindowEx
            (
                WS_EX_CLIENTEDGE,
                "EDIT",
                "0",
                (WS_CHILD | ES_AUTOHSCROLL),
                RECT_TABS_X1,
                RECT_TABS_Y1 + (2 * WINDOW_HEIGHT) + (1 * WINDOW_PADDING),
                RECT_TABS_X2,
                WINDOW_HEIGHT,
                myWindowsGroupMain[0],
                (HMENU)IDM_EDITBOX_ANIM_ID,
                hInstance,
                NULL
            );

            if (0 == test_hwnd)
            {
                return false;
            }

            SendMessage(test_hwnd, WM_SETFONT, (WPARAM)myWindowsFont, FALSE);

            myWindowsGroupAnimation[1] = test_hwnd;

            /********************************/
            /* [GROUP 3/4] Create button */

            test_hwnd = CreateWindow
            (
                "BUTTON",
                "Reset Timer",
                (WS_CHILD | BS_DEFPUSHBUTTON),
                RECT_TABS_X1,
                RECT_TABS_Y1 + (3 * WINDOW_HEIGHT) + (2 * WINDOW_PADDING),
                RECT_TABS_X2,
                WINDOW_HEIGHT,
                myWindowsGroupMain[0],
                (HMENU)IDM_BUTTON_RESET_TIMER,
                hInstance,
                NULL
            );

            if (0 == test_hwnd)
            {
                return false;
            }

            SendMessage(test_hwnd, WM_SETFONT, (WPARAM)myWindowsFont, FALSE);

            myWindowsGroupAnimation[2] = test_hwnd;

            /********************************/
            /* [GROUP 3/4] Create dummy label */

            test_hwnd = CreateWindow
            (
                "STATIC",
                "Frames per second",
                (WS_CHILD),
                RECT_TABS_X1,
                RECT_TABS_Y1 + (4 * WINDOW_HEIGHT) + (3 * WINDOW_PADDING),
                RECT_TABS_X2,
                WINDOW_HEIGHT,
                myWindowsGroupMain[0],
                NULL,
                hInstance,
                NULL
            );

            SendMessage(test_hwnd, WM_SETFONT, (WPARAM)myWindowsFont, FALSE);

            myWindowsGroupAnimation[3] = test_hwnd;

            /********************************/
            /* [GROUP 3/4] Create editbox window */

            test_hwnd = CreateWindowEx
            (
                WS_EX_CLIENTEDGE,
                "EDIT",
                "1",
                (WS_CHILD | ES_AUTOHSCROLL),
                RECT_TABS_X1,
                RECT_TABS_Y1 + (5 * WINDOW_HEIGHT) + (3 * WINDOW_PADDING),
                RECT_TABS_X2,
                WINDOW_HEIGHT,
                myWindowsGroupMain[0],
                (HMENU)IDM_EDITBOX_ANIM_FPS,
                hInstance,
                NULL
            );

            if (0 == test_hwnd)
            {
                return false;
            }

            SendMessage(test_hwnd, WM_SETFONT, (WPARAM)myWindowsFont, FALSE);

            myWindowsGroupAnimation[4] = test_hwnd;

            /********************************/
            /* [GROUP 4/4] Create dummy label */

            test_hwnd = CreateWindow
            (
                "STATIC",
                "",
                (WS_CHILD),
                RECT_TABS_X1,
                RECT_TABS_Y1 + (1 * WINDOW_HEIGHT) + (1 * WINDOW_PADDING),
                RECT_TABS_X2,
                (2 * WINDOW_HEIGHT),
                myWindowsGroupMain[0],
                NULL,
                hInstance,
                NULL
            );

            SendMessage(test_hwnd, WM_SETFONT, (WPARAM)myWindowsFont, FALSE);

            myWindowsGroupNodes[0] = test_hwnd;

            /********************************/
            /* [GROUP 4/4] Create button */

            test_hwnd = CreateWindow
            (
                "BUTTON",
                "^ Archive Root",
                (WS_CHILD | BS_DEFPUSHBUTTON),
                RECT_TABS_X1,
                RECT_TABS_Y1 + (3 * WINDOW_HEIGHT) + (2 * WINDOW_PADDING),
                (RECT_TABS_X2 / 2) - (WINDOW_PADDING / 2),
                WINDOW_HEIGHT,
                myWindowsGroupMain[0],
                (HMENU)IDM_BUTTON_RESET_NODES,
                hInstance,
                NULL
            );

            if (0 == test_hwnd)
            {
                return false;
            }

            SendMessage(test_hwnd, WM_SETFONT, (WPARAM)myWindowsFont, FALSE);

            myWindowsGroupNodes[1] = test_hwnd;

            /********************************/
            /* [GROUP 4/4] Create button */

            test_hwnd = CreateWindow
            (
                "BUTTON",
                "^ Parent Node",
                (WS_CHILD | BS_DEFPUSHBUTTON),
                RECT_TABS_X1 + (RECT_TABS_X2 / 2) + (WINDOW_PADDING / 2),
                RECT_TABS_Y1 + (3 * WINDOW_HEIGHT) + (2 * WINDOW_PADDING),
                (RECT_TABS_X2 / 2) - (WINDOW_PADDING / 2),
                WINDOW_HEIGHT,
                myWindowsGroupMain[0],
                (HMENU)IDM_BUTTON_PARENT_NODE,
                hInstance,
                NULL
            );

            if (0 == test_hwnd)
            {
                return false;
            }

            SendMessage(test_hwnd, WM_SETFONT, (WPARAM)myWindowsFont, FALSE);

            myWindowsGroupNodes[2] = test_hwnd;

            /********************************/
            /* [GROUP 4/4] Create button */

            test_hwnd = CreateWindow
            (
                "BUTTON",
                "Toggle Node",
                (WS_CHILD | BS_DEFPUSHBUTTON),
                RECT_TABS_X1,
                RECT_TABS_Y1 + (4 * WINDOW_HEIGHT) + (3 * WINDOW_PADDING),
                (RECT_TABS_X2 / 2) - (WINDOW_PADDING / 2),
                WINDOW_HEIGHT,
                myWindowsGroupMain[0],
                (HMENU)IDM_BUTTON_TOGGLE_NODE,
                hInstance,
                NULL
            );

            if (0 == test_hwnd)
            {
                return false;
            }

            SendMessage(test_hwnd, WM_SETFONT, (WPARAM)myWindowsFont, FALSE);

            myWindowsGroupNodes[3] = test_hwnd;

            /********************************/
            /* [GROUP 4/4] Create button */

            test_hwnd = CreateWindow
            (
                "BUTTON",
                "Delete Node",
                (WS_CHILD | BS_DEFPUSHBUTTON),
                RECT_TABS_X1 + (RECT_TABS_X2 / 2) + (WINDOW_PADDING / 2),
                RECT_TABS_Y1 + (4 * WINDOW_HEIGHT) + (3 * WINDOW_PADDING),
                (RECT_TABS_X2 / 2) - (WINDOW_PADDING / 2),
                WINDOW_HEIGHT,
                myWindowsGroupMain[0],
                (HMENU)IDM_BUTTON_DELETE_NODE,
                hInstance,
                NULL
            );

            if (0 == test_hwnd)
            {
                return false;
            }

            SendMessage(test_hwnd, WM_SETFONT, (WPARAM)myWindowsFont, FALSE);

            myWindowsGroupNodes[4] = test_hwnd;

            /********************************/
            /* [GROUP 4/4] Create button */

            test_hwnd = CreateWindow
            (
                "BUTTON",
                "Export TriMesh",
                (WS_CHILD | BS_DEFPUSHBUTTON),
                RECT_TABS_X1,
                RECT_TABS_Y1 + (5 * WINDOW_HEIGHT) + (4 * WINDOW_PADDING),
                (RECT_TABS_X2 / 2) - (WINDOW_PADDING / 2),
                WINDOW_HEIGHT,
                myWindowsGroupMain[0],
                (HMENU)IDM_BUTTON_EXPORT_TRIMESH,
                hInstance,
                NULL
            );

            if (0 == test_hwnd)
            {
                return false;
            }

            SendMessage(test_hwnd, WM_SETFONT, (WPARAM)myWindowsFont, FALSE);

            myWindowsGroupNodes[5] = test_hwnd;

            /********************************/
            /* [GROUP 4/4] Create button */

            test_hwnd = CreateWindow
            (
                "BUTTON",
                "Import TriMesh",
                (WS_CHILD | BS_DEFPUSHBUTTON),
                RECT_TABS_X1 + (RECT_TABS_X2 / 2) + (WINDOW_PADDING / 2),
                RECT_TABS_Y1 + (5 * WINDOW_HEIGHT) + (4 * WINDOW_PADDING),
                (RECT_TABS_X2 / 2) - (WINDOW_PADDING / 2),
                WINDOW_HEIGHT,
                myWindowsGroupMain[0],
                (HMENU)IDM_BUTTON_IMPORT_TRIMESH,
                hInstance,
                NULL
            );

            if (0 == test_hwnd)
            {
                return false;
            }

            SendMessage(test_hwnd, WM_SETFONT, (WPARAM)myWindowsFont, FALSE);

            myWindowsGroupNodes[6] = test_hwnd;

            /********************************/
            /* [GROUP 4/4] Create button */

            test_hwnd = CreateWindow
            (
                "BUTTON",
                "Rebuild collision",
                (WS_CHILD | BS_DEFPUSHBUTTON),
                RECT_TABS_X1,
                RECT_TABS_Y1 + (6 * WINDOW_HEIGHT) + (5 * WINDOW_PADDING),
                (RECT_TABS_X2 / 2) - (WINDOW_PADDING / 2),
                WINDOW_HEIGHT,
                myWindowsGroupMain[0],
                (HMENU)IDM_BUTTON_REBUILD_COLLISION,
                hInstance,
                NULL
            );

            if (0 == test_hwnd)
            {
                return false;
            }

            SendMessage(test_hwnd, WM_SETFONT, (WPARAM)myWindowsFont, FALSE);

            myWindowsGroupNodes[7] = test_hwnd;

            /********************************/
            /* [GROUP 4/4] Create listbox window */

            test_hwnd = CreateWindowEx
            (
                WS_EX_CLIENTEDGE,
                "LISTBOX",
                NULL,
                (WS_CHILD | WS_HSCROLL | WS_VSCROLL | LBS_DISABLENOSCROLL | LBS_HASSTRINGS | LBS_NOTIFY),
                RECT_TABS_X1,
                RECT_TABS_Y1 + (7 * WINDOW_HEIGHT) + (6 * WINDOW_PADDING),
                RECT_TABS_X2,
                384,
                myWindowsGroupMain[0],
                (HMENU)IDM_LISTBOX_NODES,
                hInstance,
                NULL
            );

            if (0 == test_hwnd)
            {
                return false;
            }

            SendMessage(test_hwnd, WM_SETFONT, (WPARAM)myWindowsFont, FALSE);

            myWindowsGroupNodes[8] = test_hwnd;

            /********************************/
            /* WinApi creation completed. :) */

            changeWindowGroup();

            ShowWindow(myWindowsGroupMain[0], SW_SHOW);

            return true;
        }


        ////////////////////////////////////////////////////////////////
        // Set window group visibility
        ////////////////////////////////////////////////////////////////
        void changeWindowGroup()
        {
            int32_t i;
            int show_status;

            char bufor[256];

            const char* page_names[4] =
            {
                "theAR",
                "Denis",
                "Animation",
                "Nodes list"
            };

            show_status = (1 == myWindowsCurrentGroup) ? SW_SHOW : SW_HIDE;

            for (i = 0; i < 8; i++)
            {
                ShowWindow(myWindowsGroupAr[i], show_status);
            }

            show_status = (2 == myWindowsCurrentGroup) ? SW_SHOW : SW_HIDE;

            for (i = 0; i < 4; i++)
            {
                ShowWindow(myWindowsGroupDenis[i], show_status);
            }

            show_status = (3 == myWindowsCurrentGroup) ? SW_SHOW : SW_HIDE;

            for (i = 0; i < 5; i++)
            {
                ShowWindow(myWindowsGroupAnimation[i], show_status);
            }

            show_status = (4 == myWindowsCurrentGroup) ? SW_SHOW : SW_HIDE;

            for (i = 0; i < 9; i++)
            {
                ShowWindow(myWindowsGroupNodes[i], show_status);
            }

            sprintf_s
            (
                bufor,
                256,
                "Page [%d/4] %s",
                myWindowsCurrentGroup,
                page_names[myWindowsCurrentGroup - 1]
            );

            SetWindowText(myWindowsGroupMain[2], bufor);
        }


        ////////////////////////////////////////////////////////////////
        // Update ListBox of nodes
        ////////////////////////////////////////////////////////////////
        void updateNodesList(int32_t mode, void* param)
        {
            eString* test_str = (eString*)param;
            HWND label = myWindowsGroupNodes[0];
            HWND listbox = GetDlgItem(myWindowsGroupMain[0], IDM_LISTBOX_NODES);

            if ((NULL == label) || (NULL == listbox))
            {
                return;
            }

            if (nullptr != test_str)
            {
                if (mode < 0)
                {
                    SetWindowText(label, test_str->getText());
                }
                else
                {
                    SendMessage(listbox, LB_ADDSTRING, 0, (LPARAM)(test_str->getText()));
                }
            }
            else
            {
                SetWindowText(label, "");
                SendMessage(listbox, LB_RESETCONTENT, 0, 0);
            }
        }


    }
}
