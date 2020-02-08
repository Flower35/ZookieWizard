#ifndef H_KAO2AR_CAMERASHAKER
#define H_KAO2AR_CAMERASHAKER

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eCameraShaker interface
    ////////////////////////////////////////////////////////////////

    class eCameraShaker : public Gadget
    {

        /*** Methods ***/

        public:

            eCameraShaker();
            ~eCameraShaker();

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eCameraShaker TypeInfo
    // <kao2.004D59B0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_CAMERASHAKER_ID = 0xCA3E7A11;

    extern TypeInfo E_CAMERASHAKER_TYPEINFO;

}

#endif
