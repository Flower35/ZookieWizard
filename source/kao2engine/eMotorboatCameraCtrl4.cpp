#include <kao2engine/eMotorboatCameraCtrl4.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eMotorboatCameraCtrl4 interface
    // <kao_tw.005ABC68> (constructor)
    // <kao_tw.005AD980> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_MOTORBOATCAMERACTRL4_TYPEINFO
    (
        E_MOTORBOATCAMERACTRL4_ID,
        "eMotorboatCameraCtrl4",
        &E_FOLLOWCAMERACTRL_TYPEINFO,
        []() -> eObject*
        {
            return new eMotorboatCameraCtrl4;
        }
    );

    TypeInfo* eMotorboatCameraCtrl4::getType()
    {
        return &E_MOTORBOATCAMERACTRL4_TYPEINFO;
    }

    eMotorboatCameraCtrl4::eMotorboatCameraCtrl4()
    : eFollowCameraCtrl()
    {}

    eMotorboatCameraCtrl4::~eMotorboatCameraCtrl4() {}


    ////////////////////////////////////////////////////////////////
    // eMotorboatCameraCtrl4 serialization
    ////////////////////////////////////////////////////////////////
    void eMotorboatCameraCtrl4::serialize(Archive &ar)
    {
        if (ar.getVersion() < 0x89)
        {
            throw ErrorMessage
            (
                "eMotorboatCameraCtrl4::serialize():\n" \
                "ar.version() 137 required!"
            );
        }

        Gadget::serialize(ar);
    }

}
