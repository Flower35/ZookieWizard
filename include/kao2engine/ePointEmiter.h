#ifndef H_KAO2AR_POINTEMITER
#define H_KAO2AR_POINTEMITER

#include <kao2engine/eParticleEmiter.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // ePointEmiter interface
    ////////////////////////////////////////////////////////////////

    class ePointEmiter : public eParticleEmiter
    {
        /*** Methods ***/

        public:

            ePointEmiter();
            ~ePointEmiter();

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // ePointEmiter TypeInfo
    // <kao2.005536D0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_POINTEMITER_ID = 0x0001E001;

    extern TypeInfo E_POINTEMITER_TYPEINFO;

}

#endif
