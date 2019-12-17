#include <kao2engine/eGloveTarget.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eGloveTarget interface
    // <kao2.005045A0> (constructor)
    // <kao2.00504610> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_GLOVETARGET_TYPEINFO
    (
        E_GLOVETARGET_ID,
        "eGloveTarget",
        &E_EGGTARGET_TYPEINFO,
        []() -> eObject*
        {
            return new eGloveTarget;
        }
    );

    TypeInfo* eGloveTarget::getType()
    {
        return &E_GLOVETARGET_TYPEINFO;
    }

    eGloveTarget::eGloveTarget()
    : eEggTarget()
    {}

    eGloveTarget::~eGloveTarget() {}

}
