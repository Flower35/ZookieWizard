#include <ZookieWizard/ZookieWizard.h>
#include <ZookieWizard/WindowsManager.h>

#include <kao2ar/Archive.h>
#include <kao2engine/Log.h>

#include <kao2engine/eMaterial.h>
#include <kao2engine/eMaterialState.h>
#include <kao2engine/eTexture.h>
#include <kao2engine/eTexTransform.h>
#include <kao2engine/eLeafCtrl.h>
#include <kao2engine/eBitmap.h>
#include <kao2engine/eGeometry.h>

namespace ZookieWizard
{
    namespace GUI
    {
        ////////////////////////////////////////////////////////////////
        // Materials Manager: Variables and Definitions
        ////////////////////////////////////////////////////////////////

        int matMgr_MatList_Count;
        int matMgr_MatList_MaxLength;
        eMaterial** matMgr_MatList;
        int matMgr_MatList_Current;

        int matMgr_TexList_Count;
        int matMgr_TexList_MaxLength;
        eTexture** matMgr_TexList;
        int matMgr_TexList_Current;

        int matMgr_BmpList_Count;
        int matMgr_BmpList_MaxLength;
        eBitmap** matMgr_BmpList;
        int matMgr_BmpList_Current;

        GLuint matMgr_textures[1];

        int matMgr_RenderedList;
        int matMgr_scrollPos;
        float matMgr_mousePos[2];
        int matMgr_mouseMode;

        #define MATMGR_RENDERED_LIST_MIN              1

        #define MATMGR_RENDERED_LIST_THUMBNAILS_GRID  1
        #define MATMGR_RENDERED_LIST_SINGLE_BITMAP    2

        #define MATMGR_RENDERED_LIST_MAX              2

        const int THUMBNAILS_IN_GRID = 10;
        const float THUMBNAIL_HW = 1.0f;
        const float BIG_THUMBNAIL_HW = 7.5f;

        #define MATMGR_WINDOW_SUBPAGENAME                   0

        #define MATMGR_INFO_WINDOW_START                    1

        #define MATMGR_INFO_WINDOW_TOTALS_LABEL             1
        #define MATMGR_INFO_WINDOW_TOTALS_BITMAPS           2
        #define MATMGR_INFO_WINDOW_TOTALS_TEXTURES          3
        #define MATMGR_INFO_WINDOW_TOTALS_STATES            4
        #define MATMGR_INFO_WINDOW_TOTALS_MATERIALS         5
        #define MATMGR_INFO_WINDOW_OPTIMIZE_PAUSE           6
        #define MATMGR_INFO_WINDOW_OPTIMIZE_BMPBTN          7
        #define MATMGR_INFO_WINDOW_OPTIMIZE_TEXBTN          8
        #define MATMGR_INFO_WINDOW_OPTIMIZE_NOTES           9

        #define MATMGR_INFO_WINDOW_END                      9

        #define MATMGR_MATERIALS_WINDOW_START              10

        #define MATMGR_MATERIALS_WINDOW_LIST               10
        #define MATMGR_MATERIALS_WINDOW_TEXLIST_PAUSE      11
        #define MATMGR_MATERIALS_WINDOW_TEXLIST_LABEL      12
        #define MATMGR_MATERIALS_WINDOW_TEXLIST            13
        #define MATMGR_MATERIALS_WINDOW_TEXTBTNS_CREATE    14
        #define MATMGR_MATERIALS_WINDOW_TEXTBTNS_REMOVE    15
        #define MATMGR_MATERIALS_WINDOW_TEXTBTNS_MOVEUP    16
        #define MATMGR_MATERIALS_WINDOW_TEXTBTNS_MOVEDOWN  17
        #define MATMGR_MATERIALS_WINDOW_TEXTBTNS_REPLACE   18
        #define MATMGR_MATERIALS_WINDOW_STATE_PAUSE        19
        #define MATMGR_MATERIALS_WINDOW_STATECHECK_USED    20
        #define MATMGR_MATERIALS_WINDOW_STATE_STATUS       21
        #define MATMGR_MATERIALS_WINDOW_STATEBTN_CLONE     22
        #define MATMGR_MATERIALS_WINDOW_STATE_C1_LABEL     23
        #define MATMGR_MATERIALS_WINDOW_STATEEDIT_C1_R     24
        #define MATMGR_MATERIALS_WINDOW_STATEEDIT_C1_G     25
        #define MATMGR_MATERIALS_WINDOW_STATEEDIT_C1_B     26
        #define MATMGR_MATERIALS_WINDOW_STATE_C2_LABEL     27
        #define MATMGR_MATERIALS_WINDOW_STATEEDIT_C2_R     28
        #define MATMGR_MATERIALS_WINDOW_STATEEDIT_C2_G     29
        #define MATMGR_MATERIALS_WINDOW_STATEEDIT_C2_B     30
        #define MATMGR_MATERIALS_WINDOW_STATE_C3_LABEL     31
        #define MATMGR_MATERIALS_WINDOW_STATEEDIT_C3_R     32
        #define MATMGR_MATERIALS_WINDOW_STATEEDIT_C3_G     33
        #define MATMGR_MATERIALS_WINDOW_STATEEDIT_C3_B     34
        #define MATMGR_MATERIALS_WINDOW_STATE_C4_LABEL     35
        #define MATMGR_MATERIALS_WINDOW_STATEEDIT_C4_R     36
        #define MATMGR_MATERIALS_WINDOW_STATEEDIT_C4_G     37
        #define MATMGR_MATERIALS_WINDOW_STATEEDIT_C4_B     38
        #define MATMGR_MATERIALS_WINDOW_STATE_48_LABEL     39
        #define MATMGR_MATERIALS_WINDOW_STATEEDIT_48       40
        #define MATMGR_MATERIALS_WINDOW_STATECHECK_4C      41
        #define MATMGR_MATERIALS_WINDOW_FLAGS_PAUSE        42
        #define MATMGR_MATERIALS_WINDOW_FLAGS_LABEL        43
        #define MATMGR_MATERIALS_WINDOW_FLAGSCHECK1        44
        #define MATMGR_MATERIALS_WINDOW_FLAGSCHECK2        45
        #define MATMGR_MATERIALS_WINDOW_FLAGSCHECK3        46
        #define MATMGR_MATERIALS_WINDOW_FLAGSCHECK4        47
        #define MATMGR_MATERIALS_WINDOW_COLLIST_PAUSE      48
        #define MATMGR_MATERIALS_WINDOW_COLLIST_LABEL      49
        #define MATMGR_MATERIALS_WINDOW_COLLIST            50
        #define MATMGR_MATERIALS_WINDOW_SNDLIST_PAUSE      51
        #define MATMGR_MATERIALS_WINDOW_SNDLIST_LABEL      52
        #define MATMGR_MATERIALS_WINDOW_SNDLIST            53
        #define MATMGR_MATERIALS_WINDOW_NAMEEDIT_PAUSE     54
        #define MATMGR_MATERIALS_WINDOW_NAMEEDIT_LABEL     55
        #define MATMGR_MATERIALS_WINDOW_NAMEEDIT           56
        #define MATMGR_MATERIALS_WINDOW_ALPHAEDIT_PAUSE    57
        #define MATMGR_MATERIALS_WINDOW_ALPHAEDIT_LABEL    58
        #define MATMGR_MATERIALS_WINDOW_ALPHAEDIT          59

        #define MATMGR_MATERIALS_WINDOW_END                59

        #define MATMGR_TEXTURES_WINDOW_START               60

        #define MATMGR_TEXTURES_WINDOW_LIST                60
        #define MATMGR_TEXTURES_WINDOW_FLAGS_PAUSE         61
        #define MATMGR_TEXTURES_WINDOW_FLAGS_LABEL         62
        #define MATMGR_TEXTURES_WINDOW_FLAGSCHECK1         63
        #define MATMGR_TEXTURES_WINDOW_FLAGSCHECK2         64
        #define MATMGR_TEXTURES_WINDOW_FLAGSCHECK3         65
        #define MATMGR_TEXTURES_WINDOW_BMPBTNS_PAUSE       66
        #define MATMGR_TEXTURES_WINDOW_BMPBTNS_CREATE      67
        #define MATMGR_TEXTURES_WINDOW_BMPBTNS_REMOVE      68
        #define MATMGR_TEXTURES_WINDOW_BMPBTNS_REPLACE     69
        #define MATMGR_TEXTURES_WINDOW_FORM_PAUSE          70
        #define MATMGR_TEXTURES_WINDOW_FORMCHECK_USED      71
        #define MATMGR_TEXTURES_WINDOW_FORMKEYS_LABEL      72
        #define MATMGR_TEXTURES_WINDOW_FORMKEYS            73
        #define MATMGR_TEXTURES_WINDOW_FORMBTNS_CAT_SX     74
        #define MATMGR_TEXTURES_WINDOW_FORMBTNS_CAT_SY     75
        #define MATMGR_TEXTURES_WINDOW_FORMBTNS_CAT_U      76
        #define MATMGR_TEXTURES_WINDOW_FORMBTNS_CAT_V      77
        #define MATMGR_TEXTURES_WINDOW_FORM_OORTLIST       78
        #define MATMGR_TEXTURES_WINDOW_FORMEDIT_TIME       79
        #define MATMGR_TEXTURES_WINDOW_FORMEDIT_VALUE      80
        #define MATMGR_TEXTURES_WINDOW_FORMBTNS_CREATE     81
        #define MATMGR_TEXTURES_WINDOW_FORMBTNS_REMOVE     82

        #define MATMGR_TEXTURES_WINDOW_END                 82

        #define MATMGR_BITMAPS_WINDOW_START                83

        #define MATMGR_BITMAPS_WINDOW_LIST                 83
        #define MATMGR_BITMAPS_WINDOW_PATHEDIT_PAUSE       84
        #define MATMGR_BITMAPS_WINDOW_PATHEDIT_LABEL       85
        #define MATMGR_BITMAPS_WINDOW_PATHEDIT             86
        #define MATMGR_BITMAPS_WINDOW_EXTCHECK_PAUSE       87
        #define MATMGR_BITMAPS_WINDOW_EXTCHECK             88
        #define MATMGR_BITMAPS_WINDOW_BTNS_PAUSE           89
        #define MATMGR_BITMAPS_WINDOW_BTNS_BROWSE          90
        #define MATMGR_BITMAPS_WINDOW_BTNS_ENLARGE         91
        #define MATMGR_BITMAPS_WINDOW_BTNS_EXPORT          92
        #define MATMGR_BITMAPS_WINDOW_BTNS_REIMPORT        93
        #define MATMGR_BITMAPS_WINDOW_BTNS_ALL_EXPORT      94
        #define MATMGR_BITMAPS_WINDOW_BTNS_ALL_REIMPORT    95
        #define MATMGR_BITMAPS_WINDOW_BTNS_BULK_EXPORT     96
        #define MATMGR_BITMAPS_WINDOW_BTNS_BULK_REIMPORT   97

        #define MATMGR_BITMAPS_WINDOW_END                  97

        #define MATMGR_WINDOWS_COUNT                       98

        static bool matMgr_UpdatingWindowsNotByUser;
        int32_t matMgr_MaterialTextureId;
        int32_t matMgr_TextureKeyframesCategory;
        int32_t matMgr_TextureKeyframesId;

        int32_t matMgr_CurrentSubpage;
        HWND matMgr_Windows[MATMGR_WINDOWS_COUNT];

        static const char* matMgr_SubpageNames[4] =
        {
            "Statistics and Optimizations",
            "\"Materials\" (contain \"Textures\")",
            "\"Textures\" (contain \"Bitmaps\")",
            "\"Bitmaps\" (actual 2D Images)"
        };


        ////////////////////////////////////////////////////////////////
        // Materials Manager: Constructor
        ////////////////////////////////////////////////////////////////
        bool prepareMaterialsManager()
        {
            uint8_t pixels[32 * 32 * 3];

            matMgr_MatList_Count = 0;
            matMgr_MatList_MaxLength = 0;
            matMgr_MatList = nullptr;
            matMgr_MatList_Current = (-1);

            matMgr_TexList_Count = 0;
            matMgr_TexList_MaxLength = 0;
            matMgr_TexList = nullptr;
            matMgr_TexList_Current = (-1);

            matMgr_BmpList_Count = 0;
            matMgr_BmpList_MaxLength = 0;
            matMgr_BmpList = nullptr;
            matMgr_BmpList_Current = (-1);

            matMgr_RenderedList = MATMGR_RENDERED_LIST_THUMBNAILS_GRID;
            matMgr_scrollPos = 0;
            matMgr_mousePos[0] = 0;
            matMgr_mousePos[1] = 0;
            matMgr_mouseMode = 0;

            matMgr_UpdatingWindowsNotByUser = false;
            matMgr_MaterialTextureId = (-1);
            matMgr_TextureKeyframesCategory = (-1);
            matMgr_TextureKeyframesId = 0;
            matMgr_CurrentSubpage = 0;

            /* Generate misc textures */

            glGenTextures(1, matMgr_textures);

            for (int y = 0; y < 32; y++)
            {
                for (int x = 0; x < 32; x++)
                {
                    uint8_t shade = (((x < 16) && (y < 16)) || ((x >= 16) && (y >= 16)))
                      ? 0xC0 : 0xFF;

                    int place = (y * 32 * 3) + (x * 3);

                    pixels[place + 0] = shade;
                    pixels[place + 1] = shade;
                    pixels[place + 2] = shade;
                }
            }

            glBindTexture(GL_TEXTURE_2D, matMgr_textures[0]);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, 32, 32, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glBindTexture(GL_TEXTURE_2D, 0);

            return true;
        }


        ////////////////////////////////////////////////////////////////
        // Materials Manager: Destructor
        ////////////////////////////////////////////////////////////////
        void clearMaterialsManager()
        {
            glDeleteTextures(1, matMgr_textures);

            if (nullptr != matMgr_MatList)
            {
                delete[](matMgr_MatList);
                matMgr_BmpList = nullptr;
            }

            matMgr_MatList_Count = 0;

            if (nullptr != matMgr_TexList)
            {
                delete[](matMgr_TexList);
                matMgr_TexList = nullptr;
            }

            matMgr_TexList_Count = 0;

            if (nullptr != matMgr_BmpList)
            {
                delete[](matMgr_BmpList);
                matMgr_BmpList = nullptr;
            }

            matMgr_BmpList_Count = 0;

            /* ListBoxes don't need to be cleared because the program is beind closed anyways */
        }


        ////////////////////////////////////////////////////////////////
        // Materials Manager: Update Statistics
        // (counters of specific object types)
        ////////////////////////////////////////////////////////////////
        void materialsManager_UpdateStatistics()
        {
            char bufor[(LARGE_BUFFER_SIZE / 2)];

            sprintf_s(bufor, (LARGE_BUFFER_SIZE / 2), "# Bitmaps: %d", matMgr_BmpList_Count);
            SetWindowText(matMgr_Windows[MATMGR_INFO_WINDOW_TOTALS_BITMAPS], bufor);

            sprintf_s(bufor, (LARGE_BUFFER_SIZE / 2), "# Textures: %d", matMgr_TexList_Count);
            SetWindowText(matMgr_Windows[MATMGR_INFO_WINDOW_TOTALS_TEXTURES], bufor);

            sprintf_s(bufor, (LARGE_BUFFER_SIZE / 2), "# Material States: %d", theMaterialStatesCounter);
            SetWindowText(matMgr_Windows[MATMGR_INFO_WINDOW_TOTALS_STATES], bufor);

            sprintf_s(bufor, (LARGE_BUFFER_SIZE / 2), "# Materials: %d", matMgr_MatList_Count);
            SetWindowText(matMgr_Windows[MATMGR_INFO_WINDOW_TOTALS_MATERIALS], bufor);
        }


        ////////////////////////////////////////////////////////////////
        // Materials Manager: Inserting objects to the lists
        ////////////////////////////////////////////////////////////////

        void materialsManager_InsertMaterial(eMaterial* material)
        {
            int32_t a;
            eMaterial** dummy_list;

            if (nullptr == material)
            {
                /* Invalid parameter */
                return;
            }

            for (a = 0; a < matMgr_MatList_Count; a++)
            {
                if (material == matMgr_MatList[a])
                {
                    /* Given "eMaterial" pointer is already listed */
                    return;
                }
            }

            if ((matMgr_MatList_Count + 1) > matMgr_MatList_MaxLength)
            {
                dummy_list = new eMaterial* [matMgr_MatList_MaxLength + 1];
                matMgr_MatList_MaxLength++;

                if (nullptr != matMgr_MatList)
                {
                    for (a = 0; a < matMgr_MatList_Count; a++)
                    {
                        dummy_list[a] = matMgr_MatList[a];
                    }

                    delete[](matMgr_MatList);
                }

                matMgr_MatList = dummy_list;
            }

            matMgr_MatList[matMgr_MatList_Count] = material;
            matMgr_MatList_Count++;

            materialsManager_UpdateStatistics();

            /* Update Materials ListBox */

            SendMessage(matMgr_Windows[MATMGR_MATERIALS_WINDOW_LIST], LB_ADDSTRING, 0, (LPARAM)"<Unnamed Material>");
        }

        void materialsManager_InsertTexture(eTexture* texture)
        {
            int32_t a;
            eTexture** dummy_list;

            if (nullptr == texture)
            {
                /* Invalid parameter */
                return;
            }

            for (a = 0; a < matMgr_TexList_Count; a++)
            {
                if (texture == matMgr_TexList[a])
                {
                    /* Given "eTexture" pointer is already listed */
                    return;
                }
            }

            if ((matMgr_TexList_Count + 1) > matMgr_TexList_MaxLength)
            {
                dummy_list = new eTexture* [matMgr_TexList_MaxLength + 1];
                matMgr_TexList_MaxLength++;

                if (nullptr != matMgr_TexList)
                {
                    for (a = 0; a < matMgr_TexList_Count; a++)
                    {
                        dummy_list[a] = matMgr_TexList[a];
                    }

                    delete[](matMgr_TexList);
                }

                matMgr_TexList = dummy_list;
            }

            matMgr_TexList[matMgr_TexList_Count] = texture;
            matMgr_TexList_Count++;

            materialsManager_UpdateStatistics();

            /* Update Textures ListBox */

            SendMessage(matMgr_Windows[MATMGR_TEXTURES_WINDOW_LIST], LB_ADDSTRING, 0, (LPARAM)"[Static] <Empty Texture>");
        }

        void materialsManager_InsertBitmap(eBitmap* bitmap)
        {
            int32_t a;
            eBitmap** dummy_list;

            if (nullptr == bitmap)
            {
                /* Invalid parameter */
                return;
            }

            for (a = 0; a < matMgr_BmpList_Count; a++)
            {
                if (bitmap == matMgr_BmpList[a])
                {
                    /* Given "eBitmap" pointer is already listed */
                    return;
                }
            }

            if ((matMgr_BmpList_Count + 1) > matMgr_BmpList_MaxLength)
            {
                dummy_list = new eBitmap* [matMgr_BmpList_MaxLength + 1];
                matMgr_BmpList_MaxLength++;

                if (nullptr != matMgr_BmpList)
                {
                    for (a = 0; a < matMgr_BmpList_Count; a++)
                    {
                        dummy_list[a] = matMgr_BmpList[a];
                    }

                    delete[](matMgr_BmpList);
                }

                matMgr_BmpList = dummy_list;
            }

            matMgr_BmpList[matMgr_BmpList_Count] = bitmap;
            matMgr_BmpList_Count++;

            materialsManager_UpdateStatistics();

            /* Update Bitmaps ListBox */

            SendMessage(matMgr_Windows[MATMGR_BITMAPS_WINDOW_LIST], LB_ADDSTRING, 0, (LPARAM)"<Unnamed Bitmap>");
        }


        ////////////////////////////////////////////////////////////////
        // Materials Manager: Get material, texture od bitmap object
        // based on current ID, or find a list-ID from the parent object.
        ////////////////////////////////////////////////////////////////

        eBitmap* materialsManager_GetCurrentBitmap()
        {
            if ((matMgr_BmpList_Current >= 0) && (matMgr_BmpList_Current < matMgr_BmpList_MaxLength))
            {
                return matMgr_BmpList[matMgr_BmpList_Current];
            }

            return nullptr;
        }

        int32_t materialsManager_FindBitmapId(eTexture* texture)
        {
            int32_t a;
            eBitmap* bitmap;

            if (nullptr != texture)
            {
                if (nullptr != (bitmap = texture->getBitmap()))
                {
                    for (a = 0; a < matMgr_BmpList_Count; a++)
                    {
                        if (bitmap == matMgr_BmpList[a])
                        {
                            return a;
                        }
                    }
                }
            }

            return (-1);
        }

        eTexture* materialsManager_GetCurrentTexture()
        {
            if ((matMgr_TexList_Current >= 0) && (matMgr_TexList_Current < matMgr_TexList_MaxLength))
            {
                return matMgr_TexList[matMgr_TexList_Current];
            }

            return nullptr;
        }

        int32_t materialsManager_FindTextureId(eMaterial* material)
        {
            int32_t a;
            eTexture* texture;

            if (nullptr != material)
            {
                if (nullptr != (texture = material->getIthTexture(matMgr_MaterialTextureId)))
                {
                    for (a = 0; a < matMgr_TexList_Count; a++)
                    {
                        if (texture == matMgr_TexList[a])
                        {
                            return a;
                        }
                    }
                }
            }

            return (-1);
        }

