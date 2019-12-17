#include <kao2engine/eStrafeCtrl.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eStrafeCtrl interface
    // <kao2.0044C540> (constructor)
    // <kao2.0044C5D0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_STRAFECTRL_TYPEINFO
    (
        E_STRAFECTRL_ID,
        "eStrafeCtrl",
        &E_PATHCTRL_TYPEINFO,
        []() -> eObject*
        {
            return new eStrafeCtrl;
        }
    );

    TypeInfo* eStrafeCtrl::getType()
    {
        return &E_STRAFECTRL_TYPEINFO;
    }

    eStrafeCtrl::eStrafeCtrl()
    : ePathCtrl()
    {}

    eStrafeCtrl::~eStrafeCtrl() {}

}
