#include <ElephantEngine/eFlyingObjectCtrl.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eFlyingObjectCtrl interface
    // <kao2.004FE0B0> (constructor)
    // <kao2.004FE120> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_FLYINGOBJECTCTRL_TYPEINFO
    (
        E_FLYINGOBJECTCTRL_ID,
        "eFlyingObjectCtrl",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eFlyingObjectCtrl;
        }
    );

    const TypeInfo* eFlyingObjectCtrl::getType() const
    {
        return &E_FLYINGOBJECTCTRL_TYPEINFO;
    }

    eFlyingObjectCtrl::eFlyingObjectCtrl()
    : Gadget()
    {}

    eFlyingObjectCtrl::~eFlyingObjectCtrl()
    {}


    ////////////////////////////////////////////////////////////////
    // eFlyingObjectCtrl: cloning the object
    ////////////////////////////////////////////////////////////////

    void eFlyingObjectCtrl::createFromOtherObject(const eFlyingObjectCtrl &other)
    {}

    eFlyingObjectCtrl::eFlyingObjectCtrl(const eFlyingObjectCtrl &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eFlyingObjectCtrl& eFlyingObjectCtrl::operator = (const eFlyingObjectCtrl &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eFlyingObjectCtrl::cloneFromMe() const
    {
        return new eFlyingObjectCtrl(*this);
    }

}
