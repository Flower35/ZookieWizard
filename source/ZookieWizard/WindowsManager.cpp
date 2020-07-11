#include <ZookieWizard/WindowsManager.h>

namespace ZookieWizard
{
    namespace GUI
    {
        ////////////////////////////////////////////////////////////////
        // EXTERNAL OBJECTS AND VARIABLES
        ////////////////////////////////////////////////////////////////

        WindowsManager theWindowsManager;

        const char* WINDOW_CLASS_NAME_1 = "ZookieWizard::GUI::WindowClass1";
        const char* WINDOW_CLASS_NAME_2 = "ZookieWizard::GUI::WindowClass2";
        const char* WINDOW_CLASS_NAME_3 = "ZookieWizard::GUI::WindowClass3";
        const char* WINDOW_CLASS_NAME_4 = "ZookieWizard::GUI::WindowClass4";
        const char* WINDOW_CLASS_NAME_5 = "ZookieWizard::GUI::WindowClass5";

        static int verticalScrollingCurrentPos = 0;
        static int verticalScrollingLimit = 0;


        ////////////////////////////////////////////////////////////////
        // STATIC FUNCTION: Switch pages
        ////////////////////////////////////////////////////////////////

        void staticFuncSwitchPagesLeft(WPARAM wParam, LPARAM lParam, void* custom_param)
        {
            theWindowsManager.switchPage(-2);
        }

        void staticFuncSwitchPagesRight(WPARAM wParam, LPARAM lParam, void* custom_param)
        {
            theWindowsManager.switchPage(-1);
        }


