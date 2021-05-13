#include <ElephantEngine/eDisableGeo.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eDisableGeo interface
    // <kao2.00432F90> (constructor)
    // <kao2.00433000> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_DISABLEGEO_TYPEINFO
    (
        E_DISABLEGEO_ID,
        "eDisableGeo",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eDisableGeo;
        }
    );

    TypeInfo* eDisableGeo::getType() const
    {
        return &E_DISABLEGEO_TYPEINFO;
    }

    eDisableGeo::eDisableGeo()
    : Gadget()
    {}

    eDisableGeo::~eDisableGeo()
    {}


    ////////////////////////////////////////////////////////////////
    // eDisableGeo: cloning the object
    ////////////////////////////////////////////////////////////////

    void eDisableGeo::createFromOtherObject(const eDisableGeo &other)
    {}

    eDisableGeo::eDisableGeo(const eDisableGeo &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eDisableGeo& eDisableGeo::operator = (const eDisableGeo &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eDisableGeo::cloneFromMe() const
    {
        return new eDisableGeo(*this);
    }

}
