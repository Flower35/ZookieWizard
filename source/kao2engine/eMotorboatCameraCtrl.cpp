#include <kao2engine/eMotorboatCameraCtrl.h>
#include <kao2ar/Archive.h>

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

    eMotorboatCameraCtrl::~eMotorboatCameraCtrl() {}


    ////////////////////////////////////////////////////////////////
    // eMotorboatCameraCtrl serialization
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