        ////////////////////////////////////////////////////////////////
        // STATIC FUNCTION: Main window procedure
        ////////////////////////////////////////////////////////////////
        LRESULT CALLBACK procedureOfMainWindow(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
        {
            switch (Msg)
            {
                /********************************/
                /* Closing the Application */

                case WM_DESTROY:
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

                    SelectObject(hdcImg, myWindowLogo);

                    BitBlt
                    (
                        hdcOkno,
                        RECT_LOGO_X1, RECT_LOGO_Y1, RECT_LOGO_X2, RECT_LOGO_Y2,
                        hdcImg, 0, 0, SRCCOPY
                    );

                    DeleteDC(hdcImg);
                    EndPaint(hWnd, &ps);

                    break;
                }

                /********************************/
                /* Checking buttons and menus */

                case WM_COMMAND:
                {
                    int32_t id = LOWORD(wParam) - WINDOWS_MANAGER_MENU_ID;

                    theWindowsManager.runStaticFunction(id, wParam, lParam);

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

                        /* Change Renderer window size and Scroll window size */

                        MoveWindow
                        (
                            theWindowsManager.getRenderWindow(),
                            RECT_RENDER_X1,
                            RECT_RENDER_Y1,
                            (new_width - RECT_RENDER_X1),
                            new_height - RECT_RENDER_Y1,
                            FALSE
                        );

                        MoveWindow
                        (
                            theWindowsManager.getScrollWindow(),
                            0,
                            RECT_TABS_Y1 + 24,
                            RECT_LOGO_X2,
                            new_height - RECT_TABS_Y1 - 24,
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
        // STATIC FUNCTION: Common procedure for object movement
        ////////////////////////////////////////////////////////////////
        void procedureForObjectMovement(uint8_t obj_mode, HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
        {
            int32_t horizontal = 0, vertical = 0;
            int8_t x = 0, y = 0, z = 0;

            switch (Msg)
            {
                case WM_LBUTTONDOWN:
                case WM_RBUTTONDOWN:
                {
                    testCamera.mouse_prev_x = (int16_t)LOWORD(lParam);
                    testCamera.mouse_prev_y = (int16_t)HIWORD(lParam);
                    testCamera.mouse_mode = (WM_LBUTTONDOWN == Msg) ? 1 : 2;

                    /* Receive keyboard inputs as well! */
                    SetFocus(hWnd);

                    testCamera.object_mode = obj_mode;

                    break;
                }

                case WM_LBUTTONUP:
                case WM_RBUTTONUP:
                {
                    testCamera.mouse_mode = 0;
                    break;
                }

                case WM_MOUSEMOVE:
                {
                    if (testCamera.mouse_mode > 0)
                    {
                        horizontal = (int16_t)LOWORD(lParam) - testCamera.mouse_prev_x;
                        vertical = testCamera.mouse_prev_y - (int16_t)HIWORD(lParam);

                        if (1 == testCamera.mouse_mode)
                        {
                            x = horizontal;
                            z = vertical;
                        }
                        else if (2 == testCamera.mouse_mode)
                        {
                            x = horizontal;
                            y = vertical;
                        }

                        moveCameraOrObject(x, y, z, testCamera.mouse_mode);

                        testCamera.mouse_prev_x = (int16_t)LOWORD(lParam);
                        testCamera.mouse_prev_y = (int16_t)HIWORD(lParam);
                    }

                    break;
                }

                case WM_KEYDOWN:
                {
                    switch (wParam)
                    {
                        case 'A':
                        {
                            testCamera.keyboard_x = (-1);
                            break;
                        }

                        case 'D':
                        {
                            testCamera.keyboard_x = 1;
                            break;
                        }

                        case 'S':
                        {
                            testCamera.keyboard_y = (-1);
                            break;
                        }

                        case 'W':
                        {
                            testCamera.keyboard_y = 1;
                            break;
                        }

                        case 'Q':
                        {
                            testCamera.keyboard_z = (-1);
                            break;
                        }

                        case 'E':
                        {
                            testCamera.keyboard_z = 1;
                            break;
                        }
                    }

                    break;
                }

                case WM_KEYUP:
                {
                    switch (wParam)
                    {
                        case 'A':
                        case 'D':
                        {
                            testCamera.keyboard_x = 0;

                            break;
                        }

                        case 'W':
                        case 'S':
                        {
                            testCamera.keyboard_y = 0;

                            break;
                        }

                        case 'Q':
                        case 'E':
                        {
                            testCamera.keyboard_z = 0;

                            break;
                        }
                    }

                    break;
                }

            }
        }


        ////////////////////////////////////////////////////////////////
        // STATIC FUNCTION: Render window procedure
        ////////////////////////////////////////////////////////////////
        LRESULT CALLBACK procedureOfRenderWindow(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
        {
            if (isOrthoMode)
            {
                int mouse_mode = 0;

                switch (Msg)
                {
                    case WM_LBUTTONDOWN:
                    case WM_RBUTTONDOWN:
                    {
                        mouse_mode = 2;
                        break;
                    }

                    case WM_LBUTTONUP:
                    case WM_RBUTTONUP:
                    {
                        mouse_mode = 3;
                        break;
                    }

                    case WM_MOUSEMOVE:
                    {
                        mouse_mode = 1;
                        break;
                    }
                }

                if (0 != mouse_mode)
                {
                    float mouse_x = 0, mouse_y = 0, ratio = 0;

                    RECT render_window_area;
                    GetClientRect(hWnd, &render_window_area);

                    float half_width = (render_window_area.right - render_window_area.left) * 0.5f;
                    float half_height = (render_window_area.bottom - render_window_area.top) * 0.5f;

                    if (0 != half_height)
                    {
                        ratio = half_width / half_height;
                    }

                    switch (Msg)
                    {
                        case WM_LBUTTONDOWN:
                        case WM_RBUTTONDOWN:
                        case WM_LBUTTONUP:
                        case WM_RBUTTONUP:
                        case WM_MOUSEMOVE:
                        {
                            if (0 != half_width)
                            {
                                mouse_x = (float)(((int16_t)LOWORD(lParam) - half_width) / half_width);

                                if (ratio > 1.0f)
                                {
                                    mouse_x *= ratio;
                                }
                            }

                            if (0 != half_height)
                            {
                                mouse_y = (float)(((int16_t)HIWORD(lParam) - half_height) / half_height);

                                if ((ratio < 1.0f) && (ratio > 0))
                                {
                                    mouse_y /= ratio;
                                }
                            }

                            break;
                        }
                    }

                    materialsManager_ParseMouse(10.0f * mouse_x, (-10.0f) * mouse_y, mouse_mode);
                }
            }
            else
            {
                procedureForObjectMovement(0, hWnd, Msg, wParam, lParam);
            }

            return DefWindowProc(hWnd, Msg, wParam, lParam);
        }


        ////////////////////////////////////////////////////////////////
        // STATIC FUNCTION: "Object moving" window procedure
        ////////////////////////////////////////////////////////////////
        LRESULT CALLBACK procedureOfObjectMovingWindow(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
        {
            procedureForObjectMovement(1, hWnd, Msg, wParam, lParam);

            return DefWindowProc(hWnd, Msg, wParam, lParam);
        }


        ////////////////////////////////////////////////////////////////
        // STATIC FUNCTION: "Object rotating" window procedure
        ////////////////////////////////////////////////////////////////
        LRESULT CALLBACK procedureOfObjectRotatingWindow(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
        {
            procedureForObjectMovement(2, hWnd, Msg, wParam, lParam);

            return DefWindowProc(hWnd, Msg, wParam, lParam);
        }


        ////////////////////////////////////////////////////////////////
        // STATIC FUNCTION: Scroll window procedure
        ////////////////////////////////////////////////////////////////
        LRESULT CALLBACK procedureOfScrollWindow(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
        {
            SCROLLINFO scroll_info;
            int32_t new_scroll_pos = verticalScrollingCurrentPos;
            int32_t new_height, i;

            switch (Msg)
            {
                /********************************/
                /* Checking buttons and menus */

                case WM_COMMAND:
                {
                    i = LOWORD(wParam) - WINDOWS_MANAGER_MENU_ID;

                    theWindowsManager.runStaticFunction(i, wParam, lParam);

                    break;
                }

                /********************************/
                /* Scrolling vertically */

                case WM_SIZE:
                {
                    new_height = HIWORD(lParam);

                    verticalScrollingLimit = max(WINDOWS_MANAGER_SCROLL_HEIGHT - new_height, 0);

                    if (verticalScrollingCurrentPos > verticalScrollingLimit)
                    {
                        /* This occurs when scroll box was moved to the bottom and user maximizes the window */
                        i = verticalScrollingCurrentPos - verticalScrollingLimit;
                        verticalScrollingCurrentPos -= i;

                        ScrollWindowEx(hWnd, 0, i, NULL, NULL, NULL, NULL, (SW_ERASE | SW_INVALIDATE | SW_SCROLLCHILDREN));
                    }

                    scroll_info.cbSize = sizeof(SCROLLINFO);
                    scroll_info.fMask = (SIF_RANGE | SIF_PAGE | SIF_POS);
                    scroll_info.nMin = 0;
                    scroll_info.nMax = WINDOWS_MANAGER_SCROLL_HEIGHT;
                    scroll_info.nPage = new_height;
                    scroll_info.nPos = verticalScrollingCurrentPos;

                    SetScrollInfo(hWnd, SB_VERT, &scroll_info, TRUE);

                    RedrawWindow(hWnd, NULL, NULL, (RDW_ERASE | RDW_INVALIDATE));

                    break;
                }

                case WM_MOUSEWHEEL:
                {
                    /* Proper 16-bit to 32-bit sign extend */
                    i = (int16_t)HIWORD(wParam);

                    if (i > 0)
                    {
                        /* Mouse wheel scrolled up */

                        new_scroll_pos = verticalScrollingCurrentPos - 32;
                    }
                    else if (i < 0)
                    {
                        /* Mouse wheel scrolled down */

                        new_scroll_pos = verticalScrollingCurrentPos + 32;
                    }

                    break;
                }

                case WM_VSCROLL:
                {
                    switch (LOWORD(wParam))
                    {
                        /* User clicked the scroll bar shaft above the scroll box */
                        case SB_PAGEUP:
                        {
                            new_scroll_pos = verticalScrollingCurrentPos - 32;
                            break;
                        }

                        /* User clicked the scroll bar shaft below the scroll box */
                        case SB_PAGEDOWN:
                        {
                            new_scroll_pos = verticalScrollingCurrentPos + 32;
                            break;
                        }

                        /* User clicked the top arrow */
                        case SB_LINEUP:
                        {
                            new_scroll_pos = verticalScrollingCurrentPos - 8;
                            break;
                        }

                        /* User clicked the bottom arrow */
                        case SB_LINEDOWN:
                        {
                            new_scroll_pos = verticalScrollingCurrentPos + 8;
                            break;
                        }

                        /* User dragged the scroll box */
                        case SB_THUMBPOSITION:
                        case SB_THUMBTRACK:
                        {
                            new_scroll_pos = HIWORD(wParam);
                            break;
                        }

                        default:
                        {
                            new_scroll_pos = verticalScrollingCurrentPos;
                        }
                    }

                    break;
                }

            }

            if (new_scroll_pos != verticalScrollingCurrentPos)
            {
                if (new_scroll_pos < 0)
                {
                    new_scroll_pos = 0;
                }
                else if (new_scroll_pos > verticalScrollingLimit)
                {
                    new_scroll_pos = verticalScrollingLimit;
                }

                /* How many pixels should the window be scrolled */
                i = verticalScrollingCurrentPos - new_scroll_pos;

                verticalScrollingCurrentPos = new_scroll_pos;

                ScrollWindowEx(hWnd, 0, i, NULL, NULL, NULL, NULL, (SW_ERASE | SW_INVALIDATE | SW_SCROLLCHILDREN));
                UpdateWindow(hWnd);

                scroll_info.cbSize = sizeof(SCROLLINFO);
                scroll_info.fMask = SIF_POS;
                scroll_info.nPos = verticalScrollingCurrentPos;

                SetScrollInfo(hWnd, SB_VERT, &scroll_info, TRUE);
            }

            return DefWindowProc(hWnd, Msg, wParam, lParam);
        }


        ////////////////////////////////////////////////////////////////
        // WindowsManagerPage: constructor and destructor
        ////////////////////////////////////////////////////////////////

        WindowsManagerPage::WindowsManagerPage()
        {
            name[0] = 0x00;
            windowsCount = 0;
            windows = nullptr;
            enterPageFunc = nullptr;
            leavePageFunc = nullptr;
        }

        void WindowsManagerPage::setName(const char* new_name)
        {
            strcpy_s(name, 32, new_name);
        }

        void WindowsManagerPage::setEnterAndLeaveFunctions(void (*enter_func)(), void (*leave_func)())
        {
            enterPageFunc = enter_func;
            leavePageFunc = leave_func;
        }

        void WindowsManagerPage::close()
        {
            if (nullptr != windows)
            {
                delete[](windows);
                windows = nullptr;
            }
        }


        ////////////////////////////////////////////////////////////////
        // WindowsManagerPage: add window to the page
        ////////////////////////////////////////////////////////////////
        void WindowsManagerPage::addWindow(HWND entry)
        {
            HWND* temp = new HWND [windowsCount + 1];

            std::memcpy(temp, windows, windowsCount * sizeof(HWND));

            if (nullptr != windows)
            {
                delete[](windows);
                windows = nullptr;
            }

            windows = temp;
            windows[windowsCount] = entry;
            windowsCount++;
        }


        ////////////////////////////////////////////////////////////////
        // WindowsManagerPage: hide or show windows
        ////////////////////////////////////////////////////////////////

        void WindowsManagerPage::hideWindows()
        {
            for (int i = 0; i < windowsCount; i++)
            {
                ShowWindow(windows[i], SW_HIDE);
            }
        }

        void WindowsManagerPage::showWindows()
        {
            for (int i = 0; i < windowsCount; i++)
            {
                ShowWindow(windows[i], SW_SHOW);
            }
        }

        ////////////////////////////////////////////////////////////////
        // WindowsManagerCustomFunction
        ////////////////////////////////////////////////////////////////

        WindowsManagerCustomFunction::WindowsManagerCustomFunction()
        {
            function = nullptr;
            param = 0;
        }

        void WindowsManagerCustomFunction::set(void_func_with_params new_function, void* new_param)
        {
            function = new_function;
            param = new_param;
        }

        void WindowsManagerCustomFunction::run(WPARAM wParam, LPARAM lParam)
        {
            if (nullptr != function)
            {
                function(wParam, lParam, param);
            }
        }


        ////////////////////////////////////////////////////////////////
        // WindowsManager: reseting and deconstructing
        ////////////////////////////////////////////////////////////////

        void WindowsManager::reset()
        {
            pagesCount = 0;
            pages = nullptr;
            currentPageNumber = (-1);

            staticFunctionsCount = 0;
            staticFunctions = nullptr;

            currentModuleInstance = NULL;
            currentClassName = nullptr;
            currentParent = NULL;
            currentStyleFlags = 0;

            setCurrentPosition(0, 0);
            updateReturningPosition();

            currentPaddingX = 0;
            currentPaddingY = 0;
            widthLimit = RECT_LOGO_X2;
            useEdges = false;

            std::memset(mainWindows, 0x00, 4 * sizeof(HWND));
        }

        WindowsManager::~WindowsManager()
        {
            int32_t i;

            if (nullptr != pages)
            {
                for (i = 0; i < pagesCount; i++)
                {
                    pages[i].close();
                }

                delete[](pages);
                pages = nullptr;
            }

            if (nullptr != staticFunctions)
            {
                delete[](staticFunctions);
                staticFunctions = nullptr;
            }
        }


        ////////////////////////////////////////////////////////////////
        // WindowsManager: setting up states
        ////////////////////////////////////////////////////////////////

        void WindowsManager::setCurrentModuleInstance(HINSTANCE instance)
        {
            currentModuleInstance = instance;
        }

        void WindowsManager::setCurrentPageNumber(int32_t number)
        {
            currentPageNumber = number;
        }

        void WindowsManager::setCurrentClassName(const char* name)
        {
            currentClassName = name;
        }

        void WindowsManager::setCurrentParent(HWND parent)
        {
            currentParent = parent;
        }

        void WindowsManager::setCurrentStyleFlags(DWORD style)
        {
            currentStyleFlags = style;
        }

        void WindowsManager::setCurrentPadding(int32_t x, int32_t y)
        {
            currentPaddingX = x;
            currentPaddingY = y;
        }

        void WindowsManager::updateReturningPosition()
        {
            returningPosX = currentPosX;
        }

        void WindowsManager::setCurrentPosition(int32_t x, int32_t y)
        {
            currentPosX = x;
            currentPosY = y;
        }

        void WindowsManager::offsetCurrentPosition(int32_t x, int32_t y)
        {
            currentPosX += x;
            currentPosY += y;
        }


        ////////////////////////////////////////////////////////////////
        // WindowsManager: add page
        ////////////////////////////////////////////////////////////////
        void WindowsManager::addPage(const char* name, void (*enter_func)(), void (*leave_func)())
        {
            WindowsManagerPage* temp = new WindowsManagerPage [pagesCount + 1];

            std::memcpy(temp, pages, pagesCount * sizeof(WindowsManagerPage));

            if (nullptr != pages)
            {
                delete[](pages);
                pages = nullptr;
            }

            pages = temp;
            pages[pagesCount].setName(name);
            pages[pagesCount].setEnterAndLeaveFunctions(enter_func, leave_func);

            currentPageNumber = pagesCount;
            pagesCount++;
        }


        ////////////////////////////////////////////////////////////////
        // WindowsManager: switch pages
        // (-2) one to the left
        // (-1) one to the right
        ////////////////////////////////////////////////////////////////
        void WindowsManager::switchPage(int32_t number)
        {
            char bufor[32];
            int previous_page_number = currentPageNumber;

            if (pagesCount <= 0)
            {
                currentPageNumber = (-1);

                return;
            }

            switch (number)
            {
                case (-2):
                {
                    currentPageNumber--;
                    break;
                }

                case (-1):
                {
                    currentPageNumber++;
                    break;
                }

                default:
                {
                    currentPageNumber = number;
                }
            }

            if (currentPageNumber < 0)
            {
                currentPageNumber = 0;
            }
            else if (currentPageNumber >= pagesCount)
            {
                currentPageNumber = (pagesCount - 1);
            }

            for (number = 0; number < pagesCount; number++)
            {
                pages[number].hideWindows();
            }

            if ((previous_page_number >= 0) && (previous_page_number < pagesCount))
            {
                if (nullptr != pages[previous_page_number].leavePageFunc)
                {
                    pages[previous_page_number].leavePageFunc();
                }
            }

            pages[currentPageNumber].showWindows();

            if (nullptr != pages[currentPageNumber].enterPageFunc)
            {
                pages[currentPageNumber].enterPageFunc();
            }

            /* Update pages label */

            sprintf_s(bufor, 32, "[page %d/%d] %s", (currentPageNumber + 1), pagesCount, pages[currentPageNumber].name);

            SetWindowText(mainWindows[2], bufor);
        }


        ////////////////////////////////////////////////////////////////
        // WindowsManager: add menu function
        ////////////////////////////////////////////////////////////////
        HMENU WindowsManager::addStaticFunction(void_func_with_params function, void* custom_param)
        {
            WindowsManagerCustomFunction* temp = new WindowsManagerCustomFunction [staticFunctionsCount + 1];

            std::memcpy(temp, staticFunctions, staticFunctionsCount * sizeof(WindowsManagerCustomFunction));

            if (nullptr != staticFunctions)
            {
                delete[](staticFunctions);
                staticFunctions = nullptr;
            }

            staticFunctions = temp;

            staticFunctions[staticFunctionsCount].set(function, custom_param);
            staticFunctionsCount++;

            return (HMENU)(WINDOWS_MANAGER_MENU_ID + staticFunctionsCount - 1);
        }


        ////////////////////////////////////////////////////////////////
        // WindowsManager: add the "CLIENTEDGE" extended style
        ////////////////////////////////////////////////////////////////
        void WindowsManager::addEdgesToNextWindow()
        {
            useEdges = true;
        }


        ////////////////////////////////////////////////////////////////
        // WindowsManager: add window
        // (position_flags 0x01) jump to new line after this element
        // (position_flags 0x02) center horizontally
        // (position_flags 0x04) place in the center of the screen
        ////////////////////////////////////////////////////////////////
        HWND WindowsManager::addWindow
        (
            const char* name,
            int32_t width, int32_t height,
            void_func_with_params function, void* custom_param,
            uint8_t position_flags
        )
        {
            HMENU menu_id;
            HWND result;

            /* Correct position */

            if ((currentPosX + width) > widthLimit)
            {
                currentPosX = returningPosX;
            }

            if (0x02 & position_flags)
            {
                currentPosX = ((widthLimit - width) / 2);
            }

            if (0x04 & position_flags)
            {
                currentPosX = ((GetSystemMetrics(SM_CXSCREEN) - width) / 2);
                currentPosY = ((GetSystemMetrics(SM_CYSCREEN) - height) / 2);
            }

            /* Create window */

            if (nullptr != function)
            {
                menu_id = addStaticFunction(function, custom_param);

                if (0 == menu_id)
                {
                    return NULL;
                }
            }
            else
            {
                menu_id = 0;
            }

            if (useEdges)
            {
                result = CreateWindowEx
                (
                    WS_EX_CLIENTEDGE,
                    currentClassName, name, currentStyleFlags,
                    currentPosX, currentPosY, width, height,
                    currentParent, menu_id, currentModuleInstance, NULL
                );

                useEdges = false;
            }
            else
            {
                result = CreateWindow
                (
                    currentClassName, name, currentStyleFlags,
                    currentPosX, currentPosY, width, height,
                    currentParent, menu_id, currentModuleInstance, NULL
                );
            }

            /* Update positions */

            currentPosX += (width + currentPaddingX);

            if ((0x01 & position_flags) || (currentPosX >= widthLimit))
            {
                currentPosX = returningPosX;

                currentPosY += (height + currentPaddingY);
            }

            /* Test the result, set font, add to the page */

            if (NULL == result)
            {
                return NULL;
            }

            SendMessage(result, WM_SETFONT, (WPARAM)myWindowFont, FALSE);

            if (currentPageNumber >= 0)
            {
                pages[currentPageNumber].addWindow(result);
            }

            return result;
        }


        ////////////////////////////////////////////////////////////////
        // WindowsManager: create main windows
        ////////////////////////////////////////////////////////////////
        bool WindowsManager::createMainWindows()
        {
            int32_t a;
            WNDCLASSEX window_class[5];
            HBRUSH window_background;

            const int WINDOW_HEIGHT = 24;
            const int WINDOW_PADDING = 16;

            /********************************/
            /* Register window classes */

            for (a = 0; a < 5; a++)
            {
                ZeroMemory(&(window_class[a]), sizeof(WNDCLASSEX));
                window_class[a].cbSize = sizeof(WNDCLASSEX);
                window_class[a].hInstance = currentModuleInstance;
                window_class[a].style = (CS_OWNDC | CS_VREDRAW | CS_HREDRAW);

                switch (a)
                {
                    case 0: // main
                    case 2: // scroll
                    {
                        window_background = (HBRUSH)(1 + COLOR_BTNFACE);
                        break;
                    }

                    default:
                    {
                        window_background = (HBRUSH)GetStockObject(BLACK_BRUSH);
                    }
                }

                window_class[a].hbrBackground = window_background;
            }

            window_class[0].hCursor = LoadCursor(currentModuleInstance, IDC_ARROW);
            window_class[0].hIcon = LoadIcon(currentModuleInstance, MAKEINTRESOURCE(IDM_ICON));
            window_class[0].hIconSm = window_class[0].hIcon;
            window_class[0].lpfnWndProc = procedureOfMainWindow;
            window_class[0].lpszClassName = WINDOW_CLASS_NAME_1;

            window_class[1].lpfnWndProc = procedureOfRenderWindow;
            window_class[1].lpszClassName = WINDOW_CLASS_NAME_2;

            window_class[2].lpfnWndProc = procedureOfScrollWindow;
            window_class[2].lpszClassName = WINDOW_CLASS_NAME_3;

            window_class[3].lpfnWndProc = procedureOfObjectMovingWindow;
            window_class[3].lpszClassName = WINDOW_CLASS_NAME_4;

            window_class[4].lpfnWndProc = procedureOfObjectRotatingWindow;
            window_class[4].lpszClassName = WINDOW_CLASS_NAME_5;

            for (a = 0; a < 5; a++)
            {
                if (false == RegisterClassEx(&(window_class[a])))
                {
                    return false;
                }
            }

            /********************************/
            /* Create main window */

            currentPageNumber = (-1);

            setCurrentClassName(WINDOW_CLASS_NAME_1);
            setCurrentStyleFlags(WS_OVERLAPPEDWINDOW);

            mainWindows[0] = addWindow("Zookie Wizard", RECT_WINDOW_X, RECT_WINDOW_Y, nullptr, 0, 0x04);

            if (0 == mainWindows[0])
            {
                return false;
            }

            setCurrentParent(mainWindows[0]);

            /********************************/
            /* Create renderer window */

            setCurrentClassName(WINDOW_CLASS_NAME_2);
            setCurrentStyleFlags(WS_CHILD | WS_VISIBLE);
            setCurrentPosition(RECT_RENDER_X1, RECT_RENDER_Y1);

            mainWindows[1] = addWindow("", RECT_RENDER_X2, RECT_RENDER_Y2, nullptr, 0, 0);

            if (0 == mainWindows[1])
            {
                return false;
            }

            /********************************/
            /* Create buttons (previous page, next page) */

            setCurrentClassName("BUTTON");
            setCurrentStyleFlags(WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON);
            setCurrentPosition(RECT_TABS_X1, RECT_TABS_Y1 - 8);
            setCurrentPadding(8, 0);

            if (0 == addWindow("<<", 24, 20, staticFuncSwitchPagesLeft, 0, 0))
            {
                return false;
            }

            if (0 == addWindow(">>", 24, 20, staticFuncSwitchPagesRight, 0, 0))
            {
                return false;
            }

            /********************************/
            /* Create page label */

            setCurrentClassName("STATIC");
            setCurrentStyleFlags(WS_CHILD | WS_VISIBLE);

            mainWindows[2] = addWindow("", 208, WINDOW_HEIGHT, nullptr, 0, 0);

            if (0 == mainWindows[2])
            {
                return false;
            }

            /********************************/
            /* Create scrollable static window */

            setCurrentClassName(WINDOW_CLASS_NAME_3);
            setCurrentStyleFlags(WS_CHILD | WS_VISIBLE | WS_VSCROLL);
            setCurrentPosition(0, RECT_TABS_Y1 + WINDOW_HEIGHT);

            mainWindows[3] = addWindow("", RECT_LOGO_X2, RECT_WINDOW_Y - RECT_TABS_Y1 - WINDOW_HEIGHT, nullptr, 0, 0);

            if (0 == mainWindows[3])
            {
                return false;
            }

            /********************************/
            /* Create line decoration */

            setCurrentClassName("STATIC");
            setCurrentStyleFlags(WS_CHILD | WS_VISIBLE | SS_ETCHEDHORZ);
            setCurrentPosition(0, RECT_TABS_Y1 + WINDOW_HEIGHT - 2);

            if (0 == addWindow("", widthLimit, 2, nullptr, 0, 0))
            {
                return false;
            }

            /********************************/
            /* End of the windows creation */

            setCurrentParent(0);

            return true;
        }


        ////////////////////////////////////////////////////////////////
        // WindowsManager: create object movement windows
        // (classes are registered when creating main windows)
        ////////////////////////////////////////////////////////////////
        bool WindowsManager::createObjectMovementWindows()
        {
            int32_t a;

            const int WINDOW_HEIGHT = 20;
            const int WINDOW_PADDING = 8;
            const int BOX_WIDTH = 256;

            const char* description[3] =
            {
                "<< BUTTONS >\n" \
                  "(option 1): [RMB] or [A][D][S][W]\n" \
                  "(option 2): [LMB] or [A][D][Q][E]",
                "<< MOVEMENT >>\n" \
                  "(1): [x/y]\n" \
                  "(2): [x/z]",
                "<< ROTATION >>\n" \
                  "(1): [z-axis / strafe-axis]\n" \
                  "(2): [z-axis / look-axis]"
            };

            const char* class_name[2] = {WINDOW_CLASS_NAME_4, WINDOW_CLASS_NAME_5};

            setCurrentStyleFlags(WS_CHILD);

            for (a = 0; a < 3; a++)
            {
                /********************************/
                /* Create dummy label */

                setCurrentClassName("STATIC");

                if (0 == addWindow(description[a], RECT_TABS_X2, (3 * WINDOW_HEIGHT), nullptr, nullptr, 0x01))
                {
                    return false;
                }

                if (0 == a)
                {
                    offsetCurrentPosition(0, WINDOW_PADDING);
                }

                if (a > 0)
                {
                    /********************************/
                    /* Create empty area window */

                    setCurrentClassName(class_name[a - 1]);

                    addEdgesToNextWindow();
                    if (0 == addWindow("", BOX_WIDTH, BOX_WIDTH, nullptr, nullptr, 0x03))
                    {
                        return false;
                    }

                    offsetCurrentPosition(0, WINDOW_PADDING);
                }
            }

            /********************************/
            /* End of the windows creation */

            return true;
        }


        ////////////////////////////////////////////////////////////////
        // WindowsManager: get main windows
        ////////////////////////////////////////////////////////////////

        HWND WindowsManager::getMainWindow() const
        {
            return mainWindows[0];
        }

        HWND WindowsManager::getRenderWindow() const
        {
            return mainWindows[1];
        }

        HWND WindowsManager::getPageLabelWindow() const
        {
            return mainWindows[2];
        }

        HWND WindowsManager::getScrollWindow() const
        {
            return mainWindows[3];
        }


        ////////////////////////////////////////////////////////////////
        // WindowsManager: get specific window
        ////////////////////////////////////////////////////////////////
        HWND WindowsManager::getSpecificWindow(int32_t page, int32_t place)
        {
            if ((page >= 0) && (page < pagesCount))
            {
                if (place < 0)
                {
                    place = pages[page].windowsCount + place;
                }

                if ((place >= 0) && (place < pages[page].windowsCount))
                {
                    return pages[page].windows[place];
                }
            }

            return 0;
        }


        ////////////////////////////////////////////////////////////////
        // WindowsManager: run static function
        ////////////////////////////////////////////////////////////////
        void WindowsManager::runStaticFunction(int32_t id, WPARAM wparam, LPARAM lparam) const
        {
            if ((id >= 0) && (id < staticFunctionsCount))
            {
                staticFunctions[id].run(wparam, lparam);
            }
        }


        ////////////////////////////////////////////////////////////////
        // WindowsManager: display message box
        ////////////////////////////////////////////////////////////////
        void WindowsManager::displayMessage(uint8_t type, const char* text) const
        {
            const char* box_title = nullptr;
            uint32_t box_type = 0;

            switch (type)
            {
                case WINDOWS_MANAGER_MESSAGE_ERROR:
                {
                    box_title = MESSAGE_TITLE_ERROR;
                    box_type = MB_ICONERROR;

                    break;
                }

                case WINDOWS_MANAGER_MESSAGE_WARNING:
                {
                    box_title = MESSAGE_TITLE_ERROR;
                    box_type = MB_ICONWARNING;

                    break;
                }

                case WINDOWS_MANAGER_MESSAGE_INFO:
                {
                    box_title = MESSAGE_TITLE_INFO;
                    box_type = MB_ICONINFORMATION;

                    break;
                }
            }

            MessageBox(getMainWindow(), text, box_title, box_type);
        }

    }
}
