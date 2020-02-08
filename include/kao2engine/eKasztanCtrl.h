#ifndef H_KAO2AR_KASZTANCTRL
#define H_KAO2AR_KASZTANCTRL

#include <kao2engine/eEmptyCtrl.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eKasztanCtrl interface
    // <kao2.005CE398> (vptr)
    ////////////////////////////////////////////////////////////////

    class eKasztanCtrl : public eEmptyCtrl
    {

        /*** Properties ***/

        protected:

            /*[0x5C]*/ int32_t unknown_5C;
            /*[0x60]*/

        /*** Methods ***/

        public:

            eKasztanCtrl();
            ~eKasztanCtrl();

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eKasztanCtrl TypeInfo
    // <kao2.00428220> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_KASZTANCTRL_ID = 0xF0A10029;

    extern TypeInfo E_KASZTANCTRL_TYPEINFO;

}

#endif
