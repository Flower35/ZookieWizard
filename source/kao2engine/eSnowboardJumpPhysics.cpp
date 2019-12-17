#include <kao2engine/eSnowboardJumpPhysics.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSnowboardJumpPhysics interface
    // <kao2.004E5A30> (constructor)
    // <kao2.004E5AD0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_SNOWBOARDJUMPPHYSICS_TYPEINFO
    (
        E_SNOWBOARDJUMPPHYSICS_ID,
        "eSnowboardJumpPhysics",
        &E_JUMPPHYSICS_TYPEINFO,
        []() -> eObject*
        {
            return new eSnowboardJumpPhysics;
        }
    );

    TypeInfo* eSnowboardJumpPhysics::getType()
    {
        return &E_SNOWBOARDJUMPPHYSICS_TYPEINFO;
    }

    eSnowboardJumpPhysics::eSnowboardJumpPhysics()
    : eJumpPhysics()
    {}

    eSnowboardJumpPhysics::~eSnowboardJumpPhysics() {}

}
