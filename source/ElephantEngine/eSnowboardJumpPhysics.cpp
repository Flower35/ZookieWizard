#include <ElephantEngine/eSnowboardJumpPhysics.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSnowboardJumpPhysics interface
    // <kao2.004E5A30> (constructor)
    // <kao2.004E5AD0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_SNOWBOARDJUMPPHYSICS_TYPEINFO
    (
        E_SNOWBOARDJUMPPHYSICS_ID,
        "eSnowboardJumpPhysics",
        &E_JUMPPHYSICS_TYPEINFO,
        []() -> eObject*
        {
            return new eSnowboardJumpPhysics;
        }
    );

    TypeInfo* eSnowboardJumpPhysics::getType() const
    {
        return &E_SNOWBOARDJUMPPHYSICS_TYPEINFO;
    }

    eSnowboardJumpPhysics::eSnowboardJumpPhysics()
    : eJumpPhysics()
    {}

    eSnowboardJumpPhysics::~eSnowboardJumpPhysics()
    {}


    ////////////////////////////////////////////////////////////////
    // eSnowboardJumpPhysics: cloning the object
    ////////////////////////////////////////////////////////////////

    void eSnowboardJumpPhysics::createFromOtherObject(const eSnowboardJumpPhysics &other)
    {}

    eSnowboardJumpPhysics::eSnowboardJumpPhysics(const eSnowboardJumpPhysics &other)
    : eJumpPhysics(other)
    {
        createFromOtherObject(other);
    }

    eSnowboardJumpPhysics& eSnowboardJumpPhysics::operator = (const eSnowboardJumpPhysics &other)
    {
        if ((&other) != this)
        {
            eJumpPhysics::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eSnowboardJumpPhysics::cloneFromMe() const
    {
        return new eSnowboardJumpPhysics(*this);
    }

}
