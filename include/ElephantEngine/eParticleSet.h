#ifndef H_KAO2AR_PARTICLESET
#define H_KAO2AR_PARTICLESET

#include <ElephantEngine/eParticleGeometry.h>

namespace ZookieWizard
{
    class eOscilationCtrl;
    class ePosCtrl;
    class eRotCtrl;
    class eColorCtrl;


    ////////////////////////////////////////////////////////////////
    // Unknown structure
    ////////////////////////////////////////////////////////////////

    struct eParticleSetBase
    {
        /*** Properties ***/

        public:

            /*[0x00]*/ float unknown_00;
            /*[0x04]*/ float unknown_04;
            /*[0x08]*/ float unknown_08;
            /*[0x0C]*/ float unknown_0C;
            /*[0x10]*/ float unknown_10;
            /*[0x14]*/ float unknown_14;
            /*[0x18]*/ float unknown_18;
            /*[0x1C]*/ float unknown_1C;
            /*(...)*/
            /*[0x24]*/ float unknown_24;
            /*[0x28]*/ float unknown_28;
            /*[0x2C]*/ float unknown_2C;
            /*[0x30]*/ float unknown_30;
            /*[0x34]*/ float unknown_34;
            /*[0x38]*/ float unknown_38;
            /*[0x3C]*/ float unknown_3C;

        /*** Methods ***/

        public:

            void serialize(Archive &ar);
    };


    ////////////////////////////////////////////////////////////////
    // eParticleSet interface
    // <kao2.005D6A98> (vptr)
    ////////////////////////////////////////////////////////////////

    class eParticleSet : public eParticleGeometry
    {
        /*** Properties ***/

        protected:

            /*[0x00C8]*/ int32_t groupA_Count;
            /*[0x00CC]*/ int32_t groupA_MaxLength;
            /*[0x00D0]*/ eParticleSetBase* groupA;

            /*[0x00D4]*/ ePosCtrl* unknown_00D4;
            /*[0x00D8]*/ eRotCtrl* unknown_00D8;
            /*[0x00DC]*/ eColorCtrl* unknown_00DC;
            /*[0x00E0]*/ eOscilationCtrl* unknown_00E0;

            /*[0x00E4]*/ float unknown_00E4;
            /*[0x00E8]*/ int32_t unknown_00E8;
            /*[0x00EC]*/ int32_t unknown_00EC;
            /*[0x00F0]*/ int32_t unknown_00F0;
            /*[0x00F4]*/ float unknown_00F4;
            /*[0x00F8]*/ float unknown_00F8;
            /*[0x00FC]*/ float unknown_00FC;
            /*[0x0100]*/ float unknown_0100;
            /*[0x0104]*/ float unknown_0104;
            /*[0x0108]*/ int32_t unknown_0108;
            /*[0x010C]*/ int32_t unknown_010C;
            /*[0x0110]*/ float unknown_0110;
            /*[0x0114]*/ int32_t unknown_0114;

            /*[0x0118]*/ uint8_t unknown_0118;
            /*[0x0119]*/ uint8_t unknown_0119;
            /*[0x011A]*/ uint8_t unknown_011A;
            /*[0x011B]*/ uint8_t unknown_011B;
            /*[0x011C]*/ uint8_t unknown_011C;
            /*[0x011D]*/ uint8_t unknown_011D;
            /*[0x011E]*/ uint8_t unknown_011E;

            /*[0x0120]*/ float unknown_0120;
            /*[0x0124]*/ float unknown_0124;
            /*[0x0128]*/ float unknown_0128;
            /*[0x012C]*/ float unknown_012C;
            /*[0x0130]*/ uint8_t unknown_0130;
            /*[0x0131]*/ uint8_t unknown_0131;

        /*** Methods ***/

        public:

            eParticleSet();
            ~eParticleSet();

        private:

            void createFromOtherObject(const eParticleSet &other);

        public:

            eParticleSet(const eParticleSet &other);
            eParticleSet& operator = (const eParticleSet &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
            void serialize(Archive &ar) override;
    };


    ////////////////////////////////////////////////////////////////
    // eParticleSet TypeInfo
    // <kao2.00559930> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_PARTICLESET_ID = 0x12ABF012;

    extern TypeInfo E_PARTICLESET_TYPEINFO;

}

#endif
