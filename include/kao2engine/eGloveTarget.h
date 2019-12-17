#ifndef H_KAO2AR_GLOVETARGET
#define H_KAO2AR_GLOVETARGET

#include <kao2engine/eEggTarget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eGloveTarget interface
    // <kao2.005D45A0> (vptr)
    ////////////////////////////////////////////////////////////////

    class eGloveTarget : public eEggTarget
    {

        /*** Properties ***/

        protected:

            /*[0x38]*/

        /*** Methods ***/

        public:

            eGloveTarget();
            ~eGloveTarget();

            TypeInfo* getType() override;
    };


    ////////////////////////////////////////////////////////////////
    // eGloveTarget TypeInfo
    // <kao2.00504510> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_GLOVETARGET_ID = 0x3DEABEDF;

    extern TypeInfo E_GLOVETARGET_TYPEINFO;

}

#endif
