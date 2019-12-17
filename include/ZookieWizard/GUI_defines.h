#ifndef H_ZOOKIEWIZARD_GUIDEFINES
#define H_ZOOKIEWIZARD_GUIDEFINES

#define IDM_VERSION 1
#define IDM_MENU 2
#define IDM_ICON 3
#define IDM_BITMAP 4

#define IDM_MENU_KAO_SET 101
#define IDM_MENU_VERSION_1 102
#define IDM_MENU_VERSION_2 103
#define IDM_MENU_VERSION_3 104
#define IDM_MENU_AR_OPEN 105
#define IDM_MENU_AR_SAVE 106
#define IDM_MENU_AR_EXPORT_SCRIPTS 107
#define IDM_MENU_AR_EXPORT_PROXIES 108

#define IDM_EDITBOX_MEDIADIR 109
#define IDM_BUTTON_RESET_CAMERA 110
#define IDM_CHECKBOX_RENDER_INVISIBLE 111
#define IDM_CHECKBOX_RENDER_BOXZONES 112
#define IDM_CHECKBOX_RENDER_PROXIES 113

extern const char* WINDOW_CLASS_NAME_1;
extern const char* WINDOW_CLASS_NAME_2;

// (X1,Y1) -> top-left corner
// (X2,Y2) -> width and height

static const int RECT_WINDOW_X = 640;
static const int RECT_WINDOW_Y = 480;

static const int RECT_LOGO_X1 = 0;
static const int RECT_LOGO_Y1 = 0;
static const int RECT_LOGO_X2 = (RECT_WINDOW_X / 2);
static const int RECT_LOGO_Y2 = 64;

static const int RECT_RENDER_X1 = (RECT_WINDOW_X - RECT_LOGO_X2);
static const int RECT_RENDER_Y1 = 0;
static const int RECT_RENDER_X2 = (RECT_WINDOW_X - RECT_RENDER_X1);
static const int RECT_RENDER_Y2 = (RECT_WINDOW_Y);

static const int RECT_TABS_X1 = 16;
static const int RECT_TABS_Y1 = (RECT_LOGO_Y1 + RECT_LOGO_Y2 + 16);
static const int RECT_TABS_X2 = (RECT_LOGO_X2 - 2 * 16);
static const int RECT_TABS_Y2 = (RECT_WINDOW_Y - RECT_LOGO_Y1 - 16);

#endif