        eMaterial* materialsManager_GetCurrentMaterial()
        {
            if ((matMgr_MatList_Current >= 0) && (matMgr_MatList_Current < matMgr_MatList_MaxLength))
            {
                return matMgr_MatList[matMgr_MatList_Current];
            }

            return nullptr;
        }


        ////////////////////////////////////////////////////////////////
        // Materials Manager: Generating non-empty names
        // for the Materials, Textures and Bitmaps lists
        ////////////////////////////////////////////////////////////////

        eString materialsManager_GenerateBitmapListName(eBitmap* bitmap)
        {
            char bufor[LARGE_BUFFER_SIZE];
            eString name_str;

            if (nullptr != bitmap)
            {
                name_str = bitmap->getPath();
            }

            if (name_str.isEmpty())
            {
                sprintf_s(bufor, LARGE_BUFFER_SIZE, "<Unnamed Bitmap>");
            }
            else
            {
                sprintf_s(bufor, LARGE_BUFFER_SIZE, "\"%s\"", name_str.getText());
            }

            return eString(bufor);
        }

        eString materialsManager_GenerateTextureListName(eTexture* texture)
        {
            char bufor[LARGE_BUFFER_SIZE];
            eString name_str;

            int uses_form = 0;
            const char* texture_types[3] = {"???", "Static", "Animated"};
            int uses_bmp = 0;
            const char* bitmap_types[2] = {"Empty", "Unnamed"};

            eBitmap* dummy_bmp;

            if (nullptr != texture)
            {
                if (nullptr != (dummy_bmp = texture->getBitmap()))
                {
                    uses_bmp = 1;
                    name_str = dummy_bmp->getPath();
                }

                uses_form = (nullptr != texture->getTextureTransform()) ? 2 : 1;
            }

            if (name_str.isEmpty())
            {
                sprintf_s(bufor, LARGE_BUFFER_SIZE, "[%s] <%s Texture>", texture_types[uses_form], bitmap_types[uses_bmp]);
            }
            else
            {
                sprintf_s(bufor, LARGE_BUFFER_SIZE, "[%s] \"%s\"", texture_types[uses_form], name_str.getText());
            }

            return eString(bufor);
        }

        eString materialsManager_GenerateMaterialListName(eMaterial* material)
        {
            char bufor[LARGE_BUFFER_SIZE];
            eString name_str;

            if (nullptr != material)
            {
                name_str = material->getStringRepresentation();
            }

            if (name_str.isEmpty())
            {
                sprintf_s(bufor, LARGE_BUFFER_SIZE, "<Unnamed Material>");
            }
            else
            {
                sprintf_s(bufor, LARGE_BUFFER_SIZE, "\"%s\"", name_str.getText());
            }

            return eString(bufor);
        }


        ////////////////////////////////////////////////////////////////
        // Materials Manager: Updating specific listboxes and editboxes
        // (used while changing - or modifying - Textures and Materials)
        ////////////////////////////////////////////////////////////////

        void materialsManager_UpdateTextureKeyframesListbox(eTexture* texture, bool change_editboxes)
        {
            char bufor[LARGE_BUFFER_SIZE];

            int32_t a, b;
            eTexTransform* form;
            eLeafCtrl<float>* keyframes;
            float key_time, key_value;

            /****************/

            matMgr_UpdatingWindowsNotByUser = true;

            /****************/

            SendMessage(matMgr_Windows[MATMGR_TEXTURES_WINDOW_FORMCHECK_USED], BM_SETCHECK, (WPARAM)BST_UNCHECKED, 0);
            EnableWindow(matMgr_Windows[MATMGR_TEXTURES_WINDOW_FORMCHECK_USED], FALSE);

            SendMessage(matMgr_Windows[MATMGR_TEXTURES_WINDOW_FORMKEYS], LB_RESETCONTENT, 0, 0);
            EnableWindow(matMgr_Windows[MATMGR_TEXTURES_WINDOW_FORMKEYS], FALSE);

            for (a = MATMGR_TEXTURES_WINDOW_FORMBTNS_CAT_SX; a <= MATMGR_TEXTURES_WINDOW_FORMBTNS_CAT_V; a++)
            {
                SendMessage(matMgr_Windows[a], BM_SETSTATE, (WPARAM)FALSE, 0);
                EnableWindow(matMgr_Windows[a], FALSE);
            }

            EnableWindow(matMgr_Windows[MATMGR_TEXTURES_WINDOW_FORM_OORTLIST], FALSE);
            SendMessage(matMgr_Windows[MATMGR_TEXTURES_WINDOW_FORM_OORTLIST], LB_SETCURSEL, (WPARAM)(-1), 0);

            if (change_editboxes)
            {
                SetWindowText(matMgr_Windows[MATMGR_TEXTURES_WINDOW_FORMEDIT_TIME], "");
                EnableWindow(matMgr_Windows[MATMGR_TEXTURES_WINDOW_FORMEDIT_TIME], FALSE);
                SetWindowText(matMgr_Windows[MATMGR_TEXTURES_WINDOW_FORMEDIT_VALUE], "");
                EnableWindow(matMgr_Windows[MATMGR_TEXTURES_WINDOW_FORMEDIT_VALUE], FALSE);
            }

            EnableWindow(matMgr_Windows[MATMGR_TEXTURES_WINDOW_FORMBTNS_CREATE], FALSE);
            EnableWindow(matMgr_Windows[MATMGR_TEXTURES_WINDOW_FORMBTNS_REMOVE], FALSE);

            /****************/

            if (nullptr != texture)
            {
                EnableWindow(matMgr_Windows[MATMGR_TEXTURES_WINDOW_FORMCHECK_USED], TRUE);

                if (nullptr != (form = texture->getTextureTransform()))
                {
                    SendMessage(matMgr_Windows[MATMGR_TEXTURES_WINDOW_FORMCHECK_USED], BM_SETCHECK, (WPARAM)BST_CHECKED, 0);

                    EnableWindow(matMgr_Windows[MATMGR_TEXTURES_WINDOW_FORMBTNS_CREATE], TRUE);
                    EnableWindow(matMgr_Windows[MATMGR_TEXTURES_WINDOW_FORMBTNS_REMOVE], TRUE);

                    for (a = MATMGR_TEXTURES_WINDOW_FORMBTNS_CAT_SX; a <= MATMGR_TEXTURES_WINDOW_FORMBTNS_CAT_V; a++)
                    {
                        EnableWindow(matMgr_Windows[a], TRUE);
                    }

                    keyframes = nullptr;

                    switch (matMgr_TextureKeyframesCategory)
                    {
                        case 0:
                        {
                            keyframes = form->getXScaleCtrl();
                            SendMessage(matMgr_Windows[MATMGR_TEXTURES_WINDOW_FORMBTNS_CAT_SX], BM_SETSTATE, (WPARAM)TRUE, 0);
                            break;
                        }

                        case 1:
                        {
                            keyframes = form->getYScaleCtrl();
                            SendMessage(matMgr_Windows[MATMGR_TEXTURES_WINDOW_FORMBTNS_CAT_SY], BM_SETSTATE, (WPARAM)TRUE, 0);
                            break;
                        }

                        case 2:
                        {
                            keyframes = form->getUOffsetCtrl();
                            SendMessage(matMgr_Windows[MATMGR_TEXTURES_WINDOW_FORMBTNS_CAT_U], BM_SETSTATE, (WPARAM)TRUE, 0);
                            break;
                        }

                        case 3:
                        {
                            keyframes = form->getVOffsetCtrl();
                            SendMessage(matMgr_Windows[MATMGR_TEXTURES_WINDOW_FORMBTNS_CAT_V], BM_SETSTATE, (WPARAM)TRUE, 0);
                            break;
                        }
                    }

                    if (nullptr != keyframes)
                    {
                        EnableWindow(matMgr_Windows[MATMGR_TEXTURES_WINDOW_FORMKEYS], TRUE);

                        EnableWindow(matMgr_Windows[MATMGR_TEXTURES_WINDOW_FORM_OORTLIST], TRUE);

                        if (change_editboxes)
                        {
                            EnableWindow(matMgr_Windows[MATMGR_TEXTURES_WINDOW_FORMEDIT_TIME], TRUE);
                            EnableWindow(matMgr_Windows[MATMGR_TEXTURES_WINDOW_FORMEDIT_VALUE], TRUE);
                        }

                        a = keyframes->getLeafLoopType(0);
                        SendMessage(matMgr_Windows[MATMGR_TEXTURES_WINDOW_FORM_OORTLIST], LB_SETCURSEL, (WPARAM)a, 0);

                        key_value = keyframes->getDefaultValue();
                        sprintf_s(bufor, LARGE_BUFFER_SIZE, "DEFAULT: %f", key_value);
                        SendMessage(matMgr_Windows[MATMGR_TEXTURES_WINDOW_FORMKEYS], LB_ADDSTRING, 0, (LPARAM)bufor);

                        if (change_editboxes && (matMgr_TextureKeyframesId <= 0))
                        {
                            sprintf_s(bufor, LARGE_BUFFER_SIZE, "%f", key_value);
                            SetWindowText(matMgr_Windows[MATMGR_TEXTURES_WINDOW_FORMEDIT_VALUE], bufor);
                        }

                        b = keyframes->getLeafKeysCount();
                        a = 0;
                        while (a < b)
                        {
                            if (false == keyframes->getIthLeafKey(a, key_time, key_value))
                            {
                                key_time = (-1);
                                key_value = 0;
                            }

                            a++;
                            sprintf_s(bufor, LARGE_BUFFER_SIZE, "%2d / %2d: [%3d] %f", a, b, (int32_t)key_time, key_value);
                            SendMessage(matMgr_Windows[MATMGR_TEXTURES_WINDOW_FORMKEYS], LB_ADDSTRING, 0, (LPARAM)bufor);

                            if (change_editboxes && (matMgr_TextureKeyframesId == a))
                            {
                                sprintf_s(bufor, LARGE_BUFFER_SIZE, "%d", (int32_t)key_time);
                                SetWindowText(matMgr_Windows[MATMGR_TEXTURES_WINDOW_FORMEDIT_TIME], bufor);
                                sprintf_s(bufor, LARGE_BUFFER_SIZE, "%f", key_value);
                                SetWindowText(matMgr_Windows[MATMGR_TEXTURES_WINDOW_FORMEDIT_VALUE], bufor);
                            }
                        }

                        SendMessage(matMgr_Windows[MATMGR_TEXTURES_WINDOW_FORMKEYS], LB_SETCURSEL, (WPARAM)matMgr_TextureKeyframesId, 0);
                    }
                }
            }
            else
            {
                matMgr_TextureKeyframesCategory = (-1);
                matMgr_TextureKeyframesId = 0;
            }

            matMgr_UpdatingWindowsNotByUser = false;
        }

        void materialsManager_UpdateMaterialTexturesListbox(eMaterial* material)
        {
            char bufor[LARGE_BUFFER_SIZE];

            int32_t a, b;
            eTexture* dummy_texture;
            eString dummy_name;

            /****************/

            matMgr_UpdatingWindowsNotByUser = true;

            /****************/

            SendMessage(matMgr_Windows[MATMGR_MATERIALS_WINDOW_TEXLIST], LB_RESETCONTENT, 0, 0);
            EnableWindow(matMgr_Windows[MATMGR_MATERIALS_WINDOW_TEXLIST], FALSE);

            for (a = MATMGR_MATERIALS_WINDOW_TEXTBTNS_CREATE; a <= MATMGR_MATERIALS_WINDOW_TEXTBTNS_REPLACE; a++)
            {
                EnableWindow(matMgr_Windows[a], FALSE);
            }

            /****************/

            if (nullptr != material)
            {
                EnableWindow(matMgr_Windows[MATMGR_MATERIALS_WINDOW_TEXLIST], TRUE);

                for (a = MATMGR_MATERIALS_WINDOW_TEXTBTNS_CREATE; a <= MATMGR_MATERIALS_WINDOW_TEXTBTNS_REPLACE; a++)
                {
                    EnableWindow(matMgr_Windows[a], TRUE);
                }

                b = material->getTexturesCount();
                a = 0;
                while (a < b)
                {
                    dummy_texture = material->getIthTexture(a);

                    dummy_name = materialsManager_GenerateTextureListName(dummy_texture);

                    a++;
                    sprintf_s(bufor, LARGE_BUFFER_SIZE, "%2d / %2d: %s", a, b, dummy_name.getText());
                    SendMessage(matMgr_Windows[MATMGR_MATERIALS_WINDOW_TEXLIST], LB_ADDSTRING, 0, (LPARAM)bufor);
                }

                SendMessage(matMgr_Windows[MATMGR_MATERIALS_WINDOW_TEXLIST], LB_SETCURSEL, (WPARAM)matMgr_MaterialTextureId, 0);
            }
            else
            {
                matMgr_MaterialTextureId = (-1);
            }

            matMgr_UpdatingWindowsNotByUser = false;
        }

        void materialsManager_UpdateMaterialStateEditboxes(eMaterial* material)
        {
            char bufor[LARGE_BUFFER_SIZE];

            int32_t a, b;
            bool c;
            float color[3];
            eMaterialState* state;

            /****************/

            matMgr_UpdatingWindowsNotByUser = true;

            /****************/

            SendMessage(matMgr_Windows[MATMGR_MATERIALS_WINDOW_STATECHECK_USED], BM_SETCHECK, (WPARAM)BST_UNCHECKED, 0);
            EnableWindow(matMgr_Windows[MATMGR_MATERIALS_WINDOW_STATECHECK_USED], FALSE);

            SetWindowText(matMgr_Windows[MATMGR_MATERIALS_WINDOW_STATE_STATUS], "");

            EnableWindow(matMgr_Windows[MATMGR_MATERIALS_WINDOW_STATEBTN_CLONE], FALSE);

            a = MATMGR_MATERIALS_WINDOW_STATEEDIT_C1_R;

            for (b = 0; b < 4; b++)
            {
                SetWindowText(matMgr_Windows[a], "");
                EnableWindow(matMgr_Windows[a], FALSE);
                a++;

                SetWindowText(matMgr_Windows[a], "");
                EnableWindow(matMgr_Windows[a], FALSE);
                a++;

                SetWindowText(matMgr_Windows[a], "");
                EnableWindow(matMgr_Windows[a], FALSE);
                a += 2;
            }

            SetWindowText(matMgr_Windows[MATMGR_MATERIALS_WINDOW_STATEEDIT_48], "");
            EnableWindow(matMgr_Windows[MATMGR_MATERIALS_WINDOW_STATEEDIT_48], FALSE);

            SendMessage(matMgr_Windows[MATMGR_MATERIALS_WINDOW_STATECHECK_4C], BM_SETCHECK, (WPARAM)BST_UNCHECKED, 0);
            EnableWindow(matMgr_Windows[MATMGR_MATERIALS_WINDOW_STATECHECK_4C], FALSE);

            /****************/

            if (nullptr != material)
            {
                EnableWindow(matMgr_Windows[MATMGR_MATERIALS_WINDOW_STATECHECK_USED], TRUE);

                if (nullptr != (state = material->getMaterialState()))
                {
                    SendMessage(matMgr_Windows[MATMGR_MATERIALS_WINDOW_STATECHECK_USED], BM_SETCHECK, (WPARAM)BST_CHECKED, 0);

                    sprintf_s(bufor, LARGE_BUFFER_SIZE, "Material State references: %d", state->getReferenceCount());
                    SetWindowText(matMgr_Windows[MATMGR_MATERIALS_WINDOW_STATE_STATUS], bufor);

                    EnableWindow(matMgr_Windows[MATMGR_MATERIALS_WINDOW_STATEBTN_CLONE], TRUE);

                    state->getAmbientColor(color);

                    a = MATMGR_MATERIALS_WINDOW_STATEEDIT_C1_R;
                    for (b = 0; b < 3; b++)
                    {
                        sprintf_s(bufor, LARGE_BUFFER_SIZE, "%f", color[b]);

                        EnableWindow(matMgr_Windows[a], TRUE);
                        SetWindowText(matMgr_Windows[a], bufor);
                        a++;
                    }

                    state->getDiffuseColor(color);

                    a = MATMGR_MATERIALS_WINDOW_STATEEDIT_C2_R;
                    for (b = 0; b < 3; b++)
                    {
                        sprintf_s(bufor, LARGE_BUFFER_SIZE, "%f", color[b]);

                        EnableWindow(matMgr_Windows[a], TRUE);
                        SetWindowText(matMgr_Windows[a], bufor);
                        a++;
                    }

                    state->getEmissiveColor(color);

                    a = MATMGR_MATERIALS_WINDOW_STATEEDIT_C3_R;
                    for (b = 0; b < 3; b++)
                    {
                        sprintf_s(bufor, LARGE_BUFFER_SIZE, "%f", color[b]);

                        EnableWindow(matMgr_Windows[a], TRUE);
                        SetWindowText(matMgr_Windows[a], bufor);
                        a++;
                    }

                    state->getSpecularColor(color);

                    a = MATMGR_MATERIALS_WINDOW_STATEEDIT_C4_R;
                    for (b = 0; b < 3; b++)
                    {
                        sprintf_s(bufor, LARGE_BUFFER_SIZE, "%f", color[b]);

                        EnableWindow(matMgr_Windows[a], TRUE);
                        SetWindowText(matMgr_Windows[a], bufor);
                        a++;
                    }

                    color[0] = state->getShininess();
                    sprintf_s(bufor, LARGE_BUFFER_SIZE, "%f", color[0]);
                    EnableWindow(matMgr_Windows[MATMGR_MATERIALS_WINDOW_STATEEDIT_48], TRUE);
                    SetWindowText(matMgr_Windows[MATMGR_MATERIALS_WINDOW_STATEEDIT_48], bufor);

                    c = state->getGlobalAmbientLightState();
                    EnableWindow(matMgr_Windows[MATMGR_MATERIALS_WINDOW_STATECHECK_4C], TRUE);
                    SendMessage(matMgr_Windows[MATMGR_MATERIALS_WINDOW_STATECHECK_4C], BM_SETCHECK, (WPARAM)(c ? BST_CHECKED : BST_UNCHECKED), 0);
                }
            }

            matMgr_UpdatingWindowsNotByUser = false;
        }


        ////////////////////////////////////////////////////////////////
        // Materials Manager: Update names on the lists
        ////////////////////////////////////////////////////////////////

        void materialsManager_UpdateMaterialName(eMaterial* material)
        {
            int32_t a;
            eString name_for_the_list;

            if (nullptr == material)
            {
                /* Invalid parameter */
                return;
            }

            for (a = 0; a < matMgr_MatList_Count; a++)
            {
                if (material == matMgr_MatList[a])
                {
                    name_for_the_list = materialsManager_GenerateMaterialListName(material);

                    matMgr_UpdatingWindowsNotByUser = true;

                    SendMessage(matMgr_Windows[MATMGR_MATERIALS_WINDOW_LIST], LB_DELETESTRING, (WPARAM)a, 0);

                    SendMessage(matMgr_Windows[MATMGR_MATERIALS_WINDOW_LIST], LB_INSERTSTRING, (WPARAM)a, (LPARAM)name_for_the_list.getText());

                    if (matMgr_MatList_Current == a)
                    {
                        SendMessage(matMgr_Windows[MATMGR_MATERIALS_WINDOW_LIST], LB_SETCURSEL, (WPARAM)matMgr_MatList_Current, 0);
                    }

                    matMgr_UpdatingWindowsNotByUser = false;

                    return;
                }
            }
        }

        void materialsManager_UpdateTextureName(eTexture* texture)
        {
            int32_t a, b;
            eString name_for_the_list;

            eMaterial* material;

            if (nullptr == texture)
            {
                /* Invalid parameter */
                return;
            }

            for (a = 0; a < matMgr_TexList_Count; a++)
            {
                if (texture == matMgr_TexList[a])
                {
                    name_for_the_list = materialsManager_GenerateTextureListName(texture);

                    matMgr_UpdatingWindowsNotByUser = true;

                    SendMessage(matMgr_Windows[MATMGR_TEXTURES_WINDOW_LIST], LB_DELETESTRING, (WPARAM)a, 0);

                    SendMessage(matMgr_Windows[MATMGR_TEXTURES_WINDOW_LIST], LB_INSERTSTRING, (WPARAM)a, (LPARAM)name_for_the_list.getText());

                    if (matMgr_TexList_Current == a)
                    {
                        SendMessage(matMgr_Windows[MATMGR_TEXTURES_WINDOW_LIST], LB_SETCURSEL, (WPARAM)matMgr_TexList_Current, 0);
                    }

                    /****************/

                    if (nullptr != (material = materialsManager_GetCurrentMaterial()))
                    {
                        b = material->getTexturesCount();

                        for (a = 0; a < b; a++)
                        {
                            if (material->getIthTexture(a) == texture)
                            {
                                materialsManager_UpdateMaterialTexturesListbox(material);

                                a = b;
                            }
                        }
                    }

                    /****************/

                    matMgr_UpdatingWindowsNotByUser = false;

                    return;
                }
            }
        }

