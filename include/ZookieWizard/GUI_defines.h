#ifndef H_ZOOKIEWIZARD_GUI_DEFINES
#define H_ZOOKIEWIZARD_GUI_DEFINES

#define IDM_VERSION 1
#define IDM_ICON 2
#define IDM_BITMAP 3

// (X1,Y1) -> top-left corner
// (X2,Y2) -> width and height

static const int RECT_WINDOW_X = 1280;
static const int RECT_WINDOW_Y = 800;

static const int RECT_LOGO_X1 = 0;
static const int RECT_LOGO_Y1 = 0;
static const int RECT_LOGO_X2 = (RECT_WINDOW_X / 4);
static const int RECT_LOGO_Y2 = 64;

static const int NODE_TREE_X1 = 0;
static const int NODE_TREE_Y1 = 64;
static const int NODE_TREE_X2 = (RECT_WINDOW_X / 4);
static const int NODE_TREE_Y2 = (RECT_WINDOW_Y - RECT_LOGO_Y2);

static const int RECT_RENDER_X1 = (RECT_WINDOW_X - 2 * RECT_LOGO_X2);
static const int RECT_RENDER_Y1 = 0;
static const int RECT_RENDER_X2 = (RECT_WINDOW_X - RECT_RENDER_X1);
static const int RECT_RENDER_Y2 = (RECT_WINDOW_Y);

static const int RECT_TABS_X1 = 16;
static const int RECT_TABS_Y1 = 16;
static const int RECT_TABS_X2 = (RECT_LOGO_X2 - 3 * 16);
static const int RECT_TABS_Y2 = (RECT_WINDOW_Y - 2 * 16);

static const int SCROLL_WINDOW_X = (RECT_WINDOW_X / 4);
static const int SCROLL_WINDOW_Y = (RECT_TABS_Y1);

#endif
