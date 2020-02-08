#include <kao2engine/eWalkingPhysics.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eWalkingPhysics interface
    // <kao2.004E9140> (constructor)
    // <kao2.004E91B0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_WALKINGPHYSICS_TYPEINFO
    (
        E_WALKINGPHYSICS_ID,
        "eWalkingPhysics",
        &E_PHYSICS_TYPEINFO,
        []() -> eObject*
        {
            return new eWalkingPhysics;
        }
    );

    TypeInfo* eWalkingPhysics::getType() const
    {
        return &E_WALKINGPHYSICS_TYPEINFO;
    }

    eWalkingPhysics::eWalkingPhysics()
    : ePhysics()
    {}

    eWalkingPhysics::~eWalkingPhysics() {}

}
