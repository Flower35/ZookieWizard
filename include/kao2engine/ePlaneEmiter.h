#ifndef H_KAO2AR_PLANEEMITER
#define H_KAO2AR_PLANEEMITER

#include <kao2engine/eParticleEmiter.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // ePlaneEmiter interface
    ////////////////////////////////////////////////////////////////

    class ePlaneEmiter : public eParticleEmiter
    {

        /*** Properties ***/

        protected:

            /*[0x021C]*/ float unknown_021C;
            /*[0x0220]*/ float unknown_0220;

        /*** Methods ***/

        public:

            ePlaneEmiter();
            ~ePlaneEmiter();

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // ePlaneEmiter TypeInfo
    // <kao2.00553870> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_PLANEEMITER_ID = 0x0001E003;

    extern TypeInfo E_PLANEEMITER_TYPEINFO;

}

#endif
