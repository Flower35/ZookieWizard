#include <ElephantEngine/eWaterPhysics.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eWaterPhysics interface
    // <kao2.004F69F0> (constructor)
    // <kao2.004F6D60> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_WATERPHYSICS_TYPEINFO
    (
        E_WATERPHYSICS_ID,
        "eWaterPhysics",
        &E_PHYSICS_TYPEINFO,
        []() -> eObject*
        {
            return new eWaterPhysics;
        }
    );

    TypeInfo* eWaterPhysics::getType() const
    {
        return &E_WATERPHYSICS_TYPEINFO;
    }

    eWaterPhysics::eWaterPhysics()
    : ePhysics()
    {}

    eWaterPhysics::~eWaterPhysics()
    {}


    ////////////////////////////////////////////////////////////////
    // eWaterPhysics: cloning the object
    ////////////////////////////////////////////////////////////////

    void eWaterPhysics::createFromOtherObject(const eWaterPhysics &other)
    {}

    eWaterPhysics::eWaterPhysics(const eWaterPhysics &other)
    : ePhysics(other)
    {
        createFromOtherObject(other);
    }

    eWaterPhysics& eWaterPhysics::operator = (const eWaterPhysics &other)
    {
        if ((&other) != this)
        {
            ePhysics::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eWaterPhysics::cloneFromMe() const
    {
        return new eWaterPhysics(*this);
    }

}
