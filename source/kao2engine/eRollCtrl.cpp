#include <kao2engine/eRollCtrl.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eRollCtrl interface
    // <kao2.0044B8F3> (constructor)
    // <kao2.0044B980> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_ROLLCTRL_TYPEINFO
    (
        E_ROLLCTRL_ID,
        "eRollCtrl",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eRollCtrl;
        }
    );

    TypeInfo* eRollCtrl::getType()
    {
        return &E_ROLLCTRL_TYPEINFO;
    }

    eRollCtrl::eRollCtrl()
    : Gadget()
    {}

    eRollCtrl::~eRollCtrl() {}

}
