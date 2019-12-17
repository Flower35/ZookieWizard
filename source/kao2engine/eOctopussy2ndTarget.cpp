#include <kao2engine/eOctopussy2ndTarget.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eOctopussy2ndTarget interface
    // <kao2.00517001> (constructor)
    // <kao2.005171F0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_OCTOPUSSY2NDTARGET_TYPEINFO
    (
        E_OCTOPUSSY2NDTARGET_ID,
        "eOctopussy2ndTarget",
        &E_SECONDCAMERATARGET_TYPEINFO,
        []() -> eObject*
        {
            return new eOctopussy2ndTarget;
        }
    );

    TypeInfo* eOctopussy2ndTarget::getType()
    {
        return &E_OCTOPUSSY2NDTARGET_TYPEINFO;
    }

    eOctopussy2ndTarget::eOctopussy2ndTarget()
    : eSecondCameraTarget()
    {}

    eOctopussy2ndTarget::~eOctopussy2ndTarget() {}

}
