#include <ZookieWizard/ZookieWizard.h>
#include <ZookieWizard/WindowsManager.h>

#include <kao2ar/Archive.h>
#include <kao2engine/Log.h>

#include <kao2engine/eMaterial.h>
#include <kao2engine/eTexture.h>
#include <kao2engine/eBitmap.h>

namespace ZookieWizard
{
    namespace GUI
    {
        ////////////////////////////////////////////////////////////////
        // Materials Manager: Variables
        ////////////////////////////////////////////////////////////////

        int matMgr_MatList_Count;
        int matMgr_MatList_MaxLength;
        eMaterial** matMgr_MatList;
        int matMgr_MatList_Current;

        int matMgr_BmpList_Count;
        int matMgr_BmpList_MaxLength;
        eBitmap** matMgr_BmpList;
        int matMgr_BmpList_Current;

        GLuint matMgr_textures[1];

        int matMgr_RenderedList;
        int matMgr_scrollPos;
        float matMgr_mousePos[2];
        int matMgr_mouseMode;

        HWND matMgr_Windows[9];

        const int THUMBNAILS_IN_GRID = 10;
        const float THUMBNAIL_HW = 1.0f;
        const float BIG_THUMBNAIL_HW = 7.5f;


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

            matMgr_BmpList_Count = 0;
            matMgr_BmpList_MaxLength = 0;
            matMgr_BmpList = nullptr;
            matMgr_BmpList_Current = (-1);

            matMgr_RenderedList = 0;
            matMgr_scrollPos = 0;
            matMgr_mousePos[0] = 0;
            matMgr_mousePos[1] = 0;
            matMgr_mouseMode = 0;

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

            if (nullptr != matMgr_BmpList)
            {
                delete[](matMgr_BmpList);
                matMgr_BmpList = nullptr;
            }

            matMgr_BmpList_Count = 0;

            /* ListBoxes don't need to be cleared because the program is beind closed anyways */
        }


        ////////////////////////////////////////////////////////////////
        // Materials Manager: Inserting objects to the lists
        ////////////////////////////////////////////////////////////////

        void materialsManager_InsertMaterial(void* object)
        {
            int i;
            eMaterial* new_material = (eMaterial*)object;
            eMaterial** dummy_list;

            if (nullptr == new_material)
            {
                /* Invalid parameter */
                return;
            }

            for (i = 0; i < matMgr_MatList_Count; i++)
            {
                if (new_material == matMgr_MatList[i])
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
                    for (i = 0; i < matMgr_MatList_Count; i++)
                    {
                        dummy_list[i] = matMgr_MatList[i];
                    }

                    delete[](matMgr_MatList);
                }

                matMgr_MatList = dummy_list;
            }

            matMgr_MatList[matMgr_MatList_Count] = new_material;
            matMgr_MatList_Count++;

            /* Update Materials ListBox */