        void materialsManager_UpdateBitmapPath(eBitmap* bitmap)
        {
            int32_t a;
            eString name_for_the_list;

            eTexture* texture;

            if (nullptr == bitmap)
            {
                /* Invalid parameter */
                return;
            }

            for (a = 0; a < matMgr_BmpList_Count; a++)
            {
                if (bitmap == matMgr_BmpList[a])
                {
                    name_for_the_list = materialsManager_GenerateBitmapListName(bitmap);

                    matMgr_UpdatingWindowsNotByUser = true;

                    SendMessage(matMgr_Windows[MATMGR_BITMAPS_WINDOW_LIST], LB_DELETESTRING, (WPARAM)a, 0);

                    SendMessage(matMgr_Windows[MATMGR_BITMAPS_WINDOW_LIST], LB_INSERTSTRING, (WPARAM)a, (LPARAM)name_for_the_list.getText());

                    if (matMgr_BmpList_Current == a)
                    {
                        SendMessage(matMgr_Windows[MATMGR_BITMAPS_WINDOW_LIST], LB_SETCURSEL, (WPARAM)matMgr_BmpList_Current, 0);
                    }

                    /****************/

                    for (a = 0; a < matMgr_TexList_Count; a++)
                    {
                        if (nullptr != (texture = matMgr_TexList[a]))
                        {
                            if (texture->getBitmap() == bitmap)
                            {
                                materialsManager_UpdateTextureName(texture);
                            }
                        }
                    }

                    /****************/

                    matMgr_UpdatingWindowsNotByUser = false;

                    return;
                }
            }
        }


        ////////////////////////////////////////////////////////////////
        // Materials manager: Choosing selections on the lists,
        // and updating windows linked to objects' properties
        ////////////////////////////////////////////////////////////////

        void materialsManager_ResetBitmapWindows()
        {
            matMgr_UpdatingWindowsNotByUser = true;

            SetWindowText(matMgr_Windows[MATMGR_BITMAPS_WINDOW_PATHEDIT], "");
            EnableWindow(matMgr_Windows[MATMGR_BITMAPS_WINDOW_PATHEDIT], FALSE);

            SendMessage(matMgr_Windows[MATMGR_BITMAPS_WINDOW_EXTCHECK], BM_SETCHECK, (WPARAM)BST_UNCHECKED, 0);
            EnableWindow(matMgr_Windows[MATMGR_BITMAPS_WINDOW_EXTCHECK], FALSE);

            matMgr_UpdatingWindowsNotByUser = false;
        }

        void materialsManager_ResetTextureWindows()
        {
            int32_t a;

            matMgr_UpdatingWindowsNotByUser = true;

            for (a = MATMGR_TEXTURES_WINDOW_FLAGSCHECK1; a <= MATMGR_TEXTURES_WINDOW_FLAGSCHECK3; a++)
            {
                SendMessage(matMgr_Windows[a], BM_SETCHECK, (WPARAM)BST_UNCHECKED, 0);
                EnableWindow(matMgr_Windows[a], FALSE);
            }

            for (a = MATMGR_TEXTURES_WINDOW_BMPBTNS_CREATE; a <= MATMGR_TEXTURES_WINDOW_BMPBTNS_REPLACE; a++)
            {
                EnableWindow(matMgr_Windows[a], FALSE);
            }

            matMgr_UpdatingWindowsNotByUser = false;
        }

        void materialsManager_ResetMaterialWindows()
        {
            int32_t a;

            matMgr_UpdatingWindowsNotByUser = true;

            for (a = MATMGR_MATERIALS_WINDOW_FLAGSCHECK1; a <= MATMGR_MATERIALS_WINDOW_FLAGSCHECK4; a++)
            {
                SendMessage(matMgr_Windows[a], BM_SETCHECK, (WPARAM)BST_UNCHECKED, 0);
                EnableWindow(matMgr_Windows[a], FALSE);
            }

            SendMessage(matMgr_Windows[MATMGR_MATERIALS_WINDOW_COLLIST], LB_SETCURSEL, (WPARAM)(-1), 0);
            EnableWindow(matMgr_Windows[MATMGR_MATERIALS_WINDOW_COLLIST], FALSE);

            SendMessage(matMgr_Windows[MATMGR_MATERIALS_WINDOW_SNDLIST], LB_SETCURSEL, (WPARAM)(-1), 0);
            EnableWindow(matMgr_Windows[MATMGR_MATERIALS_WINDOW_SNDLIST], FALSE);

            SetWindowText(matMgr_Windows[MATMGR_MATERIALS_WINDOW_NAMEEDIT], "");
            EnableWindow(matMgr_Windows[MATMGR_MATERIALS_WINDOW_NAMEEDIT], FALSE);

            SetWindowText(matMgr_Windows[MATMGR_MATERIALS_WINDOW_ALPHAEDIT], "");
            EnableWindow(matMgr_Windows[MATMGR_MATERIALS_WINDOW_ALPHAEDIT], FALSE);

            matMgr_UpdatingWindowsNotByUser = false;
        }

        void materialsManager_SetCurrentBitmap(int32_t selected_id, bool update_listbox, bool update_windows)
        {
            eBitmap* bitmap;
            eString path_str;

            matMgr_BmpList_Current = selected_id;

            if (matMgr_BmpList_Current >= matMgr_BmpList_Count)
            {
                matMgr_BmpList_Current = (-1);
            }

            if (update_listbox)
            {
                matMgr_UpdatingWindowsNotByUser = true;

                SendMessage
                (
                    matMgr_Windows[MATMGR_BITMAPS_WINDOW_LIST],
                    LB_SETCURSEL,
                    (WPARAM)matMgr_BmpList_Current,
                    0
                );

                matMgr_UpdatingWindowsNotByUser = false;
            }

            if (update_windows)
            {
                materialsManager_ResetBitmapWindows();

                if ((matMgr_BmpList_Current >= 0) && (nullptr != (bitmap = matMgr_BmpList[matMgr_BmpList_Current])))
                {
                    matMgr_UpdatingWindowsNotByUser = true;

                    /* Update Bitmap Path Editbox */

                    EnableWindow(matMgr_Windows[MATMGR_BITMAPS_WINDOW_PATHEDIT], TRUE);

                    path_str = bitmap->getPath();

                    if (path_str.isEmpty())
                    {
                        SetWindowText(matMgr_Windows[MATMGR_BITMAPS_WINDOW_PATHEDIT], "");
                    }
                    else
                    {
                        SetWindowText(matMgr_Windows[MATMGR_BITMAPS_WINDOW_PATHEDIT], path_str.getText());
                    }

                    /* Update "isExternal" Checkbox */

                    EnableWindow(matMgr_Windows[MATMGR_BITMAPS_WINDOW_EXTCHECK], TRUE);

                    bool is_external = bitmap->getLoadedFromExternalFileFlag();

                    SendMessage(matMgr_Windows[MATMGR_BITMAPS_WINDOW_EXTCHECK], BM_SETCHECK, (WPARAM)(is_external ? BST_CHECKED : BST_UNCHECKED), 0);

                    /* Done updating Bitmap-related windows */

                    matMgr_RenderedList = MATMGR_RENDERED_LIST_SINGLE_BITMAP;
                    matMgr_scrollPos = 0;

                    matMgr_UpdatingWindowsNotByUser = false;
                }
            }
        }

        void materialsManager_SetCurrentTexture(int selected_id, bool update_listbox, bool update_windows, bool update_bmp)
        {
            eTexture* texture;
            int32_t a;
            uint32_t render_flags;

            matMgr_TexList_Current = selected_id;

            if (matMgr_TexList_Current >= matMgr_TexList_Count)
            {
                matMgr_TexList_Current = (-1);
            }

            if (update_listbox)
            {
                matMgr_UpdatingWindowsNotByUser = true;

                SendMessage
                (
                    matMgr_Windows[MATMGR_TEXTURES_WINDOW_LIST],
                    LB_SETCURSEL,
                    (WPARAM)matMgr_TexList_Current,
                    0
                );

                matMgr_UpdatingWindowsNotByUser = false;
            }

            if (update_windows)
            {
                materialsManager_ResetTextureWindows();

                if ((matMgr_TexList_Current >= 0) && (nullptr != (texture = matMgr_TexList[matMgr_TexList_Current])))
                {
                    matMgr_UpdatingWindowsNotByUser = true;

                    /* Update Texture Flags Checkboxes */

                    render_flags = texture->getTextureFlags();

                    for (a = MATMGR_TEXTURES_WINDOW_FLAGSCHECK1; a <= MATMGR_TEXTURES_WINDOW_FLAGSCHECK3; a++)
                    {
                        EnableWindow(matMgr_Windows[a], TRUE);
                        SendMessage(matMgr_Windows[a], BM_SETCHECK, (WPARAM)((render_flags & 0x01) ? BST_CHECKED : BST_UNCHECKED), 0);

                        render_flags >>= 1;
                    }

                    /* Enable Bitmap-related Buttons */

                    for (a = MATMGR_TEXTURES_WINDOW_BMPBTNS_CREATE; a <= MATMGR_TEXTURES_WINDOW_BMPBTNS_REPLACE; a++)
                    {
                        EnableWindow(matMgr_Windows[a], TRUE);
                    }

                    /* Update TexTransform Buttons and Keyframes List */

                    matMgr_TextureKeyframesCategory = (-1);
                    matMgr_TextureKeyframesId = 0;

                    materialsManager_UpdateTextureKeyframesListbox(texture, true);
                    matMgr_UpdatingWindowsNotByUser = true;

                    /* Update Texture's bitmap options, if needed */

                    if (update_bmp)
                    {
                        a = materialsManager_FindBitmapId(texture);

                        materialsManager_SetCurrentBitmap(a, true, true);
                    }

                    /* Done updating Texture-related windows */

                    matMgr_UpdatingWindowsNotByUser = false;
                }
                else
                {
                    materialsManager_UpdateTextureKeyframesListbox(nullptr, true);

                    if (update_bmp)
                    {
                        materialsManager_SetCurrentBitmap((-1), true, true);
                    }
                }
            }
        }

        void materialsManager_SetCurrentMaterial(int selected_id, bool update_listbox, bool update_windows, int32_t update_tex)
        {
            eMaterial* material;
            char bufor[32];
            eString name_str;
            int32_t a, b;
            float alpha_test_ref;
            uint32_t test32;
            uint16_t test16;
            uint8_t test8;

            matMgr_MatList_Current = selected_id;

            if (matMgr_MatList_Current >= matMgr_MatList_Count)
            {
                matMgr_MatList_Current = (-1);
            }

            if (update_listbox)
            {
                matMgr_UpdatingWindowsNotByUser = true;

                SendMessage
                (
                    matMgr_Windows[MATMGR_MATERIALS_WINDOW_LIST],
                    LB_SETCURSEL,
                    (WPARAM)matMgr_MatList_Current,
                    0
                );

                matMgr_UpdatingWindowsNotByUser = false;
            }

            if (update_windows)
            {
                materialsManager_ResetMaterialWindows();

                if ((matMgr_MatList_Current >= 0) && (nullptr != (material = matMgr_MatList[matMgr_MatList_Current])))
                {
                    matMgr_UpdatingWindowsNotByUser = true;

                    /* Update Textures Buttons and Listbox */

                    matMgr_MaterialTextureId = update_tex;

                    materialsManager_UpdateMaterialTexturesListbox(material);
                    matMgr_UpdatingWindowsNotByUser = true;

                    /* Update MaterialState Editboxes */

                    materialsManager_UpdateMaterialStateEditboxes(material);
                    matMgr_UpdatingWindowsNotByUser = true;

                    /* Update Rendering Flags Checkboxes */

                    test8 = material->getMaterialFlags();

                    for (a = MATMGR_MATERIALS_WINDOW_FLAGSCHECK1; a <= MATMGR_MATERIALS_WINDOW_FLAGSCHECK4; a++)
                    {
                        EnableWindow(matMgr_Windows[a], TRUE);
                        SendMessage(matMgr_Windows[a], BM_SETCHECK, (WPARAM)((test8 & 0x01) ? BST_CHECKED : BST_UNCHECKED), 0);

                        test8 >>= 1;
                    }

                    /* Update Collision Type Listbox */

                    test32 = material->getCollisionType();
                    b = (-1);

                    for (a = 0; (b < 0) && (a < KAO2_MATERIAL_TYPES_COUNT); a++)
                    {
                        if (theMaterialTypes[a].id == test32)
                        {
                            b = a;
                        }
                    }

                    EnableWindow(matMgr_Windows[MATMGR_MATERIALS_WINDOW_COLLIST], TRUE);
                    SendMessage(matMgr_Windows[MATMGR_MATERIALS_WINDOW_COLLIST], LB_SETCURSEL, (WPARAM)b, 0);

                    /* Update Sound Type Listbox */

                    test16 = material->getSoundType();
                    b = (-1);

                    for (a = 0; (b < 0) && (a < KAO2_MATERIAL_SOUNDS_COUNT); a++)
                    {
                        if (theMaterialSounds[a].id == test16)
                        {
                            b = a;
                        }
                    }

                    EnableWindow(matMgr_Windows[MATMGR_MATERIALS_WINDOW_SNDLIST], TRUE);
                    SendMessage(matMgr_Windows[MATMGR_MATERIALS_WINDOW_SNDLIST], LB_SETCURSEL, (WPARAM)b, 0);

                    /* Update Material Name */

                    EnableWindow(matMgr_Windows[MATMGR_MATERIALS_WINDOW_NAMEEDIT], TRUE);

                    name_str = material->getStringRepresentation();

                    if (name_str.isEmpty())
                    {
                        SetWindowText(matMgr_Windows[MATMGR_MATERIALS_WINDOW_NAMEEDIT], "");
                    }
                    else
                    {
                        SetWindowText(matMgr_Windows[MATMGR_MATERIALS_WINDOW_NAMEEDIT], name_str.getText());
                    }

                    /* Update AlphaTestRef Editbox */

                    alpha_test_ref = material->getAlphaTestRef();
                    sprintf_s(bufor, 32, "%f", alpha_test_ref);

                    EnableWindow(matMgr_Windows[MATMGR_MATERIALS_WINDOW_ALPHAEDIT], TRUE);
                    SetWindowText(matMgr_Windows[MATMGR_MATERIALS_WINDOW_ALPHAEDIT], bufor);

                    /* Update Material's texture options, if needed */

                    if (update_tex >= 0)
                    {
                        a = materialsManager_FindTextureId(material);

                        materialsManager_SetCurrentTexture(a, true, true, true);
                    }

                    /* Done updating Texture-related windows */

                    matMgr_UpdatingWindowsNotByUser = false;
                }
                else
                {
                    materialsManager_UpdateMaterialTexturesListbox(nullptr);
                    materialsManager_UpdateMaterialStateEditboxes(nullptr);

                    if (update_tex >= 0)
                    {
                        materialsManager_SetCurrentTexture((-1), true, true, true);
                    }
                }
            }
        }

        void materialsManager_SetCurrentMaterialFromGeometry(eMaterial* material)
        {
            if (nullptr != material)
            {
                for (int a = 0; a < matMgr_MatList_Count; a++)
                {
                    if (material == matMgr_MatList[a])
                    {
                        materialsManager_SetCurrentMaterial(a, true, true, 0);

                        return;
                    }
                }
            }

            materialsManager_SetCurrentMaterial((-1), true, true, 0);
        }


        ////////////////////////////////////////////////////////////////
        // Materials manager: Changing single properties of the objects,
        // after making some edits in specific windows
        ////////////////////////////////////////////////////////////////

        void materialsManager_ChangeBitmapProp_Name(const char* new_name)
        {
            eBitmap* bitmap;

            if (nullptr != (bitmap = materialsManager_GetCurrentBitmap()))
            {
                bitmap->setPath(new_name);
                materialsManager_UpdateBitmapPath(bitmap);
            }
        }

        void materialsManager_ChangeBitmapProp_Ext(bool new_ext_state)
        {
            eBitmap* bitmap;

            if (nullptr != (bitmap = materialsManager_GetCurrentBitmap()))
            {
                bitmap->setLoadedFromExternalFileFlag(new_ext_state);
            }
        }

        void materialsManager_ChangeTextureProp_Flags(bool set_or_unset, uint32_t some_bit)
        {
            eTexture* texture;

            if (nullptr != (texture = materialsManager_GetCurrentTexture()))
            {
                if (set_or_unset)
                {
                    texture->setTextureFlags(some_bit);
                }
                else
                {
                    texture->unsetTextureFlags(some_bit);
                }
            }
        }

        void materialsManager_ChangeTextureProp_CheckKeyframes(bool add_or_remove)
        {
            eTexture* texture;
            eTexTransform* form;

            const char* removal_question =
                "You are about to delete ALL the keyframes in ALL the categories.\n\n" \
                "This operation cannot be undone! Are you sure you want to continue?";

            if (nullptr != (texture = materialsManager_GetCurrentTexture()))
            {
                form = texture->getTextureTransform();

                if (add_or_remove && (nullptr == form))
                {
                    texture->setTextureTransform(new eTexTransform());
                }
                else if ((!add_or_remove) && (nullptr != form))
                {
                    if (theWindowsManager.askQuestion(removal_question))
                    {
                        texture->setTextureTransform(nullptr);
                    }
                }

                materialsManager_UpdateTextureName(texture);

                materialsManager_UpdateTextureKeyframesListbox(texture, true);
            }
        }

        void materialsManager_ChangeTextureProp_Keyframes(int32_t action, void* param)
        {
            eTexture* texture;
            eTexTransform* form;
            eLeafCtrl<float>* keyframes = nullptr;

            int32_t a, b;
            float key_time, key_value, default_value;
            bool update_editboxes = true;

            const char* removal_question =
                "By choosing the default key, you are about to delete ALL the keyframes in the current category.\n\n" \
                "This operation cannot be undone! Are you sure you want to continue?";

            if (nullptr != (texture = materialsManager_GetCurrentTexture()))
            {
                if (nullptr != (form = texture->getTextureTransform()))
                {
                    switch (matMgr_TextureKeyframesCategory)
                    {
                        case 0:
                        {
                            keyframes = form->getXScaleCtrl();
                            default_value = 1.0f;
                            break;
                        }

                        case 1:
                        {
                            keyframes = form->getYScaleCtrl();
                            default_value = 1.0f;
                            break;
                        }

                        case 2:
                        {
                            keyframes = form->getUOffsetCtrl();
                            default_value = 0;
                            break;
                        }

                        case 3:
                        {
                            keyframes = form->getVOffsetCtrl();
                            default_value = 0;
                            break;
                        }

                        default:
                        {
                            return;
                        }
                    }

                    switch (action)
                    {
                        case MATMGR_TEXTURES_WINDOW_FORM_OORTLIST:
                        {
                            if (nullptr == keyframes)
                            {
                                matMgr_UpdatingWindowsNotByUser = true;

                                SendMessage(matMgr_Windows[MATMGR_TEXTURES_WINDOW_FORM_OORTLIST], LB_SETCURSEL, (WPARAM)(-1), 0);

                                matMgr_UpdatingWindowsNotByUser = false;
                            }
                            else
                            {
                                keyframes->ctrlSetLoopType(0, (int32_t)param, 0x01);
                            }

                            break;
                        }

                        case MATMGR_TEXTURES_WINDOW_FORMBTNS_CREATE:
                        {
                            if (nullptr == keyframes)
                            {
                                keyframes = new eLeafCtrl<float>();
                                keyframes->incRef();

                                keyframes->setDefaultValue(default_value);
                                keyframes->ctrlSetLoopType(0, 1, 0x01);

                                switch (matMgr_TextureKeyframesCategory)
                                {
                                    case 0:
                                    {
                                        form->setXScaleCtrl(keyframes);
                                        break;
                                    }

                                    case 1:
                                    {
                                        form->setYScaleCtrl(keyframes);
                                        break;
                                    }

                                    case 2:
                                    {
                                        form->setUOffsetCtrl(keyframes);
                                        break;
                                    }

                                    case 3:
                                    {
                                        form->setVOffsetCtrl(keyframes);
                                        break;
                                    }
                                }

                                matMgr_TextureKeyframesId = 0;
                            }
                            else
                            {
                                keyframes->incRef();

                                a = keyframes->getLeafKeysCount();

                                if (a > 0)
                                {
                                    if (keyframes->getIthLeafKey((a - 1), key_time, key_value))
                                    {
                                        key_time++;
                                    }
                                    else
                                    {
                                        key_time = 0;
                                    }
                                }
                                else
                                {
                                    key_time = 0;
                                }

                                matMgr_TextureKeyframesId = (1 + keyframes->addLeafKey(key_time, default_value));
                            }

                            keyframes->decRef();

                            break;
                        }

                        case MATMGR_TEXTURES_WINDOW_FORMBTNS_REMOVE:
                        {
                            if (nullptr != keyframes)
                            {
                                if (matMgr_TextureKeyframesId <= 0)
                                {
                                    if (theWindowsManager.askQuestion(removal_question))
                                    {
                                        switch (matMgr_TextureKeyframesCategory)
                                        {
                                            case 0:
                                            {
                                                form->setXScaleCtrl(nullptr);
                                                break;
                                            }

                                            case 1:
                                            {
                                                form->setYScaleCtrl(nullptr);
                                                break;
                                            }

                                            case 2:
                                            {
                                                form->setUOffsetCtrl(nullptr);
                                                break;
                                            }

                                            case 3:
                                            {
                                                form->setVOffsetCtrl(nullptr);
                                                break;
                                            }
                                        }
                                    }
                                }
                                else
                                {
                                    a = matMgr_TextureKeyframesId - 1;
                                    keyframes->removeIthLeafKey(a);
                                    b = keyframes->getLeafKeysCount();

                                    if (a >= b)
                                    {
                                        matMgr_TextureKeyframesId = b;
                                    }
                                }
                            }

                            break;
                        }

                        case MATMGR_TEXTURES_WINDOW_FORMEDIT_TIME:
                        {
                            update_editboxes = false;

                            if ((nullptr != keyframes) && matMgr_TextureKeyframesId > 0)
                            {
                                if (keyframes->getIthLeafKey((matMgr_TextureKeyframesId - 1), key_time, key_value))
                                {
                                    key_time = (float)std::atoi((const char*)param);

                                    if (key_time < (-30.0f))
                                    {
                                        key_time = (-30.0f);
                                    }

                                    keyframes->removeIthLeafKey(matMgr_TextureKeyframesId - 1);

                                    matMgr_TextureKeyframesId = (1 + keyframes->addLeafKey(key_time, key_value));
                                }
                            }

                            break;
                        }

                        case MATMGR_TEXTURES_WINDOW_FORMEDIT_VALUE:
                        {
                            update_editboxes = false;

                            if (nullptr != keyframes)
                            {
                                default_value = (float)std::atof((const char*)param);

                                if (matMgr_TextureKeyframesId <= 0)
                                {
                                    keyframes->setDefaultValue(default_value);
                                }
                                else if (keyframes->getIthLeafKey((matMgr_TextureKeyframesId - 1), key_time, key_value))
                                {
                                    keyframes->removeIthLeafKey(matMgr_TextureKeyframesId - 1);

                                    matMgr_TextureKeyframesId = (1 + keyframes->addLeafKey(key_time, default_value));
                                }
                            }

                            break;
                        }
                    }

                    materialsManager_UpdateTextureKeyframesListbox(texture, update_editboxes);
                }
            }
        }

