#include <kao2engine/eColorCtrl.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eColorCtrl interface
    // <kao2.0055BF20> (constructor)
    // <kao2.0055BFE0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_COLORCTRL_TYPEINFO
    (
        E_COLORCTRL_ID,
        "eColorCtrl",
        &E_REFCOUNTER_TYPEINFO,
        []() -> eObject*
        {
            return new eColorCtrl;
        }
    );

    TypeInfo* eColorCtrl::getType() const
    {
        return &E_COLORCTRL_TYPEINFO;
    }

    eColorCtrl::eColorCtrl()
    : eRefCounter()
    {
        unknown_7C = 1;
    }

    eColorCtrl::~eColorCtrl()
    {}


    ////////////////////////////////////////////////////////////////
    // eColorCtrl: cloning the object
    ////////////////////////////////////////////////////////////////

    void eColorCtrl::createFromOtherObject(const eColorCtrl &other)
    {
        unknown_08 = other.unknown_08;

        unknown_50 = other.unknown_50;

        unknown_7C = other.unknown_7C;
        unknown_80 = other.unknown_80;
        unknown_84 = other.unknown_84;
        unknown_88 = other.unknown_88;
        unknown_8C = other.unknown_8C;
        unknown_90 = other.unknown_90;
    }

    eColorCtrl::eColorCtrl(const eColorCtrl &other)
    : eRefCounter(other)
    {
        createFromOtherObject(other);
    }

    eColorCtrl& eColorCtrl::operator = (const eColorCtrl &other)
    {
        if ((&other) != this)
        {
            eRefCounter::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eColorCtrl::cloneFromMe() const
    {
        return new eColorCtrl(*this);
    }


    ////////////////////////////////////////////////////////////////
    // eColorCtrl: serialization
    // <kao2.0055C290>
    ////////////////////////////////////////////////////////////////
    void eColorCtrl::serialize(Archive &ar)
    {
        /* [0x08] eLinearCtrl::serialize() */
        unknown_08.serialize(ar);

        /* [0x50] e3fCtrl::serialize() */
        unknown_50.serialize(ar);

        /* [0x7C] unknown */
        ar.readOrWrite(&unknown_7C, 0x04);

        /* unknown values */

        ar.readOrWrite(&unknown_80, 0x04);
        ar.readOrWrite(&unknown_84, 0x04);
        ar.readOrWrite(&unknown_88, 0x04);
        ar.readOrWrite(&unknown_8C, 0x04);
        ar.readOrWrite(&unknown_90, 0x01);
    }

}
