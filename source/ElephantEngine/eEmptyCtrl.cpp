#include <ElephantEngine/eEmptyCtrl.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eEmptyCtrl interface
    // <kao2.004280A1> (constructor)
    // <kao2.00428110> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_EMPTYCTRL_TYPEINFO
    (
        E_EMPTYCTRL_ID,
        "eEmptyCtrl",
        &E_PATHCTRL_TYPEINFO,
        []() -> eObject*
        {
            return new eEmptyCtrl;
        }
    );

    const TypeInfo* eEmptyCtrl::getType() const
    {
        return &E_EMPTYCTRL_TYPEINFO;
    }

    eEmptyCtrl::eEmptyCtrl()
    : ePathCtrl()
    {}

    eEmptyCtrl::~eEmptyCtrl()
    {}


    ////////////////////////////////////////////////////////////////
    // eEmptyCtrl: cloning the object
    ////////////////////////////////////////////////////////////////

    void eEmptyCtrl::createFromOtherObject(const eEmptyCtrl &other)
    {
        unknown_50 = other.unknown_50;
        unknown_51 = other.unknown_51;
    }

    eEmptyCtrl::eEmptyCtrl(const eEmptyCtrl &other)
    : ePathCtrl(other)
    {
        createFromOtherObject(other);
    }

    eEmptyCtrl& eEmptyCtrl::operator = (const eEmptyCtrl &other)
    {
        if ((&other) != this)
        {
            ePathCtrl::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eEmptyCtrl::cloneFromMe() const
    {
        return new eEmptyCtrl(*this);
    }


    ////////////////////////////////////////////////////////////////
    // eEmptyCtrl: serialization
    // <kao2.004275C0>
    ////////////////////////////////////////////////////////////////
    void eEmptyCtrl::serialize(Archive &ar)
    {
        ePathCtrl::serialize(ar);

        /* [0x50] unknown */

        ar.readOrWrite(&unknown_50, 0x01);

        /* [0x51] unknown */

        ar.readOrWrite(&unknown_51, 0x01);
    }

}
