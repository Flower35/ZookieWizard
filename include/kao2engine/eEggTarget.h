#ifndef H_KAO2AR_EGGTARGET
#define H_KAO2AR_EGGTARGET

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eEggTarget interface
    // <kao2.005D4388> (vptr)
    ////////////////////////////////////////////////////////////////

    class eEggTarget : public Gadget
    {

        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x34]*/

        /*** Methods ***/

        public:

            eEggTarget();
            ~eEggTarget();

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eEggTarget TypeInfo
    // <kao2.005026B0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_EGGTARGET_ID = 0x3BF45DCD;

    extern TypeInfo E_EGGTARGET_TYPEINFO;

}

#endif
