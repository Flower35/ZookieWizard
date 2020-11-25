#ifndef H_KAO2AR_NODEREFLINKER
#define H_KAO2AR_NODEREFLINKER

#include <kao2ar/eObject.h>

namespace ZookieWizard
{
    class eNode;
    class eGroup;
    class Actor;

    ////////////////////////////////////////////////////////////////
    // NodeRefLinker interface
    // <kao2.005D50DC> (vptr)
    ////////////////////////////////////////////////////////////////

    class NodeRefLinker : public eObject
    {
        /*** Properties ***/

        protected:

            /*[0x04]*/ Actor* actor;
            /*[0x08]*/ eString passedMask;
            /*[0x0C]*/ eString passedName;
            /*[0x10]*/ TypeInfo* linkType;
            /*[0x14]*/

        /*** Methods ***/

        public:

            NodeRefLinker();
            ~NodeRefLinker();

        private:

            void createFromOtherObject(const NodeRefLinker &other);

        public:

            NodeRefLinker(const NodeRefLinker &other);
            NodeRefLinker& operator = (const NodeRefLinker &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;

            /* << NodeRefLinker >> */

            private:

                void throwErrorMessage(const char* reason) const;
                eNode* findLinkByFormat(eNode* node, eString mask) const;

            public:

                eNode* findLink(eNode* root, eNode* current_node, eString link_name, eString mask, TypeInfo* type_info);
    };


    ////////////////////////////////////////////////////////////////
    // NodeRefLinker TypeInfo
    // <kao2.005A01B0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_NODEREFLINKER_ID = 0x07EA0022;

    extern TypeInfo E_NODEREFLINKER_TYPEINFO;

}

#endif
