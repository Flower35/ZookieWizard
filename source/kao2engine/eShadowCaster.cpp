#include <kao2engine/eShadowCaster.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eShadowCaster interface
    // <kao2.00556F01> (constructor)
    // <kao2.00556F90> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_SHADOWCASTER_TYPEINFO
    (
        E_SHADOWCASTER_ID,
        "eShadowCaster",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eShadowCaster;
        }
    );

    TypeInfo* eShadowCaster::getType() const
    {
        return &E_SHADOWCASTER_TYPEINFO;
    }

    eShadowCaster::eShadowCaster()
    : Gadget()
    {}

    eShadowCaster::~eShadowCaster() {}

}
