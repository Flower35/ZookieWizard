#include <kao2engine/eTurnCollisionOff.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eTurnCollisionOff interface
    // <kao2.0059A1E1> (constructor)
    // <kao2.0059A250> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_TURNCOLLISIONOFF_TYPEINFO
    (
        E_TURNCOLLISIONOFF_ID,
        "eTurnCollisionOff",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eTurnCollisionOff;
        }
    );

    TypeInfo* eTurnCollisionOff::getType() const
    {
        return &E_TURNCOLLISIONOFF_TYPEINFO;
    }

    eTurnCollisionOff::eTurnCollisionOff()
    : Gadget()
    {}

    eTurnCollisionOff::~eTurnCollisionOff()
    {}


    ////////////////////////////////////////////////////////////////
    // eTurnCollisionOff: cloning the object
    ////////////////////////////////////////////////////////////////

    void eTurnCollisionOff::createFromOtherObject(const eTurnCollisionOff &other)
    {}

    eTurnCollisionOff::eTurnCollisionOff(const eTurnCollisionOff &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eTurnCollisionOff& eTurnCollisionOff::operator = (const eTurnCollisionOff &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eTurnCollisionOff::cloneFromMe() const
    {
        return new eTurnCollisionOff(*this);
    }

}
