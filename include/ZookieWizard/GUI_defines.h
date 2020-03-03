#ifndef H_ZOOKIEWIZARD_GUI_DEFINES
#define H_ZOOKIEWIZARD_GUI_DEFINES

#define IDM_VERSION 1
#define IDM_ICON 2
#define IDM_BITMAP 3

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
static const int RECT_TABS_X2 = (RECT_LOGO_X2 - 3 * 16);
static const int RECT_TABS_Y2 = (RECT_WINDOW_Y - RECT_LOGO_Y1 - 2 * 16);

#endif
