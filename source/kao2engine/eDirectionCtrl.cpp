#include <kao2engine/eDirectionCtrl.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eDirectionCtrl interface
    // <kao2.0042F7D1> (constructor)
    // <kao2.0042F850> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_DIRECTIONCTRL_TYPEINFO
    (
        E_DIRECTIONCTRL_ID,
        "eDirectionCtrl",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eDirectionCtrl;
        }
    );

    TypeInfo* eDirectionCtrl::getType() const
    {
        return &E_DIRECTIONCTRL_TYPEINFO;
    }

    eDirectionCtrl::eDirectionCtrl()
    : Gadget()
    {}

    eDirectionCtrl::~eDirectionCtrl() {}


    ////////////////////////////////////////////////////////////////
    // eDirectionCtrl: get default name (scripting shenanigans)
    ////////////////////////////////////////////////////////////////
    eString eDirectionCtrl::getDefaultGadgetName() const
    {
        return "dirCtrl";
    }

}
