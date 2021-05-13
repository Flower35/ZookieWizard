#include <ElephantEngine/eWalkingPhysics.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eWalkingPhysics interface
    // <kao2.004E9140> (constructor)
    // <kao2.004E91B0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_WALKINGPHYSICS_TYPEINFO
    (
        E_WALKINGPHYSICS_ID,
        "eWalkingPhysics",
        &E_PHYSICS_TYPEINFO,
        []() -> eObject*
        {
            return new eWalkingPhysics;
        }
    );

    TypeInfo* eWalkingPhysics::getType() const
    {
        return &E_WALKINGPHYSICS_TYPEINFO;
    }

    eWalkingPhysics::eWalkingPhysics()
    : ePhysics()
    {}

    eWalkingPhysics::~eWalkingPhysics()
    {}


    ////////////////////////////////////////////////////////////////
    // eWalkingPhysics: cloning the object
    ////////////////////////////////////////////////////////////////

    void eWalkingPhysics::createFromOtherObject(const eWalkingPhysics &other)
    {}

    eWalkingPhysics::eWalkingPhysics(const eWalkingPhysics &other)
    : ePhysics(other)
    {
        createFromOtherObject(other);
    }

    eWalkingPhysics& eWalkingPhysics::operator = (const eWalkingPhysics &other)
    {
        if ((&other) != this)
        {
            ePhysics::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eWalkingPhysics::cloneFromMe() const
    {
        return new eWalkingPhysics(*this);
    }

}
