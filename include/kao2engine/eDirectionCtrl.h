#ifndef H_KAO2AR_DIRECTIONCTRL
#define H_KAO2AR_DIRECTIONCTRL

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eDirectionCtrl interface
    // <kao2.005CE890> (vptr)
    ////////////////////////////////////////////////////////////////

    class eDirectionCtrl : public Gadget
    {
        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*[0x14]*/
            /*[0x18]*/

        /*** Methods ***/

        public:

            eDirectionCtrl();
            ~eDirectionCtrl();

        private:

            void createFromOtherObject(const eDirectionCtrl &other);

        public:

            eDirectionCtrl(const eDirectionCtrl &other);
            eDirectionCtrl& operator = (const eDirectionCtrl &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;

            /* << Gadget >> */

            eString getDefaultGadgetName() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eDirectionCtrl TypeInfo
    // <kao2.0042F770> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_DIRECTIONCTRL_ID = 0x0000FEBE;

    extern TypeInfo E_DIRECTIONCTRL_TYPEINFO;

}

#endif
