#ifndef H_KAO2AR_GLOBALLIGHTCTRL
#define H_KAO2AR_GLOBALLIGHTCTRL

#include <ElephantEngine/eGroup.h>

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

        private:

            void createFromOtherObject(const eGlobalLightCtrl &other);

        public:

            eGlobalLightCtrl(const eGlobalLightCtrl &other);
            eGlobalLightCtrl& operator = (const eGlobalLightCtrl &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
            void serialize(Archive &ar) override;
    };


    ////////////////////////////////////////////////////////////////
    // eGlobalLightCtrl TypeInfo
    // <kao_tw.0052FA50> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_GLOBALLIGHTCTRL_ID = 0x05102509;

    extern TypeInfo E_GLOBALLIGHTCTRL_TYPEINFO;

}

#endif
