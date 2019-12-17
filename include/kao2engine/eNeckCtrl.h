#ifndef H_KAO2AR_NECKCTRL
#define H_KAO2AR_NECKCTRL

#include <kao2engine/eLookAtCtrl.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eNeckCtrl interface
    // <kao2.005CEDB8> (vptr)
    ////////////////////////////////////////////////////////////////

    class eNeckCtrl : public eLookAtCtrl
    {

        /*** Properties ***/

        protected:

            /*[0x28]*/
            /*(...)*/
            /*[0x80]*/

        /*** Methods ***/

        public:

            eNeckCtrl();
            ~eNeckCtrl();

            TypeInfo* getType() override;
    };


    ////////////////////////////////////////////////////////////////
    // eNeckCtrl TypeInfo
    // <kao2.004382A0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_NECKCTRL_ID = 0x3BB4EFBE;

    extern TypeInfo E_NECKCTRL_TYPEINFO;

}

#endif
