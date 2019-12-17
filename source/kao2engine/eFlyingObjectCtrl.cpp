#include <kao2engine/eFlyingObjectCtrl.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eFlyingObjectCtrl interface
    // <kao2.004FE0B0> (constructor)
    // <kao2.004FE120> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_FLYINGOBJECTCTRL_TYPEINFO
    (
        E_FLYINGOBJECTCTRL_ID,
        "eFlyingObjectCtrl",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eFlyingObjectCtrl;
        }
    );

    TypeInfo* eFlyingObjectCtrl::getType()
    {
        return &E_FLYINGOBJECTCTRL_TYPEINFO;
    }

    eFlyingObjectCtrl::eFlyingObjectCtrl()
    : Gadget()
    {}

    eFlyingObjectCtrl::~eFlyingObjectCtrl() {}

}
