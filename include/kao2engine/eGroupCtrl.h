#ifndef H_KAO2AR_GROUPCTRL
#define H_KAO2AR_GROUPCTRL

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eGroupCtrl interface
    // <kao2.005CE6D8> (vptr)
    ////////////////////////////////////////////////////////////////

    class eGroupCtrl : public Gadget
    {

        /*** Properties ***/

        protected:

            /*[0x10]*/ eRefCounter* unknown_10;
            /*[0x14]*/ uint8_t unknown_14;

        /*** Methods ***/

        public:

            eGroupCtrl();
            ~eGroupCtrl();

            void serialize(Archive &ar) override;
            TypeInfo* getType() override;

            eString getDefaultGadgetName() override;
    };


    ////////////////////////////////////////////////////////////////
    // eGroupCtrl TypeInfo
    // <kao2.0042CB20> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_GROUPCTRL_ID = 0xFA013020;

    extern TypeInfo E_GROUPCTRL_TYPEINFO;

}

#endif
