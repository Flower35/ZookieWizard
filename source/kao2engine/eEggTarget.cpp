#include <kao2engine/eEggTarget.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eEggTarget interface
    // <kao2.00502740> (constructor)
    // <kao2.005027F0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_EGGTARGET_TYPEINFO
    (
        E_EGGTARGET_ID,
        "eEggTarget",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eEggTarget;
        }
    );

    TypeInfo* eEggTarget::getType() const
    {
        return &E_EGGTARGET_TYPEINFO;
    }

    eEggTarget::eEggTarget()
    : Gadget()
    {}

    eEggTarget::~eEggTarget() {}

}
