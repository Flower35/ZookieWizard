#ifndef H_KAO2AR_PARTICLEEMITER
#define H_KAO2AR_PARTICLEEMITER

#include <ElephantEngine/eGroup.h>

#include <ElephantEngine/eGlobalCtrl.h>

namespace ZookieWizard
{
    class eSndEmiter;

    ////////////////////////////////////////////////////////////////
    // eParticleEmiter interface
    // <kao2.005D6428> (vptr)
    ////////////////////////////////////////////////////////////////

    class eParticleEmiter : public eGroup
    {
        /*** Properties ***/

        protected:

            /*[0x0048]*/ float unknown_0048;
            /*[0x004C]*/ float unknown_004C;
            /*[0x0050]*/ float unknown_0050;
            /*[0x0054]*/ float unknown_0054;
            /*[0x0058]*/ float unknown_0058;
            /*[0x005C]*/ float unknown_005C;
            /*[0x0060]*/ float unknown_0060;

            /*(...)*/

            /*[0x0070-0x01D8]*/ eGlobalCtrl unknown_0070;

            /*[0x01DC]*/ float unknown_01DC;
            /*[0x01E0]*/ float unknown_01E0;
            /*[0x01E4]*/ float unknown_01E4;
            /*[0x01E8]*/ float unknown_01E8;
            /*(...)*/
            /*[0x01F0]*/ uint8_t unknown_01F0;
            /*[0x01F1]*/ uint8_t unknown_01F1;
            /*[0x01F4]*/ float unknown_01F4;
            /*[0x01F8]*/ float unknown_01F8;
            /*[0x01FC]*/ float unknown_01FC;
            /*[0x0200]*/ float unknown_0200;
            /*[0x0204]*/ int32_t unknown_0204;

            /*(...)*/

            /*[0x0210]*/ eString soundEmiterFileName;
            /*[0x0214]*/ eSndEmiter* soundEmiter;

            /*[0x0218]*/ uint8_t unknown_0218;

        /*** Methods ***/

        public:

            eParticleEmiter();
            ~eParticleEmiter();

        private:

            void createFromOtherObject(const eParticleEmiter &other);

        public:

            eParticleEmiter(const eParticleEmiter &other);
            eParticleEmiter& operator = (const eParticleEmiter &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
            void serialize(Archive &ar) override;
    };


    ////////////////////////////////////////////////////////////////
    // eParticleEmiter TypeInfo
    // <kao2.00553620> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_PARTICLEEMITER_ID = 0x0001E000;

    extern TypeInfo E_PARTICLEEMITER_TYPEINFO;

}

#endif
