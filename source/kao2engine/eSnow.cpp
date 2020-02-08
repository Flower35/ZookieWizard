#include <kao2engine/eSnow.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSnow interface
    // <kao2.0055FC20> (constructor)
    // <kao2.0055FDB0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_SNOW_TYPEINFO
    (
        E_SNOW_ID,
        "eSnow",
        &E_PARTICLEGEOMETRY_TYPEINFO,
        []() -> eObject*
        {
            return new eSnow;
        }
    );

    TypeInfo* eSnow::getType() const
    {
        return &E_SNOW_TYPEINFO;
    }

    eSnow::eSnow()
    : eParticleGeometry()
    {}

    eSnow::~eSnow() {}


    ////////////////////////////////////////////////////////////////
    // eSnow serialization
    // <kao2.00560B30>
    ////////////////////////////////////////////////////////////////
    void eSnow::serialize(Archive &ar)
    {
        eGeometry::serialize(ar);

        /* Calls virtual function [[vptr]+0x94] */
    }

}
