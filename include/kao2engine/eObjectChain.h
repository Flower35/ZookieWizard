#ifndef H_KAO2AR_OBJECTCHAIN
#define H_KAO2AR_OBJECTCHAIN

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eObjectChain interface
    // <kao2.005D5858> (vptr)
    ////////////////////////////////////////////////////////////////

    class eObjectChain : public Gadget
    {

        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x4C]*/

        /*** Methods ***/

        public:

            eObjectChain();
            ~eObjectChain();

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eObjectChain TypeInfo
    // <kao2.00525FF0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_OBJECTCHAIN_ID = 0x000204C4;

    extern TypeInfo E_OBJECTCHAIN_TYPEINFO;

}

#endif
