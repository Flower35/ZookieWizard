#include <ElephantEngine/eOscilationCtrl.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eOscilationCtrl interface
    // <kao2.0055B460> (constructor)
    // <kao2.0055B5F0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_OSCILATIONCTRL_TYPEINFO
    (
        E_OSCILATIONCTRL_ID,
        "eOscilationCtrl",
        &E_REFCOUNTER_TYPEINFO,
        []() -> eObject*
        {
            return new eOscilationCtrl;
        }
    );

    TypeInfo* eOscilationCtrl::getType() const
    {
        return &E_OSCILATIONCTRL_TYPEINFO;
    }

    eOscilationCtrl::eOscilationCtrl()
    : eRefCounter()
    {}

    eOscilationCtrl::~eOscilationCtrl()
    {}


    ////////////////////////////////////////////////////////////////
    // eOscilationCtrl: cloning the object
    ////////////////////////////////////////////////////////////////

    void eOscilationCtrl::createFromOtherObject(const eOscilationCtrl &other)
    {
        unknown_0008 = other.unknown_0008;
        unknown_0050 = other.unknown_0050;
        unknown_0098 = other.unknown_0098;
        unknown_00E0 = other.unknown_00E0;
    }

    eOscilationCtrl::eOscilationCtrl(const eOscilationCtrl &other)
    : eRefCounter(other)
    {
        createFromOtherObject(other);
    }

    eOscilationCtrl& eOscilationCtrl::operator = (const eOscilationCtrl &other)
    {
        if ((&other) != this)
        {
            eRefCounter::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eOscilationCtrl::cloneFromMe() const
    {
        return new eOscilationCtrl(*this);
    }


    ////////////////////////////////////////////////////////////////
    // eOscilationCtrl: serialization
    // <kao2.0055B8B0>
    ////////////////////////////////////////////////////////////////
    void eOscilationCtrl::serialize(Archive &ar)
    {
        /* [0x08] eLinearCtrl::serialize() */
        unknown_0008.serialize(ar);

        /* [0x50] eLinearCtrl::serialize() */
        unknown_0050.serialize(ar);

        /* [0x98] eLinearCtrl::serialize() */
        unknown_0098.serialize(ar);

        /* [0xE0] eLinearCtrl::serialize() */
        unknown_00E0.serialize(ar);
    }

}
