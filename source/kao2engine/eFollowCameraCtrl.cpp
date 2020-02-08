#include <kao2engine/eFollowCameraCtrl.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eFollowCameraCtrl interface
    // <kao2.00510C00> (constructor)
    // <kao2.00510D00> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_FOLLOWCAMERACTRL_TYPEINFO
    (
        E_FOLLOWCAMERACTRL_ID,
        "eFollowCameraCtrl",
        &E_CAMERATARGET_TYPEINFO,
        []() -> eObject*
        {
            return new eFollowCameraCtrl;
        }
    );

    TypeInfo* eFollowCameraCtrl::getType() const
    {
        return &E_FOLLOWCAMERACTRL_TYPEINFO;
    }

    eFollowCameraCtrl::eFollowCameraCtrl()
    : eCameraTarget()
    {}

    eFollowCameraCtrl::~eFollowCameraCtrl() {}

}
