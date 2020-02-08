#include <kao2engine/eWaterTarget.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eWaterTarget interface
    // <kao2.00507950> (constructor)
    // <kao2.005079C0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_WATERTARGET_TYPEINFO
    (
        E_WATERTARGET_ID,
        "eWaterTarget",
        &E_EGGTARGET_TYPEINFO,
        []() -> eObject*
        {
            return new eWaterTarget;
        }
    );

    TypeInfo* eWaterTarget::getType() const
    {
        return &E_WATERTARGET_TYPEINFO;
    }

    eWaterTarget::eWaterTarget()
    : eEggTarget()
    {}

    eWaterTarget::~eWaterTarget() {}

}
