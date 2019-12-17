#include <kao2engine/eFlyingTarget.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eFlyingTarget interface
    // <kao2.00500BD0> (constructor)
    // <kao2.00500D60> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_FLYINGTARGET_TYPEINFO
    (
        E_FLYINGTARGET_ID,
        "eFlyingTarget",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eFlyingTarget;
        }
    );

    TypeInfo* eFlyingTarget::getType()
    {
        return &E_FLYINGTARGET_TYPEINFO;
    }

    eFlyingTarget::eFlyingTarget()
    : Gadget()
    {}

    eFlyingTarget::~eFlyingTarget() {}

}
