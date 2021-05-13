#ifndef H_KAO2AR_VISIBILITYCTRL
#define H_KAO2AR_VISIBILITYCTRL

#include <ElephantEngine/Gadget.h>

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

        private:

            void createFromOtherObject(const eVisibilityCtrl &other);

        public:

            eVisibilityCtrl(const eVisibilityCtrl &other);
            eVisibilityCtrl& operator = (const eVisibilityCtrl &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eVisibilityCtrl TypeInfo
    // <kao2.004304B0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_VISIBILITYCTRL_ID = 0xFAC13020;

    extern TypeInfo E_VISIBILITYCTRL_TYPEINFO;

}

#endif
