#include <kao2engine/eWhalePhysics.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eWhalePhysics interface
    // <kao2.004FBB90> (constructor)
    // <kao2.004FBCC0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_WHALEPHYSICS_TYPEINFO
    (
        E_WHALEPHYSICS_ID,
        "eWhalePhysics",
        &E_PHYSICS_TYPEINFO,
        []() -> eObject*
        {
            return new eWhalePhysics;
        }
    );

    TypeInfo* eWhalePhysics::getType() const
    {
        return &E_WHALEPHYSICS_TYPEINFO;
    }

    eWhalePhysics::eWhalePhysics()
    : ePhysics()
    {}

    eWhalePhysics::~eWhalePhysics() {}

}
