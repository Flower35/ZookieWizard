#include <ElephantEngine/eDirectionCtrl.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eDirectionCtrl interface
    // <kao2.0042F7D1> (constructor)
    // <kao2.0042F850> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_DIRECTIONCTRL_TYPEINFO
    (
        E_DIRECTIONCTRL_ID,
        "eDirectionCtrl",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eDirectionCtrl;
        }
    );

    const TypeInfo* eDirectionCtrl::getType() const
    {
        return &E_DIRECTIONCTRL_TYPEINFO;
    }

    eDirectionCtrl::eDirectionCtrl()
    : Gadget()
    {}

    eDirectionCtrl::~eDirectionCtrl()
    {}


    ////////////////////////////////////////////////////////////////
    // eDirectionCtrl: cloning the object
    ////////////////////////////////////////////////////////////////

    void eDirectionCtrl::createFromOtherObject(const eDirectionCtrl &other)
    {}

    eDirectionCtrl::eDirectionCtrl(const eDirectionCtrl &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eDirectionCtrl& eDirectionCtrl::operator = (const eDirectionCtrl &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eDirectionCtrl::cloneFromMe() const
    {
        return new eDirectionCtrl(*this);
    }


    ////////////////////////////////////////////////////////////////
    // eDirectionCtrl: get default name (scripting shenanigans)
    ////////////////////////////////////////////////////////////////
    eString eDirectionCtrl::getDefaultGadgetName() const
    {
        return "dirCtrl";
    }

}
