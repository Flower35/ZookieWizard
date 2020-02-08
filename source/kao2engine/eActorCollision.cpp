#include <kao2engine/eActorCollision.h>
#include <kao2ar/Archive.h>

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

    TypeInfo* eActorCollision::getType() const
    {
        return &E_ACTORCOLLISION_TYPEINFO;
    }

    eActorCollision::eActorCollision()
    : Gadget()
    {}

    eActorCollision::~eActorCollision() {}

}
