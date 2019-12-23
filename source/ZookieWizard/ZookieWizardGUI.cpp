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

        HWND myWindowsGroupMain[2] = {NULL};
        HWND myWindowsGroupAr[7] = {NULL};
        HWND myWindowsGroupDenis[4] = {NULL};

        int32_t myWindowsCurrentGroup = 1;

        HBITMAP myWindowsLogo = NULL;
        HFONT myWindowsFont = NULL;
        

        ////////////////////////////////////////////////////////////////
        // Main window procedure
        ////////////////////////////////////////////////////////////////
        LRESULT CALLBACK procedureOfMainWindow(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
        {
            switch (Msg)
            {
                /********************************/
                /* Closing the Application */

                case  WM_DESTROY:
                {
                    PostQuitMessage(0);

                    break;
                }

                case WM_CLOSE:
                {
                    DestroyWindow(hWnd);

                    break;
                }

                /********************************/
                /* Drawing small bitmap logo */

                case WM_PAINT:
                {
                    PAINTSTRUCT ps;
                    HDC hdcOkno = BeginPaint(hWnd, &ps);
                    HDC hdcImg = CreateCompatibleDC(hdcOkno);

                    SelectObject(hdcImg, myWindowsLogo);
                    
                    BitBlt
                    (
                        hdcOkno,
                        RECT_LOGO_X1,
                        RECT_LOGO_Y1,
                        RECT_LOGO_X2,
                        RECT_LOGO_Y2,
                        hdcImg,
                        0,
                        0,
                        SRCCOPY
                    );
                    
                    DeleteDC(hdcImg);
                    EndPaint(hWnd, &ps);

                    break;
                }

                /********************************/
                /* Checking buttons */

                case WM_COMMAND:
                {
                    switch (LOWORD(wParam))
                    {
                        case IDM_MENU_VERSION_1:
                        {
                            setGameVersion(GAME_VERSION_KAO2_PL_PC);

                            break;
                        }

                        case IDM_MENU_VERSION_2:
                        {
                            setGameVersion(GAME_VERSION_KAO2_EUR_PC);

                            break;
                        }

                        case IDM_MENU_VERSION_3:
                        {
                            setGameVersion(GAME_VERSION_KAO_TW_PC);

                            break;
                        }

                        case IDM_MENU_DENIS_OPEN:
                        {
                            openDenisLevel();

                            break;
                        }

                        case IDM_MENU_DENIS_CONVERT:
                        {
                            convertDenisLevel();

                            break;
                        }

                        case IDM_MENU_AR_OPEN:
                        {
                            openOrSaveAr(AR_MODE_READ);

                            break;
                        }

                        case IDM_MENU_AR_SAVE:
                        {
                            openOrSaveAr(AR_MODE_WRITE);

                            break;
                        }

                        case IDM_MENU_AR_EXPORT_SCRIPTS:
                        {
                            openOrSaveAr(AR_MODE_EXPORT_SCRIPTS);

                            break;
                        }

                        case IDM_MENU_AR_EXPORT_PROXIES:
                        {
                            openOrSaveAr(AR_MODE_EXPORT_PROXIES);

                            break;
                        }

                        case IDM_MENU_AR_EXPORT_STRUCTURE:
                        {
                            writeArStructureToTextFile();

                            break;
                        }

                        case IDM_EDITBOX_MEDIADIR:
                        {
                            if (EN_CHANGE == HIWORD(wParam))
                            {
                                GetWindowText((HWND)lParam, currentWorkingDirectory, 256);
                            }

                            break;
                        }

                        case IDM_EDITBOX_DENISDIR:
                        {
                            if (EN_CHANGE == HIWORD(wParam))
                            {
                                GetWindowText((HWND)lParam, denisDirectory, 256);
                            }

                            break;
                        }

                        case IDM_EDITBOX_DENISLVL:
                        {
                            if (EN_CHANGE == HIWORD(wParam))
                            {
                                GetWindowText((HWND)lParam, denisLevelName, 256);
                            }

                            break;
                        }

                        case IDM_BUTTON_RESET_CAMERA:
                        {
                            if (BN_CLICKED == HIWORD(wParam))
                            {
                                testCamera.reset();
                            }

                            break;
                        }

                        case IDM_CHECKBOX_RENDER_INVISIBLE:
                        {
                            if (BN_CLICKED == HIWORD(wParam))
                            {
                                if (BST_CHECKED == SendMessage((HWND)lParam, BM_GETCHECK, 0, 0))
                                {
                                    myDrawFlags |= drawFlags::DRAW_FLAG_INVISIBLE;
                                }
                                else
                                {
                                    myDrawFlags &= (~ drawFlags::DRAW_FLAG_INVISIBLE);
                                }
                            }

                            break;
                        }

                        case IDM_CHECKBOX_RENDER_BOXZONES:
                        {
                            if (BN_CLICKED == HIWORD(wParam))
                            {
                                if (BST_CHECKED == SendMessage((HWND)lParam, BM_GETCHECK, 0, 0))
                                {
                                    myDrawFlags |= drawFlags::DRAW_FLAG_BOXZONES;
                                }
                                else
                                {
                                    myDrawFlags &= (~ drawFlags::DRAW_FLAG_BOXZONES);
                                }
                            }

                            break;
                        }

                        case IDM_CHECKBOX_RENDER_PROXIES:
                        {
                            if (BN_CLICKED == HIWORD(wParam))
                            {
                                if (BST_CHECKED == SendMessage((HWND)lParam, BM_GETCHECK, 0, 0))
                                {
                                    myDrawFlags |= drawFlags::DRAW_FLAG_PROXIES;
                                }
                                else
                                {
                                    myDrawFlags &= (~ drawFlags::DRAW_FLAG_PROXIES);
                                }
                            }

                            break;
                        }

                        case IDM_BUTTON_PAGE_PREV:
                        {
                            myWindowsCurrentGroup--;

                            if (myWindowsCurrentGroup < 1)
                            {
                                myWindowsCurrentGroup = 1;
                            }

                            changeWindowGroup();

                            break;
                        }

                        case IDM_BUTTON_PAGE_NEXT:
                        {
                            myWindowsCurrentGroup++;

                            if (myWindowsCurrentGroup > 2)
                            {
                                myWindowsCurrentGroup = 2;
                            }

                            changeWindowGroup();

                            break;
                        }
                    }

                    break;
                }

                /********************************/
                /* Resizing */

                case WM_SIZING:
                {
                    RECT* w = (RECT*)lParam;

                    /* Check is width isn't too small */

                    if ((w->right - w->left) < RECT_WINDOW_X)
                    {
                        switch (wParam)
                        {
                            case WMSZ_BOTTOMRIGHT:
                            case WMSZ_RIGHT:
                            case WMSZ_TOPRIGHT:
                            {
                                w->right = (w->left + RECT_WINDOW_X);

                                break;
                            }

                            case WMSZ_BOTTOMLEFT:
                            case WMSZ_LEFT:
                            case WMSZ_TOPLEFT:
                            {
                                w->left = (w->right - RECT_WINDOW_X);

                                break;
                            }
                        }
                    }

                    /* Check if height isn't too small */

                    if ((w->bottom - w->top) < RECT_WINDOW_Y)
                    {
                        switch (wParam)
                        {
                            case WMSZ_BOTTOM:
                            case WMSZ_BOTTOMLEFT:
                            case WMSZ_BOTTOMRIGHT:
                            {
                                w->bottom = (w->top + RECT_WINDOW_Y);

                                break;
                            }

                            case WMSZ_TOP:
                            case WMSZ_TOPLEFT:
                            case WMSZ_TOPRIGHT:
                            {
                                w->top = (w->bottom - RECT_WINDOW_Y);

                                break;
                            }
                        }
                    }

                    return TRUE;
                }

                /********************************/
                /* Window changed its dimensions */

                case WM_SIZE:
                {
                    if (SIZE_MINIMIZED != wParam)
                    {
                        WORD new_width = LOWORD(lParam);
                        WORD new_height = HIWORD(lParam);

                        /* Change Renderer window size */

                        MoveWindow
                        (
                            myWindowsGroupMain[1],
                            RECT_RENDER_X1,
                            RECT_RENDER_Y1,
                            (new_width - RECT_RENDER_X1),
                            new_height,
                            FALSE
                        );

                        setPerspective((new_width - RECT_RENDER_X1), new_height);

                        return 0;
                    }

                    break;
                }
            }

            return DefWindowProc(hWnd, Msg, wParam, lParam);
        }


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
            /* [GROUP 1/3] Create main window */

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
            /* [GROUP 1/3] Create renderer window */

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
            /* [GROUP 1/3] Create button (previous page) */

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
            /* [GROUP 1/3] Create button (next page) */

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
            /* [GROUP 2/3] Create dummy label */

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
            /* [GROUP 2/3] Create editbox window */

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
            /* [GROUP 2/3] Create button */

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
            /* [GROUP 2/3] Create checkboxes */

            const int checkboxes_ids[drawFlags::DRAW_FLAGS_COUNT] =
            {
                IDM_CHECKBOX_RENDER_INVISIBLE,
                IDM_CHECKBOX_RENDER_BOXZONES,
                IDM_CHECKBOX_RENDER_PROXIES
            };

            const char* checkboxes_names[drawFlags::DRAW_FLAGS_COUNT] =
            {
                "draw INVISIBLE MESHES",
                "draw BOX ZONES",
                "draw PROXIES"
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
            /* [GROUP 2/3] Create dummy label */

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

            myWindowsGroupAr[6] = test_hwnd;
            
            /********************************/
            /* [GROUP 3/3] Create dummy label */

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
            /* [GROUP 3/3] Create editbox window */

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
                (HMENU)IDM_EDITBOX_DENISDIR,
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
            /* [GROUP 3/3] Create dummy label */

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
            /* [GROUP 3/3] Create editbox window */

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
                (HMENU)IDM_EDITBOX_DENISLVL,
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
            /* WinApi creation completed. :) */

            ShowWindow(myWindowsGroupMain[0], SW_SHOW);

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

                ReleaseDC(myWindowsGroupMain[1], openGL_DeviceContext);
            }

            /* Close/Unload others */

            if (NULL != myWindowsLogo)
            {
                FreeResource(myWindowsLogo);
            }

            if (NULL != myWindowsFont)
            {
                DeleteObject(myWindowsFont);
            }
        }
        
        
        ////////////////////////////////////////////////////////////////
        // Set window group visibility
        ////////////////////////////////////////////////////////////////
        void changeWindowGroup()
        {
            int32_t i;
            int show_status;

            show_status = (1 == myWindowsCurrentGroup) ? SW_SHOW : SW_HIDE;

            for (i = 0; i < 7; i++)
            {
                ShowWindow(myWindowsGroupAr[i], show_status);
            }

            show_status = (2 == myWindowsCurrentGroup) ? SW_SHOW : SW_HIDE;

            for (i = 0; i < 4; i++)
            {
                ShowWindow(myWindowsGroupDenis[i], show_status);
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
