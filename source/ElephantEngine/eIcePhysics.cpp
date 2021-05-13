#include <ElephantEngine/eIcePhysics.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eIcePhysics interface
    // <kao2.004DF690> (constructor)
    // <kao2.004DF700> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_ICEPHYSICS_TYPEINFO
    (
        E_ICEPHYSICS_ID,
        "eIcePhysics",
        &E_PHYSICS_TYPEINFO,
        []() -> eObject*
        {
            return new eIcePhysics;
        }
    );

    TypeInfo* eIcePhysics::getType() const
    {
        return &E_ICEPHYSICS_TYPEINFO;
    }

    eIcePhysics::eIcePhysics()
    : ePhysics()
    {}

    eIcePhysics::~eIcePhysics()
    {}


    ////////////////////////////////////////////////////////////////
    // eIcePhysics: cloning the object
    ////////////////////////////////////////////////////////////////

    void eIcePhysics::createFromOtherObject(const eIcePhysics &other)
    {}

    eIcePhysics::eIcePhysics(const eIcePhysics &other)
    : ePhysics(other)
    {
        createFromOtherObject(other);
    }

    eIcePhysics& eIcePhysics::operator = (const eIcePhysics &other)
    {
        if ((&other) != this)
        {
            ePhysics::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eIcePhysics::cloneFromMe() const
    {
        return new eIcePhysics(*this);
    }

}
