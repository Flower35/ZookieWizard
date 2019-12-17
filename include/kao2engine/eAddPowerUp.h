#ifndef H_KAO2AR_ADDPOWERUP
#define H_KAO2AR_ADDPOWERUP

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eAddPowerUp interface
    // <kao2.005D87E0> (vptr)
    ////////////////////////////////////////////////////////////////

    class eAddPowerUp : public Gadget
    {

        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x20]*/

        /*** Methods ***/

        public:

            eAddPowerUp();
            ~eAddPowerUp();

            TypeInfo* getType() override;
    };


    ////////////////////////////////////////////////////////////////
    // eAddPowerUp TypeInfo
    // <kao2.005A4910> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_ADDPOWERUP_ID = 0x3E1CA1FD;

    extern TypeInfo E_ADDPOWERUP_TYPEINFO;

}

#endif
