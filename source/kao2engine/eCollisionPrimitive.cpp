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

    eCollisionPrimitive::~eCollisionPrimitive()
    {}


    ////////////////////////////////////////////////////////////////
    // eCollisionPrimitive: cloning the object
    ////////////////////////////////////////////////////////////////

    void eCollisionPrimitive::createFromOtherObject(const eCollisionPrimitive &other)
    {}

    eCollisionPrimitive::eCollisionPrimitive(const eCollisionPrimitive &other)
    : eCollision(other)
    {
        createFromOtherObject(other);
    }

    eCollisionPrimitive& eCollisionPrimitive::operator = (const eCollisionPrimitive &other)
    {
        if ((&other) != this)
        {
            eCollision::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eCollisionPrimitive::cloneFromMe() const
    {
        return nullptr;
    }

}
