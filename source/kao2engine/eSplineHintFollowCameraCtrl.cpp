#include <kao2engine/eSplineHintFollowCameraCtrl.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSplineHintFollowCameraCtrl interface
    // <kao2.004D79D4> (constructor)
    // <kao2.004D7B70> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_SPLINEHINTFOLLOWCAMERACTRL_TYPEINFO
    (
        E_SPLINEHINTFOLLOWCAMERACTRL_ID,
        "eSplineHintFollowCameraCtrl",
        &E_FOLLOWCAMERACTRL_TYPEINFO,
        []() -> eObject*
        {
            return new eSplineHintFollowCameraCtrl;
        }
    );

    TypeInfo* eSplineHintFollowCameraCtrl::getType() const
    {
        return &E_SPLINEHINTFOLLOWCAMERACTRL_TYPEINFO;
    }

    eSplineHintFollowCameraCtrl::eSplineHintFollowCameraCtrl()
    : eFollowCameraCtrl()
    {}

    eSplineHintFollowCameraCtrl::~eSplineHintFollowCameraCtrl() {}

}
