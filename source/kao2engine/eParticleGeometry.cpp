#include <kao2engine/eParticleGeometry.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eParticleGeometry interface
    // <kao2.005618F0> (constructor)
    // <kao2.005583B0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_PARTICLEGEOMETRY_TYPEINFO
    (
        E_PARTICLEGEOMETRY_ID,
        "eParticleGeometry",
        &E_GEOMETRY_TYPEINFO,
        []() -> eObject*
        {
            return new eParticleGeometry;
        }
    );

    TypeInfo* eParticleGeometry::getType()
    {
        return &E_PARTICLEGEOMETRY_TYPEINFO;
    }

    eParticleGeometry::eParticleGeometry()
    : eGeometry()
    {
        /*[0xC0]*/ unknown_C0 = 0;
        /*[0x58]*/ unknown_58 = 0;
        /*[0xBC]*/ unknown_BC = 0;

        /*[0x00C4]*/ unknown_C4 = (-1);
    }

    eParticleGeometry::~eParticleGeometry() {}

}
