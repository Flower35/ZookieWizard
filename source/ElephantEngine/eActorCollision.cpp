#include <ElephantEngine/eActorCollision.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eActorCollision interface
    // <kao2.00599F12> (constructor)
    // <kao2.00576C60> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_ACTORCOLLISION_TYPEINFO
    (
        E_ACTORCOLLISION_ID,
        "eActorCollision",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eActorCollision;
        }
    );

    const TypeInfo* eActorCollision::getType() const
    {
        return &E_ACTORCOLLISION_TYPEINFO;
    }

    eActorCollision::eActorCollision()
    : Gadget()
    {}

    eActorCollision::~eActorCollision()
    {}


    ////////////////////////////////////////////////////////////////
    // eActorCollision: cloning the object
    ////////////////////////////////////////////////////////////////

    void eActorCollision::createFromOtherObject(const eActorCollision &other)
    {}

    eActorCollision::eActorCollision(const eActorCollision &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eActorCollision& eActorCollision::operator = (const eActorCollision &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eActorCollision::cloneFromMe() const
    {
        return new eActorCollision(*this);
    }

}
