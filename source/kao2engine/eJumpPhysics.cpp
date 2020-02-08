#include <kao2engine/eJumpPhysics.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eJumpPhysics interface
    // <kao2.004EF350> (constructor)
    // <kao2.004E5BC0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_JUMPPHYSICS_TYPEINFO
    (
        E_JUMPPHYSICS_ID,
        "eJumpPhysics",
        &E_PHYSICS_TYPEINFO,
        []() -> eObject*
        {
            return new eJumpPhysics;
        }
    );

    TypeInfo* eJumpPhysics::getType() const
    {
        return &E_JUMPPHYSICS_TYPEINFO;
    }

    eJumpPhysics::eJumpPhysics()
    : ePhysics()
    {}

    eJumpPhysics::~eJumpPhysics() {}

}
