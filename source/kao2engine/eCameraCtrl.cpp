#include <kao2engine/eCameraCtrl.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eCameraCtrl interface
    // <kao2.????????> (constructor)
    // <kao2.????????> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_CAMERACTRL_TYPEINFO
    (
        E_CAMERACTRL_ID,
        "eCameraCtrl",
        &E_REFCOUNTER_TYPEINFO,
        []() -> eObject*
        {
            return nullptr;
        }
    );

    TypeInfo* eCameraCtrl::getType() const
    {
        return &E_CAMERACTRL_TYPEINFO;
    }

    eCameraCtrl::eCameraCtrl()
    : eRefCounter()
    {}

    eCameraCtrl::~eCameraCtrl() {}

}
