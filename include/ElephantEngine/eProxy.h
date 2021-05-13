#ifndef H_KAO2AR_PROXY
#define H_KAO2AR_PROXY

#include <ElephantEngine/eTransform.h>

namespace ZookieWizard
{
    class eXRefProxy;

    ////////////////////////////////////////////////////////////////
    // eProxy interface
    // <kao2.005D1090> (vptr)
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

        private:

            void createFromOtherObject(const eProxy &other);

        public:

            eProxy(const eProxy &other);
            eProxy& operator = (const eProxy &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
            void serialize(Archive &ar) override;

            void writeStructureToTextFile(FileOperator &file, int32_t indentation, bool group_written) const override;

            /* << eNode >> */

            void destroyNode() override;
            void findAndDereference(eNode* target) override;

            bool removeEmptyAndUnreferencedGroups() override;

            void renderNode(eDrawContext &draw_context) const override;

            void editingNewNodeSetup() override;

            int32_t parsingSetProperty(char* result_msg, const TxtParsingNodeProp &property) override;
            int32_t parsingCustomMessage(char* result_msg, const eString &message, int32_t params_count, const TxtParsingNodeProp* params) override;

            void reloadXRef(const eString &media_dir, int32_t ar_version) override;
            void exportXRef(const eString &media_dir, int32_t ar_version) const override;

            /* << eProxy >> */

            void setCategory(int32_t new_category);
            void setTargetName(eString new_target_name);
    };


    ////////////////////////////////////////////////////////////////
    // eProxy TypeInfo
    // <kao2.004855E0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_PROXY_ID = 0x13454032;

    extern TypeInfo E_PROXY_TYPEINFO;

}

#endif
