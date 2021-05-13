#ifndef H_KAO2AR_PARTICLECTRL
#define H_KAO2AR_PARTICLECTRL

#include <ElephantEngine/Gadget.h>

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

        private:

            void createFromOtherObject(const eParticleCtrl &other);

        public:

            eParticleCtrl(const eParticleCtrl &other);
            eParticleCtrl& operator = (const eParticleCtrl &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
            void serialize(Archive &ar) override;

            /* << Gadget >> */

            eString getDefaultGadgetName() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eParticleCtrl TypeInfo
    // <kao2.004305E0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_PARTICLECTRL_ID = 0xFACE3020;

    extern TypeInfo E_PARTICLECTRL_TYPEINFO;

}

#endif
