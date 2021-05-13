#include <ElephantEngine/eSplineHintFollowCameraCtrl.h>
#include <ElephantBase/Archive.h>

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

    const TypeInfo* eSplineHintFollowCameraCtrl::getType() const
    {
        return &E_SPLINEHINTFOLLOWCAMERACTRL_TYPEINFO;
    }

    eSplineHintFollowCameraCtrl::eSplineHintFollowCameraCtrl()
    : eFollowCameraCtrl()
    {}

    eSplineHintFollowCameraCtrl::~eSplineHintFollowCameraCtrl()
    {}


    ////////////////////////////////////////////////////////////////
    // eSplineHintFollowCameraCtrl: cloning the object
    ////////////////////////////////////////////////////////////////

    void eSplineHintFollowCameraCtrl::createFromOtherObject(const eSplineHintFollowCameraCtrl &other)
    {}

    eSplineHintFollowCameraCtrl::eSplineHintFollowCameraCtrl(const eSplineHintFollowCameraCtrl &other)
    : eFollowCameraCtrl(other)
    {
        createFromOtherObject(other);
    }

    eSplineHintFollowCameraCtrl& eSplineHintFollowCameraCtrl::operator = (const eSplineHintFollowCameraCtrl &other)
    {
        if ((&other) != this)
        {
            eFollowCameraCtrl::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eSplineHintFollowCameraCtrl::cloneFromMe() const
    {
        return new eSplineHintFollowCameraCtrl(*this);
    }

}
