#include <kao2engine/ePhysics.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // ePhysics interface
    // <kao2.004DE130> (constructor)
    // <kao2.004DE1B0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_PHYSICS_TYPEINFO
    (
        E_PHYSICS_ID,
        "ePhysics",
        &E_BASEPHYSICS_TYPEINFO,
        []() -> eObject*
        {
            return nullptr;
        }
    );

    TypeInfo* ePhysics::getType() const
    {
        return &E_PHYSICS_TYPEINFO;
    }

    ePhysics::ePhysics()
    : eBasePhysics()
    {}

    ePhysics::~ePhysics() {}

}
