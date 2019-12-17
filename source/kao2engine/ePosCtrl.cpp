#include <kao2engine/ePosCtrl.h>
#include <kao2ar/Archive.h>

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

    TypeInfo* ePosCtrl::getType()
    {
        return &E_POSCTRL_TYPEINFO;
    }

    ePosCtrl::ePosCtrl()
    : eRefCounter()
    {}

    ePosCtrl::~ePosCtrl() {}


    ////////////////////////////////////////////////////////////////
    // ePosCtrl serialization
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
