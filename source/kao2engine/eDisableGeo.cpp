#include <kao2engine/eDisableGeo.h>
#include <kao2ar/Archive.h>

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

    TypeInfo* eDisableGeo::getType()
    {
        return &E_DISABLEGEO_TYPEINFO;
    }

    eDisableGeo::eDisableGeo()
    : Gadget()
    {}

    eDisableGeo::~eDisableGeo() {}

}
