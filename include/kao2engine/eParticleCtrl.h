#ifndef H_KAO2AR_PARTICLECTRL
#define H_KAO2AR_PARTICLECTRL

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eParticleCtrl interface
    // <kao2.005CE9A0> (vptr)
    ////////////////////////////////////////////////////////////////

    class eParticleCtrl : public Gadget
    {

        /*** Methods ***/

        public:

            eParticleCtrl();
            ~eParticleCtrl();

            void serialize(Archive &ar) override;
            TypeInfo* getType() override;

            eString getDefaultGadgetName() override;
    };


    ////////////////////////////////////////////////////////////////
    // eParticleCtrl TypeInfo
    // <kao2.00430610> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_PARTICLECTRL_ID = 0xFACE3020;

    extern TypeInfo E_PARTICLECTRL_TYPEINFO;

}

#endif
