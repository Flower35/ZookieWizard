#include <kao2engine/eCollisionSphere.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eCollisionSphere interface
    // <kao2.00598EE0> (constructor)
    // <kao2.00598F60> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_COLLISIONSPHERE_TYPEINFO
    (
        E_COLLISIONSPHERE_ID,
        "eCollisionSphere",
        &E_COLLISIONPRIMITIVE_TYPEINFO,
        []() -> eObject*
        {
            return new eCollisionSphere;
        }
    );

    TypeInfo* eCollisionSphere::getType() const
    {
        return &E_COLLISIONSPHERE_TYPEINFO;
    }

    eCollisionSphere::eCollisionSphere()
    : eCollisionPrimitive()
    {}

    eCollisionSphere::~eCollisionSphere() {}

}
