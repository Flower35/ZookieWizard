#include <kao2engine/eWaterPhysics.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eWaterPhysics interface
    // <kao2.004F69F0> (constructor)
    // <kao2.004F6D60> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_WATERPHYSICS_TYPEINFO
    (
        E_WATERPHYSICS_ID,
        "eWaterPhysics",
        &E_PHYSICS_TYPEINFO,
        []() -> eObject*
        {
            return new eWaterPhysics;
        }
    );

    TypeInfo* eWaterPhysics::getType()
    {
        return &E_WATERPHYSICS_TYPEINFO;
    }

    eWaterPhysics::eWaterPhysics()
    : ePhysics()
    {}

    eWaterPhysics::~eWaterPhysics() {}

}
