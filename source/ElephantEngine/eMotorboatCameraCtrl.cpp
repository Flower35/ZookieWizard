#include <ElephantEngine/eMotorboatCameraCtrl.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eMotorboatCameraCtrl interface
    // <kao2.004D6846> (constructor)
    // <kao2.004D7920> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_MOTORBOATCAMERACTRL_TYPEINFO
    (
        E_MOTORBOATCAMERACTRL_ID,
        "eMotorboatCameraCtrl",
        &E_FOLLOWCAMERACTRL_TYPEINFO,
        []() -> eObject*
        {
            return new eMotorboatCameraCtrl;
        }
    );

    TypeInfo* eMotorboatCameraCtrl::getType() const
    {
        return &E_MOTORBOATCAMERACTRL_TYPEINFO;
    }

    eMotorboatCameraCtrl::eMotorboatCameraCtrl()
    : eFollowCameraCtrl()
    {}

    eMotorboatCameraCtrl::~eMotorboatCameraCtrl()
    {}


    ////////////////////////////////////////////////////////////////
    // eMotorboatCameraCtrl: cloning the object
    ////////////////////////////////////////////////////////////////

    void eMotorboatCameraCtrl::createFromOtherObject(const eMotorboatCameraCtrl &other)
    {}

    eMotorboatCameraCtrl::eMotorboatCameraCtrl(const eMotorboatCameraCtrl &other)
    : eFollowCameraCtrl(other)
    {
        createFromOtherObject(other);
    }

    eMotorboatCameraCtrl& eMotorboatCameraCtrl::operator = (const eMotorboatCameraCtrl &other)
    {
        if ((&other) != this)
        {
            eFollowCameraCtrl::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eMotorboatCameraCtrl::cloneFromMe() const
    {
        return new eMotorboatCameraCtrl(*this);
    }


    ////////////////////////////////////////////////////////////////
    // eMotorboatCameraCtrl: serialization
    ////////////////////////////////////////////////////////////////
    void eMotorboatCameraCtrl::serialize(Archive &ar)
    {
        if (ar.getVersion() >= 0x8B)
        {
            throw ErrorMessage
            (
                "eMotorboatCameraCtrl::serialize():\n" \
                "not supported!"
            );
        }

        Gadget::serialize(ar);
    }

}
