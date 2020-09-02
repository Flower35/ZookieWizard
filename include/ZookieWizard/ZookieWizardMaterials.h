#ifndef H_ZOOKIEWIZARD_MATERIALSMANAGER
#define H_ZOOKIEWIZARD_MATERIALSMANAGER

namespace ZookieWizard
{
    namespace GUI
    {
        ////////////////////////////////////////////////////////////////
        // Zookie Wizard: Materials Manager
        ////////////////////////////////////////////////////////////////

        bool prepareMaterialsManager();
        void clearMaterialsManager();

        void materialsManager_InsertMaterial(void* object);
        void materialsManager_InsertBitmap(void* object);
        void* materialsManager_FindMaterial(const char* bitmap_path);

        void materialsManager_SetCurrentMaterialFromGeometry(void* object);
        void materialsManager_UpdateMaterialName(void* object);
        void materialsManager_UpdateBitmapName(void* object);

        void materialsManager_DeleteMaterial(void* object);
        void materialsManager_DeleteBitmap(void* object);

        void materialsManager_ParseMouse(float pos_x, float pos_y, int click);
        void materialsManager_Render();
        bool materialsManager_AddWindows();
    }
}

#endif
