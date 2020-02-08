#ifndef H_KAO2AR_FLYINGTARGET
#define H_KAO2AR_FLYINGTARGET

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eFlyingTarget interface
    // <kao2.005D4260> (vptr)
    ////////////////////////////////////////////////////////////////

    class eFlyingTarget : public Gadget
    {

        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*[0x14]*/
            /*[0x18]*/
            /*[0x1C]*/

        /*** Methods ***/

        public:

            eFlyingTarget();
            ~eFlyingTarget();

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eFlyingTarget TypeInfo
    // <kao2.00500B40> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_FLYINGTARGET_ID = 0x0002F0F4;

    extern TypeInfo E_FLYINGTARGET_TYPEINFO;

}

#endif
