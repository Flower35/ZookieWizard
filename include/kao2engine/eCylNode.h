#ifndef H_KAO2AR_CYLNODE
#define H_KAO2AR_CYLNODE

#include <kao2engine/eGeometry.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eCylNode interface
    ////////////////////////////////////////////////////////////////

    class eCylNode : public eGeometry
    {

        /*** Properties ***/

        protected:

            /*[0x58]*/ float radius;
            /*[0x5C]*/ float height;

        /*** Methods ***/

        public:

            eCylNode();
            ~eCylNode();

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;

            void renderNode(eDrawContext &draw_context) const override;

            void editingRebuildCollision() override;

            int32_t parsingSetProperty(char* result_msg, const TxtParsingNodeProp &property) override;
            int32_t parsingCustomMessage(char* result_msg, const eString &message, int32_t params_count, const TxtParsingNodeProp* params) override;
    };


    ////////////////////////////////////////////////////////////////
    // eCylNode TypeInfo
    // <kao2.004AC030> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_CYLNODE_ID = 0x0101F34A;

    extern TypeInfo E_CYLNODE_TYPEINFO;

}

#endif