            SendMessage(matMgr_Windows[0], LB_ADDSTRING, 0, (LPARAM)"<Unnamed Material>");
        }

        void materialsManager_InsertBitmap(void* object)
        {
            int i;
            eBitmap* new_bitmap = (eBitmap*)object;
            eBitmap** dummy_list;

            if (nullptr == new_bitmap)
            {
                /* Invalid parameter */
                return;
            }

            for (i = 0; i < matMgr_BmpList_Count; i++)
            {
                if (new_bitmap == matMgr_BmpList[i])
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
                    for (i = 0; i < matMgr_BmpList_Count; i++)
                    {
                        dummy_list[i] = matMgr_BmpList[i];
                    }

                    delete[](matMgr_BmpList);
                }

                matMgr_BmpList = dummy_list;
            }

            matMgr_BmpList[matMgr_BmpList_Count] = new_bitmap;
            matMgr_BmpList_Count++;

            /* Update Bitmaps ListBox */

            SendMessage(matMgr_Windows[3], LB_ADDSTRING, 0, (LPARAM)"<Unnamed Bitmap>");
        }


        ////////////////////////////////////////////////////////////////
        // Materials Manager: Finding material by the Bitmap path
        ////////////////////////////////////////////////////////////////
        void* materialsManager_FindMaterial(const char* bitmap_path)
        {
            int32_t a, b, c;
            eTexture* dummy_texture;
            eBitmap* dummy_bitmap;
            eString dummy_path;

            for (a = 0; a < matMgr_MatList_Count; a++)
            {
                if (nullptr != matMgr_MatList[a])
                {
                    c =  matMgr_MatList[a]->getTexturesCount();

                    for (b = 0; b < c; b++)
                    {
                        dummy_texture = matMgr_MatList[a]->getIthTexture(b);

                        if (nullptr != dummy_texture)
                        {
                            dummy_bitmap = dummy_texture->getBitmap();

                            if (nullptr != dummy_bitmap)
                            {
                                dummy_path = dummy_bitmap->getPath();

                                if (dummy_path.comparePath(bitmap_path))
                                {
                                    return matMgr_MatList[a];
                                }
                            }
                        }
                    }
                }
            }

            return nullptr;
        }


        ////////////////////////////////////////////////////////////////
        // Materials manager: Updating selections on the lists, changing properties
        ////////////////////////////////////////////////////////////////

        void materialsManager_SetCurrentBitmap(int selected_id, bool update_listbox)
        {
            matMgr_BmpList_Current = selected_id;

            if (update_listbox)
            {
                SendMessage(matMgr_Windows[3], LB_SETCURSEL, (WPARAM)matMgr_BmpList_Current, 0);
            }

            /* Update `isExternal` checkbox */

            if ((matMgr_BmpList_Current >= 0) && (matMgr_BmpList_Current < matMgr_BmpList_Count))
            {
                eBitmap* current_bitmap = matMgr_BmpList[matMgr_BmpList_Current];

                if (nullptr != current_bitmap)
                {
                    bool is_external = current_bitmap->getLoadedFromExternalFileFlag();

                    SendMessage(matMgr_Windows[8], BM_SETCHECK, (WPARAM)(is_external ? BST_CHECKED : BST_UNCHECKED), 0);
                }
            }
        }

        void materialsManager_SetCurrentMaterial(int selected_id, bool update_listbox, bool update_bitmap)
        {
            matMgr_MatList_Current = selected_id;

            if ((matMgr_MatList_Current >= 0) && (matMgr_MatList_Current < matMgr_MatList_Count))
            {
                eMaterial* current_material = matMgr_MatList[matMgr_MatList_Current];

                if (nullptr != current_material)
                {
                    if (update_listbox)
                    {
                        SendMessage(matMgr_Windows[0], LB_SETCURSEL, (WPARAM)matMgr_MatList_Current, 0);
                    }

                    /* Update Collision Type ListBox */

                    uint32_t collision_type = (current_material->getCollisionType() & 0x0000FFFF);

                    SendMessage(matMgr_Windows[1], LB_SETCURSEL, (WPARAM)collision_type, 0);

                    /* Update Flags Checkboxes */

                    uint8_t material_flags = current_material->getMaterialFlags();

                    for (int a = 0; a < 4; a++)
                    {
                        SendMessage
                        (
                            matMgr_Windows[4 + a],
                            BM_SETCHECK,
                            (WPARAM)(((0x01 << a) & material_flags) ? BST_CHECKED : BST_UNCHECKED),
                            0
                        );
                    }

                    /* Update Sound Type ListBox */

                    uint16_t sound_type = current_material->getSoundType();

                    switch (sound_type)
                    {
                        case 0x0000: // <GRASS>
                        {
                            sound_type = 0;
                            break;
                        }

                        case 0x1000: // <WOOD>
                        {
                            sound_type = 1;
                            break;
                        }

                        case 0x2000: // <METAL>
                        {
                            sound_type = 2;
                            break;
                        }

                        case 0x4000: // <STONE>
                        {
                            sound_type = 3;
                            break;
                        }

                        case 0x8000: // <SNOW>
                        {
                            sound_type = 4;
                            break;
                        }

                        case 0x0001: // <SAND>
                        {
                            sound_type = 5;
                            break;
                        }

                        default:
                        {
                            sound_type = (-1);
                        }
                    }

                    SendMessage(matMgr_Windows[2], LB_SETCURSEL, (WPARAM)sound_type, 0);

                    if (update_bitmap)
                    {
                        /* Update Bitmaps ListBox */

                        int b = (-1);

                        eTexture* dummy_texture = current_material->getIthTexture(0);

                        if (nullptr != dummy_texture)
                        {
                            eBitmap* dummy_bitmap = dummy_texture->getBitmap();

                            if (nullptr != dummy_bitmap)
                            {
                                for (int a = 0; (b < 0) && (a < matMgr_BmpList_Count); a++)
                                {
                                    if (dummy_bitmap == matMgr_BmpList[a])
                                    {
                                        b = a;
                                    }
                                }
                            }
                        }

                        materialsManager_SetCurrentBitmap(b, true);
                    }

                    return;
                }
            }

            /* Default case - reset ListBoxes for Collision, Sound and Bitmaps */

            SendMessage(matMgr_Windows[0], LB_SETCURSEL, (WPARAM)(-1), 0);
            SendMessage(matMgr_Windows[1], LB_SETCURSEL, (WPARAM)(-1), 0);
            SendMessage(matMgr_Windows[2], LB_SETCURSEL, (WPARAM)(-1), 0);

            for (int a = 0; a < 4; a++)
            {
                SendMessage(matMgr_Windows[4 + a], BM_SETCHECK, BST_UNCHECKED, 0);
            }

            if (update_bitmap)
            {
                SendMessage(matMgr_Windows[3], LB_SETCURSEL, (WPARAM)(-1), 0);
            }
        }

        void materialsManager_UpdateCurrentBitmap(bool new_external_state)
        {
            if ((matMgr_BmpList_Current >= 0) && (matMgr_BmpList_Current < matMgr_BmpList_Count))
            {
                eBitmap* current_bitmap = matMgr_BmpList[matMgr_BmpList_Current];

                if (nullptr != current_bitmap)
                {
                    current_bitmap->setLoadedFromExternalFileFlag(new_external_state);
                }
            }
        }

        void materialsManager_UpdateCurrentMaterial(int32_t new_collision_type, int32_t new_sound_type, uint16_t new_flags)
        {
            if ((matMgr_MatList_Current >= 0) && (matMgr_MatList_Current < matMgr_MatList_Count))
            {
                eMaterial* current_material = matMgr_MatList[matMgr_MatList_Current];

                uint32_t resulting_id;

                uint8_t flags_to_apply = new_flags & 0x00FF;
                uint8_t flags_to_remove = (new_flags >> 8) & 0x00FF;

                if (nullptr != current_material)
                {
                    if ((new_collision_type >= 0) && (new_collision_type < KAO2_MATERIAL_TYPES_COUNT))
                    {
                        resulting_id = theMaterialTypes[new_collision_type].id;

                        current_material->setCollisionType(resulting_id);
                    }

                    if ((new_sound_type >= 0) && (new_sound_type < KAO2_MATERIAL_SOUNDS_COUNT))
                    {
                        resulting_id = theMaterialSounds[new_sound_type].id;

                        current_material->setSoundType(resulting_id);
                    }

                    if (0 != flags_to_apply)
                    {
                        current_material->setMaterialFlags(flags_to_apply);
                    }

                    if (0 != flags_to_remove)
                    {
                        current_material->unsetMaterialFlags(flags_to_remove);
                    }
                }
            }
        }

        void materialsManager_SetCurrentMaterialFromGeometry(void* object)
        {
            eMaterial* test_material = (eMaterial*)object;

            if (nullptr != test_material)
            {
                for (int a = 0; a < matMgr_MatList_Count; a++)
                {
                    if (test_material == matMgr_MatList[a])
                    {
                        materialsManager_SetCurrentMaterial(a, true, true);

                        return;
                    }
                }
            }
        }

        void materialsManager_ChangeList(int list_id)
        {
            if ((1 == matMgr_RenderedList) && (1 == list_id))
            {
                matMgr_scrollPos++;

                if ((THUMBNAILS_IN_GRID * THUMBNAILS_IN_GRID * matMgr_scrollPos) >= matMgr_BmpList_Count)
                {
                    matMgr_scrollPos = 0;
                }
            }
            else if ((list_id >= 1) && (list_id <= 2))
            {
                matMgr_RenderedList = list_id;

                matMgr_scrollPos = 0;

            }
            else
            {
                matMgr_RenderedList = 0;
                materialsManager_SetCurrentMaterial((-1), true, true);
                materialsManager_SetCurrentBitmap((-1), true);
            }
        }


        ////////////////////////////////////////////////////////////////
        // Materials Manager: Update names on the list
        ////////////////////////////////////////////////////////////////

        void materialsManager_UpdateMaterialName(void* object)
        {
            char bufor[LARGE_BUFFER_SIZE];
            eMaterial* current_material = (eMaterial*)object;

            if (nullptr == current_material)
            {
                /* Invalid parameter */
                return;
            }

            for (int a = 0; a < matMgr_MatList_Count; a++)
            {
                if (current_material == matMgr_MatList[a])
                {
                    eString name_str = current_material->getStringRepresentation();
                    const char* name_txt = name_str.getText();

                    if ((nullptr == name_txt) || (name_str.getLength() <= 0))
                    {
                        sprintf_s(bufor, LARGE_BUFFER_SIZE, "<Unnamed Material>");
                    }
                    else
                    {
                        sprintf_s(bufor, LARGE_BUFFER_SIZE, "\"%s\"", name_txt);
                    }

                    SendMessage(matMgr_Windows[0], LB_DELETESTRING, (WPARAM)a, 0);
                    SendMessage(matMgr_Windows[0], LB_INSERTSTRING, (WPARAM)a, (LPARAM)bufor);

                    return;
                }
            }
        }

        void materialsManager_UpdateBitmapName(void* object)
        {
            char bufor[LARGE_BUFFER_SIZE];
            eBitmap* current_bitmap = (eBitmap*)object;

            if (nullptr == current_bitmap)
            {
                /* Invalid parameter */
                return;
            }

            for (int a = 0; a < matMgr_BmpList_Count; a++)
            {
                if (current_bitmap == matMgr_BmpList[a])
                {
                    eString name_str = current_bitmap->getPath();
                    const char* name_txt = name_str.getText();

                    if ((nullptr == name_txt) || (name_str.getLength() <= 0))
                    {
                        sprintf_s(bufor, LARGE_BUFFER_SIZE, "<Unnamed Bitmap>");
                    }
                    else
                    {
                        sprintf_s(bufor, LARGE_BUFFER_SIZE, "\"%s\"", name_txt);
                    }

                    SendMessage(matMgr_Windows[3], LB_DELETESTRING, (WPARAM)a, 0);
                    SendMessage(matMgr_Windows[3], LB_INSERTSTRING, (WPARAM)a, (LPARAM)bufor);

                    return;
                }
            }
        }


        ////////////////////////////////////////////////////////////////
        // Materials Manager: Deleting objects from the lists
        ////////////////////////////////////////////////////////////////

        void materialsManager_DeleteMaterial(void* object)
        {
            eMaterial* current_material = (eMaterial*)object;

            for (int a = 0; a < matMgr_MatList_Count; a++)
            {
                if (current_material == matMgr_MatList[a])
                {
                    /* Mark current item as invalid and notify the ListBox */

                    matMgr_MatList[a] = nullptr;

                    SendMessage(matMgr_Windows[0], LB_DELETESTRING, (WPARAM)a, 0);

                    for (int b = (a + 1); b < matMgr_MatList_Count; b++)
                    {
                        matMgr_MatList[b - 1] = matMgr_MatList[b];
                        matMgr_MatList[b] = nullptr;
                    }

                    matMgr_MatList_Count--;

                    materialsManager_SetCurrentMaterial((-1), true, true);

                    /* Don't delete bitmaps, because they could be referenced in other materials */

                    return;
                }
            }
        }

        void materialsManager_DeleteBitmap(void* object)
        {
            eBitmap* current_bitmap = (eBitmap*)object;

            for (int a = 0; a < matMgr_BmpList_Count; a++)
            {
                if (current_bitmap == matMgr_BmpList[a])
                {
                    /* Mark current item as invalid and notify the ListBox */

                    matMgr_BmpList[a] = nullptr;

                    SendMessage(matMgr_Windows[3], LB_DELETESTRING, (WPARAM)a, 0);

                    materialsManager_SetCurrentBitmap((-1), true);

                    /* Move other items one place backwards */

                    for (int b = (a + 1); b < matMgr_BmpList_Count; b++)
                    {
                        matMgr_BmpList[b - 1] = matMgr_BmpList[b];
                        matMgr_BmpList[b] = nullptr;
                    }

                    matMgr_BmpList_Count--;
                    return;
                }
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

            if ((3 == click) && (1 == matMgr_RenderedList))
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
                            materialsManager_SetCurrentMaterial((-1), true, false);
                            materialsManager_SetCurrentBitmap(counter, true);

                            materialsManager_ChangeList(2);

                            return;
                        }

                        counter++;
                    }
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

            if (1 == matMgr_RenderedList)
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
            if (2 == matMgr_RenderedList)
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
                if (dummy_bitmap->getPath().getLength() > 0)
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
                if (dummy_bitmap->getPath().getLength() > 0)
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
            int test_length = directory.getLength();
            const char* test_text = directory.getText();

            if (test_length > 0)
            {
                switch (test_text[test_length - 1])
                {
                    case '/':
                    case '\\':
                    {
                        break;
                    }

                    default:
                    {
                        directory += "/";
                    }
                }
            }

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

                if (bmp_path.getLength() > 0)
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

                if (bmp_path.getLength() > 0)
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

        void menuFunc_MaterialsManagerEnter()
        {
            changeView(false);
        }

        void menuFunc_MaterialsManagerLeave()
        {
            changeView(true);
        }

        void buttonFunc_MaterialsManager(WPARAM wParam, LPARAM lParam, void* custom_param)
        {
            if (BN_CLICKED == HIWORD(wParam))
            {
                if (1 == (int)custom_param)
                {
                    /* "Browse Thumbnails" */
                    materialsManager_ChangeList(1);
                }
                else if (2 == (int)custom_param)
                {
                    /* "Show Selected Bitmap" */
                    materialsManager_ChangeList(2);
                }
                else if (3 == (int)custom_param)
                {
                    /* "Export Selected Bitmap" */
                    materialsManager_ExportCurrentBitmap();
                }
                else if (4 == (int)custom_param)
                {
                    /* "Reimport Selected Bitmap" */
                    materialsManager_ReimportCurrentBitmap();
                }
                else if (5 == (int)custom_param)
                {
                    /* "Export All Loaded Bitmaps" */
                    materialsManager_ExportAllBitmaps(0, getEditorString(1, false), false);
                }
                else if (6 == (int)custom_param)
                {
                    /* "Reimport All Loaded Bitmaps" */
                    materialsManager_ReimportAllBitmaps(0, getEditorString(1, false), false);
                }
                else if (7 == (int)custom_param)
                {
                    /* "Bulk Textures Export" */
                    materialsManager_BulkTexturesExport();
                }
                else if (8 == (int)custom_param)
                {
                    /* "Bulk Textures Reimport" */
                    materialsManager_BulkTexturesReimport();
                }
            }
        }

        void buttonFunc_MaterialsListBoxes(WPARAM wParam, LPARAM lParam, void* custom_param)
        {
            int selection = (int)custom_param;

            switch (HIWORD(wParam))
            {
                case LBN_SELCHANGE:
                case LBN_SELCANCEL:
                {
                    int id_from_the_list = (int)SendMessage((HWND)lParam, LB_GETCURSEL, 0, 0);

                    if (1 == selection)
                    {
                        /* Simple list of Materials */
                        materialsManager_SetCurrentMaterial(id_from_the_list, false, true);
                    }
                    else if (2 == selection)
                    {
                        /* List of Material Collision types */
                        materialsManager_UpdateCurrentMaterial(id_from_the_list, (-1), 0x0000);
                    }
                    else if (3 == selection)
                    {
                        /* List of Material Sounds */
                        materialsManager_UpdateCurrentMaterial((-1), id_from_the_list, 0x0000);
                    }
                    else if (4 == selection)
                    {
                        /* Simple list of Bitmaps */
                        materialsManager_SetCurrentMaterial((-1), true, false);
                        materialsManager_SetCurrentBitmap(id_from_the_list, false);
                    }

                    break;
                }
            }
        }

        void buttonFunc_MaterialsCheckBoxes(WPARAM wParam, LPARAM lParam, void* custom_param)
        {
            if (BN_CLICKED == HIWORD(wParam))
            {
                int selection = (int)custom_param;

                if ((selection >= 0) && (selection < 4))
                {
                    selection = (0x01 << selection) & 0x00FF;

                    if (BST_CHECKED != SendMessage((HWND)lParam, BM_GETCHECK, 0, 0))
                    {
                        selection = (selection << 8) & 0xFF00;
                    }

                    materialsManager_UpdateCurrentMaterial((-1), (-1), selection);
                }
            }
        }

        void buttonFunc_BitmapCheckBox(WPARAM wParam, LPARAM lParam, void* custom_param)
        {
            if (BN_CLICKED == HIWORD(wParam))
            {
                bool is_external = (BST_CHECKED == SendMessage((HWND)lParam, BM_GETCHECK, 0, 0));

                materialsManager_UpdateCurrentBitmap(is_external);
            }
        }

        bool materialsManager_AddWindows()
        {
            int32_t a;
            char bufor[32];

            const int WINDOW_HEIGHT = 24;
            const int WINDOW_PADDING = 16;
            const int WINDOW_PADDING_SMALL = 8;
            const int TOP_OFFSET = 8;

            const char* MATERIALS_INFO =
                "* Press the \"Browse Thumbnails\" button to switch the list every 100 thumbnails.\n" \
                "* Make sure to set up \"Media Directory\" before extracting/reimporting bitamps (except for Bulk processing functions)";

            const DWORD LISTBOX_STYLES = (WS_CHILD | WS_VSCROLL | LBS_DISABLENOSCROLL | LBS_HASSTRINGS | LBS_NOTIFY);

            /********************************/
            /* [MAT MGR PAGE] */

            theWindowsManager.addPage("Materials manager", menuFunc_MaterialsManagerEnter, menuFunc_MaterialsManagerLeave);

            theWindowsManager.setCurrentPosition(RECT_TABS_X1, TOP_OFFSET);

            /********************************/
            /* [MAT MGR PAGE] (0) Small info */

            theWindowsManager.setCurrentClassName("STATIC");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD);

            if (0 == theWindowsManager.addWindow(MATERIALS_INFO, RECT_TABS_X2, 4 * WINDOW_HEIGHT, nullptr, nullptr, 0x01))
            {
                return false;
            }

            theWindowsManager.offsetCurrentPosition(0, WINDOW_PADDING_SMALL);

            /********************************/
            /* [MAT MGR PAGE] (1 – 8) Create buttons */

            theWindowsManager.setCurrentClassName("BUTTON");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | BS_DEFPUSHBUTTON | BS_MULTILINE);

            theWindowsManager.setCurrentPadding(WINDOW_PADDING_SMALL, WINDOW_PADDING_SMALL);

            a = (RECT_TABS_X2 / 2) - (WINDOW_PADDING / 2);

            if (0 == theWindowsManager.addWindow("Browse Thumbnails", a, 2 * WINDOW_HEIGHT, buttonFunc_MaterialsManager, (void*)(1), 0))
            {
                return false;
            }

            if (0 == theWindowsManager.addWindow("Show Selected Bitmap", a, 2 * WINDOW_HEIGHT, buttonFunc_MaterialsManager, (void*)(2), 0x01))
            {
                return false;
            }

            if (0 == theWindowsManager.addWindow("Export Selected Bitmap", a, 2 * WINDOW_HEIGHT, buttonFunc_MaterialsManager, (void*)(3), 0))
            {
                return false;
            }

            if (0 == theWindowsManager.addWindow("Reimport Selected Bitmap", a, 2 * WINDOW_HEIGHT, buttonFunc_MaterialsManager, (void*)(4), 0x01))
            {
                return false;
            }

            if (0 == theWindowsManager.addWindow("Export All Loaded Bitmaps", a, 2 * WINDOW_HEIGHT, buttonFunc_MaterialsManager, (void*)(5), 0))
            {
                return false;
            }

            if (0 == theWindowsManager.addWindow("Reimport All Loaded Bitmaps", a, 2 * WINDOW_HEIGHT, buttonFunc_MaterialsManager, (void*)(6), 0x01))
            {
                return false;
            }

            if (0 == theWindowsManager.addWindow("Bulk Textures Export", a, 2 * WINDOW_HEIGHT, buttonFunc_MaterialsManager, (void*)(7), 0))
            {
                return false;
            }

            if (0 == theWindowsManager.addWindow("Bulk Textures Reimport", a, 2 * WINDOW_HEIGHT, buttonFunc_MaterialsManager, (void*)(8), 0x01))
            {
                return false;
            }

            theWindowsManager.setCurrentPadding(0, 0);

            /********************************/
            /* Create line decoration */

            theWindowsManager.setCurrentClassName("STATIC");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | WS_VISIBLE | SS_ETCHEDHORZ);
            theWindowsManager.getCurrentPosition(nullptr, &a);
            theWindowsManager.setCurrentPosition(0, a + WINDOW_PADDING_SMALL);

            if (0 == theWindowsManager.addWindow("", RECT_LOGO_X2, 2, nullptr, 0, 0x01))
            {
                return false;
            }

            theWindowsManager.offsetCurrentPosition(0, (WINDOW_PADDING_SMALL - 2));

            /********************************/
            /* Create label */

            theWindowsManager.setCurrentClassName("STATIC");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD);

            if (0 == theWindowsManager.addWindow("List of Materials:", RECT_TABS_X2, WINDOW_HEIGHT, nullptr, nullptr, 0x01))
            {
                return false;
            }

            /********************************/
            /* (0) Create listbox - Materials list */

            theWindowsManager.setCurrentClassName("LISTBOX");
            theWindowsManager.setCurrentStyleFlags(LISTBOX_STYLES | WS_HSCROLL);

            theWindowsManager.addEdgesToNextWindow();
            if (0 == (matMgr_Windows[0] = theWindowsManager.addWindow("", RECT_TABS_X2, 256, buttonFunc_MaterialsListBoxes, (void*)(1), 0x01)))
            {
                return false;
            }

            SendMessage(matMgr_Windows[0], LB_SETHORIZONTALEXTENT, (WPARAM)512, 0);

            /********************************/
            /* Create line decoration and label */

            theWindowsManager.setCurrentClassName("STATIC");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | WS_VISIBLE | SS_ETCHEDHORZ);
            theWindowsManager.getCurrentPosition(nullptr, &a);
            theWindowsManager.setCurrentPosition(0, a + WINDOW_PADDING_SMALL);

            if (0 == theWindowsManager.addWindow("", RECT_LOGO_X2, 2, nullptr, 0, 0x01))
            {
                return false;
            }

            theWindowsManager.offsetCurrentPosition(0, (WINDOW_PADDING_SMALL - 2));
            theWindowsManager.setCurrentStyleFlags(WS_CHILD);

            if (0 == theWindowsManager.addWindow("Selected material's Collision type:", RECT_TABS_X2, WINDOW_HEIGHT, nullptr, nullptr, 0x01))
            {
                return false;
            }

            /********************************/
            /* (1) Create listbox - Material Collision Types */

            theWindowsManager.setCurrentClassName("LISTBOX");
            theWindowsManager.setCurrentStyleFlags(LISTBOX_STYLES);

            theWindowsManager.addEdgesToNextWindow();
            if (0 == (matMgr_Windows[1] = theWindowsManager.addWindow("", RECT_TABS_X2, 128, buttonFunc_MaterialsListBoxes, (void*)(2), 0x01)))
            {
                return false;
            }

            for (a = 0; a < KAO2_MATERIAL_TYPES_COUNT; a++)
            {
                sprintf_s(bufor, 32, "%02d: \"%s\"", a, theMaterialTypes[a].name);
                SendMessage(matMgr_Windows[1], LB_ADDSTRING, 0, (LPARAM)bufor);
            }

            /********************************/
            /* Create line decoration and label */

            theWindowsManager.setCurrentClassName("STATIC");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | WS_VISIBLE | SS_ETCHEDHORZ);
            theWindowsManager.getCurrentPosition(nullptr, &a);
            theWindowsManager.setCurrentPosition(0, a + WINDOW_PADDING_SMALL);

            if (0 == theWindowsManager.addWindow("", RECT_LOGO_X2, 2, nullptr, 0, 0x01))
            {
                return false;
            }

            theWindowsManager.offsetCurrentPosition(0, (WINDOW_PADDING_SMALL - 2));
            theWindowsManager.setCurrentStyleFlags(WS_CHILD);

            if (0 == theWindowsManager.addWindow("Selected material's Sound:", RECT_TABS_X2, WINDOW_HEIGHT, nullptr, nullptr, 0x01))
            {
                return false;
            }

            /********************************/
            /* (2) Create listbox - Material Sound Types */

            theWindowsManager.setCurrentClassName("LISTBOX");
            theWindowsManager.setCurrentStyleFlags(LISTBOX_STYLES);

            theWindowsManager.addEdgesToNextWindow();
            if (0 == (matMgr_Windows[2] = theWindowsManager.addWindow("", RECT_TABS_X2, 128, buttonFunc_MaterialsListBoxes, (void*)(3), 0x01)))
            {
                return false;
            }

            for (a = 0; a < KAO2_MATERIAL_SOUNDS_COUNT; a++)
            {
                sprintf_s(bufor, 32, "%02d: \"%s\"", a, theMaterialSounds[a].name);
                SendMessage(matMgr_Windows[2], LB_ADDSTRING, 0, (LPARAM)bufor);
            }

            /********************************/
            /* Create line decoration and label */

            theWindowsManager.setCurrentClassName("STATIC");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | WS_VISIBLE | SS_ETCHEDHORZ);
            theWindowsManager.getCurrentPosition(nullptr, &a);
            theWindowsManager.setCurrentPosition(0, a + WINDOW_PADDING_SMALL);

            if (0 == theWindowsManager.addWindow("", RECT_LOGO_X2, 2, nullptr, 0, 0x01))
            {
                return false;
            }

            theWindowsManager.offsetCurrentPosition(0, (WINDOW_PADDING_SMALL - 2));
            theWindowsManager.setCurrentStyleFlags(WS_CHILD);

            if (0 == theWindowsManager.addWindow("Selected material's Flags:\n(BLEND + ADDITIVE = OPAQUE)", RECT_TABS_X2, 2 * WINDOW_HEIGHT, nullptr, nullptr, 0x01))
            {
                return false;
            }

            /********************************/
            /*  (4-7) Create checkboxes - Material Blending Flags */

            theWindowsManager.setCurrentClassName("BUTTON");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | BS_AUTOCHECKBOX);

            for (a = 0; a < 4; a++)
            {
                sprintf_s(bufor, 32, "0x%02X: \"%s\"", (0x01 << a), theMaterialFlags[a]);

                if (0 == (matMgr_Windows[4 + a] = theWindowsManager.addWindow(bufor, RECT_TABS_X2, WINDOW_HEIGHT, buttonFunc_MaterialsCheckBoxes, (void*)(a), 0x01)))
                {
                    return false;
                }
            }

            /********************************/
            /* Create line decoration and label */

            theWindowsManager.setCurrentClassName("STATIC");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | WS_VISIBLE | SS_ETCHEDHORZ);
            theWindowsManager.getCurrentPosition(nullptr, &a);
            theWindowsManager.setCurrentPosition(0, a + WINDOW_PADDING_SMALL);

            if (0 == theWindowsManager.addWindow("", RECT_LOGO_X2, 2, nullptr, 0, 0x01))
            {
                return false;
            }

            theWindowsManager.offsetCurrentPosition(0, (WINDOW_PADDING_SMALL - 2));
            theWindowsManager.setCurrentStyleFlags(WS_CHILD);

            if (0 == theWindowsManager.addWindow("List of Bitmaps:", RECT_TABS_X2, WINDOW_HEIGHT, nullptr, nullptr, 0x01))
            {
                return false;
            }

            /********************************/
            /* (3) Create listbox - Bitmaps list */

            theWindowsManager.setCurrentClassName("LISTBOX");
            theWindowsManager.setCurrentStyleFlags(LISTBOX_STYLES | WS_HSCROLL);

            theWindowsManager.addEdgesToNextWindow();
            if (0 == (matMgr_Windows[3] = theWindowsManager.addWindow("", RECT_TABS_X2, 256, buttonFunc_MaterialsListBoxes, (void*)(4), 0x01)))
            {
                return false;
            }

            SendMessage(matMgr_Windows[3], LB_SETHORIZONTALEXTENT, (WPARAM)512, 0);

            /********************************/
            /* Create line decoration */

            theWindowsManager.setCurrentClassName("STATIC");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | WS_VISIBLE | SS_ETCHEDHORZ);
            theWindowsManager.getCurrentPosition(nullptr, &a);
            theWindowsManager.setCurrentPosition(0, a + WINDOW_PADDING_SMALL);

            if (0 == theWindowsManager.addWindow("", RECT_LOGO_X2, 2, nullptr, 0, 0x01))
            {
                return false;
            }

            /********************************/
            /* (8) Create checkbox - Bitmap marked as external */

            theWindowsManager.setCurrentClassName("BUTTON");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | BS_AUTOCHECKBOX);

            if (0 == (matMgr_Windows[8] = theWindowsManager.addWindow("Loaded from external file", RECT_TABS_X2, WINDOW_HEIGHT, buttonFunc_BitmapCheckBox, nullptr, 0x01)))
            {
                return false;
            }

            /********************************/
            /* Create the last line decoration */

            theWindowsManager.setCurrentClassName("STATIC");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | WS_VISIBLE | SS_ETCHEDHORZ);
            theWindowsManager.getCurrentPosition(nullptr, &a);
            theWindowsManager.setCurrentPosition(0, a + WINDOW_PADDING_SMALL);

            if (0 == theWindowsManager.addWindow("", RECT_LOGO_X2, 2, nullptr, 0, 0x01))
            {
                return false;
            }

            return true;
        }
    }
}
