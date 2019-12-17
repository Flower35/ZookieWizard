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

        HWND myWindows[windowID::WINDOWS_COUNT] = {0};
        HBITMAP myWindowsLogo = NULL;
        HFONT myWindowsFont = NULL;
        HDC openGL_DeviceContext = NULL;
        HGLRC openGL_RenderingContext = NULL;

        int32_t mousePosAndButton[3] = {0, 0, 0};
        float backgroundColor[3] = {0, 1.0f, 1.0f};
        bool isOrthoMode = false;
        testCameraStruct testCamera;

        int32_t myDrawFlags = 0;

        testCameraStruct::testCameraStruct()
        {
            reset();
        }

        void testCameraStruct::reset()
        {
            pos_x = 0;
            pos_y = (-1000);
            pos_z = 0;

            look_x = 0;
            look_y = 1.0;
            look_z = 0;

            pitch = 0;
            yaw = 0;
        }


        ////////////////////////////////////////////////////////////////
        // Renderer window procedure
        ////////////////////////////////////////////////////////////////
        LRESULT CALLBACK procedureOfRenderWindow(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
        {
            switch (Msg)
            {
                case WM_LBUTTONDOWN:
                {
                    mousePosAndButton[0] = LOWORD(lParam);
                    mousePosAndButton[1] = HIWORD(lParam);
                    mousePosAndButton[2] = 1;

                    break;
                }

                case WM_RBUTTONDOWN:
                {
                    mousePosAndButton[0] = LOWORD(lParam);
                    mousePosAndButton[1] = HIWORD(lParam);
                    mousePosAndButton[2] = 2;

                    break;
                }

                case WM_LBUTTONUP:
                case WM_RBUTTONUP:
                {
                    mousePosAndButton[2] = 0;

                    break;
                }

                case WM_MOUSEMOVE:
                {
                    if (mousePosAndButton[2] > 0)
                    {
                        moveCameraAndLook
                        (
                            (LOWORD(lParam) - mousePosAndButton[0]),
                            (HIWORD(lParam) - mousePosAndButton[1])
                        );

                        mousePosAndButton[0] = LOWORD(lParam);
                        mousePosAndButton[1] = HIWORD(lParam);
                    }

                    break;
                }
            }

            return DefWindowProc(hWnd, Msg, wParam, lParam);
        }



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

                        case IDM_EDITBOX_MEDIADIR:
                        {
                            if (EN_CHANGE == HIWORD(wParam))
                            {
                                GetWindowText((HWND)lParam, currentWorkingDirectory, 256);
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
                            myWindows[windowID::WINDOW_RENDER],
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
            /* Create main window */

            const DWORD pos_x = ((GetSystemMetrics(SM_CXSCREEN) - RECT_WINDOW_X) / 2);
            const DWORD pos_y = ((GetSystemMetrics(SM_CYSCREEN) - RECT_WINDOW_Y) / 2);

            myWindows[windowID::WINDOW_MAIN] = CreateWindow
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

            if (0 == myWindows[windowID::WINDOW_MAIN])
            {
                return false;
            }

            /********************************/
            /* Create renderer window */

            myWindows[windowID::WINDOW_RENDER] = CreateWindow
            (
                WINDOW_CLASS_NAME_2,
                NULL,
                (WS_CHILD | WS_VISIBLE),
                RECT_RENDER_X1,
                RECT_RENDER_Y1,
                RECT_RENDER_X2,
                RECT_RENDER_Y2,
                myWindows[windowID::WINDOW_MAIN],
                NULL,
                hInstance,
                NULL
            );

            if (0 == myWindows[windowID::WINDOW_RENDER])
            {
                return false;
            }

            /********************************/
            /* Create dummy label */

            test_hwnd = CreateWindow
            (
                "STATIC",
                "Working directory (\"/media/\"):",
                (WS_CHILD | WS_VISIBLE),
                RECT_TABS_X1,
                RECT_TABS_Y1 + (0 * 24) + (0 * 16),
                RECT_TABS_X2,
                24,
                myWindows[windowID::WINDOW_MAIN],
                NULL,
                hInstance,
                NULL
            );

            SendMessage(test_hwnd, WM_SETFONT, (WPARAM)myWindowsFont, FALSE);

            /********************************/
            /* Create editbox window */

            test_hwnd = CreateWindowEx
            (
                WS_EX_CLIENTEDGE,
                "EDIT",
                NULL,
                (WS_CHILD | WS_VISIBLE),
                RECT_TABS_X1,
                RECT_TABS_Y1 + (1 * 24) + (0 * 16),
                RECT_TABS_X2,
                24,
                myWindows[windowID::WINDOW_MAIN],
                (HMENU)IDM_EDITBOX_MEDIADIR,
                hInstance,
                NULL
            );

            if (0 == test_hwnd)
            {
                return false;
            }

            SendMessage(test_hwnd, WM_SETFONT, (WPARAM)myWindowsFont, FALSE);

            /********************************/
            /* Create button */

            test_hwnd = CreateWindow
            (
                "BUTTON",
                "reset camera",
                (WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON),
                RECT_TABS_X1,
                RECT_TABS_Y1 + (2 * 24) + (1 * 16),
                RECT_TABS_X2,
                24,
                myWindows[windowID::WINDOW_MAIN],
                (HMENU)IDM_BUTTON_RESET_CAMERA,
                hInstance,
                NULL
            );

            if (0 == test_hwnd)
            {
                return false;
            }

            SendMessage(test_hwnd, WM_SETFONT, (WPARAM)myWindowsFont, FALSE);

            /********************************/
            /* Create checkboxes */

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
                    RECT_TABS_Y1 + ((i + 3) * 24) + (2 * 16),
                    RECT_TABS_X2,
                    24,
                    myWindows[windowID::WINDOW_MAIN],
                    (HMENU)checkboxes_ids[i],
                    hInstance,
                    NULL
                );

                if (0 == test_hwnd)
                {
                    return false;
                }

                SendMessage(test_hwnd, WM_SETFONT, (WPARAM)myWindowsFont, FALSE);
            }

            /********************************/
            /* Create dummy label */

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
                RECT_TABS_Y1 + ((drawFlags::DRAW_FLAGS_COUNT + 3) * 24) + (3 * 16),
                RECT_TABS_X2,
                (5 * 24),
                myWindows[windowID::WINDOW_MAIN],
                NULL,
                hInstance,
                NULL
            );

            SendMessage(test_hwnd, WM_SETFONT, (WPARAM)myWindowsFont, FALSE);

            /********************************/
            /* WinApi creation completed. :) */

            ShowWindow(myWindows[windowID::WINDOW_MAIN], SW_SHOW);

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

                ReleaseDC(myWindows[windowID::WINDOW_RENDER], openGL_DeviceContext);
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


        ////////////////////////////////////////////////////////////////
        // Prepare OpenGL window
        ////////////////////////////////////////////////////////////////
        bool prepareRendering()
        {
            int pixel_format;
            PIXELFORMATDESCRIPTOR pfd = {0};

            openGL_DeviceContext = GetDC(myWindows[windowID::WINDOW_RENDER]);

            pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
            pfd.nVersion = 1;
            pfd.iLayerType = PFD_MAIN_PLANE;
            pfd.dwFlags = (PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER);
            pfd.cDepthBits = 32;
            pfd.cColorBits = 24;
            pfd.iPixelType = PFD_TYPE_RGBA;

            pixel_format = ChoosePixelFormat(openGL_DeviceContext, &pfd);

            if (FALSE == SetPixelFormat(openGL_DeviceContext, pixel_format, &pfd))
            {
                return false;
            }

            if (NULL == (openGL_RenderingContext = wglCreateContext(openGL_DeviceContext)))
            {
                return false;
            }

            if (FALSE == wglMakeCurrent(openGL_DeviceContext, openGL_RenderingContext))
            {
                return false;
            }

            /* Triangles cropping */
            glCullFace(GL_FRONT);

            /* Wireframe */
            glPolygonMode(GL_BACK, GL_LINE);

            /* Depth testing */
            glClearDepth(1.0f);
            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LEQUAL);

            /* Transparent textures */
            //// glEnable(GL_BLEND);
            //// glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            //// glBlendEquation(GL_FUNC_ADD);

            /* Default perspective */
            setPerspective(RECT_RENDER_X2, RECT_RENDER_Y2);

            return true;
        }


        ////////////////////////////////////////////////////////////////
        // Prepare OpenGL window
        ////////////////////////////////////////////////////////////////
        void setPerspective(GLsizei new_width, GLsizei new_height)
        {
            float p_x = 1.0f;
            float p_y = 1.0f;

            /* DO NOT DIVICE BY ZERO! */
            if (0 == new_width)
            {
                new_width = 1;
            }
            if (0 == new_height)
            {
                new_height = 1;
            }

            /* Set background color for this scene */
            glClearColor
            (
                backgroundColor[0], // Red
                backgroundColor[1], // Green
                backgroundColor[2], // Blue
                1.0 // Alpha
            );

            glViewport(0, 0, new_width, new_height);

            /* Begin with the projection matrix */
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();

            if (isOrthoMode)
            {
                /* Calculate proportions */
                if (new_height > new_width)
                {
                    p_y = (float)new_height / (float)new_width;
                }
                else if (new_height < new_width)
                {
                    p_x = (float)new_width / (float)new_height;
                }

                glOrtho
                (
                    (-p_x), // left
                    p_x, // right
                    (-p_y), // top
                    p_y, // bottom
                    0.0, // zNear
                    1.0 // zFar
                );
            }
            else
            {
                gluPerspective
                (
                    45.0, // field of view
                    ((GLfloat)new_width / (GLfloat)new_height), // aspect ratio
                    1.0, // zNear
                    160000.0 // zFar
                );
            }

            /* Finish with the model matrix */
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
        }


        ////////////////////////////////////////////////////////////////
        // Change OpenGL viewing
        ////////////////////////////////////////////////////////////////
        void changeView(bool change_to_perspective_view)
        {
            float to_be_changed = false;
            RECT rc;

            if ((!change_to_perspective_view) && (!isOrthoMode))
            {
                isOrthoMode = true;
                to_be_changed = true;
            }

            if (change_to_perspective_view && isOrthoMode)
            {
                isOrthoMode = false;
                to_be_changed = true;
            }

            if (to_be_changed)
            {
                GetWindowRect(myWindows[windowID::WINDOW_RENDER], &rc);
                setPerspective((rc.right - rc.left), (rc.bottom - rc.top));
            }
        }


        ////////////////////////////////////////////////////////////////
        // Try to use mouse to move camera around...
        ////////////////////////////////////////////////////////////////
        void moveCameraAndLook(int32_t x, int32_t y)
        {
            bool calculations = false;

            const double ROTATING_SPEED = 0.01;
            const double STRAFING_SPEED = 100.0;

            if (!isOrthoMode)
            {
                /* 1 (LMB): rotate camera */
                /* 2 (RMB): pan camera */

                switch (mousePosAndButton[2])
                {
                    case 1:
                    {
                        /* Modify "rot_Z" */

                        if (x > 0) // look to the right (ADD)
                        {
                            testCamera.yaw += ((double)x * ROTATING_SPEED);
                        }
                        else if (x < 0) // look to the left (SUBTRACT)
                        {
                            testCamera.yaw -= ((double)(-x) * ROTATING_SPEED);
                        }

                        /* Modify "rot_X" */

                        if (y > 0) // look down (SUBTRACT)
                        {
                            testCamera.pitch -= ((double)y * ROTATING_SPEED);
                        }
                        else if (y < 0) // look up (ADD)
                        {
                            testCamera.pitch += ((double)(-y) * ROTATING_SPEED);
                        }

                        calculations = true;
                        break;
                    }

                    case 2:
                    {
                        if (x > 0) // move to the right
                        {
                            testCamera.pos_x += (testCamera.look_y * STRAFING_SPEED);
                            testCamera.pos_y -= (testCamera.look_x * STRAFING_SPEED);
                        }
                        else if (x < 0) // move to the left
                        {
                            testCamera.pos_x -= (testCamera.look_y * STRAFING_SPEED);
                            testCamera.pos_y += (testCamera.look_x * STRAFING_SPEED);
                        }

                        if (y > 0) // move backwards
                        {
                            testCamera.pos_x -= (testCamera.look_x * STRAFING_SPEED);
                            testCamera.pos_y -= (testCamera.look_y * STRAFING_SPEED);
                            testCamera.pos_z -= (testCamera.look_z * STRAFING_SPEED);
                        }
                        else if (y < 0) // move forwards
                        {
                            testCamera.pos_x += (testCamera.look_x * STRAFING_SPEED);
                            testCamera.pos_y += (testCamera.look_y * STRAFING_SPEED);
                            testCamera.pos_z += (testCamera.look_z * STRAFING_SPEED);
                        }

                        break;
                    }
                }

                /* Get camera direction */

                if (calculations)
                {
                    if (testCamera.pitch > (M_PI / 2.0 - 0.0001))
                    {
                        testCamera.pitch = (M_PI / 2.0 - 0.0001);
                    }
                    else if (testCamera.pitch < - (M_PI / 2.0 - 0.0001))
                    {
                        testCamera.pitch = - (M_PI / 2.0 - 0.0001);
                    }
                    
                    if ((testCamera.yaw > (2.0 * M_PI)) || (testCamera.yaw < (- 2.0 * M_PI)))
                    {
                        testCamera.yaw = 0;
                    }

                    testCamera.look_x = cos(testCamera.pitch) * sin(testCamera.yaw);
                    testCamera.look_y = cos(testCamera.pitch) * cos(testCamera.yaw);
                    testCamera.look_z = sin(testCamera.pitch);
                }

                /* Load identity before making eye contact... */
                glLoadIdentity();

                gluLookAt
                (
                    testCamera.pos_x, // eyes X
                    testCamera.pos_y, // eyes Y
                    testCamera.pos_z, // eyes Z
                    (testCamera.pos_x + testCamera.look_x), // center X
                    (testCamera.pos_y + testCamera.look_y), // center Y
                    (testCamera.pos_z + testCamera.look_z), // center Z
                    0, // up X
                    0, // up Y
                    1.0 // up Z
                );
            }
        }


        ////////////////////////////////////////////////////////////////
        // Render current scene
        ////////////////////////////////////////////////////////////////
        void render()
        {
            glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

            moveCameraAndLook(0, 0);

            myARs[0].renderScene(0, myDrawFlags);

            SwapBuffers(openGL_DeviceContext);
        }

    }
}
