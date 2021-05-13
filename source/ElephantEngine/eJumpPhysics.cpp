#include <ElephantEngine/eJumpPhysics.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eJumpPhysics interface
    // <kao2.004EF350> (constructor)
    // <kao2.004E5BC0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_JUMPPHYSICS_TYPEINFO
    (
        E_JUMPPHYSICS_ID,
        "eJumpPhysics",
        &E_PHYSICS_TYPEINFO,
        []() -> eObject*
        {
            return new eJumpPhysics;
        }
    );

    const TypeInfo* eJumpPhysics::getType() const
    {
        return &E_JUMPPHYSICS_TYPEINFO;
    }

    eJumpPhysics::eJumpPhysics()
    : ePhysics()
    {}

    eJumpPhysics::~eJumpPhysics()
    {}


    ////////////////////////////////////////////////////////////////
    // eJumpPhysics: cloning the object
    ////////////////////////////////////////////////////////////////

    void eJumpPhysics::createFromOtherObject(const eJumpPhysics &other)
    {}

    eJumpPhysics::eJumpPhysics(const eJumpPhysics &other)
    : ePhysics(other)
    {
        createFromOtherObject(other);
    }

    eJumpPhysics& eJumpPhysics::operator = (const eJumpPhysics &other)
    {
        if ((&other) != this)
        {
            ePhysics::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eJumpPhysics::cloneFromMe() const
    {
        return new eJumpPhysics(*this);
    }

}
