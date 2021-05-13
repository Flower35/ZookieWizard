#include <ElephantEngine/eFollowCameraCtrl.h>
#include <ElephantBase/Archive.h>

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

    const TypeInfo* eFollowCameraCtrl::getType() const
    {
        return &E_FOLLOWCAMERACTRL_TYPEINFO;
    }

    eFollowCameraCtrl::eFollowCameraCtrl()
    : eCameraTarget()
    {}

    eFollowCameraCtrl::~eFollowCameraCtrl()
    {}


    ////////////////////////////////////////////////////////////////
    // eFollowCameraCtrl: cloning the object
    ////////////////////////////////////////////////////////////////

    void eFollowCameraCtrl::createFromOtherObject(const eFollowCameraCtrl &other)
    {}

    eFollowCameraCtrl::eFollowCameraCtrl(const eFollowCameraCtrl &other)
    : eCameraTarget(other)
    {
        createFromOtherObject(other);
    }

    eFollowCameraCtrl& eFollowCameraCtrl::operator = (const eFollowCameraCtrl &other)
    {
        if ((&other) != this)
        {
            eCameraTarget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eFollowCameraCtrl::cloneFromMe() const
    {
        return new eFollowCameraCtrl(*this);
    }

}
