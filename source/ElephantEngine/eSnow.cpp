#include <ElephantEngine/eSnow.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSnow interface
    // <kao2.0055FC20> (constructor)
    // <kao2.0055FDB0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_SNOW_TYPEINFO
    (
        E_SNOW_ID,
        "eSnow",
        &E_PARTICLEGEOMETRY_TYPEINFO,
        []() -> eObject*
        {
            return new eSnow;
        }
    );

    TypeInfo* eSnow::getType() const
    {
        return &E_SNOW_TYPEINFO;
    }

    eSnow::eSnow()
    : eParticleGeometry()
    {}

    eSnow::~eSnow()
    {}


    ////////////////////////////////////////////////////////////////
    // eSnow: cloning the object
    ////////////////////////////////////////////////////////////////

    void eSnow::createFromOtherObject(const eSnow &other)
    {}

    eSnow::eSnow(const eSnow &other)
    : eParticleGeometry(other)
    {
        createFromOtherObject(other);
    }

    eSnow& eSnow::operator = (const eSnow &other)
    {
        if ((&other) != this)
        {
            eParticleGeometry::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eSnow::cloneFromMe() const
    {
        return new eSnow(*this);
    }


    ////////////////////////////////////////////////////////////////
    // eSnow: serialization
    // <kao2.00560B30>
    ////////////////////////////////////////////////////////////////
    void eSnow::serialize(Archive &ar)
    {
        eGeometry::serialize(ar);

        /* Calls virtual function [[vptr]+0x94] */
    }

}
