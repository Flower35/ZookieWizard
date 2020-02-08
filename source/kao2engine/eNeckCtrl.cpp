#include <kao2engine/eNeckCtrl.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eNeckCtrl interface
    // <kao2.00437200> (constructor)
    // <kao2.004372A0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_NECKCTRL_TYPEINFO
    (
        E_NECKCTRL_ID,
        "eNeckCtrl",
        &E_LOOKATCTRL_TYPEINFO,
        []() -> eObject*
        {
            return new eNeckCtrl;
        }
    );

    TypeInfo* eNeckCtrl::getType() const
    {
        return &E_NECKCTRL_TYPEINFO;
    }

    eNeckCtrl::eNeckCtrl()
    : eLookAtCtrl()
    {}

    eNeckCtrl::~eNeckCtrl() {}

}
