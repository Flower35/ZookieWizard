#include <ElephantEngine/eKasztanCtrl.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eKasztanCtrl interface
    // <kao2.00427A20> (constructor)
    // <kao2.00427A90> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_KASZTANCTRL_TYPEINFO
    (
        E_KASZTANCTRL_ID,
        "eKasztanCtrl",
        &E_EMPTYCTRL_TYPEINFO,
        []() -> eObject*
        {
            return new eKasztanCtrl;
        }
    );

    const TypeInfo* eKasztanCtrl::getType() const
    {
        return &E_KASZTANCTRL_TYPEINFO;
    }

    eKasztanCtrl::eKasztanCtrl()
    : eEmptyCtrl()
    {}

    eKasztanCtrl::~eKasztanCtrl()
    {}


    ////////////////////////////////////////////////////////////////
    // eKasztanCtrl: cloning the object
    ////////////////////////////////////////////////////////////////

    void eKasztanCtrl::createFromOtherObject(const eKasztanCtrl &other)
    {
        unknown_5C = other.unknown_5C;
    }

    eKasztanCtrl::eKasztanCtrl(const eKasztanCtrl &other)
    : eEmptyCtrl(other)
    {
        createFromOtherObject(other);
    }

    eKasztanCtrl& eKasztanCtrl::operator = (const eKasztanCtrl &other)
    {
        if ((&other) != this)
        {
            eEmptyCtrl::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eKasztanCtrl::cloneFromMe() const
    {
        return new eKasztanCtrl(*this);
    }


    ////////////////////////////////////////////////////////////////
    // eKasztanCtrl: serialization
    // <kao2.00427DE0>
    ////////////////////////////////////////////////////////////////
    void eKasztanCtrl::serialize(Archive &ar)
    {
        eEmptyCtrl::serialize(ar);

        /* [0x5C] unknown */

        ar.readOrWrite(&unknown_5C, 0x04);
    }

}
