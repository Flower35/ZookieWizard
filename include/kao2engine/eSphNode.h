#ifndef H_KAO2AR_SPHNODE
#define H_KAO2AR_SPHNODE

#include <kao2engine/eGeometry.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSphNode interface
    // <kao2.005D1E20> (vptr)
    ////////////////////////////////////////////////////////////////

    class eSphNode : public eGeometry
    {

        /*** Properties ***/

        protected:

            /*[0x58]*/ float radius;

        /*** Methods ***/

        public:

            eSphNode();
            ~eSphNode();

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;

            void renderNode(eDrawContext &draw_context) const override;

            void editingRebuildCollision() override;

            int32_t parsingSetProperty(char* result_msg, const TxtParsingNodeProp &property) override;
            int32_t parsingCustomMessage(char* result_msg, const eString &message, int32_t params_count, const TxtParsingNodeProp* params) override;
    };


    ////////////////////////////////////////////////////////////////
    // eSphNode TypeInfo
    // <kao2.004AC520> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_SPHNODE_ID = 0x0101F34B;

    extern TypeInfo E_SPHNODE_TYPEINFO;

}

#endif
