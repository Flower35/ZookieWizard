#include <kao2engine/eCameraFOVCtrl.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eCameraFOVCtrl interface
    // <kao2.004D5BC1> (constructor)
    // <kao2.004D5D20> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_CAMERAFOVCTRL_TYPEINFO
    (
        E_CAMERAFOVCTRL_ID,
        "eCameraFOVCtrl",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eCameraFOVCtrl;
        }
    );

    TypeInfo* eCameraFOVCtrl::getType() const
    {
        return &E_CAMERAFOVCTRL_TYPEINFO;
    }

    eCameraFOVCtrl::eCameraFOVCtrl()
    : Gadget()
    {}

    eCameraFOVCtrl::~eCameraFOVCtrl() {}

}
