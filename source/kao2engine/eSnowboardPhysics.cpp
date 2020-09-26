#include <kao2engine/eSnowboardPhysics.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSnowboardPhysics interface
    // <kao2.004E33D0> (constructor)
    // <kao2.004E3450> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_SNOWBOARDPHYSICS_TYPEINFO
    (
        E_SNOWBOARDPHYSICS_ID,
        "eSnowboardPhysics",
        &E_BASEPHYSICS_TYPEINFO,
        []() -> eObject*
        {
            return new eSnowboardPhysics;
        }
    );

    TypeInfo* eSnowboardPhysics::getType() const
    {
        return &E_SNOWBOARDPHYSICS_TYPEINFO;
    }

    eSnowboardPhysics::eSnowboardPhysics()
    : eBasePhysics()
    {}

    eSnowboardPhysics::~eSnowboardPhysics()
    {}


    ////////////////////////////////////////////////////////////////
    // eSnowboardPhysics: cloning the object
    ////////////////////////////////////////////////////////////////

    void eSnowboardPhysics::createFromOtherObject(const eSnowboardPhysics &other)
    {}

    eSnowboardPhysics::eSnowboardPhysics(const eSnowboardPhysics &other)
    : eBasePhysics(other)
    {
        createFromOtherObject(other);
    }

    eSnowboardPhysics& eSnowboardPhysics::operator = (const eSnowboardPhysics &other)
    {
        if ((&other) != this)
        {
            eBasePhysics::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eSnowboardPhysics::cloneFromMe() const
    {
        return new eSnowboardPhysics(*this);
    }

}
