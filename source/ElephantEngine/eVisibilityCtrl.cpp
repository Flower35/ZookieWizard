#include <ElephantEngine/eVisibilityCtrl.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eVisibilityCtrl interface
    // <kao2.00430511> (constructor)
    // <kao2.00430590> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_VISIBILITYCTRL_TYPEINFO
    (
        E_VISIBILITYCTRL_ID,
        "eVisibilityCtrl",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eVisibilityCtrl;
        }
    );

    TypeInfo* eVisibilityCtrl::getType() const
    {
        return &E_VISIBILITYCTRL_TYPEINFO;
    }

    eVisibilityCtrl::eVisibilityCtrl()
    : Gadget()
    {}

    eVisibilityCtrl::~eVisibilityCtrl()
    {}


    ////////////////////////////////////////////////////////////////
    // eVisibilityCtrl: cloning the object
    ////////////////////////////////////////////////////////////////

    void eVisibilityCtrl::createFromOtherObject(const eVisibilityCtrl &other)
    {}

    eVisibilityCtrl::eVisibilityCtrl(const eVisibilityCtrl &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eVisibilityCtrl& eVisibilityCtrl::operator = (const eVisibilityCtrl &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eVisibilityCtrl::cloneFromMe() const
    {
        return new eVisibilityCtrl(*this);
    }

}
