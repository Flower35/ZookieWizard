#include <ElephantEngine/eMotorboatCameraCtrl4.h>
#include <ElephantBase/Archive.h>

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

    const TypeInfo* eMotorboatCameraCtrl4::getType() const
    {
        return &E_MOTORBOATCAMERACTRL4_TYPEINFO;
    }

    eMotorboatCameraCtrl4::eMotorboatCameraCtrl4()
    : eFollowCameraCtrl()
    {}

    eMotorboatCameraCtrl4::~eMotorboatCameraCtrl4()
    {}


    ////////////////////////////////////////////////////////////////
    // eMotorboatCameraCtrl4: cloning the object
    ////////////////////////////////////////////////////////////////

    void eMotorboatCameraCtrl4::createFromOtherObject(const eMotorboatCameraCtrl4 &other)
    {}

    eMotorboatCameraCtrl4::eMotorboatCameraCtrl4(const eMotorboatCameraCtrl4 &other)
    : eFollowCameraCtrl(other)
    {
        createFromOtherObject(other);
    }

    eMotorboatCameraCtrl4& eMotorboatCameraCtrl4::operator = (const eMotorboatCameraCtrl4 &other)
    {
        if ((&other) != this)
        {
            eFollowCameraCtrl::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eMotorboatCameraCtrl4::cloneFromMe() const
    {
        return new eMotorboatCameraCtrl4(*this);
    }


    ////////////////////////////////////////////////////////////////
    // eMotorboatCameraCtrl4: serialization
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
