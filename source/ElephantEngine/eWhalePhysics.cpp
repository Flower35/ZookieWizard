#include <ElephantEngine/eWhalePhysics.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eWhalePhysics interface
    // <kao2.004FBB90> (constructor)
    // <kao2.004FBCC0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_WHALEPHYSICS_TYPEINFO
    (
        E_WHALEPHYSICS_ID,
        "eWhalePhysics",
        &E_PHYSICS_TYPEINFO,
        []() -> eObject*
        {
            return new eWhalePhysics;
        }
    );

    const TypeInfo* eWhalePhysics::getType() const
    {
        return &E_WHALEPHYSICS_TYPEINFO;
    }

    eWhalePhysics::eWhalePhysics()
    : ePhysics()
    {}

    eWhalePhysics::~eWhalePhysics()
    {}


    ////////////////////////////////////////////////////////////////
    // eWhalePhysics: cloning the object
    ////////////////////////////////////////////////////////////////

    void eWhalePhysics::createFromOtherObject(const eWhalePhysics &other)
    {}

    eWhalePhysics::eWhalePhysics(const eWhalePhysics &other)
    : ePhysics(other)
    {
        createFromOtherObject(other);
    }

    eWhalePhysics& eWhalePhysics::operator = (const eWhalePhysics &other)
    {
        if ((&other) != this)
        {
            ePhysics::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eWhalePhysics::cloneFromMe() const
    {
        return new eWhalePhysics(*this);
    }

}
