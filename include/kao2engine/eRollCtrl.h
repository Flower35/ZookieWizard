#ifndef H_KAO2AR_ROLLCTRL
#define H_KAO2AR_ROLLCTRL

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eRollCtrl interface
    // <kao2.005CF910> (vptr)
    ////////////////////////////////////////////////////////////////

    class eRollCtrl : public Gadget
    {

        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x38]*/

        /*** Methods ***/

        public:

            eRollCtrl();
            ~eRollCtrl();

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eRollCtrl TypeInfo
    // <kao2.0044B8C0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_ROLLCTRL_ID = 0xF001A031;

    extern TypeInfo E_ROLLCTRL_TYPEINFO;

}

#endif
