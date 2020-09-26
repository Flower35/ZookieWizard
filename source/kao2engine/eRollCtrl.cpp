#include <kao2engine/eRollCtrl.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eRollCtrl interface
    // <kao2.0044B8F3> (constructor)
    // <kao2.0044B980> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_ROLLCTRL_TYPEINFO
    (
        E_ROLLCTRL_ID,
        "eRollCtrl",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eRollCtrl;
        }
    );

    TypeInfo* eRollCtrl::getType() const
    {
        return &E_ROLLCTRL_TYPEINFO;
    }

    eRollCtrl::eRollCtrl()
    : Gadget()
    {}

    eRollCtrl::~eRollCtrl()
    {}


    ////////////////////////////////////////////////////////////////
    // eRollCtrl: cloning the object
    ////////////////////////////////////////////////////////////////

    void eRollCtrl::createFromOtherObject(const eRollCtrl &other)
    {}

    eRollCtrl::eRollCtrl(const eRollCtrl &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eRollCtrl& eRollCtrl::operator = (const eRollCtrl &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eRollCtrl::cloneFromMe() const
    {
        return new eRollCtrl(*this);
    }

}
