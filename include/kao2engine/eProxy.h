#ifndef H_KAO2AR_PROXY
#define H_KAO2AR_PROXY

#include <kao2engine/eTransform.h>

namespace ZookieWizard
{
    class eXRefProxy;

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

            eXRefProxy* externalContentLink;

        /*** Methods ***/

        public:

            eProxy();
            ~eProxy();

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;

            void findAndDereference(eNode* target) override;

            void writeStructureToTextFile(FileOperator &file, int32_t indentation) const override;

            void renderNode(eDrawContext &draw_context) const override;

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
