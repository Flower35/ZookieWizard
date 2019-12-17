#ifndef H_KAO2AR_ADDNODE
#define H_KAO2AR_ADDNODE

#include <kao2engine/Gadget.h>

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

            TypeInfo* getType() override;
    };


    ////////////////////////////////////////////////////////////////
    // eAddNode TypeInfo
    // <kao2.00519250> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_ADDNODE_ID = 0x00465719;

    extern TypeInfo E_ADDNODE_TYPEINFO;

}

#endif
