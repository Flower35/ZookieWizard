#ifndef H_KAO2AR_DRAWCONTEXT
#define H_KAO2AR_DRAWCONTEXT

#include <kao2ar/kao2ar.h>

namespace ZookieWizard
{
    struct eAnimate;
    class eTexture;
    class eMaterial;
    class eLight;

    ////////////////////////////////////////////////////////////////
    // KAO2 DRAW CONTEXT
    ////////////////////////////////////////////////////////////////

    class eDrawContext
    {
        /*** Properties ***/

        private:

            int32_t drawFlags;
            uint32_t nodeFlags;
            eAnimate* anim;
            eSRP* parentSRP;
            eMatrix4x4* parentMatrix;
            int32_t markedID;

            eMaterial* previousMaterial;
            int32_t previousTextureID;
            eTexture* previousTexture;
            int32_t previousMaterialFlags;
            float previousAlphaTest;

            int32_t lightsCount;

        /*** Methods ***/

        public:

            eDrawContext();

            void softReset();
            void hardReset();

            int32_t getDrawFlags() const;
            void setDrawFlags(int32_t new_flags);

            bool checkNodeFlags(uint32_t current_node_flags, bool is_group) const;
            void setNodeFlags(uint32_t new_flags);

            eAnimate* getAnimateObject() const;
            void setAnimateObject(const eAnimate* new_object);

            eSRP* getParentSRP() const;
            void setParentSRP(const eSRP* new_parent_srp);

            eMatrix4x4* getParentMatrix() const;
            void setParentMatrix(const eMatrix4x4* new_parent_matrix);

            int32_t getMarekedId() const;
            void setMarkedId(int32_t new_marked_id);
            bool setMarkedForGroupNode();
            void setMarkedForChildNode(bool matches_id);
            bool isNodeSelectedOrMarked() const;
            bool isNodeMarkedOrChildOfMarked() const;
            bool isNodeOutlined() const;

            void useMaterial(const eMaterial* material, int32_t texture_id);

            void useLight(const eLight* light);
            void decreaseLights(int32_t number);
    };

}

#endif
