#include <ElephantEngine/ePhysics.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // ePhysics interface
    // <kao2.004DE130> (constructor)
    // <kao2.004DE1B0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_PHYSICS_TYPEINFO
    (
        E_PHYSICS_ID,
        "ePhysics",
        &E_BASEPHYSICS_TYPEINFO,
        []() -> eObject*
        {
            return nullptr;
        }
    );

    TypeInfo* ePhysics::getType() const
    {
        return &E_PHYSICS_TYPEINFO;
    }

    ePhysics::ePhysics()
    : eBasePhysics()
    {}

    ePhysics::~ePhysics()
    {}


    ////////////////////////////////////////////////////////////////
    // ePhysics: cloning the object
    ////////////////////////////////////////////////////////////////

    void ePhysics::createFromOtherObject(const ePhysics &other)
    {}

    ePhysics::ePhysics(const ePhysics &other)
    : eBasePhysics(other)
    {
        createFromOtherObject(other);
    }

    ePhysics& ePhysics::operator = (const ePhysics &other)
    {
        if ((&other) != this)
        {
            eBasePhysics::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* ePhysics::cloneFromMe() const
    {
        return nullptr;
    }

}