        void materialsManager_ChangeTextureProp_Bitmap(int32_t action)
        {
            eTexture* texture;
            eBitmap* bitmap;

            if (nullptr != (texture = materialsManager_GetCurrentTexture()))
            {
                switch (action)
                {
                    case MATMGR_TEXTURES_WINDOW_BMPBTNS_CREATE:
                    {
                        texture->setBitmap(new eBitmap());

                        break;
                    }

                    case MATMGR_TEXTURES_WINDOW_BMPBTNS_REMOVE:
                    {
                        texture->setBitmap(nullptr);

                        break;
                    }

                    case MATMGR_TEXTURES_WINDOW_BMPBTNS_REPLACE:
                    {
                        if (nullptr != (bitmap = materialsManager_GetCurrentBitmap()))
                        {
                            texture->setBitmap(bitmap);
                        }

                        break;
                    }
                }

                materialsManager_UpdateTextureName(texture);

                materialsManager_SetCurrentBitmap(materialsManager_FindBitmapId(texture), true, true);
            }
        }

        void materialsManager_ChangeMaterialProp_Textures(int32_t action)
        {
            eMaterial* material;
            eTexture* texture;
            int32_t textures_count;

            if (nullptr != (material = materialsManager_GetCurrentMaterial()))
            {
                switch (action)
                {
                    case MATMGR_MATERIALS_WINDOW_TEXTBTNS_CREATE:
                    {
                        material->appendTexture(new eTexture(nullptr));

                        break;
                    }

                    case MATMGR_MATERIALS_WINDOW_TEXTBTNS_REMOVE:
                    {
                        material->removeTexture(matMgr_MaterialTextureId);

                        break;
                    }

                    case MATMGR_MATERIALS_WINDOW_TEXTBTNS_MOVEUP:
                    {
                        material->swapTexture(matMgr_MaterialTextureId, (-1));

                        if (material->getTexturesCount() <= 0)
                        {
                            matMgr_MaterialTextureId = (-1);
                        }
                        else
                        {
                            matMgr_MaterialTextureId--;

                            if (matMgr_MaterialTextureId < 0)
                            {
                                matMgr_MaterialTextureId = 0;
                            }
                        }

                        break;
                    }

                    case MATMGR_MATERIALS_WINDOW_TEXTBTNS_MOVEDOWN:
                    {
                        material->swapTexture(matMgr_MaterialTextureId, (+1));

                        matMgr_MaterialTextureId++;

                        textures_count = material->getTexturesCount();

                        if (matMgr_MaterialTextureId >= textures_count)
                        {
                            matMgr_MaterialTextureId = (textures_count - 1);
                        }

                        break;
                    }

                    case MATMGR_MATERIALS_WINDOW_TEXTBTNS_REPLACE:
                    {
                        if (nullptr != (texture = materialsManager_GetCurrentTexture()))
                        {
                            material->setIthTexture(matMgr_MaterialTextureId, texture);
                        }

                        break;
                    }
                }

                materialsManager_UpdateMaterialTexturesListbox(material);
            }
        }

        void materialsManager_ChangeMaterialProp_Flags(bool set_or_unset, uint8_t some_bit)
        {
            eMaterial* material;

            if (nullptr != (material = materialsManager_GetCurrentMaterial()))
            {
                if (set_or_unset)
                {
                    material->setMaterialFlags(some_bit);
                }
                else
                {
                    material->unsetMaterialFlags(some_bit);
                }
            }
        }

        void materialsManager_ChangeMaterialProp_CheckState(bool add_or_remove)
        {
            eMaterial* material;
            eMaterialState* state;

            const char* removal_question =
                "You are about to delete a Material State with all its properties.\n\n" \
                "This operation cannot be undone! Are you sure you want to continue?";

            if (nullptr != (material = materialsManager_GetCurrentMaterial()))
            {
                state = material->getMaterialState();

                if (add_or_remove && (nullptr == state))
                {
                    material->setMaterialState(new eMaterialState());
                }
                else if ((!add_or_remove) && (nullptr != state))
                {
                    if (theWindowsManager.askQuestion(removal_question))
                    {
                        material->setMaterialState(nullptr);
                    }
                }

                materialsManager_UpdateMaterialStateEditboxes(material);
            }
        }

        void materialsManager_ChangeMaterialProp_CloneState()
        {
            eMaterial* material;
            eMaterialState* state;

            if (nullptr != (material = materialsManager_GetCurrentMaterial()))
            {
                if (nullptr != (state = material->getMaterialState()))
                {
                    if (state->getReferenceCount() >= 2)
                    {
                        material->setMaterialState(new eMaterialState(*state));

                        materialsManager_UpdateMaterialStateEditboxes(material);
                    }
                }
            }
        }

        void materialsManager_ChangeMaterialProp_State(int32_t id, int32_t rgb, const char* text_value)
        {
            eMaterial* material;
            eMaterialState* state;
            float color[3];

            if (nullptr != (material = materialsManager_GetCurrentMaterial()))
            {
                if (nullptr != (state = material->getMaterialState()))
                {
                    /* Get source color (not required for changing "shinines" and "global ambient") */

                    switch (id)
                    {
                        case 0:
                        {
                            state->getAmbientColor(color);
                            break;
                        }

                        case 1:
                        {
                            state->getDiffuseColor(color);
                            break;
                        }

                        case 2:
                        {
                            state->getEmissiveColor(color);
                            break;
                        }

                        case 3:
                        {
                            state->getSpecularColor(color);
                            break;
                        }
                    }

                    /* Align the color index (not required for "global ambient") */

                    switch (id)
                    {
                        case 0: case 1: case 2: case 3:
                        {
                            if (rgb < 0)
                            {
                                rgb = 0;
                            }
                            else if (rgb > 2)
                            {
                                rgb = 2;
                            }

                            break;
                        }

                        case 4:
                        {
                            rgb = 0;
                            break;
                        }
                    }

                    /* Convert the text to a floating-point value (not required for "global ambient") */

                    switch (id)
                    {
                        case 0: case 1: case 2: case 3: case 4:
                        {
                            color[rgb] = (float)std::atof(text_value);

                            break;
                        }
                    }

                    /* Mapping the new value, if it is outside of a valid range */

                    switch (id)
                    {
                        case 0: case 1: case 2: case 3:
                        {
                            if (color[rgb] < (-1.0f))
                            {
                                color[rgb] = (-1.0f);
                            }
                            else if (color[rgb] > 1.0f)
                            {
                                color[rgb] = 1.0f;
                            }

                            break;
                        }

                        case 4:
                        {
                            if (color[rgb] < 0)
                            {
                                color[rgb] = 0;
                            }
                            else if (color[rgb] > 128.0f)
                            {
                                color[rgb] = 128.0f;
                            }

                            break;
                        }
                    }

                    /* Upload changed value back to the "Material State" */

                    switch (id)
                    {
                        case 0:
                        {
                            state->setAmbientColor(color);
                            break;
                        }

                        case 1:
                        {
                            state->setDiffuseColor(color);
                            break;
                        }

                        case 2:
                        {
                            state->setEmissiveColor(color);
                            break;
                        }

                        case 3:
                        {
                            state->setSpecularColor(color);
                            break;
                        }

                        case 4:
                        {
                            state->setShininess(color[0]);
                            break;
                        }

                        case 5:
                        {
                            state->setGlobalAmbientLightState((bool)rgb);
                            break;
                        }
                    }
                }
            }
        }

        void materialsManager_ChangeMaterialProp_Collision(int32_t id)
        {
            eMaterial* material;

            if (nullptr != (material = materialsManager_GetCurrentMaterial()))
            {
                if ((id >= 0) && (id < KAO2_MATERIAL_TYPES_COUNT))
                {
                    material->setCollisionType(theMaterialTypes[id].id);
                }
            }
        }

        void materialsManager_ChangeMaterialProp_Sound(int32_t id)
        {
            eMaterial* material;

            if (nullptr != (material = materialsManager_GetCurrentMaterial()))
            {
                if ((id >= 0) && (id < KAO2_MATERIAL_SOUNDS_COUNT))
                {
                    material->setSoundType(theMaterialSounds[id].id);
                }
            }
        }

        void materialsManager_ChangeMaterialProp_Name(const char* new_name)
        {
            eMaterial* material;

            if (nullptr != (material = materialsManager_GetCurrentMaterial()))
            {
                material->setName(new_name);
                materialsManager_UpdateMaterialName(material);
            }
        }

        void materialsManager_ChangeMaterialProp_AlphaTest(const char* text_value)
        {
            eMaterial* material;
            float alpha_test_ref;

            if (nullptr != (material = materialsManager_GetCurrentMaterial()))
            {
                alpha_test_ref = (float)std::atof(text_value);

                if (alpha_test_ref < 0)
                {
                    alpha_test_ref = 0;
                }
                else if (alpha_test_ref > 1.0f)
                {
                    alpha_test_ref = 1.0f;
                }

                material->setAlphaTestRef(alpha_test_ref);
            }
        }


        ////////////////////////////////////////////////////////////////
        // Materials Manager: Deleting objects from the lists
        ////////////////////////////////////////////////////////////////

        void materialsManager_DeleteBitmap(eBitmap* bitmap)
        {
            for (int32_t a = 0; a < matMgr_BmpList_Count; a++)
            {
                if (bitmap == matMgr_BmpList[a])
                {
                    /* Mark current item as invalid and notify the ListBox */

                    matMgr_BmpList[a] = nullptr;

                    SendMessage(matMgr_Windows[MATMGR_BITMAPS_WINDOW_LIST], LB_DELETESTRING, (WPARAM)a, 0);

                    if (matMgr_BmpList_Current == a)
                    {
                        materialsManager_SetCurrentBitmap((-1), true, true);
                    }
                    else if (matMgr_BmpList_Current > a)
                    {
                        matMgr_BmpList_Current--;
                    }

                    /* Move other items one place backwards */

                    for (int b = (a + 1); b < matMgr_BmpList_Count; b++)
                    {
                        matMgr_BmpList[b - 1] = matMgr_BmpList[b];
                        matMgr_BmpList[b] = nullptr;
                    }

                    matMgr_BmpList_Count--;

                    materialsManager_UpdateStatistics();

                    return;
                }
            }
        }

        void materialsManager_DeleteTexture(eTexture* texture)
        {
            for (int32_t a = 0; a < matMgr_TexList_Count; a++)
            {
                if (texture == matMgr_TexList[a])
                {
                    /* Mark current item as invalid and notify the ListBox */

                    matMgr_TexList[a] = nullptr;

                    SendMessage(matMgr_Windows[MATMGR_TEXTURES_WINDOW_LIST], LB_DELETESTRING, (WPARAM)a, 0);

                    if (matMgr_TexList_Current == a)
                    {
                        materialsManager_SetCurrentTexture((-1), true, true, true);
                    }
                    else if (matMgr_TexList_Current > a)
                    {
                        matMgr_TexList_Current--;
                    }

                    /* Move other items one place backwards */

                    for (int b = (a + 1); b < matMgr_TexList_Count; b++)
                    {
                        matMgr_TexList[b - 1] = matMgr_TexList[b];
                        matMgr_TexList[b] = nullptr;
                    }

                    matMgr_TexList_Count--;

                    materialsManager_UpdateStatistics();

                    return;
                }
            }
        }

        void materialsManager_DeleteMaterial(eMaterial* material)
        {
            for (int32_t a = 0; a < matMgr_MatList_Count; a++)
            {
                if (material == matMgr_MatList[a])
                {
                    /* Mark current item as invalid and notify the ListBox */

                    matMgr_MatList[a] = nullptr;

                    SendMessage(matMgr_Windows[MATMGR_MATERIALS_WINDOW_LIST], LB_DELETESTRING, (WPARAM)a, 0);

                    if (matMgr_MatList_Current == a)
                    {
                        materialsManager_SetCurrentMaterial((-1), true, true, 0);
                    }
                    else if (matMgr_MatList_Current > a)
                    {
                        matMgr_MatList_Current--;
                    }

                    /* Move other items one place backwards */

                    for (int b = (a + 1); b < matMgr_MatList_Count; b++)
                    {
                        matMgr_MatList[b - 1] = matMgr_MatList[b];
                        matMgr_MatList[b] = nullptr;
                    }

                    matMgr_MatList_Count--;

                    materialsManager_UpdateStatistics();

                    return;
                }
            }
        }


        ////////////////////////////////////////////////////////////////
        // Materials manager: optimizations (removing duplicate objects)
        ////////////////////////////////////////////////////////////////

        void materialsManager_ReduceSimilarBitmaps(bool silent)
        {
            char bufor[(LARGE_BUFFER_SIZE / 2)];
            int32_t a, b, count;
            eTexture* textures[2];

            count = matMgr_BmpList_Count;

            for (a = 0; a < (matMgr_TexList_Count - 1); a++)
            {
                if (nullptr != (textures[0] = matMgr_TexList[a]))
                {
                    for (b = (a + 1); b < matMgr_TexList_Count; b++)
                    {
                        if (nullptr != (textures[1] = matMgr_TexList[b]))
                        {
                            textures[0]->optimizeTextureByComparingBitmaps(*(textures[1]));
                        }
                    }
                }
            }

            if (!silent)
            {
                count = (matMgr_BmpList_Count - count);

                if (count < 0)
                {
                    sprintf_s(bufor, (LARGE_BUFFER_SIZE / 2), "%d \"Bitmaps\" were removed!", (0 - count));
                }
                else if (count > 0)
                {
                    sprintf_s(bufor, (LARGE_BUFFER_SIZE / 2), "There are now %d more \"Bitmaps\"... THIS SHOULD NEVER HAPPEN!", count);
                }
                else
                {
                    sprintf_s(bufor, (LARGE_BUFFER_SIZE / 2), "No similar \"Bitmaps\" found.");
                }

                theWindowsManager.displayMessage(WINDOWS_MANAGER_MESSAGE_INFO, bufor);
            }
        }

        void materialsManager_ReduceSimilarTexturesAndStates(bool silent)
        {
            char bufor_a[2][(LARGE_BUFFER_SIZE / 2)];
            char bufor_b[LARGE_BUFFER_SIZE];
            int32_t a, b, count[2];
            eMaterial* materials[2];

            count[0] = matMgr_TexList_Count;
            count[1] = theMaterialStatesCounter;

            for (a = 0; a < (matMgr_MatList_Count - 1); a++)
            {
                if (nullptr != (materials[0] = matMgr_MatList[a]))
                {
                    for (b = (a + 1); b < matMgr_MatList_Count; b++)
                    {
                        if (nullptr != (materials[1] = matMgr_MatList[b]))
                        {
                            materials[0]->optimizeMaterialByComparingTexturesAndStates(*(materials[1]));
                        }
                    }
                }
            }

            if (!silent)
            {
                count[0] = (matMgr_TexList_Count - count[0]);
                count[1] = (theMaterialStatesCounter - count[1]);

                if (count[0] < 0)
                {
                    sprintf_s(bufor_a[0], (LARGE_BUFFER_SIZE / 2), "%d \"Textures\" were removed!", (0 - count[0]));
                }
                else if (count[0] > 0)
                {
                    sprintf_s(bufor_a[0], (LARGE_BUFFER_SIZE / 2), "There are now %d more \"Textures\"... THIS SHOULD NEVER HAPPEN!", count[0]);
                }
                else
                {
                    sprintf_s(bufor_a[0], (LARGE_BUFFER_SIZE / 2), "No similar \"Textures\" found.");
                }

                if (count[1] < 0)
                {
                    sprintf_s(bufor_a[1], (LARGE_BUFFER_SIZE / 2), "%d \"Material States\" were removed!", (0 - count[1]));
                }
                else if (count[1] > 0)
                {
                    sprintf_s(bufor_a[1], (LARGE_BUFFER_SIZE / 2), "There are now %d more \"Material States\"... THIS SHOULD NEVER HAPPEN!", count[1]);
                }
                else
                {
                    sprintf_s(bufor_a[1], (LARGE_BUFFER_SIZE / 2), "No similar \"Material States\" found.");
                }

                sprintf_s(bufor_b, LARGE_BUFFER_SIZE, "%s\n\n%s", bufor_a[0], bufor_a[1]);

                theWindowsManager.displayMessage(WINDOWS_MANAGER_MESSAGE_INFO, bufor_b);
            }
        }

        void materialsManager_ReduceSimilarMaterials(eNode* root_node, bool silent)
        {
            char bufor[(LARGE_BUFFER_SIZE / 2)];
            int32_t a, b, count[2];
            eGeometry* geo[2];
            Collection<ArFunctions::serialize_eRefCounter> list;

            if (nullptr == root_node)
            {
                /* Invalid parameter */
                return;
            }

            count[0] = matMgr_MatList_Count;

            root_node->collectNodesOfSomeType(&E_GEOMETRY_TYPEINFO, list);
            count[1] = list.getSize();

            for (a = 0; a < (count[1] - 1); a++)
            {
                if (nullptr != (geo[0] = (eGeometry*)list.getIthChild(a)))
                {
                    for (b = (a + 1); b < count[1]; b++)
                    {
                        if (nullptr != (geo[1] = (eGeometry*)list.getIthChild(b)))
                        {
                            geo[0]->optimizeGeometryByComparingMaterials(*(geo[1]));
                        }
                    }
                }
            }

            if (!silent)
            {
                count[0] = (matMgr_MatList_Count - count[0]);

                if (count[0] < 0)
                {
                    sprintf_s(bufor, (LARGE_BUFFER_SIZE / 2), "%d \"Materials\" were removed!", (0 - count[0]));
                }
                else if (count[0] > 0)
                {
                    sprintf_s(bufor, (LARGE_BUFFER_SIZE / 2), "There are now %d more \"Materials\"... THIS SHOULD NEVER HAPPEN!", count[0]);
                }
                else
                {
                    sprintf_s(bufor, (LARGE_BUFFER_SIZE / 2), "No similar \"Materials\" found.");
                }

                theWindowsManager.displayMessage(WINDOWS_MANAGER_MESSAGE_INFO, bufor);
            }
        }


        ////////////////////////////////////////////////////////////////
        // Materials Manager: Update Thumbnails Window
        // (1 = browsing every 100 thumbnails, 2 = enlarging a specific image)
        ////////////////////////////////////////////////////////////////
        void materialsManager_UpdateThumbnailsWindow(int list_id)
        {
            if ((MATMGR_RENDERED_LIST_THUMBNAILS_GRID == matMgr_RenderedList) && (MATMGR_RENDERED_LIST_THUMBNAILS_GRID == list_id))
            {
                matMgr_scrollPos++;

                if ((THUMBNAILS_IN_GRID * THUMBNAILS_IN_GRID * matMgr_scrollPos) >= matMgr_BmpList_Count)
                {
                    matMgr_scrollPos = 0;
                }
            }
            else if ((list_id >= MATMGR_RENDERED_LIST_MIN) && (list_id <= MATMGR_RENDERED_LIST_MAX))
            {
                matMgr_RenderedList = list_id;

                matMgr_scrollPos = 0;
            }
        }


        ////////////////////////////////////////////////////////////////
        // Materials manager: Rendering
        ////////////////////////////////////////////////////////////////

