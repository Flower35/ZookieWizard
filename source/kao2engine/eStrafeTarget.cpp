#include <kao2engine/eStrafeTarget.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eStrafeTarget interface
    // <kao2.004E8C40> (constructor)
    // <kao2.004E8CC0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_STRAFETARGET_TYPEINFO
    (
        E_STRAFETARGET_ID,
        "eStrafeTarget",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eStrafeTarget;
        }
    );

    TypeInfo* eStrafeTarget::getType() const
    {
        return &E_STRAFETARGET_TYPEINFO;
    }

    eStrafeTarget::eStrafeTarget()
    : Gadget()
    {}

    eStrafeTarget::~eStrafeTarget() {}

}
