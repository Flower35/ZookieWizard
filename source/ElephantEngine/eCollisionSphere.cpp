#include <ElephantEngine/eCollisionSphere.h>
#include <ElephantBase/Archive.h>

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

    const TypeInfo* eCollisionSphere::getType() const
    {
        return &E_COLLISIONSPHERE_TYPEINFO;
    }

    eCollisionSphere::eCollisionSphere()
    : eCollisionPrimitive()
    {}

    eCollisionSphere::~eCollisionSphere()
    {}


    ////////////////////////////////////////////////////////////////
    // eCollisionSphere: cloning the object
    ////////////////////////////////////////////////////////////////

    void eCollisionSphere::createFromOtherObject(const eCollisionSphere &other)
    {}

    eCollisionSphere::eCollisionSphere(const eCollisionSphere &other)
    : eCollisionPrimitive(other)
    {
        createFromOtherObject(other);
    }

    eCollisionSphere& eCollisionSphere::operator = (const eCollisionSphere &other)
    {
        if ((&other) != this)
        {
            eCollisionPrimitive::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eCollisionSphere::cloneFromMe() const
    {
        return new eCollisionSphere(*this);
    }

}