        void materialsManager_ParseMouse(float pos_x, float pos_y, int click)
        {
            /* click: [1] = move, [2] = pressed, [3] = released */

            matMgr_mousePos[0] = pos_x;
            matMgr_mousePos[1] = pos_y;
            matMgr_mouseMode = click;

            if (3 == click)
            {
                if (MATMGR_RENDERED_LIST_THUMBNAILS_GRID == matMgr_RenderedList)
                {
                    int counter = THUMBNAILS_IN_GRID * THUMBNAILS_IN_GRID * matMgr_scrollPos;

                    for (int y = 0; (counter < matMgr_BmpList_Count) && (y < THUMBNAILS_IN_GRID); y++)
                    {
                        for (int x = 0; (counter < matMgr_BmpList_Count) && (x < THUMBNAILS_IN_GRID); x++)
                        {
                            float center_x = (float)(((x - (THUMBNAILS_IN_GRID / 2.0f)) * 2) + 1);
                            float center_y = (float)(((y - (THUMBNAILS_IN_GRID / 2.0f)) * (-2)) - 1);

                            if ((matMgr_mousePos[0] >= (center_x - THUMBNAIL_HW))
                                && (matMgr_mousePos[0] <= (center_x + THUMBNAIL_HW))
                                && (matMgr_mousePos[1] >= (center_y - THUMBNAIL_HW))
                                && (matMgr_mousePos[1] <= (center_y + THUMBNAIL_HW)))
                            {
                                materialsManager_SetCurrentBitmap(counter, true, true);

                                materialsManager_UpdateThumbnailsWindow(MATMGR_RENDERED_LIST_SINGLE_BITMAP);

                                return;
                            }

                            counter++;
                        }
                    }

                    /* Mouse button released outside the Thumbnails Grid. */
                    /* Browsing another page (if available).              */
                    materialsManager_UpdateThumbnailsWindow(MATMGR_RENDERED_LIST_THUMBNAILS_GRID);
                }
                else if (MATMGR_RENDERED_LIST_SINGLE_BITMAP == matMgr_RenderedList)
                {
                    /* Switch back to the Thumbnails List                  */
                    /* by clicking anywhere when a single bitmap is shown. */
                    matMgr_RenderedList = MATMGR_RENDERED_LIST_THUMBNAILS_GRID;
                    matMgr_scrollPos = 0;
                }
            }
        }

        void materialsManager_Render()
        {
            /* Render the checkerboard background */

            glEnable(GL_TEXTURE_2D);

            glBindTexture(GL_TEXTURE_2D, matMgr_textures[0]);

            glBegin(GL_TRIANGLE_STRIP);
            {
                glTexCoord2f(40.0f, 0);
                glVertex3f(20.0f, 20.0f, (-1.0f));

                glTexCoord2f(0, 0);
                glVertex3f((-20.0f), 20.0f, (-1.0f));

                glTexCoord2f(40.0f, 40.0f);
                glVertex3f(20.0f, (-20.0f), (-1.0f));

                glTexCoord2f(0, 40.0f);
                glVertex3f((-20.0f), (-20.0f), (-1.0f));
            }
            glEnd();

            if (MATMGR_RENDERED_LIST_THUMBNAILS_GRID == matMgr_RenderedList)
            {
                /* Rendering thumbnails */

                int counter = THUMBNAILS_IN_GRID * THUMBNAILS_IN_GRID * matMgr_scrollPos;

                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

                for (int y = 0; (counter < matMgr_BmpList_Count) && (y < THUMBNAILS_IN_GRID); y++)
                {
                    for (int x = 0; (counter < matMgr_BmpList_Count) && (x < THUMBNAILS_IN_GRID); x++)
                    {
                        eBitmap* dummy_bitmap = matMgr_BmpList[counter];

                        if (nullptr != dummy_bitmap)
                        {
                            float center_x = (float)(((x - (THUMBNAILS_IN_GRID / 2.0f)) * 2) + 1);
                            float center_y = (float)(((y - (THUMBNAILS_IN_GRID / 2.0f)) * (-2)) - 1);

                            float ratio = dummy_bitmap->getAspectRatio();
                            float render_x = (ratio < 1.0f) ? (THUMBNAIL_HW * ratio) : THUMBNAIL_HW;
                            float render_y = (ratio > 1.0f) ? (THUMBNAIL_HW / ratio) : THUMBNAIL_HW;

                            glBindTexture(GL_TEXTURE_2D, dummy_bitmap->getTextureId());

                            glBegin(GL_TRIANGLE_STRIP);
                            {
                                glTexCoord2f(1.0f, 0);
                                glVertex3f(center_x + render_x, center_y + render_y, (-0.5f));

                                glTexCoord2f(0, 0);
                                glVertex3f(center_x - render_x, center_y + render_y, (-0.5f));

                                glTexCoord2f(1.0f, 1.0f);
                                glVertex3f(center_x + render_x, center_y - render_y, (-0.5f));

                                glTexCoord2f(0, 1.0f);
                                glVertex3f(center_x - render_x, center_y - render_y, (-0.5f));
                            }
                            glEnd();

                            if ((matMgr_mousePos[0] >= (center_x - THUMBNAIL_HW))
                              && (matMgr_mousePos[0] <= (center_x + THUMBNAIL_HW))
                              && (matMgr_mousePos[1] >= (center_y - THUMBNAIL_HW))
                              && (matMgr_mousePos[1] <= (center_y + THUMBNAIL_HW)))
                            {
                                float shade = (2 == matMgr_mouseMode) ? 0 : 1.0f;

                                glColor4f(shade, shade, shade, 0.5f);

                                glBindTexture(GL_TEXTURE_2D, 0);

                                glBegin(GL_TRIANGLE_STRIP);
                                {
                                    glVertex3f(center_x + render_x, center_y + render_y, 0);
                                    glVertex3f(center_x - render_x, center_y + render_y, 0);
                                    glVertex3f(center_x + render_x, center_y - render_y, 0);
                                    glVertex3f(center_x - render_x, center_y -render_y, 0);
                                }
                                glEnd();

                                glColor3f(1.0f, 1.0f, 1.0f);
                            }
                        }

                        counter++;
                    }
                }

                glDisable(GL_BLEND);
            }
            else if (MATMGR_RENDERED_LIST_SINGLE_BITMAP == matMgr_RenderedList)
            {
                /* Rendering a bitmap */

                if ((matMgr_BmpList_Current >= 0) && (matMgr_BmpList_Current < matMgr_BmpList_Count))
                {
                    eBitmap* dummy_bitmap = matMgr_BmpList[matMgr_BmpList_Current];

                    if (nullptr != dummy_bitmap)
                    {
                        float ratio = dummy_bitmap->getAspectRatio();
                        float render_x = (ratio < 1.0f) ? (BIG_THUMBNAIL_HW * ratio) : BIG_THUMBNAIL_HW;
                        float render_y = (ratio > 1.0f) ? (BIG_THUMBNAIL_HW / ratio) : BIG_THUMBNAIL_HW;

                        glBindTexture(GL_TEXTURE_2D, dummy_bitmap->getTextureId());

                        glEnable(GL_BLEND);
                        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

                        glBegin(GL_TRIANGLE_STRIP);
                        {
                            glTexCoord2f(1.0f, 0);
                            glVertex3f(render_x, render_y, (-0.5f));

                            glTexCoord2f(0, 0);
                            glVertex3f((-render_x), render_y, (-0.5f));

                            glTexCoord2f(1.0f, 1.0f);
                            glVertex3f(render_x, (-render_y), (-0.5f));

                            glTexCoord2f(0, 1.0f);
                            glVertex3f((-render_x), (-render_y), (-0.5f));
                        }
                        glEnd();

                        glDisable(GL_BLEND);

                        /* Render a border */

                        const float HALF_BORDER_WIDTH = 0.25f;

                        glBindTexture(GL_TEXTURE_2D, 0);

                        float border_color[3];
                        GUI::colorOfMarkedObject(border_color[0], border_color[1], border_color[2]);

                        glColor3f(border_color[0], border_color[1], border_color[2]);
                        glLineWidth(5.0f);

                        render_x += HALF_BORDER_WIDTH;
                        render_y += HALF_BORDER_WIDTH;

                        glBegin(GL_LINES);
                        {
                            glVertex3f((-render_x), (-render_y), 0);
                            glVertex3f(render_x, (-render_y), 0);

                            glVertex3f(render_x, (-render_y), 0);
                            glVertex3f(render_x, render_y, 0);

                            glVertex3f(render_x, render_y, 0);
                            glVertex3f((-render_x), render_y, 0);

                            glVertex3f((-render_x), render_y, 0);
                            glVertex3f((-render_x), (-render_y), 0);
                        }
                        glEnd();

                        glLineWidth(1.0f);
                        glColor3f(1.0f, 1.0f, 1.0f);
                    }
                }
            }

            glBindTexture(GL_TEXTURE_2D, 0);
            glDisable(GL_TEXTURE_2D);
        }


        ////////////////////////////////////////////////////////////////
        // Materials manager: Exporting and reimporting
        ////////////////////////////////////////////////////////////////

        bool materialsManager_ExportBitmap(int id, eString &working_directory)
        {
            if ((id < 0) || (id >= matMgr_BmpList_Count))
            {
                return false;
            }

            eBitmap* dummy_bitmap = matMgr_BmpList[id];

            if (nullptr != dummy_bitmap)
            {
                if (!(dummy_bitmap->getPath().isEmpty()))
                {
                    try
                    {
                        dummy_bitmap->exportImageFile(working_directory);

                        return true;
                    }
                    catch (ErrorMessage &err)
                    {
                        err.display();
                    }
                }
            }

            return false;
        }

        bool materialsManager_ReimportBitmap(int id, eString &working_directory, bool silent)
        {
            if ((id < 0) || (id >= matMgr_BmpList_Count))
            {
                return false;
            }

            eBitmap* dummy_bitmap = matMgr_BmpList[id];

            if (nullptr != dummy_bitmap)
            {
                if (!(dummy_bitmap->getPath().isEmpty()))
                {
                    try
                    {
                        bool result = dummy_bitmap->loadFromFile(working_directory, silent);

                        if (true == result)
                        {
                            dummy_bitmap->generateTexture();

                            return true;
                        }
                    }
                    catch (ErrorMessage &err)
                    {
                        err.display();
                    }
                }
            }

            return false;
        }

        eString materialsManager_AssignWorkingDirectory(eString directory)
        {
            directory.assertPath();
            return directory;
        }

        void materialsManager_ExportCurrentBitmap()
        {
            char bufor[512];
            eString test_str = "<Invalid Selection>";
            eString working_directory = materialsManager_AssignWorkingDirectory(getEditorString(1, false));

            theLog.print
            (
                "================================\n" \
                "==    EXPORTING ONE BITMAP    ==\n" \
                "==            BEGIN           ==\n" \
                "================================\n"
            );

            if ((matMgr_BmpList_Current >= 0) && (matMgr_BmpList_Current < matMgr_BmpList_Count))
            {
                test_str = "<Unnamed Bitmap>";

                eString bmp_path = matMgr_BmpList[matMgr_BmpList_Current]->getPath();

                if (!(bmp_path.isEmpty()))
                {
                    test_str = eString("\"") + bmp_path + "\"";
                }
            }

            if (materialsManager_ExportBitmap(matMgr_BmpList_Current, working_directory))
            {
                theLog.print
                (
                    "================================\n" \
                    "==    EXPORTING ONE BITMAP    ==\n" \
                    "==          FINISHED          ==\n" \
                    "================================\n"
                );

                sprintf_s
                (
                    bufor, 512,
                    "Selected bitmap has been successfully exported! :)\n\n%s",
                    test_str.getText()
                );
            }
            else
            {
                theLog.print
                (
                    "================================\n" \
                    "==    EXPORTING ONE BITMAP    ==\n" \
                    "==            oops!           ==\n" \
                    "================================\n"
                );

                sprintf_s
                (
                    bufor, 512,
                    "Could not export the selected bitmap! :(\n\n%s",
                    test_str.getText()
                );
            }

            theWindowsManager.displayMessage(WINDOWS_MANAGER_MESSAGE_INFO, bufor);
        }

        void materialsManager_ReimportCurrentBitmap()
        {
            char bufor[512];
            eString test_str = "<Invalid Selection>";
            eString working_directory = materialsManager_AssignWorkingDirectory(getEditorString(1, false));

            theLog.print
            (
                "================================\n" \
                "==   REIMPORTING ONE BITMAP   ==\n" \
                "==            BEGIN           ==\n" \
                "================================\n"
            );

            if ((matMgr_BmpList_Current >= 0) && (matMgr_BmpList_Current < matMgr_BmpList_Count))
            {
                test_str = "<Unnamed Bitmap>";

                eString bmp_path = matMgr_BmpList[matMgr_BmpList_Current]->getPath();

                if (!(bmp_path.isEmpty()))
                {
                    test_str = eString("\"") + bmp_path + "\"";
                }
            }

            if (materialsManager_ReimportBitmap(matMgr_BmpList_Current, working_directory, false))
            {
                theLog.print
                (
                    "================================\n" \
                    "==   REIMPORTING ONE BITMAP   ==\n" \
                    "==          FINISHED          ==\n" \
                    "================================\n"
                );

                sprintf_s
                (
                    bufor, 512, "Selected bitmap has been successfully reimported! :)\n\n%s",
                    test_str.getText()
                );
            }
            else
            {
                theLog.print
                (
                    "================================\n" \
                    "==   REIMPORTING ONE BITMAP   ==\n" \
                    "==            oops!           ==\n" \
                    "================================\n"
                );

                sprintf_s
                (
                    bufor, 512,
                    "Could not reimport the selected bitmap! :(\n\n%s",
                    test_str.getText()
                );
            }

            theWindowsManager.displayMessage(WINDOWS_MANAGER_MESSAGE_INFO, bufor);
        }

        int materialsManager_ExportAllBitmaps(int start_id, eString working_directory, bool silent)
        {
            char bufor[LARGE_BUFFER_SIZE];
            int result = 0;
            int total = 0;

            working_directory = materialsManager_AssignWorkingDirectory(working_directory);

            if (false == silent)
            {
                theLog.print
                (
                    "================================\n" \
                    "==   EXPORTING ALL BITMAPS    ==\n" \
                    "==            BEGIN           ==\n" \
                    "================================\n"
                );
            }

            for (int a = start_id; a < matMgr_BmpList_Count; a++)
            {
                if (materialsManager_ExportBitmap(a, working_directory))
                {
                    result++;
                }

                total++;
            }

            if (false == silent)
            {
                theLog.print
                (
                    "================================\n" \
                    "==   EXPORTING ALL BITMAPS    ==\n" \
                    "==          FINISHED          ==\n" \
                    "================================\n"
                );

                sprintf_s(bufor, LARGE_BUFFER_SIZE, "Exported %d / %d bitmaps.", result, total);

                theWindowsManager.displayMessage(WINDOWS_MANAGER_MESSAGE_INFO, bufor);
            }

            return result;
        }

        int materialsManager_ReimportAllBitmaps(int start_id, eString working_directory, bool silent)
        {
            char bufor[LARGE_BUFFER_SIZE];
            int result = 0;
            int total = 0;

            working_directory = materialsManager_AssignWorkingDirectory(working_directory);

            if (false == silent)
            {
                theLog.print
                (
                    "================================\n" \
                    "==  REIMPORTING ALL BITMAPS   ==\n" \
                    "==            BEGIN           ==\n" \
                    "================================\n"
                );
            }

            for (int a = start_id; a < matMgr_BmpList_Count; a++)
            {
                if (materialsManager_ReimportBitmap(a, working_directory, true))
                {
                    result++;
                }

                total++;
            }

            if (false == silent)
            {
                theLog.print
                (
                    "================================\n" \
                    "==  REIMPORTING ALL BITMAPS   ==\n" \
                    "==          FINISHED          ==\n" \
                    "================================\n"
                );

                sprintf_s(bufor, LARGE_BUFFER_SIZE, "Reimported %d / %d bitmaps.", result, total);

                theWindowsManager.displayMessage(WINDOWS_MANAGER_MESSAGE_INFO, bufor);
            }

            return result;
        }

        void materialsManager_BulkTexturesExport()
        {
            int result_textures, result_archives, engine_version, test_id;
            char bufor[LARGE_BUFFER_SIZE];

            eString output_dir;
            eString keywords[3];
            Archive dummy_ar;

            FileOperator list;

            try
            {
                /* Show instruction */

                GUI::theWindowsManager.displayMessage
                (
                    WINDOWS_MANAGER_MESSAGE_INFO,
                    "Select a text file structured in a following way:\n\n" \
                    "First line: [game version] [media directory]\n" \
                    "Second line: [output directory]\n" \
                    "next lines: file names (in reference to media directory)\n" \
                    "\n--------------------------------\n" \
                    "    EXAMPLE:\n\n" \
                    "[1] 1 C:\\Program Files (x86)\\Kangurek Kao - Runda 2\\media\n" \
                    "[2] C:\\Kao2 Textures\n" \
                    "[3] build/pc/00_hub.ar\n" \
                    "[4] build/pc/02_forest_of_canada.ar\n"
                );

                /* Try to open a text file */

                bufor[0] = 0x00;

                ofn.lpstrFile = bufor;
                ofn.nMaxFile = LARGE_BUFFER_SIZE;
                ofn.lpstrTitle = "Opening a list file..";
                ofn.lpstrFilter = "Text files (*.txt)\0*.txt\0";
                ofn.Flags = (OFN_FILEMUSTEXIST | OFN_HIDEREADONLY);

                if (0 == GetOpenFileName(&ofn))
                {
                    return;
                }

                theLog.print
                (
                    "================================\n" \
                    "==  BULK TEXTURES EXPORTING   ==\n" \
                    "==            BEGIN           ==\n" \
                    "================================\n"
                );

                if (!list.open(bufor, FILE_OPERATOR_MODE_READ))
                {
                    throw ErrorMessage("Could not open file: \"%s\".", bufor);
                }

                /* Reading the first two lines */

                keywords[2] << list;

                ArFunctions::splitString(keywords[2], keywords, 2);

                /* [1.1] Game engine version */

                engine_version = std::atoi(keywords[0].getText());

                switch (engine_version)
                {
                    case GAME_VERSION_KAO2_PL_PC:
                    case GAME_VERSION_KAO2_EUR_PC:
                    case GAME_VERSION_KAO_TW_PC:
                    case GAME_VERSION_ASTERIX_XXL2_PSP:
                    {
                        break;
                    }

                    default:
                    {
                        throw ErrorMessage
                        (
                            "Error while parsing the beginning of the list:\n" \
                            "Incorrect game version number!"
                        );
                    }
                }

                /* [1.2] and [2] - Working directories */

                dummy_ar.setMediaDir(keywords[1]);

                output_dir << list;
                output_dir = materialsManager_AssignWorkingDirectory(output_dir);

                /* Begin the conversion... */

                result_textures = 0;
                result_archives = 0;

                while (!list.endOfFileReached())
                {
                    keywords[1] << list;

                    if (ArFunctions::splitString(keywords[1], keywords, 1) >= 1)
                    {
                        /* "*.ar" */

                        if ((keywords[0].getLength() > 3) && ('#' != keywords[0].getText()[0]))
                        {
                            /* Source archive */

                            test_id = matMgr_BmpList_Count;

                            dummy_ar.open
                            (
                                dummy_ar.getMediaDir() + keywords[0],
                                (AR_MODE_SKIP_PROXIES | AR_MODE_READ),
                                engine_version,
                                0
                            );

                            /* Export all bitmaps */

                            result_textures += materialsManager_ExportAllBitmaps(test_id, output_dir, true);

                            dummy_ar.close(true);

                            result_archives++;
                        }
                    }
                }

                list.close();

                theLog.print
                (
                    "================================\n" \
                    "==  BULK TEXTURES EXPORTING   ==\n" \
                    "==          FINISHED          ==\n" \
                    "================================\n"
                );

                sprintf_s
                (
                    bufor, LARGE_BUFFER_SIZE,
                    "Successfully exported %d textures from %d KAO2 archives!",
                    result_textures,
                    result_archives
                );

                GUI::theWindowsManager.displayMessage(WINDOWS_MANAGER_MESSAGE_INFO, bufor);
            }
            catch (ErrorMessage &err)
            {
                theLog.print
                (
                    "================================\n" \
                    "==  BULK TEXTURES EXPORTING   ==\n" \
                    "==            oops!           ==\n" \
                    "================================\n"
                );

                err.display();
            }
        }

