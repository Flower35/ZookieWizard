#include <kao2engine/eOscilationCtrl.h>
#include <kao2ar/Archive.h>

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

    eOscilationCtrl::~eOscilationCtrl() {}


    ////////////////////////////////////////////////////////////////
    // eOscilationCtrl serialization
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
