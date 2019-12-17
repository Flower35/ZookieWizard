#ifndef H_KAO2AR_NODEREF
#define H_KAO2AR_NODEREF

#include <kao2engine/eRefCounter.h>

namespace ZookieWizard
{
    class eNode;

    ////////////////////////////////////////////////////////////////
    // NodeRef interface
    ////////////////////////////////////////////////////////////////

    class NodeRef : public eRefCounter
    {

        /*** Properties ***/

        protected:

            /*[0x08]*/ eString name;
            /*[0x0C]*/ eString nodeName;
            /*[0x10]*/ TypeInfo* nodeType;
            /*[0x14]*/ eNode* node;
            int32_t unknown_new_id;

        /*** Methods ***/

        public:

            NodeRef();
            ~NodeRef();

            void serialize(Archive &ar) override;
            TypeInfo* getType() override;

            eString getStringRepresentation() override;
            eString generateScriptText() override;
    };


    ////////////////////////////////////////////////////////////////
    // NodeRef TypeInfo
    // <kao2.005A07F0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_NODEREF_ID = 0x07EA0002;

    extern TypeInfo E_NODEREF_TYPEINFO;

}

#endif
