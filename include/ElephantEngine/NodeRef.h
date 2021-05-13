#ifndef H_KAO2AR_NODEREF
#define H_KAO2AR_NODEREF

#include <ElephantEngine/eRefCounter.h>

namespace ZookieWizard
{
    class eNode;

    ////////////////////////////////////////////////////////////////
    // NodeRef interface
    // <kao2.005D8738> (vptr)
    ////////////////////////////////////////////////////////////////

    class NodeRef : public eRefCounter
    {
        /*** Properties ***/

        protected:

            /*[0x08]*/ eString name;
            /*[0x0C]*/ eString nodeName;
            /*[0x10]*/ const TypeInfo* nodeType;
            /*[0x14]*/ eNode* node;
            int32_t unknown_new_id;

        /*** Methods ***/

        public:

            NodeRef();
            ~NodeRef();

        private:

            void createFromOtherObject(const NodeRef &other);

        public:

            NodeRef(const NodeRef &other);
            NodeRef& operator = (const NodeRef &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
            void serialize(Archive &ar) override;

            eString getStringRepresentation() const override;
            eString generateScriptText() const override;

            /* << NodeRef >> */

            eNode* getLinkedNode() const;
    };


    ////////////////////////////////////////////////////////////////
    // NodeRef TypeInfo
    // <kao2.005A07C0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_NODEREF_ID = 0x07EA0002;

    extern TypeInfo E_NODEREF_TYPEINFO;

}

#endif
