#include <kao2engine/eSnowCameraCtrl.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSnowCameraCtrl interface
    // <kao2.00516304> (constructor)
    // <kao2.00516390> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_SNOWCAMERACTRL_TYPEINFO
    (
        E_SNOWCAMERACTRL_ID,
        "eSnowCameraCtrl",
        &E_FOLLOWCAMERACTRL_TYPEINFO,
        []() -> eObject*
        {
            return new eSnowCameraCtrl;
        }
    );

    TypeInfo* eSnowCameraCtrl::getType() const
    {
        return &E_SNOWCAMERACTRL_TYPEINFO;
    }

    eSnowCameraCtrl::eSnowCameraCtrl()
    : eFollowCameraCtrl()
    {}

    eSnowCameraCtrl::~eSnowCameraCtrl()
    {}


    ////////////////////////////////////////////////////////////////
    // eSnowCameraCtrl: cloning the object
    ////////////////////////////////////////////////////////////////

    void eSnowCameraCtrl::createFromOtherObject(const eSnowCameraCtrl &other)
    {}

    eSnowCameraCtrl::eSnowCameraCtrl(const eSnowCameraCtrl &other)
    : eFollowCameraCtrl(other)
    {
        createFromOtherObject(other);
    }

    eSnowCameraCtrl& eSnowCameraCtrl::operator = (const eSnowCameraCtrl &other)
    {
        if ((&other) != this)
        {
            eFollowCameraCtrl::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eSnowCameraCtrl::cloneFromMe() const
    {
        return new eSnowCameraCtrl(*this);
    }

}
