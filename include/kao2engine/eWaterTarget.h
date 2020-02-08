#ifndef H_KAO2AR_WATERTARGET
#define H_KAO2AR_WATERTARGET

#include <kao2engine/eEggTarget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eWaterTarget interface
    // <kao2.005D46F8> (vptr)
    ////////////////////////////////////////////////////////////////

    class eWaterTarget : public eEggTarget
    {

        /*** Methods ***/

        public:

            eWaterTarget();
            ~eWaterTarget();

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eWaterTarget TypeInfo
    // <kao2.005078C0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_WATERTARGET_ID = 0x3BFA6DCD;

    extern TypeInfo E_WATERTARGET_TYPEINFO;

}

#endif