        void materialsManager_BulkTexturesReimport()
        {
            int result_textures, result_archives, engine_version, archive_version, test_id;
            char bufor[LARGE_BUFFER_SIZE];

            eString input_dir;
            eString keywords[3];
            Archive dummy_ar;

            FileOperator list;

            try
            {
                /* Show instruction */

                GUI::theWindowsManager.displayMessage
                (
                    WINDOWS_MANAGER_MESSAGE_INFO,
                    "Select a text file structured in a following way:\n\n" \
                    "First line: [game version] [media directory]\n" \
                    "Second line: [input directory]\n" \
                    "next lines: file names (in reference to the input directory)\n" \
                    "\n--------------------------------\n" \
                    "    EXAMPLE:\n\n" \
                    "[1] 1 C:\\Program Files (x86)\\Kangurek Kao - Runda 2\\media\n" \
                    "[2] C:\\Kao2 Textures\n" \
                    "[3] build/pc/00_hub.ar\n" \
                    "[4] build/pc/02_forest_of_canada.ar\n"
                );

                /* Try to open a text file */

                bufor[0] = 0x00;

                ofn.lpstrFile = bufor;
                ofn.nMaxFile = LARGE_BUFFER_SIZE;
                ofn.lpstrTitle = "Opening a list file..";
                ofn.lpstrFilter = "Text files (*.txt)\0*.txt\0";
                ofn.Flags = (OFN_FILEMUSTEXIST | OFN_HIDEREADONLY);

                if (0 == GetOpenFileName(&ofn))
                {
                    return;
                }

                theLog.print
                (
                    "================================\n" \
                    "==  BULK TEXTURES REMPORTING  ==\n" \
                    "==            BEGIN           ==\n" \
                    "================================\n"
                );

                if (!list.open(bufor, FILE_OPERATOR_MODE_READ))
                {
                    throw ErrorMessage("Could not open file: \"%s\".", bufor);
                }

                /* Read the first line */

                keywords[2] << list;

                ArFunctions::splitString(keywords[2], keywords, 2);

                /* [1.1] Game engine version */

                engine_version = std::atoi(keywords[0].getText());

                switch (engine_version)
                {
                    case GAME_VERSION_KAO2_PL_PC:
                    case GAME_VERSION_KAO2_EUR_PC:
                    case GAME_VERSION_KAO_TW_PC:
                    case GAME_VERSION_ASTERIX_XXL2_PSP:
                    {
                        break;
                    }

                    default:
                    {
                        throw ErrorMessage
                        (
                            "Error while parsing the beginning of the list:\n" \
                            "Incorrect game version number!"
                        );
                    }
                }

                /* [1.2] and [2] - Working directories */

                dummy_ar.setMediaDir(keywords[1]);

                input_dir << list;
                input_dir = materialsManager_AssignWorkingDirectory(input_dir);

                /* Begin the conversion... */

                result_textures = 0;
                result_archives = 0;

                while (!list.endOfFileReached())
                {
                    keywords[1] << list;

                    if (ArFunctions::splitString(keywords[1], keywords, 1) >= 1)
                    {
                        /* "*.ar" */

                        if ((keywords[0].getLength() > 3) && ('#' != keywords[0].getText()[0]))
                        {
                            keywords[0] = dummy_ar.getMediaDir() + keywords[0];

                            /* Source archive */

                            test_id = matMgr_BmpList_Count;

                            dummy_ar.open
                            (
                                keywords[0],
                                (AR_MODE_SKIP_PROXIES | AR_MODE_READ),
                                engine_version,
                                0
                            );

                            archive_version = dummy_ar.getVersion();

                            /* Reimport all found bitmaps */

                            result_textures += materialsManager_ReimportAllBitmaps(test_id, input_dir, true);

                            /* Destination archive */

                            dummy_ar.open
                            (
                                keywords[0],
                                (AR_MODE_WRITE),
                                engine_version,
                                archive_version
                            );

                            dummy_ar.close(true);

                            result_archives++;
                        }
                    }
                }

                list.close();

                theLog.print
                (
                    "================================\n" \
                    "==  BULK TEXTURES REMPORTING  ==\n" \
                    "==          FINISHED          ==\n" \
                    "================================\n"
                );

                sprintf_s
                (
                    bufor, LARGE_BUFFER_SIZE,
                    "Successfully reimported %d textures to %d KAO2 archives!",
                    result_textures,
                    result_archives
                );

                GUI::theWindowsManager.displayMessage(WINDOWS_MANAGER_MESSAGE_INFO, bufor);
            }
            catch (ErrorMessage &err)
            {
                theLog.print
                (
                    "================================\n" \
                    "==  BULK TEXTURES REMPORTING  ==\n" \
                    "==            oops!           ==\n" \
                    "================================\n"
                );

                err.display();
            }
        }


        ////////////////////////////////////////////////////////////////
        // Materials manager: GUI functions
        ////////////////////////////////////////////////////////////////

        void func_MaterialsManagerSwitchPage(int32_t direction)
        {
            char bufor[64];

            if (direction < 0)
            {
                matMgr_CurrentSubpage--;
            }
            else if (direction > 0)
            {
                matMgr_CurrentSubpage++;
            }

            if (matMgr_CurrentSubpage < 0)
            {
                matMgr_CurrentSubpage = 0;
            }
            else if (matMgr_CurrentSubpage >= 4)
            {
                matMgr_CurrentSubpage = 4 - 1;
            }

            for (int32_t i = 1; i < MATMGR_WINDOWS_COUNT; i++)
            {
                bool show_button = false;

                if ( ((0 == matMgr_CurrentSubpage) && (i >= MATMGR_INFO_WINDOW_START) && (i <= MATMGR_INFO_WINDOW_END))
                  || ((1 == matMgr_CurrentSubpage) && (i >= MATMGR_MATERIALS_WINDOW_START) && (i <= MATMGR_MATERIALS_WINDOW_END))
                  || ((2 == matMgr_CurrentSubpage) && (i >= MATMGR_TEXTURES_WINDOW_START) && (i <= MATMGR_TEXTURES_WINDOW_END))
                  || ((3 == matMgr_CurrentSubpage) && (i >= MATMGR_BITMAPS_WINDOW_START) && (i <= MATMGR_BITMAPS_WINDOW_END))
                )
                {
                    show_button = true;
                }

                ShowWindow(matMgr_Windows[i], show_button ? SW_SHOW : SW_HIDE);
            }

            sprintf_s
            (
                bufor, 64,
                "Subpage [%d/4]: %s",
                (1 + matMgr_CurrentSubpage),
                matMgr_SubpageNames[matMgr_CurrentSubpage]
            );

            SetWindowText(matMgr_Windows[MATMGR_WINDOW_SUBPAGENAME], bufor);
        }

        void buttonFunc_MaterialsManagerSwitchPage(WPARAM wParam, LPARAM lParam, void* custom_param)
        {
            if (BN_CLICKED == HIWORD(wParam))
            {
                func_MaterialsManagerSwitchPage((int32_t)custom_param);
            }
        }

        void menuFunc_MaterialsManagerEnter()
        {
            func_MaterialsManagerSwitchPage(0);

            changeView(false);
        }

        void menuFunc_MaterialsManagerLeave()
        {
            changeView(true);
        }

        void buttonFunc_MaterialsManagerClicking(WPARAM wParam, LPARAM lParam, void* custom_param)
        {
            int32_t button_id = (int32_t)custom_param;
            bool is_checked;

            if (!matMgr_UpdatingWindowsNotByUser)
            {
                if (BN_CLICKED == HIWORD(wParam))
                {
                    is_checked = (BST_CHECKED == SendMessage((HWND)lParam, BM_GETCHECK, 0, 0));

                    switch (button_id)
                    {
                        case MATMGR_INFO_WINDOW_OPTIMIZE_BMPBTN:
                        {
                            materialsManager_ReduceSimilarBitmaps(false);

                            break;
                        }

                        case MATMGR_INFO_WINDOW_OPTIMIZE_TEXBTN:
                        {
                            materialsManager_ReduceSimilarTexturesAndStates(false);

                            break;
                        }

                        case MATMGR_MATERIALS_WINDOW_TEXTBTNS_CREATE:
                        {
                            materialsManager_ChangeMaterialProp_Textures(MATMGR_MATERIALS_WINDOW_TEXTBTNS_CREATE);

                            break;
                        }

                        case MATMGR_MATERIALS_WINDOW_TEXTBTNS_REMOVE:
                        {
                            materialsManager_ChangeMaterialProp_Textures(MATMGR_MATERIALS_WINDOW_TEXTBTNS_REMOVE);

                            break;
                        }

                        case MATMGR_MATERIALS_WINDOW_TEXTBTNS_MOVEUP:
                        {
                            materialsManager_ChangeMaterialProp_Textures(MATMGR_MATERIALS_WINDOW_TEXTBTNS_MOVEUP);

                            break;
                        }

                        case MATMGR_MATERIALS_WINDOW_TEXTBTNS_MOVEDOWN:
                        {
                            materialsManager_ChangeMaterialProp_Textures(MATMGR_MATERIALS_WINDOW_TEXTBTNS_MOVEDOWN);

                            break;
                        }

                        case MATMGR_MATERIALS_WINDOW_TEXTBTNS_REPLACE:
                        {
                            materialsManager_ChangeMaterialProp_Textures(MATMGR_MATERIALS_WINDOW_TEXTBTNS_REPLACE);

                            break;
                        }

                        case MATMGR_MATERIALS_WINDOW_STATECHECK_USED:
                        {
                            materialsManager_ChangeMaterialProp_CheckState(is_checked);

                            break;
                        }

                        case MATMGR_MATERIALS_WINDOW_STATECHECK_4C:
                        {
                            materialsManager_ChangeMaterialProp_State(5, (int32_t)is_checked, nullptr);

                            break;
                        }

                        case MATMGR_MATERIALS_WINDOW_STATEBTN_CLONE:
                        {
                            materialsManager_ChangeMaterialProp_CloneState();

                            break;
                        }

                        case MATMGR_MATERIALS_WINDOW_FLAGSCHECK1:
                        {
                            materialsManager_ChangeMaterialProp_Flags(is_checked, (0x01 << 0));

                            break;
                        }

                        case MATMGR_MATERIALS_WINDOW_FLAGSCHECK2:
                        {
                            materialsManager_ChangeMaterialProp_Flags(is_checked, (0x01 << 1));

                            break;
                        }

                        case MATMGR_MATERIALS_WINDOW_FLAGSCHECK3:
                        {
                            materialsManager_ChangeMaterialProp_Flags(is_checked, (0x01 << 2));

                            break;
                        }

                        case MATMGR_MATERIALS_WINDOW_FLAGSCHECK4:
                        {
                            materialsManager_ChangeMaterialProp_Flags(is_checked, (0x01 << 3));

                            break;
                        }

                        case MATMGR_TEXTURES_WINDOW_FLAGSCHECK1:
                        {
                            materialsManager_ChangeTextureProp_Flags(is_checked, (0x01 << 0));

                            break;
                        }

                        case MATMGR_TEXTURES_WINDOW_FLAGSCHECK2:
                        {
                            materialsManager_ChangeTextureProp_Flags(is_checked, (0x01 << 1));

                            break;
                        }

                        case MATMGR_TEXTURES_WINDOW_FLAGSCHECK3:
                        {
                            materialsManager_ChangeTextureProp_Flags(is_checked, (0x01 << 2));

                            break;
                        }

                        case MATMGR_TEXTURES_WINDOW_BMPBTNS_CREATE:
                        {
                            materialsManager_ChangeTextureProp_Bitmap(MATMGR_TEXTURES_WINDOW_BMPBTNS_CREATE);

                            break;
                        }

                        case MATMGR_TEXTURES_WINDOW_BMPBTNS_REMOVE:
                        {
                            materialsManager_ChangeTextureProp_Bitmap(MATMGR_TEXTURES_WINDOW_BMPBTNS_REMOVE);

                            break;
                        }

                        case MATMGR_TEXTURES_WINDOW_BMPBTNS_REPLACE:
                        {
                            materialsManager_ChangeTextureProp_Bitmap(MATMGR_TEXTURES_WINDOW_BMPBTNS_REPLACE);

                            break;
                        }

                        case MATMGR_TEXTURES_WINDOW_FORMCHECK_USED:
                        {
                            materialsManager_ChangeTextureProp_CheckKeyframes(is_checked);

                            break;
                        }

                        case MATMGR_TEXTURES_WINDOW_FORMBTNS_CAT_SX:
                        {
                            matMgr_TextureKeyframesCategory = 0;

                            materialsManager_UpdateTextureKeyframesListbox(materialsManager_GetCurrentTexture(), true);

                            break;
                        }

                        case MATMGR_TEXTURES_WINDOW_FORMBTNS_CAT_SY:
                        {
                            matMgr_TextureKeyframesCategory = 1;

                            materialsManager_UpdateTextureKeyframesListbox(materialsManager_GetCurrentTexture(), true);

                            break;
                        }

                        case MATMGR_TEXTURES_WINDOW_FORMBTNS_CAT_U:
                        {
                            matMgr_TextureKeyframesCategory = 2;

                            materialsManager_UpdateTextureKeyframesListbox(materialsManager_GetCurrentTexture(), true);

                            break;
                        }

                        case MATMGR_TEXTURES_WINDOW_FORMBTNS_CAT_V:
                        {
                            matMgr_TextureKeyframesCategory = 3;

                            materialsManager_UpdateTextureKeyframesListbox(materialsManager_GetCurrentTexture(), true);

                            break;
                        }

                        case MATMGR_TEXTURES_WINDOW_FORMBTNS_CREATE:
                        {
                            materialsManager_ChangeTextureProp_Keyframes(MATMGR_TEXTURES_WINDOW_FORMBTNS_CREATE, nullptr);

                            break;
                        }

                        case MATMGR_TEXTURES_WINDOW_FORMBTNS_REMOVE:
                        {
                            materialsManager_ChangeTextureProp_Keyframes(MATMGR_TEXTURES_WINDOW_FORMBTNS_REMOVE, nullptr);

                            break;
                        }

                        case MATMGR_BITMAPS_WINDOW_EXTCHECK:
                        {
                            materialsManager_ChangeBitmapProp_Ext(is_checked);

                            break;
                        }

                        case MATMGR_BITMAPS_WINDOW_BTNS_BROWSE:
                        {
                            materialsManager_UpdateThumbnailsWindow(MATMGR_RENDERED_LIST_THUMBNAILS_GRID);

                            break;
                        }

                        case MATMGR_BITMAPS_WINDOW_BTNS_ENLARGE:
                        {
                            materialsManager_UpdateThumbnailsWindow(MATMGR_RENDERED_LIST_SINGLE_BITMAP);

                            break;
                        }

                        case MATMGR_BITMAPS_WINDOW_BTNS_EXPORT:
                        {
                            materialsManager_ExportCurrentBitmap();

                            break;
                        }

                        case MATMGR_BITMAPS_WINDOW_BTNS_REIMPORT:
                        {
                            materialsManager_ReimportCurrentBitmap();

                            break;
                        }

                        case MATMGR_BITMAPS_WINDOW_BTNS_ALL_EXPORT:
                        {
                            materialsManager_ExportAllBitmaps(0, getEditorString(1, false), false);

                            break;
                        }

                        case MATMGR_BITMAPS_WINDOW_BTNS_ALL_REIMPORT:
                        {
                            materialsManager_ReimportAllBitmaps(0, getEditorString(1, false), false);

                            break;
                        }

                        case MATMGR_BITMAPS_WINDOW_BTNS_BULK_EXPORT:
                        {
                            materialsManager_BulkTexturesExport();

                            break;
                        }

                        case MATMGR_BITMAPS_WINDOW_BTNS_BULK_REIMPORT:
                        {
                            materialsManager_BulkTexturesReimport();

                            break;
                        }
                    }
                }
            }
        }

        void buttonFunc_MaterialsManagerEditing(WPARAM wParam, LPARAM lParam, void* custom_param)
        {
            char bufor[LARGE_BUFFER_SIZE];
            int32_t editbox_id = (int32_t)custom_param;

            if (!matMgr_UpdatingWindowsNotByUser)
            {
                if (EN_CHANGE == HIWORD(wParam))
                {
                    GetWindowText((HWND)lParam, bufor, LARGE_BUFFER_SIZE);

                    switch (editbox_id)
                    {
                        case MATMGR_MATERIALS_WINDOW_STATEEDIT_C1_R:
                        {
                            materialsManager_ChangeMaterialProp_State(0, 0, bufor);

                            break;
                        }

                        case MATMGR_MATERIALS_WINDOW_STATEEDIT_C1_G:
                        {
                            materialsManager_ChangeMaterialProp_State(0, 1, bufor);

                            break;
                        }

                        case MATMGR_MATERIALS_WINDOW_STATEEDIT_C1_B:
                        {
                            materialsManager_ChangeMaterialProp_State(0, 2, bufor);

                            break;
                        }

                        case MATMGR_MATERIALS_WINDOW_STATEEDIT_C2_R:
                        {
                            materialsManager_ChangeMaterialProp_State(1, 0, bufor);

                            break;
                        }

                        case MATMGR_MATERIALS_WINDOW_STATEEDIT_C2_G:
                        {
                            materialsManager_ChangeMaterialProp_State(1, 1, bufor);

                            break;
                        }

                        case MATMGR_MATERIALS_WINDOW_STATEEDIT_C2_B:
                        {
                            materialsManager_ChangeMaterialProp_State(1, 2, bufor);

                            break;
                        }

                        case MATMGR_MATERIALS_WINDOW_STATEEDIT_C3_R:
                        {
                            materialsManager_ChangeMaterialProp_State(2, 0, bufor);

                            break;
                        }

                        case MATMGR_MATERIALS_WINDOW_STATEEDIT_C3_G:
                        {
                            materialsManager_ChangeMaterialProp_State(2, 1, bufor);

                            break;
                        }

                        case MATMGR_MATERIALS_WINDOW_STATEEDIT_C3_B:
                        {
                            materialsManager_ChangeMaterialProp_State(2, 2, bufor);

                            break;
                        }

                        case MATMGR_MATERIALS_WINDOW_STATEEDIT_C4_R:
                        {
                            materialsManager_ChangeMaterialProp_State(3, 0, bufor);

                            break;
                        }

                        case MATMGR_MATERIALS_WINDOW_STATEEDIT_C4_G:
                        {
                            materialsManager_ChangeMaterialProp_State(3, 1, bufor);

                            break;
                        }

                        case MATMGR_MATERIALS_WINDOW_STATEEDIT_C4_B:
                        {
                            materialsManager_ChangeMaterialProp_State(3, 2, bufor);

                            break;
                        }

                        case MATMGR_MATERIALS_WINDOW_STATEEDIT_48:
                        {
                            materialsManager_ChangeMaterialProp_State(4, 0, bufor);

                            break;
                        }

                        case MATMGR_MATERIALS_WINDOW_NAMEEDIT:
                        {
                            materialsManager_ChangeMaterialProp_Name(bufor);

                            break;
                        }

                        case MATMGR_MATERIALS_WINDOW_ALPHAEDIT:
                        {
                            materialsManager_ChangeMaterialProp_AlphaTest(bufor);

                            break;
                        }

                        case MATMGR_TEXTURES_WINDOW_FORMEDIT_TIME:
                        {
                            materialsManager_ChangeTextureProp_Keyframes(MATMGR_TEXTURES_WINDOW_FORMEDIT_TIME, bufor);

                            break;
                        }

                        case MATMGR_TEXTURES_WINDOW_FORMEDIT_VALUE:
                        {
                            materialsManager_ChangeTextureProp_Keyframes(MATMGR_TEXTURES_WINDOW_FORMEDIT_VALUE, bufor);

                            break;
                        }

                        case MATMGR_BITMAPS_WINDOW_PATHEDIT:
                        {
                            materialsManager_ChangeBitmapProp_Name(bufor);

                            break;
                        }
                    }
                }
            }
        }

        void buttonFunc_MaterialsManagerListing(WPARAM wParam, LPARAM lParam, void* custom_param)
        {
            int32_t a;
            int32_t listbox_id = (int32_t)custom_param;

            eMaterial* material;

            if (!matMgr_UpdatingWindowsNotByUser)
            {
                switch (HIWORD(wParam))
                {
                    case LBN_SELCHANGE:
                    case LBN_SELCANCEL:
                    {
                        int32_t id_from_the_list = (int)SendMessage((HWND)lParam, LB_GETCURSEL, 0, 0);

                        switch (listbox_id)
                        {
                            case MATMGR_MATERIALS_WINDOW_LIST:
                            {
                                materialsManager_SetCurrentMaterial(id_from_the_list, true, true, 0);

                                break;
                            }

                            case MATMGR_MATERIALS_WINDOW_TEXLIST:
                            {
                                if (nullptr != (material = materialsManager_GetCurrentMaterial()))
                                {
                                    matMgr_MaterialTextureId = id_from_the_list;

                                    a = materialsManager_FindTextureId(material);

                                    materialsManager_SetCurrentTexture(a, true, true, true);
                                }

                                break;
                            }

                            case MATMGR_MATERIALS_WINDOW_COLLIST:
                            {
                                materialsManager_ChangeMaterialProp_Collision(id_from_the_list);

                                break;
                            }

                            case MATMGR_MATERIALS_WINDOW_SNDLIST:
                            {
                                materialsManager_ChangeMaterialProp_Sound(id_from_the_list);

                                break;
                            }

                            case MATMGR_TEXTURES_WINDOW_LIST:
                            {
                                materialsManager_SetCurrentTexture(id_from_the_list, true, true, true);

                                break;
                            }

                            case MATMGR_TEXTURES_WINDOW_FORMKEYS:
                            {
                                matMgr_TextureKeyframesId = id_from_the_list;

                                materialsManager_UpdateTextureKeyframesListbox(materialsManager_GetCurrentTexture(), true);

                                break;
                            }

                            case MATMGR_TEXTURES_WINDOW_FORM_OORTLIST:
                            {
                                materialsManager_ChangeTextureProp_Keyframes(MATMGR_TEXTURES_WINDOW_FORM_OORTLIST, (void*)id_from_the_list);

                                break;
                            }

                            case MATMGR_BITMAPS_WINDOW_LIST:
                            {
                                materialsManager_SetCurrentBitmap(id_from_the_list, true, true);

                                break;
                            }
                        }

                        break;
                    }
                }
            }
        }

        bool materialsManager_AddLinePauseWindow(int32_t window_id)
        {
            int32_t y;

            theWindowsManager.setCurrentClassName("STATIC");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | SS_ETCHEDHORZ);

            theWindowsManager.getCurrentPosition(nullptr, &y);
            theWindowsManager.setCurrentPosition(0, (y + 8));

            theWindowsManager.setCurrentPadding(0, 8);

            if (0 == (matMgr_Windows[window_id] = theWindowsManager.addWindow("", RECT_LOGO_X2, 2, nullptr, 0, 0x01)))
            {
                return false;
            }

            theWindowsManager.setCurrentPadding(0, 0);

            return true;
        }

