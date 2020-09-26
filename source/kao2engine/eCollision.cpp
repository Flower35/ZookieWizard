#include <kao2engine/eCollision.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eCollision interface
    // <kao2.????????> (constructor)
    // <kao2.????????> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_COLLISION_TYPEINFO
    (
        E_COLLISION_ID,
        "eCollision",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return nullptr;
        }
    );

    TypeInfo* eCollision::getType() const
    {
        return &E_COLLISION_TYPEINFO;
    }

    eCollision::eCollision()
    : Gadget()
    {}

    eCollision::~eCollision()
    {}


    ////////////////////////////////////////////////////////////////
    // eCollision: cloning the object
    ////////////////////////////////////////////////////////////////

    void eCollision::createFromOtherObject(const eCollision &other)
    {}

    eCollision::eCollision(const eCollision &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eCollision& eCollision::operator = (const eCollision &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eCollision::cloneFromMe() const
    {
        return nullptr;
    }

}
