#include <ElephantEngine/eSnowboardRampPhysics.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSnowboardRampPhysics interface
    // <kao2.004E7490> (constructor)
    // <kao2.004E7500> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_SNOWBOARDRAMPPHYSICS_TYPEINFO
    (
        E_SNOWBOARDRAMPPHYSICS_ID,
        "eSnowboardRampPhysics",
        &E_SNOWBOARDPHYSICS_TYPEINFO,
        []() -> eObject*
        {
            return new eSnowboardRampPhysics;
        }
    );

    TypeInfo* eSnowboardRampPhysics::getType() const
    {
        return &E_SNOWBOARDRAMPPHYSICS_TYPEINFO;
    }

    eSnowboardRampPhysics::eSnowboardRampPhysics()
    : eSnowboardPhysics()
    {}

    eSnowboardRampPhysics::~eSnowboardRampPhysics()
    {}


    ////////////////////////////////////////////////////////////////
    // eSnowboardRampPhysics: cloning the object
    ////////////////////////////////////////////////////////////////

    void eSnowboardRampPhysics::createFromOtherObject(const eSnowboardRampPhysics &other)
    {}

    eSnowboardRampPhysics::eSnowboardRampPhysics(const eSnowboardRampPhysics &other)
    : eSnowboardPhysics(other)
    {
        createFromOtherObject(other);
    }

    eSnowboardRampPhysics& eSnowboardRampPhysics::operator = (const eSnowboardRampPhysics &other)
    {
        if ((&other) != this)
        {
            eSnowboardPhysics::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eSnowboardRampPhysics::cloneFromMe() const
    {
        return new eSnowboardRampPhysics(*this);
    }

}
