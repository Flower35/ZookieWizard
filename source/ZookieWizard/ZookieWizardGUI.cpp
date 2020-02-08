#include <ZookieWizard/ZookieWizard.h>

#include <kao2ar/Archive.h>

namespace ZookieWizard
{
    namespace GUI
    {
        ////////////////////////////////////////////////////////////////
        // Initialize variables
        ////////////////////////////////////////////////////////////////

        HBITMAP myWindowsLogo = NULL;
        HFONT myWindowsFont = NULL;


        ////////////////////////////////////////////////////////////////
        // Main window procedure
        ////////////////////////////////////////////////////////////////
        LRESULT CALLBACK procedureOfMainWindow(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
        {
            int32_t i;
            char bufor[8];

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

                        case IDM_MENU_AR_EXPORT_COLLADA:
                        {
                            exportArToCollada();

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

                        case IDM_EDITBOX_DENIS_DIR:
                        {
                            if (EN_CHANGE == HIWORD(wParam))
                            {
                                GetWindowText((HWND)lParam, denisDirectory, 256);
                            }

                            break;
                        }

                        case IDM_EDITBOX_DENIS_LVL:
                        {
                            if (EN_CHANGE == HIWORD(wParam))
                            {
                                GetWindowText((HWND)lParam, denisLevelName, 256);
                            }

                            break;
                        }

                        case IDM_EDITBOX_ANIM_ID:
                        {
                            if (EN_CHANGE == HIWORD(wParam))
                            {
                                GetWindowText((HWND)lParam, bufor, 8);

                                i = std::atoi(bufor);

                                if (i < 0)
                                {
                                    i = 0;
                                }

                                if (animationID != i)
                                {
                                    animationID = i;
                                    timerReset();
                                }
                            }

                            break;
                        }

                        case IDM_EDITBOX_ANIM_FPS:
                        {
                            if (EN_CHANGE == HIWORD(wParam))
                            {
                                GetWindowText((HWND)lParam, bufor, 8);

                                i = std::atoi(bufor);

                                if (i >= 1)
                                {
                                    animationFPS = i;
                                }
                                else
                                {
                                    animationFPS = 1;
                                }
                            }

                            break;
                        }

                        case IDM_LISTBOX_NODES:
                        {
                            if (LBN_DBLCLK == HIWORD(wParam))
                            {
                                i = SendMessage((HWND)lParam, LB_GETCURSEL, 0, 0);

                                if (i == LB_ERR)
                                {
                                    i = (-1);
                                }

                                myARs[0].changeSelectedObject(i);
                            }

                            break;
                        }

                        case IDM_BUTTON_RESET_NODES:
                        {
                            if (BN_CLICKED == HIWORD(wParam))
                            {
                                myARs[0].changeSelectedObject(-3);
                            }

                            break;
                        }

                        case IDM_BUTTON_PARENT_NODE:
                        {
                            if (BN_CLICKED == HIWORD(wParam))
                            {
                                myARs[0].changeSelectedObject(-2);
                            }

                            break;
                        }

                        case IDM_BUTTON_TOGGLE_NODE:
                        {
                            if (BN_CLICKED == HIWORD(wParam))
                            {
                                myARs[0].changeSelectedObject(-4);
                            }

                            break;
                        }

                        case IDM_BUTTON_DELETE_NODE:
                        {
                            if (BN_CLICKED == HIWORD(wParam))
                            {
                                myARs[0].changeSelectedObject(-5);
                            }

                            break;
                        }

                        case IDM_BUTTON_EXPORT_TRIMESH:
                        {
                            if (BN_CLICKED == HIWORD(wParam))
                            {
                                exportTrimeshToObj();
                            }

                            break;
                        }

                        case IDM_BUTTON_IMPORT_TRIMESH:
                        {
                            if (BN_CLICKED == HIWORD(wParam))
                            {
                                importTrimeshFromObj();
                            }

                            break;
                        }

                        case IDM_BUTTON_REBUILD_COLLISION:
                        {
                            if (BN_CLICKED == HIWORD(wParam))
                            {
                                myARs[0].changeSelectedObject(-6);
                            }

                            break;
                        }

                        case IDM_BUTTON_RESET_TIMER:
                        {
                            if (BN_CLICKED == HIWORD(wParam))
                            {
                                timerReset();
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

                        case IDM_CHECKBOX_RENDER_ANIMS:
                        {
                            if (BN_CLICKED == HIWORD(wParam))
                            {
                                if (BST_CHECKED == SendMessage((HWND)lParam, BM_GETCHECK, 0, 0))
                                {
                                    myDrawFlags |= drawFlags::DRAW_FLAG_ANIMS;
                                }
                                else
                                {
                                    myDrawFlags &= (~ drawFlags::DRAW_FLAG_ANIMS);
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

                            if (myWindowsCurrentGroup > 4)
                            {
                                myWindowsCurrentGroup = 4;
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
