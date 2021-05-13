#include <ElephantEngine/eCameraFOVCtrl.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eCameraFOVCtrl interface
    // <kao2.004D5BC1> (constructor)
    // <kao2.004D5D20> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_CAMERAFOVCTRL_TYPEINFO
    (
        E_CAMERAFOVCTRL_ID,
        "eCameraFOVCtrl",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eCameraFOVCtrl;
        }
    );

    const TypeInfo* eCameraFOVCtrl::getType() const
    {
        return &E_CAMERAFOVCTRL_TYPEINFO;
    }

    eCameraFOVCtrl::eCameraFOVCtrl()
    : Gadget()
    {}

    eCameraFOVCtrl::~eCameraFOVCtrl()
    {}


    ////////////////////////////////////////////////////////////////
    // eCameraFOVCtrl: cloning the object
    ////////////////////////////////////////////////////////////////

    void eCameraFOVCtrl::createFromOtherObject(const eCameraFOVCtrl &other)
    {}

    eCameraFOVCtrl::eCameraFOVCtrl(const eCameraFOVCtrl &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eCameraFOVCtrl& eCameraFOVCtrl::operator = (const eCameraFOVCtrl &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eCameraFOVCtrl::cloneFromMe() const
    {
        return new eCameraFOVCtrl(*this);
    }

}
