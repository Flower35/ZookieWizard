#ifndef H_KAO2AR_BUTTERFLY
#define H_KAO2AR_BUTTERFLY

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eButterfly interface
    // <kao2.005CEC58> (vptr)
    ////////////////////////////////////////////////////////////////

    class eButterfly : public Gadget
    {

        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x50]*/

        /*** Methods ***/

        public:

            eButterfly();
            ~eButterfly();

            TypeInfo* getType() override;
    };


    ////////////////////////////////////////////////////////////////
    // eButterfly TypeInfo
    // <kao2.004367B0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_BUTTERFLY_ID = 0x3BF56DDF;

    extern TypeInfo E_BUTTERFLY_TYPEINFO;

}

#endif
