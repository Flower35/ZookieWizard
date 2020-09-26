#include <kao2engine/eLookAtCtrl.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eLookAtCtrl interface
    // <kao2.004D0D10> (constructor)
    // <kao2.00437350> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_LOOKATCTRL_TYPEINFO
    (
        E_LOOKATCTRL_ID,
        "eLookAtCtrl",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eLookAtCtrl;
        }
    );

    TypeInfo* eLookAtCtrl::getType() const
    {
        return &E_LOOKATCTRL_TYPEINFO;
    }

    eLookAtCtrl::eLookAtCtrl()
    : Gadget()
    {}

    eLookAtCtrl::~eLookAtCtrl()
    {}


    ////////////////////////////////////////////////////////////////
    // eLookAtCtrl: cloning the object
    ////////////////////////////////////////////////////////////////

    void eLookAtCtrl::createFromOtherObject(const eLookAtCtrl &other)
    {}

    eLookAtCtrl::eLookAtCtrl(const eLookAtCtrl &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eLookAtCtrl& eLookAtCtrl::operator = (const eLookAtCtrl &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eLookAtCtrl::cloneFromMe() const
    {
        return new eLookAtCtrl(*this);
    }

}
