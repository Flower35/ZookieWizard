#ifndef H_KAO2AR_LINEEMITER
#define H_KAO2AR_LINEEMITER

#include <kao2engine/eParticleEmiter.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eLineEmiter interface
    ////////////////////////////////////////////////////////////////

    class eLineEmiter : public eParticleEmiter
    {

        /*** Properties ***/

        protected:

            /*[0x021C]*/ float unknown_021C;
            /*[0x0220]*/ float unknown_0220;
            /*[0x0224]*/ float unknown_0224;
            /*[0x0228]*/ float unknown_0228;
            /*[0x022C]*/ float unknown_022C;
            /*[0x0230]*/ float unknown_0230;
            /*[0x0234]*/ float unknown_0234;

        /*** Methods ***/

        public:

            eLineEmiter();
            ~eLineEmiter();

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eLineEmiter TypeInfo
    // <kao2.005537A0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_LINEEMITER_ID = 0x0001E002;

    extern TypeInfo E_LINEEMITER_TYPEINFO;

}

#endif
