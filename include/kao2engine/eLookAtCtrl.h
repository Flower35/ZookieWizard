#ifndef H_KAO2AR_LOOKATCTRL
#define H_KAO2AR_LOOKATCTRL

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eLookAtCtrl interface
    // <kao2.005CEE10> (vptr)
    ////////////////////////////////////////////////////////////////

    class eLookAtCtrl : public Gadget
    {

        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x24]*/

        /*** Methods ***/

        public:

            eLookAtCtrl();
            ~eLookAtCtrl();

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eLookAtCtrl TypeInfo
    // <kao2.004D0C80> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_LOOKATCTRL_ID = 0x3C1A9205;

    extern TypeInfo E_LOOKATCTRL_TYPEINFO;

}

#endif