        bool materialsManager_AddWindows()
        {
            int32_t a, b, x, y;
            char bufor[64];

            const int WINDOW_HEIGHT = 24;
            const int WINDOW_PADDING_SMALL = 8;
            const int TOP_OFFSET = 8;
            const int LARGE_BUTTON_WIDTH = ((RECT_TABS_X2 - (2 - 1) * WINDOW_PADDING_SMALL) / 2);
            const int SMALL_EDITBOX_WIDTH = ((RECT_TABS_X2 - (3 - 1) * WINDOW_PADDING_SMALL) / 3);

            const DWORD LISTBOX_STYLES = (WS_CHILD | WS_VSCROLL | LBS_DISABLENOSCROLL | LBS_HASSTRINGS | LBS_NOTIFY);

            const char* MATERIAL_STATE_COLORS[4] =
            {
                "Ambient color (RGB):", "Diffuse color (RGB):", "Emissive color (RGB):", "Specular color (RGB):"
            };

            for (int a = 0; a < MATMGR_WINDOWS_COUNT; a++)
            {
                matMgr_Windows[a] = NULL;
            }

            /********************************/
            /* [MATERIALS MANAGER PAGE] */

            theWindowsManager.addPage("Materials manager", menuFunc_MaterialsManagerEnter, menuFunc_MaterialsManagerLeave);

            theWindowsManager.setCurrentPosition(RECT_TABS_X1, TOP_OFFSET);

            /********************************/
            /* Create subpages-switching buttons and the subpage label */

            theWindowsManager.setCurrentClassName("BUTTON");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | BS_DEFPUSHBUTTON);

            theWindowsManager.setCurrentPadding(WINDOW_PADDING_SMALL, WINDOW_PADDING_SMALL);

            if (0 == theWindowsManager.addWindow("<<", 24, 20, buttonFunc_MaterialsManagerSwitchPage, (void*)(-1), 0))
            {
                return false;
            }

            if (0 == theWindowsManager.addWindow(">>", 24, 20, buttonFunc_MaterialsManagerSwitchPage, (void*)(+1), 0))
            {
                return false;
            }

