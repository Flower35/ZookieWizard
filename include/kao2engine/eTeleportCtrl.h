#ifndef H_KAO2AR_TELEPORTCTRL
#define H_KAO2AR_TELEPORTCTRL

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{
    class eRndNavi;

    ////////////////////////////////////////////////////////////////
    // eTeleportCtrl interface
    // <kao2.005CE9F0> (vptr)
    ////////////////////////////////////////////////////////////////

    class eTeleportCtrl : public Gadget
    {

        /*** Properties ***/

        protected:

            /*[0x10]*/ eRndNavi* unknown_10;
            /*(...)*/
            /*[0x2C]*/

        /*** Methods ***/

        public:

            eTeleportCtrl();
            ~eTeleportCtrl();

            void serialize(Archive &ar) override;
            TypeInfo* getType() override;
            
            eString getDefaultGadgetName() override;
    };


    ////////////////////////////////////////////////////////////////
    // eTeleportCtrl TypeInfo
    // <kao2.00431060> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_TELEPORTCTRL_ID = 0xFAC13022;

    extern TypeInfo E_TELEPORTCTRL_TYPEINFO;

}

#endif
