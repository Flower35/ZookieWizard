#include <kao2engine/eIcePhysics.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eIcePhysics interface
    // <kao2.004DF690> (constructor)
    // <kao2.004DF700> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_ICEPHYSICS_TYPEINFO
    (
        E_ICEPHYSICS_ID,
        "eIcePhysics",
        &E_PHYSICS_TYPEINFO,
        []() -> eObject*
        {
            return new eIcePhysics;
        }
    );

    TypeInfo* eIcePhysics::getType() const
    {
        return &E_ICEPHYSICS_TYPEINFO;
    }

    eIcePhysics::eIcePhysics()
    : ePhysics()
    {}

    eIcePhysics::~eIcePhysics() {}

}
