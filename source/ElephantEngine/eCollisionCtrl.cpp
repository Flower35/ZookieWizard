#include <ElephantEngine/eCollisionCtrl.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eCollisionCtrl interface
    // <kao2.00432D00> (constructor)
    // <kao2.00432D90> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_COLLISIONCTRL_TYPEINFO
    (
        E_COLLISIONCTRL_ID,
        "eCollisionCtrl",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eCollisionCtrl;
        }
    );

    TypeInfo* eCollisionCtrl::getType() const
    {
        return &E_COLLISIONCTRL_TYPEINFO;
    }

    eCollisionCtrl::eCollisionCtrl()
    : Gadget()
    {}

    eCollisionCtrl::~eCollisionCtrl()
    {}


    ////////////////////////////////////////////////////////////////
    // eCollisionCtrl: cloning the object
    ////////////////////////////////////////////////////////////////

    void eCollisionCtrl::createFromOtherObject(const eCollisionCtrl &other)
    {}

    eCollisionCtrl::eCollisionCtrl(const eCollisionCtrl &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eCollisionCtrl& eCollisionCtrl::operator = (const eCollisionCtrl &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eCollisionCtrl::cloneFromMe() const
    {
        return new eCollisionCtrl(*this);
    }

}
