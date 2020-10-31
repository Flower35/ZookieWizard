#ifndef H_ZOOKIEWIZARD_MATERIALSMANAGER
#define H_ZOOKIEWIZARD_MATERIALSMANAGER

namespace ZookieWizard
{
    class eMaterial;
    class eTexture;
    class eBitmap;
    class eNode;

    namespace GUI
    {
        ////////////////////////////////////////////////////////////////
        // Zookie Wizard: Materials Manager
        ////////////////////////////////////////////////////////////////

        bool prepareMaterialsManager();
        void clearMaterialsManager();

        void materialsManager_UpdateStatistics();

        void materialsManager_InsertMaterial(eMaterial* material);
        void materialsManager_InsertTexture(eTexture* texture);
        void materialsManager_InsertBitmap(eBitmap* bitmap);

        eBitmap* materialsManager_GetCurrentBitmap();
        eTexture* materialsManager_GetCurrentTexture();
        eMaterial* materialsManager_GetCurrentMaterial();

        void materialsManager_UpdateMaterialName(eMaterial* material);
        void materialsManager_UpdateTextureName(eTexture* texture);
        void materialsManager_UpdateBitmapPath(eBitmap* bitmap);

        void materialsManager_SetCurrentMaterialFromGeometry(eMaterial* material);

        void materialsManager_DeleteMaterial(eMaterial* material);
        void materialsManager_DeleteTexture(eTexture* texture);
        void materialsManager_DeleteBitmap(eBitmap* bitmap);

        void materialsManager_ReduceSimilarMaterials(eNode* root_node);

        void materialsManager_ParseMouse(float pos_x, float pos_y, int click);
        void materialsManager_Render();
        bool materialsManager_AddWindows();
    }
}

#endif
