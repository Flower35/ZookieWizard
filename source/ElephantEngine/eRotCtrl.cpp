#include <ElephantEngine/eRotCtrl.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eRotCtrl interface
    // <kao2.0055C310> (constructor)
    // <kao2.0055C3F0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_ROTCTRL_TYPEINFO
    (
        E_ROTCTRL_ID,
        "eRotCtrl",
        &E_REFCOUNTER_TYPEINFO,
        []() -> eObject*
        {
            return new eRotCtrl;
        }
    );

    const TypeInfo* eRotCtrl::getType() const
    {
        return &E_ROTCTRL_TYPEINFO;
    }

    eRotCtrl::eRotCtrl()
    : eRefCounter()
    {}

    eRotCtrl::~eRotCtrl()
    {}


    ////////////////////////////////////////////////////////////////
    // eRotCtrl: cloning the object
    ////////////////////////////////////////////////////////////////

    void eRotCtrl::createFromOtherObject(const eRotCtrl &other)
    {
        unknown_08 = other.unknown_08;
    }

    eRotCtrl::eRotCtrl(const eRotCtrl &other)
    : eRefCounter(other)
    {
        createFromOtherObject(other);
    }

    eRotCtrl& eRotCtrl::operator = (const eRotCtrl &other)
    {
        if ((&other) != this)
        {
            eRefCounter::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eRotCtrl::cloneFromMe() const
    {
        return new eRotCtrl(*this);
    }


    ////////////////////////////////////////////////////////////////
    // eRotCtrl: serialization
    // <kao2.0055C5C0>
    ////////////////////////////////////////////////////////////////
    void eRotCtrl::serialize(Archive &ar)
    {
        /* [0x08] eLinearCtrl::serialize() */
        unknown_08.serialize(ar);
    }

}
