#ifndef H_KAO2AR_PARTICLEGEOMETRY
#define H_KAO2AR_PARTICLEGEOMETRY

#include <kao2engine/eGeometry.h>

#include <kao2engine/eGeoArray.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eParticleGeometry interface
    ////////////////////////////////////////////////////////////////

    class eParticleGeometry : public eGeometry
    {

        /*** Properties ***/

        protected:

            /*[0x58]*/ int32_t unknown_58;

            /*[0x5C-0x68]*/ eGeoArray<ePoint4> unknown_5C;
            /*[0x6C-0x78]*/ eGeoArray<ePoint2> unknown_6C;
            /*[0x7C-0x88]*/ eGeoArray<ePoint3> unknown_7C;
            /*[0x8C-0x98]*/ eGeoArray<ePoint4> unknown_8C;
            /*[0x9C-0xA8]*/ eGeoArray<ePoint4> unknown_9C;
            /*[0xAC-0xB8]*/ eGeoArray<ePoint4> unknown_AC;

            /*[0xBC]*/ int32_t unknown_BC;
            /*[0xC0]*/ int32_t unknown_C0;
            /*[0xC4]*/ int32_t unknown_C4;

        /*** Methods ***/

        public:

            eParticleGeometry();
            ~eParticleGeometry();

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eParticleGeometry TypeInfo
    // <kao2.005624A0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_PARTICLEGEOMETRY_ID = 0x0333A7FD;

    extern TypeInfo E_PARTICLEGEOMETRY_TYPEINFO;

}

#endif
