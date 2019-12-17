#ifndef H_KAO2AR_GLOBALLIGHTCTRL
#define H_KAO2AR_GLOBALLIGHTCTRL

#include <kao2engine/eGroup.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eGlobalLightCtrl interface
    // <kao_tw.0069EF1C> (vptr)
    ////////////////////////////////////////////////////////////////

    class eGlobalLightCtrl : public eGroup
    {

        /*** Methods ***/

        public:

            eGlobalLightCtrl();
            ~eGlobalLightCtrl();

            void serialize(Archive &ar) override;
            TypeInfo* getType() override;
    };


    ////////////////////////////////////////////////////////////////
    // eGlobalLightCtrl TypeInfo
    // <kao_tw.0052FA80> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_GLOBALLIGHTCTRL_ID = 0x05102509;

    extern TypeInfo E_GLOBALLIGHTCTRL_TYPEINFO;

}

#endif
