#ifndef H_KAO2AR_VISIBILITYCTRL
#define H_KAO2AR_VISIBILITYCTRL

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eVisibilityCtrl interface
    // <kao2.005CE950> (vptr)
    ////////////////////////////////////////////////////////////////

    class eVisibilityCtrl : public Gadget
    {

        /*** Methods ***/

        public:

            eVisibilityCtrl();
            ~eVisibilityCtrl();

            TypeInfo* getType() override;
    };


    ////////////////////////////////////////////////////////////////
    // eVisibilityCtrl TypeInfo
    // <kao2.004304E0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_VISIBILITYCTRL_ID = 0xFAC13020;

    extern TypeInfo E_VISIBILITYCTRL_TYPEINFO;

}

#endif
