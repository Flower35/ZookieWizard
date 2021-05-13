#ifndef H_KAO2AR_ADDNODE
#define H_KAO2AR_ADDNODE

#include <ElephantEngine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eAddNode interface
    // <kao2.005D5090> (vptr)
    ////////////////////////////////////////////////////////////////

    class eAddNode : public Gadget
    {

        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*[0x14]*/

        /*** Methods ***/

        public:

            eAddNode();
            ~eAddNode();

        private:

            void createFromOtherObject(const eAddNode &other);

        public:

            eAddNode(const eAddNode &other);
            eAddNode& operator = (const eAddNode &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eAddNode TypeInfo
    // <kao2.00519220> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_ADDNODE_ID = 0x00465719;

    extern TypeInfo E_ADDNODE_TYPEINFO;

}

#endif
