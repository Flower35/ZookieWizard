#include <kao2engine/eVisibilityCtrl.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eVisibilityCtrl interface
    // <kao2.00430511> (constructor)
    // <kao2.00430590> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_VISIBILITYCTRL_TYPEINFO
    (
        E_VISIBILITYCTRL_ID,
        "eVisibilityCtrl",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eVisibilityCtrl;
        }
    );

    TypeInfo* eVisibilityCtrl::getType() const
    {
        return &E_VISIBILITYCTRL_TYPEINFO;
    }

    eVisibilityCtrl::eVisibilityCtrl()
    : Gadget()
    {}

    eVisibilityCtrl::~eVisibilityCtrl() {}

}
