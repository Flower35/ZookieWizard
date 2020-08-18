#ifndef H_WINDOWSMANAGER
#define H_WINDOWSMANAGER

#include <ZookieWizard/ZookieWizard.h>

namespace ZookieWizard
{
    namespace GUI
    {
        ////////////////////////////////////////////////////////////////
        // Helper structures
        ////////////////////////////////////////////////////////////////

        typedef void (*void_func_with_params)(WPARAM, LPARAM, void*);

        #define WINDOWS_MANAGER_MENU_ID 101
        #define WINDOWS_MANAGER_SCROLL_HEIGHT (int)(3.5 * RECT_WINDOW_Y)

        #define WINDOWS_MANAGER_MESSAGE_ERROR 0
        #define WINDOWS_MANAGER_MESSAGE_WARNING 1
        #define WINDOWS_MANAGER_MESSAGE_INFO 2

        struct WindowsManagerPage
        {
            char name[32];
            int32_t windowsCount;
            HWND* windows;
            void (*enterPageFunc)();
            void (*leavePageFunc)();

            WindowsManagerPage();
            void close();

            void setName(const char* new_name);
            void setEnterAndLeaveFunctions(void (*enter_func)(), void (*leave_func)());
            void addWindow(HWND entry);

            void hideWindows();
            void showWindows();
        };

        struct WindowsManagerCustomFunction
        {
            void_func_with_params function;
            void* param;

            WindowsManagerCustomFunction();
            void set(void_func_with_params new_function, void* new_param);
            void run(WPARAM wParam, LPARAM lParam);
        };


        ////////////////////////////////////////////////////////////////
        // WINDOWS MANAGER
        ////////////////////////////////////////////////////////////////

        class WindowsManager
        {
            /* Properties */

            private:

                int32_t pagesCount;
                WindowsManagerPage* pages;
                int32_t currentPageNumber;

                int32_t staticFunctionsCount;
                WindowsManagerCustomFunction* staticFunctions;

                HINSTANCE currentModuleInstance;
                const char* currentClassName;
                HWND currentParent;
                int32_t currentStyleFlags;
                int32_t returningPosX;
                int32_t currentPosX;
                int32_t currentPosY;
                int32_t currentPaddingX;
                int32_t currentPaddingY;
                int32_t widthLimit;
                bool useEdges;

                HWND mainWindows[4];

            /* Methods */

            public:

                ~WindowsManager();

                void reset();

                void setCurrentModuleInstance(HINSTANCE instance);
                void setCurrentPageNumber(int32_t number);
                void setCurrentClassName(const char* name);
                void setCurrentParent(HWND parent);
                void setCurrentStyleFlags(DWORD style);
                void setCurrentPadding(int32_t x, int32_t y);
                void updateReturningPosition();
                void getCurrentPosition(int32_t* x, int32_t* y);
                void setCurrentPosition(int32_t x, int32_t y);
                void offsetCurrentPosition(int32_t x, int32_t y);

                void addPage(const char* name, void (*enter_func)(), void (*leave_func)());
                void switchPage(int32_t number);

                HMENU addStaticFunction(void_func_with_params function, void* custom_param);

                void addEdgesToNextWindow();

                HWND addWindow
                (
                    const char* name,
                    int32_t width, int32_t height,
                    void_func_with_params function, void* custom_param,
                    uint8_t position_flags
                );

                bool createMainWindows();
                bool createObjectMovementWindows();

                HWND getMainWindow() const;
                HWND getRenderWindow() const;
                HWND getPageLabelWindow() const;
                HWND getScrollWindow() const;

                HWND getSpecificWindow(int32_t page, int32_t place) const;

                void runStaticFunction(int32_t id, WPARAM wparam, LPARAM lparam) const;

                void displayMessage(uint8_t type, const char* text) const;

                LRESULT overriddenListboxKeyDispatch(HWND listbox_window, uint16_t keycode) const;
        };

        extern WindowsManager theWindowsManager;
    }
}

#endif
