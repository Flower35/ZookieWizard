#include <ElephantEngine/ePosCtrl.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // ePosCtrl interface
    // <kao2.0055B9C0> (constructor)
    // <kao2.0055BB10> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_POSCTRL_TYPEINFO
    (
        E_POSCTRL_ID,
        "ePosCtrl",
        &E_REFCOUNTER_TYPEINFO,
        []() -> eObject*
        {
            return new ePosCtrl;
        }
    );

    TypeInfo* ePosCtrl::getType() const
    {
        return &E_POSCTRL_TYPEINFO;
    }

    ePosCtrl::ePosCtrl()
    : eRefCounter()
    {}

    ePosCtrl::~ePosCtrl()
    {}


    ////////////////////////////////////////////////////////////////
    // ePosCtrl: cloning the object
    ////////////////////////////////////////////////////////////////

    void ePosCtrl::createFromOtherObject(const ePosCtrl &other)
    {
        unknown_08 = other.unknown_08;
        unknown_50 = other.unknown_50;
        unknown_98 = other.unknown_98;
    }

    ePosCtrl::ePosCtrl(const ePosCtrl &other)
    : eRefCounter(other)
    {
        createFromOtherObject(other);
    }

    ePosCtrl& ePosCtrl::operator = (const ePosCtrl &other)
    {
        if ((&other) != this)
        {
            eRefCounter::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* ePosCtrl::cloneFromMe() const
    {
        return new ePosCtrl(*this);
    }


    ////////////////////////////////////////////////////////////////
    // ePosCtrl: serialization
    // <kao2.0055BE90>
    ////////////////////////////////////////////////////////////////
    void ePosCtrl::serialize(Archive &ar)
    {
        /* [0x08] eLinearCtrl::serialize() */
        unknown_08.serialize(ar);

        /* [0x50] eLinearCtrl::serialize() */
        unknown_50.serialize(ar);

        /* [0x98] eLinearCtrl::serialize() */
        unknown_98.serialize(ar);
    }

}