            theWindowsManager.setCurrentClassName("STATIC");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD);

            if (0 == (matMgr_Windows[MATMGR_WINDOW_SUBPAGENAME] = theWindowsManager.addWindow("", (RECT_TABS_X2 - 2 * (24 + WINDOW_PADDING_SMALL)), 2 * WINDOW_HEIGHT, nullptr, nullptr, 0x01)))
            {
                return false;
            }

            /********************************/
            /* [OPTIMIZATIONS SUBPAGE] */

            theWindowsManager.getCurrentPosition(&x, &y);

            /********************************/
            /* Create labels - Statistics */

            theWindowsManager.setCurrentPadding(0, 0);

            theWindowsManager.setCurrentClassName("STATIC");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD);

            if (0 == (matMgr_Windows[MATMGR_INFO_WINDOW_TOTALS_LABEL] = theWindowsManager.addWindow("<< Object Counters >>", RECT_TABS_X2, WINDOW_HEIGHT, nullptr, nullptr, 0x01)))
            {
                return false;
            }

            if (0 == (matMgr_Windows[MATMGR_INFO_WINDOW_TOTALS_BITMAPS] = theWindowsManager.addWindow("", RECT_TABS_X2, WINDOW_HEIGHT, nullptr, nullptr, 0x01)))
            {
                return false;
            }

            if (0 == (matMgr_Windows[MATMGR_INFO_WINDOW_TOTALS_TEXTURES] = theWindowsManager.addWindow("", RECT_TABS_X2, WINDOW_HEIGHT, nullptr, nullptr, 0x01)))
            {
                return false;
            }

            if (0 == (matMgr_Windows[MATMGR_INFO_WINDOW_TOTALS_STATES] = theWindowsManager.addWindow("", RECT_TABS_X2, WINDOW_HEIGHT, nullptr, nullptr, 0x01)))
            {
                return false;
            }

            if (0 == (matMgr_Windows[MATMGR_INFO_WINDOW_TOTALS_MATERIALS] = theWindowsManager.addWindow("", RECT_TABS_X2, WINDOW_HEIGHT, nullptr, nullptr, 0x01)))
            {
                return false;
            }

            materialsManager_UpdateStatistics();

            /********************************/
            /* Create buttons - Bitmaps and Textures Optimization */

            if (false == materialsManager_AddLinePauseWindow(MATMGR_INFO_WINDOW_OPTIMIZE_PAUSE))
            {
                return false;
            }

            theWindowsManager.setCurrentPadding(0, WINDOW_PADDING_SMALL);

            theWindowsManager.setCurrentClassName("BUTTON");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | BS_DEFPUSHBUTTON | BS_MULTILINE);

            if (0 == (matMgr_Windows[MATMGR_INFO_WINDOW_OPTIMIZE_BMPBTN] = theWindowsManager.addWindow("1. Scan \"Textures\" to remove similar \"Bitmaps\"", RECT_TABS_X2, 2 * WINDOW_HEIGHT, buttonFunc_MaterialsManagerClicking, (void*)MATMGR_INFO_WINDOW_OPTIMIZE_BMPBTN, 0x01)))
            {
                return false;
            }

            if (0 == (matMgr_Windows[MATMGR_INFO_WINDOW_OPTIMIZE_TEXBTN] = theWindowsManager.addWindow("2. Scan \"Materials\" to remove similar \"Textures\" and \"Material States\"", RECT_TABS_X2, 2 * WINDOW_HEIGHT, buttonFunc_MaterialsManagerClicking, (void*)MATMGR_INFO_WINDOW_OPTIMIZE_TEXBTN, 0x01)))
            {
                return false;
            }

            /********************************/
            /* Create label - Optimization notes */

            theWindowsManager.setCurrentClassName("STATIC");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD);

            if (0 == (matMgr_Windows[MATMGR_INFO_WINDOW_OPTIMIZE_NOTES] = theWindowsManager.addWindow("Use the \"Nodes list\" page to scan \"Geometry\" nodes for similar \"Materials\"", RECT_TABS_X2, 2 * WINDOW_HEIGHT, nullptr, nullptr, 0x01)))
            {
                return false;
            }

            /********************************/
            /* [MATERIALS SUBPAGE] */

            theWindowsManager.setCurrentPosition(x, y);

            /********************************/
            /* Create listbox - Materials list */

            theWindowsManager.setCurrentPadding(0, 0);

            theWindowsManager.setCurrentClassName("LISTBOX");
            theWindowsManager.setCurrentStyleFlags(LISTBOX_STYLES | WS_HSCROLL);

            theWindowsManager.addEdgesToNextWindow();
            if (0 == (matMgr_Windows[MATMGR_MATERIALS_WINDOW_LIST] = theWindowsManager.addWindow("", RECT_TABS_X2, 256, buttonFunc_MaterialsManagerListing, (void*)MATMGR_MATERIALS_WINDOW_LIST, 0x01)))
            {
                return false;
            }

            SendMessage(matMgr_Windows[MATMGR_MATERIALS_WINDOW_LIST], LB_SETHORIZONTALEXTENT, (WPARAM)512, 0);

            /********************************/
            /* Create label - Textures of the material */

            if (false == materialsManager_AddLinePauseWindow(MATMGR_MATERIALS_WINDOW_TEXLIST_PAUSE))
            {
                return false;
            }

            theWindowsManager.setCurrentClassName("STATIC");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD);

            if (0 == (matMgr_Windows[MATMGR_MATERIALS_WINDOW_TEXLIST_LABEL] = theWindowsManager.addWindow("Textures within selected Material:", RECT_TABS_X2, WINDOW_HEIGHT, nullptr, nullptr, 0x01)))
            {
                return false;
            }

            /********************************/
            /* Create listbox - Textures of the material */

            theWindowsManager.setCurrentClassName("LISTBOX");
            theWindowsManager.setCurrentStyleFlags(WS_DISABLED | LISTBOX_STYLES | WS_HSCROLL);

            theWindowsManager.addEdgesToNextWindow();
            if (0 == (matMgr_Windows[MATMGR_MATERIALS_WINDOW_TEXLIST] = theWindowsManager.addWindow("", RECT_TABS_X2, 128, buttonFunc_MaterialsManagerListing, (void*)MATMGR_MATERIALS_WINDOW_TEXLIST, 0x01)))
            {
                return false;
            }

            SendMessage(matMgr_Windows[MATMGR_MATERIALS_WINDOW_TEXLIST], LB_SETHORIZONTALEXTENT, (WPARAM)512, 0);

            /********************************/
            /* Create buttons - Textures of the material */

            theWindowsManager.setCurrentClassName("BUTTON");
            theWindowsManager.setCurrentStyleFlags(WS_DISABLED | WS_CHILD | BS_DEFPUSHBUTTON | BS_MULTILINE);

            theWindowsManager.setCurrentPadding(WINDOW_PADDING_SMALL, WINDOW_PADDING_SMALL);

            if (0 == (matMgr_Windows[MATMGR_MATERIALS_WINDOW_TEXTBTNS_CREATE] = theWindowsManager.addWindow("Append a New Texture", LARGE_BUTTON_WIDTH, 2 * WINDOW_HEIGHT, buttonFunc_MaterialsManagerClicking, (void*)MATMGR_MATERIALS_WINDOW_TEXTBTNS_CREATE, 0)))
            {
                return false;
            }

            if (0 == (matMgr_Windows[MATMGR_MATERIALS_WINDOW_TEXTBTNS_REMOVE] = theWindowsManager.addWindow("Remove Selected Texture", LARGE_BUTTON_WIDTH, 2 * WINDOW_HEIGHT, buttonFunc_MaterialsManagerClicking, (void*)MATMGR_MATERIALS_WINDOW_TEXTBTNS_REMOVE, 0x01)))
            {
                return false;
            }

            if (0 == (matMgr_Windows[MATMGR_MATERIALS_WINDOW_TEXTBTNS_MOVEUP] = theWindowsManager.addWindow("Move Selected Texture Up", LARGE_BUTTON_WIDTH, 2 * WINDOW_HEIGHT, buttonFunc_MaterialsManagerClicking, (void*)MATMGR_MATERIALS_WINDOW_TEXTBTNS_MOVEUP, 0)))
            {
                return false;
            }

            if (0 == (matMgr_Windows[MATMGR_MATERIALS_WINDOW_TEXTBTNS_MOVEDOWN] = theWindowsManager.addWindow("Move Selected Texture Down", LARGE_BUTTON_WIDTH, 2 * WINDOW_HEIGHT, buttonFunc_MaterialsManagerClicking, (void*)MATMGR_MATERIALS_WINDOW_TEXTBTNS_MOVEDOWN, 0x01)))
            {
                return false;
            }

            if (0 == (matMgr_Windows[MATMGR_MATERIALS_WINDOW_TEXTBTNS_REPLACE] = theWindowsManager.addWindow("Replace selected with a Texture from other list", RECT_TABS_X2, 2 * WINDOW_HEIGHT, buttonFunc_MaterialsManagerClicking, (void*)MATMGR_MATERIALS_WINDOW_TEXTBTNS_REPLACE, 0x01)))
            {
                return false;
            }

            /********************************/
            /* Create checkbox - Using Material State */

            theWindowsManager.offsetCurrentPosition(0, (0 - WINDOW_PADDING_SMALL));

            if (false == materialsManager_AddLinePauseWindow(MATMGR_MATERIALS_WINDOW_STATE_PAUSE))
            {
                return false;
            }

            theWindowsManager.setCurrentPadding(0, WINDOW_PADDING_SMALL);

            theWindowsManager.setCurrentClassName("BUTTON");
            theWindowsManager.setCurrentStyleFlags(WS_DISABLED | WS_CHILD | BS_AUTOCHECKBOX);

            if (0 == (matMgr_Windows[MATMGR_MATERIALS_WINDOW_STATECHECK_USED] = theWindowsManager.addWindow("Is using \"MaterialState\"", RECT_TABS_X2, WINDOW_HEIGHT, buttonFunc_MaterialsManagerClicking, (void*)MATMGR_MATERIALS_WINDOW_STATECHECK_USED, 0x01)))
            {
                return false;
            }

            /********************************/
            /* Create label - Material State Status */

            theWindowsManager.setCurrentPadding(0, 0);

            theWindowsManager.setCurrentClassName("STATIC");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD);

            if (0 == (matMgr_Windows[MATMGR_MATERIALS_WINDOW_STATE_STATUS] = theWindowsManager.addWindow("", RECT_TABS_X2, WINDOW_HEIGHT, nullptr, nullptr, 0x01)))
            {
                return false;
            }

            /********************************/
            /* Create label - Cloning the Material State */

            theWindowsManager.setCurrentPadding(0, (2 * WINDOW_PADDING_SMALL));

            theWindowsManager.setCurrentClassName("BUTTON");
            theWindowsManager.setCurrentStyleFlags(WS_DISABLED | WS_CHILD | BS_DEFPUSHBUTTON);

            if (0 == (matMgr_Windows[MATMGR_MATERIALS_WINDOW_STATEBTN_CLONE] = theWindowsManager.addWindow("Clone this Material State!", RECT_TABS_X2, WINDOW_HEIGHT, buttonFunc_MaterialsManagerClicking, (void*)MATMGR_MATERIALS_WINDOW_STATEBTN_CLONE, 0x01)))
            {
                return false;
            }

            /********************************/
            /* Create labels and editboxes - Material State Colors */

            b = MATMGR_MATERIALS_WINDOW_STATE_C1_LABEL;

            for (a = 0; a < 4; a++)
            {
                theWindowsManager.setCurrentPadding(0, 0);

                theWindowsManager.setCurrentClassName("STATIC");
                theWindowsManager.setCurrentStyleFlags(WS_CHILD);

                if (0 == (matMgr_Windows[(b + 0)] = theWindowsManager.addWindow(MATERIAL_STATE_COLORS[a], RECT_TABS_X2, WINDOW_HEIGHT, nullptr, nullptr, 0x01)))
                {
                    return false;
                }

                theWindowsManager.setCurrentPadding(WINDOW_PADDING_SMALL, WINDOW_PADDING_SMALL);

                theWindowsManager.setCurrentClassName("EDIT");
                theWindowsManager.setCurrentStyleFlags(WS_DISABLED | WS_CHILD | ES_AUTOHSCROLL);

                theWindowsManager.addEdgesToNextWindow();
                if (0 == (matMgr_Windows[(b + 1)] = theWindowsManager.addWindow("", SMALL_EDITBOX_WIDTH, WINDOW_HEIGHT, buttonFunc_MaterialsManagerEditing, (void*)(b + 1), 0)))
                {
                    return false;
                }

                theWindowsManager.addEdgesToNextWindow();
                if (0 == (matMgr_Windows[(b + 2)] = theWindowsManager.addWindow("", SMALL_EDITBOX_WIDTH, WINDOW_HEIGHT, buttonFunc_MaterialsManagerEditing, (void*)(b + 2), 0)))
                {
                    return false;
                }

                theWindowsManager.addEdgesToNextWindow();
                if (0 == (matMgr_Windows[(b + 3)] = theWindowsManager.addWindow("", SMALL_EDITBOX_WIDTH, WINDOW_HEIGHT, buttonFunc_MaterialsManagerEditing, (void*)(b + 3), 0x01)))
                {
                    return false;
                }

                b += 4;
            }

            /********************************/
            /* Create label and editbox - Material State Shininess */

            theWindowsManager.setCurrentPadding(0, 0);

            theWindowsManager.setCurrentClassName("STATIC");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD);

            if (0 == (matMgr_Windows[MATMGR_MATERIALS_WINDOW_STATE_48_LABEL] = theWindowsManager.addWindow("Shininess:", RECT_TABS_X2, WINDOW_HEIGHT, nullptr, nullptr, 0x01)))
            {
                return false;
            }

            theWindowsManager.setCurrentPadding(0, WINDOW_PADDING_SMALL);

            theWindowsManager.setCurrentClassName("EDIT");
            theWindowsManager.setCurrentStyleFlags(WS_DISABLED | WS_CHILD | ES_AUTOHSCROLL);

            theWindowsManager.addEdgesToNextWindow();
            if (0 == (matMgr_Windows[MATMGR_MATERIALS_WINDOW_STATEEDIT_48] = theWindowsManager.addWindow("", SMALL_EDITBOX_WIDTH, WINDOW_HEIGHT, buttonFunc_MaterialsManagerEditing, (void*)MATMGR_MATERIALS_WINDOW_STATEEDIT_48, 0x01)))
            {
                return false;
            }

            /********************************/
            /* Create checkbox - Material State - Global Ambient Lights - Option */

            theWindowsManager.setCurrentClassName("BUTTON");
            theWindowsManager.setCurrentStyleFlags(WS_DISABLED | WS_CHILD | BS_AUTOCHECKBOX);

            if (0 == (matMgr_Windows[MATMGR_MATERIALS_WINDOW_STATECHECK_4C] = theWindowsManager.addWindow("Global Ambient Lights", RECT_TABS_X2, 2 * WINDOW_HEIGHT, buttonFunc_MaterialsManagerClicking, (void*)MATMGR_MATERIALS_WINDOW_STATECHECK_4C, 0x01)))
            {
                return false;
            }

            /********************************/
            /* Create label - Material Flags */

            theWindowsManager.offsetCurrentPosition(0, (0 - WINDOW_PADDING_SMALL));

            if (false == materialsManager_AddLinePauseWindow(MATMGR_MATERIALS_WINDOW_FLAGS_PAUSE))
            {
                return false;
            }

            theWindowsManager.setCurrentClassName("STATIC");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD);

            if (0 == (matMgr_Windows[MATMGR_MATERIALS_WINDOW_FLAGS_LABEL] = theWindowsManager.addWindow("Selected material's Flags:", RECT_TABS_X2, WINDOW_HEIGHT, nullptr, nullptr, 0x01)))
            {
                return false;
            }

            /********************************/
            /* Create checkboxes - Material Flags */

            theWindowsManager.setCurrentClassName("BUTTON");
            theWindowsManager.setCurrentStyleFlags(WS_DISABLED | WS_CHILD | BS_AUTOCHECKBOX);

            b = MATMGR_MATERIALS_WINDOW_FLAGSCHECK1;

            for (a = 0; a < KAO2_MATERIAL_FLAGS_COUNT; a++)
            {
                sprintf_s(bufor, 64, "0x%02X: \"%s\"", (0x01 << a), theMaterialFlags[a]);

                if (0 == (matMgr_Windows[b] = theWindowsManager.addWindow(bufor, RECT_TABS_X2, WINDOW_HEIGHT, buttonFunc_MaterialsManagerClicking, (void*)(b), 0x01)))
                {
                    return false;
                }

                b++;
            }

            /********************************/
            /* Create label - Material Collision types */

            if (false == materialsManager_AddLinePauseWindow(MATMGR_MATERIALS_WINDOW_COLLIST_PAUSE))
            {
                return false;
            }

            theWindowsManager.setCurrentClassName("STATIC");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD);

            if (0 == (matMgr_Windows[MATMGR_MATERIALS_WINDOW_COLLIST_LABEL] = theWindowsManager.addWindow("Selected material's Collision type:", RECT_TABS_X2, WINDOW_HEIGHT, nullptr, nullptr, 0x01)))
            {
                return false;
            }

            /********************************/
            /* Create listbox - Material Collision types */

            theWindowsManager.setCurrentClassName("LISTBOX");
            theWindowsManager.setCurrentStyleFlags(WS_DISABLED | LISTBOX_STYLES);

            theWindowsManager.addEdgesToNextWindow();
            if (0 == (matMgr_Windows[MATMGR_MATERIALS_WINDOW_COLLIST] = theWindowsManager.addWindow("", RECT_TABS_X2, 128, buttonFunc_MaterialsManagerListing, (void*)MATMGR_MATERIALS_WINDOW_COLLIST, 0x01)))
            {
                return false;
            }

            for (a = 0; a < KAO2_MATERIAL_TYPES_COUNT; a++)
            {
                sprintf_s(bufor, 64, "%2d: \"%s\"", (1 + a), theMaterialTypes[a].name);
                SendMessage(matMgr_Windows[MATMGR_MATERIALS_WINDOW_COLLIST], LB_ADDSTRING, 0, (LPARAM)bufor);
            }

            /********************************/
            /* Create label - Material Sound */

            if (false == materialsManager_AddLinePauseWindow(MATMGR_MATERIALS_WINDOW_SNDLIST_PAUSE))
            {
                return false;
            }

            theWindowsManager.setCurrentClassName("STATIC");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD);

            if (0 == (matMgr_Windows[MATMGR_MATERIALS_WINDOW_SNDLIST_LABEL] = theWindowsManager.addWindow("Selected material's Sound:", RECT_TABS_X2, WINDOW_HEIGHT, nullptr, nullptr, 0x01)))
            {
                return false;
            }

            /********************************/
            /* Create listbox - Material Sound */

            theWindowsManager.setCurrentClassName("LISTBOX");
            theWindowsManager.setCurrentStyleFlags(WS_DISABLED | LISTBOX_STYLES);

            theWindowsManager.addEdgesToNextWindow();
            if (0 == (matMgr_Windows[MATMGR_MATERIALS_WINDOW_SNDLIST] = theWindowsManager.addWindow("", RECT_TABS_X2, 128, buttonFunc_MaterialsManagerListing, (void*)MATMGR_MATERIALS_WINDOW_SNDLIST, 0x01)))
            {
                return false;
            }

            for (a = 0; a < KAO2_MATERIAL_SOUNDS_COUNT; a++)
            {
                sprintf_s(bufor, 64, "%2d: \"%s\"", (1 + a), theMaterialSounds[a].name);
                SendMessage(matMgr_Windows[MATMGR_MATERIALS_WINDOW_SNDLIST], LB_ADDSTRING, 0, (LPARAM)bufor);
            }

            /********************************/
            /* Create label and editbox - Material Name */

            if (false == materialsManager_AddLinePauseWindow(MATMGR_MATERIALS_WINDOW_NAMEEDIT_PAUSE))
            {
                return false;
            }

            theWindowsManager.setCurrentClassName("STATIC");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD);

            if (0 == (matMgr_Windows[MATMGR_MATERIALS_WINDOW_NAMEEDIT_LABEL] = theWindowsManager.addWindow("Selected material's Name:", RECT_TABS_X2, WINDOW_HEIGHT, nullptr, nullptr, 0x01)))
            {
                return false;
            }

            theWindowsManager.setCurrentClassName("EDIT");
            theWindowsManager.setCurrentStyleFlags(WS_DISABLED | WS_CHILD | ES_AUTOHSCROLL);

            theWindowsManager.addEdgesToNextWindow();
            if (0 == (matMgr_Windows[MATMGR_MATERIALS_WINDOW_NAMEEDIT] = theWindowsManager.addWindow("", RECT_TABS_X2, WINDOW_HEIGHT, buttonFunc_MaterialsManagerEditing, (void*)MATMGR_MATERIALS_WINDOW_NAMEEDIT, 0x01)))
            {
                return false;
            }

            /********************************/
            /* Create label and editbox - Material AlphaRef */

            if (false == materialsManager_AddLinePauseWindow(MATMGR_MATERIALS_WINDOW_ALPHAEDIT_PAUSE))
            {
                return false;
            }

            theWindowsManager.setCurrentClassName("STATIC");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD);

            if (0 == (matMgr_Windows[MATMGR_MATERIALS_WINDOW_ALPHAEDIT_LABEL] = theWindowsManager.addWindow("Selected material's AlphaTest Reference:", RECT_TABS_X2, WINDOW_HEIGHT, nullptr, nullptr, 0x01)))
            {
                return false;
            }

            theWindowsManager.setCurrentClassName("EDIT");
            theWindowsManager.setCurrentStyleFlags(WS_DISABLED | WS_CHILD | ES_AUTOHSCROLL);

            theWindowsManager.addEdgesToNextWindow();
            if (0 == (matMgr_Windows[MATMGR_MATERIALS_WINDOW_ALPHAEDIT] = theWindowsManager.addWindow("", RECT_TABS_X2, WINDOW_HEIGHT, buttonFunc_MaterialsManagerEditing, (void*)MATMGR_MATERIALS_WINDOW_ALPHAEDIT, 0x01)))
            {
                return false;
            }

            /********************************/
            /* [TEXTURES SUBPAGE] */

            theWindowsManager.setCurrentPosition(x, y);

            /********************************/
            /* Create listbox - Textures list */

            theWindowsManager.setCurrentClassName("LISTBOX");
            theWindowsManager.setCurrentStyleFlags(LISTBOX_STYLES | WS_HSCROLL);

            theWindowsManager.addEdgesToNextWindow();
            if (0 == (matMgr_Windows[MATMGR_TEXTURES_WINDOW_LIST] = theWindowsManager.addWindow("", RECT_TABS_X2, 256, buttonFunc_MaterialsManagerListing, (void*)MATMGR_TEXTURES_WINDOW_LIST, 0x01)))
            {
                return false;
            }

            SendMessage(matMgr_Windows[MATMGR_TEXTURES_WINDOW_LIST], LB_SETHORIZONTALEXTENT, (WPARAM)512, 0);

            /********************************/
            /* Create label - Texture Flags */

            if (false == materialsManager_AddLinePauseWindow(MATMGR_TEXTURES_WINDOW_FLAGS_PAUSE))
            {
                return false;
            }

            theWindowsManager.setCurrentClassName("STATIC");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD);

            if (0 == (matMgr_Windows[MATMGR_TEXTURES_WINDOW_FLAGS_LABEL] = theWindowsManager.addWindow("Selected texture's Flags:\n(when set / when unset)", RECT_TABS_X2, (int)(1.5 * WINDOW_HEIGHT), nullptr, nullptr, 0x01)))
            {
                return false;
            }

            /********************************/
            /* Create checkboxes - Texture Flags */

            theWindowsManager.setCurrentClassName("BUTTON");
            theWindowsManager.setCurrentStyleFlags(WS_DISABLED | WS_CHILD | BS_AUTOCHECKBOX | BS_MULTILINE);

            b = MATMGR_TEXTURES_WINDOW_FLAGSCHECK1;

            for (a = 0; a < KAO2_TEXTURE_FLAGS_COUNT; a++)
            {
                sprintf_s(bufor, 64, "0x%02X: \"%s\"", (0x01 << a), theTextureFlags[a]);

                if (0 == (matMgr_Windows[b] = theWindowsManager.addWindow(bufor, RECT_TABS_X2, (int)(1.5 * WINDOW_HEIGHT), buttonFunc_MaterialsManagerClicking, (void*)(b), 0x01)))
                {
                    return false;
                }

                b++;
            }

            /********************************/
            /* Create buttons - Bitmap of the texture */

            if (false == materialsManager_AddLinePauseWindow(MATMGR_TEXTURES_WINDOW_BMPBTNS_PAUSE))
            {
                return false;
            }

            theWindowsManager.setCurrentClassName("BUTTON");
            theWindowsManager.setCurrentStyleFlags(WS_DISABLED | WS_CHILD | BS_DEFPUSHBUTTON | BS_MULTILINE);

            theWindowsManager.setCurrentPadding(WINDOW_PADDING_SMALL, WINDOW_PADDING_SMALL);

            if (0 == (matMgr_Windows[MATMGR_TEXTURES_WINDOW_BMPBTNS_CREATE] = theWindowsManager.addWindow("Create New Bitmap", LARGE_BUTTON_WIDTH, 2 * WINDOW_HEIGHT, buttonFunc_MaterialsManagerClicking, (void*)MATMGR_TEXTURES_WINDOW_BMPBTNS_CREATE, 0)))
            {
                return false;
            }

            if (0 == (matMgr_Windows[MATMGR_TEXTURES_WINDOW_BMPBTNS_REMOVE] = theWindowsManager.addWindow("Remove Bitmap from this Texture", LARGE_BUTTON_WIDTH, 2 * WINDOW_HEIGHT, buttonFunc_MaterialsManagerClicking, (void*)MATMGR_TEXTURES_WINDOW_BMPBTNS_REMOVE, 0x01)))
            {
                return false;
            }

            if (0 == (matMgr_Windows[MATMGR_TEXTURES_WINDOW_BMPBTNS_REPLACE] = theWindowsManager.addWindow("Replace with a Bitmap from other list", RECT_TABS_X2, 2 * WINDOW_HEIGHT, buttonFunc_MaterialsManagerClicking, (void*)MATMGR_TEXTURES_WINDOW_BMPBTNS_REPLACE, 0x01)))
            {
                return false;
            }

            /********************************/
            /* Create checkbox - Using Texture Transform */

            theWindowsManager.offsetCurrentPosition(0, (0 - WINDOW_PADDING_SMALL));

            if (false == materialsManager_AddLinePauseWindow(MATMGR_TEXTURES_WINDOW_FORM_PAUSE))
            {
                return false;
            }

            theWindowsManager.setCurrentPadding(0, WINDOW_PADDING_SMALL);

            theWindowsManager.setCurrentClassName("BUTTON");
            theWindowsManager.setCurrentStyleFlags(WS_DISABLED | WS_CHILD | BS_AUTOCHECKBOX);

            if (0 == (matMgr_Windows[MATMGR_TEXTURES_WINDOW_FORMCHECK_USED] = theWindowsManager.addWindow("Is using \"TexTransform\"", RECT_TABS_X2, WINDOW_HEIGHT, buttonFunc_MaterialsManagerClicking, (void*)MATMGR_TEXTURES_WINDOW_FORMCHECK_USED, 0x01)))
            {
                return false;
            }

            /********************************/
            /* Create label - Texture Transform Keyframes */

            theWindowsManager.setCurrentPadding(0, 0);

            theWindowsManager.setCurrentClassName("STATIC");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD);

            if (0 == (matMgr_Windows[MATMGR_TEXTURES_WINDOW_FORMKEYS_LABEL] = theWindowsManager.addWindow("Selected texture's Keyframes:\n(editboxes: [time, value])", RECT_TABS_X2, (int)(1.5 * WINDOW_HEIGHT), nullptr, nullptr, 0x01)))
            {
                return false;
            }

            /********************************/
            /* Create listbox - Texture Transform Keyframes */

            theWindowsManager.setCurrentPadding(0, WINDOW_PADDING_SMALL);

            theWindowsManager.setCurrentClassName("LISTBOX");
            theWindowsManager.setCurrentStyleFlags(WS_DISABLED | LISTBOX_STYLES | WS_HSCROLL);

            theWindowsManager.addEdgesToNextWindow();
            if (0 == (matMgr_Windows[MATMGR_TEXTURES_WINDOW_FORMKEYS] = theWindowsManager.addWindow("", RECT_TABS_X2, 128, buttonFunc_MaterialsManagerListing, (void*)MATMGR_TEXTURES_WINDOW_FORMKEYS, 0x01)))
            {
                return false;
            }

            /********************************/
            /* Create buttons - Texture Transform Categories */

            theWindowsManager.setCurrentClassName("BUTTON");
            theWindowsManager.setCurrentStyleFlags(WS_DISABLED | WS_CHILD | BS_DEFPUSHBUTTON | BS_PUSHLIKE);

            theWindowsManager.setCurrentPadding(WINDOW_PADDING_SMALL, WINDOW_PADDING_SMALL);

            if (0 == (matMgr_Windows[MATMGR_TEXTURES_WINDOW_FORMBTNS_CAT_SX] = theWindowsManager.addWindow("X-Scale Keys", LARGE_BUTTON_WIDTH, WINDOW_HEIGHT, buttonFunc_MaterialsManagerClicking, (void*)MATMGR_TEXTURES_WINDOW_FORMBTNS_CAT_SX, 0)))
            {
                return false;
            }

            if (0 == (matMgr_Windows[MATMGR_TEXTURES_WINDOW_FORMBTNS_CAT_SY] = theWindowsManager.addWindow("Y-Scale Keys", LARGE_BUTTON_WIDTH, WINDOW_HEIGHT, buttonFunc_MaterialsManagerClicking, (void*)MATMGR_TEXTURES_WINDOW_FORMBTNS_CAT_SY, 0x01)))
            {
                return false;
            }

            if (0 == (matMgr_Windows[MATMGR_TEXTURES_WINDOW_FORMBTNS_CAT_U] = theWindowsManager.addWindow("U-Offset Keys", LARGE_BUTTON_WIDTH, WINDOW_HEIGHT, buttonFunc_MaterialsManagerClicking, (void*)MATMGR_TEXTURES_WINDOW_FORMBTNS_CAT_U, 0)))
            {
                return false;
            }

            if (0 == (matMgr_Windows[MATMGR_TEXTURES_WINDOW_FORMBTNS_CAT_V] = theWindowsManager.addWindow("V-Offset Keys", LARGE_BUTTON_WIDTH, WINDOW_HEIGHT, buttonFunc_MaterialsManagerClicking, (void*)MATMGR_TEXTURES_WINDOW_FORMBTNS_CAT_V, 0x01)))
            {
                return false;
            }

            /********************************/
            /* Create listbox - Out of Range Types */

            theWindowsManager.setCurrentClassName("LISTBOX");
            theWindowsManager.setCurrentStyleFlags(WS_DISABLED | LISTBOX_STYLES | WS_HSCROLL);

            theWindowsManager.addEdgesToNextWindow();
            if (0 == (matMgr_Windows[MATMGR_TEXTURES_WINDOW_FORM_OORTLIST] = theWindowsManager.addWindow("", RECT_TABS_X2, 128, buttonFunc_MaterialsManagerListing, (void*)MATMGR_TEXTURES_WINDOW_FORM_OORTLIST, 0x01)))
            {
                return false;
            }

            SendMessage(matMgr_Windows[MATMGR_TEXTURES_WINDOW_FORM_OORTLIST], LB_SETHORIZONTALEXTENT, (WPARAM)512, 0);

            for (a = 0; a < KAO2_LEAFKEY_OORT_COUNT; a++)
            {
                sprintf_s(bufor, 64, " Out of Range Type %d: \"%s\"", a, theLeafOoRT[a]);
                SendMessage(matMgr_Windows[MATMGR_TEXTURES_WINDOW_FORM_OORTLIST], LB_ADDSTRING, 0, (LPARAM)bufor);
            }

            /********************************/
            /* Create editboxes - Texture Transform time and value */

            theWindowsManager.setCurrentClassName("EDIT");
            theWindowsManager.setCurrentStyleFlags(WS_DISABLED | WS_CHILD | ES_AUTOHSCROLL);

            theWindowsManager.addEdgesToNextWindow();
            if (0 == (matMgr_Windows[MATMGR_TEXTURES_WINDOW_FORMEDIT_TIME] = theWindowsManager.addWindow("", LARGE_BUTTON_WIDTH, WINDOW_HEIGHT, buttonFunc_MaterialsManagerEditing, (void*)MATMGR_TEXTURES_WINDOW_FORMEDIT_TIME, 0)))
            {
                return false;
            }

            theWindowsManager.addEdgesToNextWindow();
            if (0 == (matMgr_Windows[MATMGR_TEXTURES_WINDOW_FORMEDIT_VALUE] = theWindowsManager.addWindow("", LARGE_BUTTON_WIDTH, WINDOW_HEIGHT, buttonFunc_MaterialsManagerEditing, (void*)MATMGR_TEXTURES_WINDOW_FORMEDIT_VALUE, 0x01)))
            {
                return false;
            }

            /********************************/
            /* Create buttons - Texture Transform Actions */

            theWindowsManager.setCurrentClassName("BUTTON");
            theWindowsManager.setCurrentStyleFlags(WS_DISABLED | WS_CHILD | BS_DEFPUSHBUTTON | BS_MULTILINE);

            if (0 == (matMgr_Windows[MATMGR_TEXTURES_WINDOW_FORMBTNS_CREATE] = theWindowsManager.addWindow("Create Keyframe", LARGE_BUTTON_WIDTH, WINDOW_HEIGHT, buttonFunc_MaterialsManagerClicking, (void*)MATMGR_TEXTURES_WINDOW_FORMBTNS_CREATE, 0)))
            {
                return false;
            }

            if (0 == (matMgr_Windows[MATMGR_TEXTURES_WINDOW_FORMBTNS_REMOVE] = theWindowsManager.addWindow("Remove Keyframe", LARGE_BUTTON_WIDTH, WINDOW_HEIGHT, buttonFunc_MaterialsManagerClicking, (void*)MATMGR_TEXTURES_WINDOW_FORMBTNS_REMOVE, 0x01)))
            {
                return false;
            }

            /********************************/
            /* [BITMAPS SUBPAGE] */

            theWindowsManager.setCurrentPosition(x, y);

            /********************************/
            /* Create listbox - Bitmaps list */

            theWindowsManager.setCurrentPadding(0, 0);

            theWindowsManager.setCurrentClassName("LISTBOX");
            theWindowsManager.setCurrentStyleFlags(LISTBOX_STYLES | WS_HSCROLL);

            theWindowsManager.addEdgesToNextWindow();
            if (0 == (matMgr_Windows[MATMGR_BITMAPS_WINDOW_LIST] = theWindowsManager.addWindow("", RECT_TABS_X2, 256, buttonFunc_MaterialsManagerListing, (void*)MATMGR_BITMAPS_WINDOW_LIST, 0x01)))
            {
                return false;
            }

            SendMessage(matMgr_Windows[MATMGR_BITMAPS_WINDOW_LIST], LB_SETHORIZONTALEXTENT, (WPARAM)512, 0);

            /********************************/
            /* Create label and editbox - Bitmap Path */

            if (false == materialsManager_AddLinePauseWindow(MATMGR_BITMAPS_WINDOW_PATHEDIT_PAUSE))
            {
                return false;
            }

            theWindowsManager.setCurrentClassName("STATIC");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD);

            if (0 == (matMgr_Windows[MATMGR_BITMAPS_WINDOW_PATHEDIT_LABEL] = theWindowsManager.addWindow("Selected bitmaps's Path:", RECT_TABS_X2, WINDOW_HEIGHT, nullptr, nullptr, 0x01)))
            {
                return false;
            }

            theWindowsManager.setCurrentClassName("EDIT");
            theWindowsManager.setCurrentStyleFlags(WS_DISABLED | WS_CHILD | ES_AUTOHSCROLL);

            theWindowsManager.addEdgesToNextWindow();
            if (0 == (matMgr_Windows[MATMGR_BITMAPS_WINDOW_PATHEDIT] = theWindowsManager.addWindow("", RECT_TABS_X2, WINDOW_HEIGHT, buttonFunc_MaterialsManagerEditing, (void*)MATMGR_BITMAPS_WINDOW_PATHEDIT, 0x01)))
            {
                return false;
            }

            /********************************/
            /* Create checkbox - Bitmap marked as external */

            if (false == materialsManager_AddLinePauseWindow(MATMGR_BITMAPS_WINDOW_EXTCHECK_PAUSE))
            {
                return false;
            }

            theWindowsManager.setCurrentClassName("BUTTON");
            theWindowsManager.setCurrentStyleFlags(WS_DISABLED | WS_CHILD | BS_AUTOCHECKBOX);

            if (0 == (matMgr_Windows[MATMGR_BITMAPS_WINDOW_EXTCHECK] = theWindowsManager.addWindow("Loaded from external file", RECT_TABS_X2, WINDOW_HEIGHT, buttonFunc_MaterialsManagerClicking, (void*)MATMGR_BITMAPS_WINDOW_EXTCHECK, 0x01)))
            {
                return false;
            }

            /********************************/
            /* Create buttons - Bitmap actions */

            if (false == materialsManager_AddLinePauseWindow(MATMGR_BITMAPS_WINDOW_BTNS_PAUSE))
            {
                return false;
            }

            theWindowsManager.setCurrentClassName("BUTTON");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | BS_DEFPUSHBUTTON | BS_MULTILINE);

            theWindowsManager.setCurrentPadding(WINDOW_PADDING_SMALL, WINDOW_PADDING_SMALL);

            if (0 == (matMgr_Windows[MATMGR_BITMAPS_WINDOW_BTNS_BROWSE] = theWindowsManager.addWindow("Browse Thumbnails", LARGE_BUTTON_WIDTH, 2 * WINDOW_HEIGHT, buttonFunc_MaterialsManagerClicking, (void*)MATMGR_BITMAPS_WINDOW_BTNS_BROWSE, 0)))
            {
                return false;
            }

            if (0 == (matMgr_Windows[MATMGR_BITMAPS_WINDOW_BTNS_ENLARGE] = theWindowsManager.addWindow("Show Selected Bitmap", LARGE_BUTTON_WIDTH, 2 * WINDOW_HEIGHT, buttonFunc_MaterialsManagerClicking, (void*)MATMGR_BITMAPS_WINDOW_BTNS_ENLARGE, 0x01)))
            {
                return false;
            }

            if (0 == (matMgr_Windows[MATMGR_BITMAPS_WINDOW_BTNS_EXPORT] = theWindowsManager.addWindow("Export Selected Bitmap", LARGE_BUTTON_WIDTH, 2 * WINDOW_HEIGHT, buttonFunc_MaterialsManagerClicking, (void*)MATMGR_BITMAPS_WINDOW_BTNS_EXPORT, 0)))
            {
                return false;
            }

            if (0 == (matMgr_Windows[MATMGR_BITMAPS_WINDOW_BTNS_REIMPORT] = theWindowsManager.addWindow("Reimport Selected Bitmap", LARGE_BUTTON_WIDTH, 2 * WINDOW_HEIGHT, buttonFunc_MaterialsManagerClicking, (void*)MATMGR_BITMAPS_WINDOW_BTNS_REIMPORT, 0x01)))
            {
                return false;
            }

            if (0 == (matMgr_Windows[MATMGR_BITMAPS_WINDOW_BTNS_ALL_EXPORT] = theWindowsManager.addWindow("Export All Loaded Bitmaps", LARGE_BUTTON_WIDTH, 2 * WINDOW_HEIGHT, buttonFunc_MaterialsManagerClicking, (void*)MATMGR_BITMAPS_WINDOW_BTNS_ALL_EXPORT, 0)))
            {
                return false;
            }

            if (0 == (matMgr_Windows[MATMGR_BITMAPS_WINDOW_BTNS_ALL_REIMPORT] = theWindowsManager.addWindow("Reimport All Loaded Bitmaps", LARGE_BUTTON_WIDTH, 2 * WINDOW_HEIGHT, buttonFunc_MaterialsManagerClicking, (void*)MATMGR_BITMAPS_WINDOW_BTNS_ALL_REIMPORT, 0x01)))
            {
                return false;
            }

            if (0 == (matMgr_Windows[MATMGR_BITMAPS_WINDOW_BTNS_BULK_EXPORT] = theWindowsManager.addWindow("Bulk Textures Export", LARGE_BUTTON_WIDTH, 2 * WINDOW_HEIGHT, buttonFunc_MaterialsManagerClicking, (void*)MATMGR_BITMAPS_WINDOW_BTNS_BULK_EXPORT, 0)))
            {
                return false;
            }

            if (0 == (matMgr_Windows[MATMGR_BITMAPS_WINDOW_BTNS_BULK_REIMPORT] = theWindowsManager.addWindow("Bulk Textures Reimport", LARGE_BUTTON_WIDTH, 2 * WINDOW_HEIGHT, buttonFunc_MaterialsManagerClicking, (void*)MATMGR_BITMAPS_WINDOW_BTNS_BULK_REIMPORT, 0x01)))
            {
                return false;
            }

            /********************************/
            /* Done! :) */

            return true;
        }
    }
}
