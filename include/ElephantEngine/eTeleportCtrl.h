#ifndef H_KAO2AR_TELEPORTCTRL
#define H_KAO2AR_TELEPORTCTRL

#include <ElephantEngine/Gadget.h>

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

        private:

            void createFromOtherObject(const eTeleportCtrl &other);

        public:

            eTeleportCtrl(const eTeleportCtrl &other);
            eTeleportCtrl& operator = (const eTeleportCtrl &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
            void serialize(Archive &ar) override;

            /* << Gadget >> */

            eString getDefaultGadgetName() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eTeleportCtrl TypeInfo
    // <kao2.00431030> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_TELEPORTCTRL_ID = 0xFAC13022;

    extern TypeInfo E_TELEPORTCTRL_TYPEINFO;

}

#endif
