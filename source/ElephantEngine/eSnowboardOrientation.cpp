#include <ElephantEngine/eSnowboardOrientation.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSnowboardOrientation interface
    // <kao2.004E1176> (constructor)
    // <kao2.004E1240> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_SNOWBOARDORIENTATION_TYPEINFO
    (
        E_SNOWBOARDORIENTATION_ID,
        "eSnowboardOrientation",
        &E_BASEPHYSICS_TYPEINFO,
        []() -> eObject*
        {
            return new eSnowboardOrientation;
        }
    );

    const TypeInfo* eSnowboardOrientation::getType() const
    {
        return &E_SNOWBOARDORIENTATION_TYPEINFO;
    }

    eSnowboardOrientation::eSnowboardOrientation()
    : eBasePhysics()
    {}

    eSnowboardOrientation::~eSnowboardOrientation()
    {}


    ////////////////////////////////////////////////////////////////
    // eSnowboardOrientation: cloning the object
    ////////////////////////////////////////////////////////////////

    void eSnowboardOrientation::createFromOtherObject(const eSnowboardOrientation &other)
    {}

    eSnowboardOrientation::eSnowboardOrientation(const eSnowboardOrientation &other)
    : eBasePhysics(other)
    {
        createFromOtherObject(other);
    }

    eSnowboardOrientation& eSnowboardOrientation::operator = (const eSnowboardOrientation &other)
    {
        if ((&other) != this)
        {
            eBasePhysics::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eSnowboardOrientation::cloneFromMe() const
    {
        return new eSnowboardOrientation(*this);
    }

}
