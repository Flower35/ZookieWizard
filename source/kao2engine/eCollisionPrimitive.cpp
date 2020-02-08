#include <kao2engine/eCollisionPrimitive.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eCollisionPrimitive interface
    // <kao2.00598940> (constructor)
    // <kao2.005989B0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_COLLISIONPRIMITIVE_TYPEINFO
    (
        E_COLLISIONPRIMITIVE_ID,
        "eCollisionPrimitive",
        &E_COLLISION_TYPEINFO,
        []() -> eObject*
        {
            return nullptr;
        }
    );

    TypeInfo* eCollisionPrimitive::getType() const
    {
        return &E_COLLISIONPRIMITIVE_TYPEINFO;
    }

    eCollisionPrimitive::eCollisionPrimitive()
    : eCollision()
    {}

    eCollisionPrimitive::~eCollisionPrimitive() {}

}
