#include <kao2engine/eRotCtrl.h>
#include <kao2ar/Archive.h>

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

    TypeInfo* eRotCtrl::getType() const
    {
        return &E_ROTCTRL_TYPEINFO;
    }

    eRotCtrl::eRotCtrl()
    : eRefCounter()
    {}

    eRotCtrl::~eRotCtrl() {}


    ////////////////////////////////////////////////////////////////
    // eRotCtrl serialization
    // <kao2.0055C5C0>
    ////////////////////////////////////////////////////////////////
    void eRotCtrl::serialize(Archive &ar)
    {
        /* [0x08] eLinearCtrl::serialize() */
        unknown_08.serialize(ar);
    }

}
