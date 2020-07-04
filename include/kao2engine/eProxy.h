#ifndef H_KAO2AR_PROXY
#define H_KAO2AR_PROXY

#include <kao2engine/eTransform.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eProxy interface
    ////////////////////////////////////////////////////////////////

    class eProxy : public eTransform
    {

        /*** Properties ***/

        protected:

            /*[0xAC]*/ eString targetFile;
            /*[0xB0]*/ int32_t category;

            // 0 = "(particle) [ar]"
            // 1 = "(hero)"
            // 2 = "(powerup) [def]"
            // 3 = "(enemy) [def]"
            // 4 = "(fluff) [def]"
            // 5 = "(geoproxy) [ar]"
            // 6 = "(object) [def]"

            bool externalContent;

        /*** Methods ***/

        public:

            eProxy();
            ~eProxy();

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;

            void writeStructureToTextFile(FileOperator &file, int32_t indentation) const override;

            bool renderObject(int32_t draw_flags, eAnimate* anim, eSRP &parent_srp, eMatrix4x4 &parent_matrix, int32_t marked_id) override;

            void destroyNode() override;

            void reloadXRef(Archive &ar);
            void exportXRef(Archive &ar);

            void setTargetName(eString new_target);
            void setCategory(int32_t new_category);
    };


    ////////////////////////////////////////////////////////////////
    // eProxy TypeInfo
    // <kao2.00485610> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_PROXY_ID = 0x13454032;

    extern TypeInfo E_PROXY_TYPEINFO;

}

#endif
