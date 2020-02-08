#include <kao2engine/eKasztanCtrl.h>
#include <kao2ar/Archive.h>

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

    TypeInfo* eKasztanCtrl::getType() const
    {
        return &E_KASZTANCTRL_TYPEINFO;
    }

    eKasztanCtrl::eKasztanCtrl()
    : eEmptyCtrl()
    {}

    eKasztanCtrl::~eKasztanCtrl() {}


    ////////////////////////////////////////////////////////////////
    // eKasztanCtrl serialization
    // <kao2.00427DE0>
    ////////////////////////////////////////////////////////////////
    void eKasztanCtrl::serialize(Archive &ar)
    {
        eEmptyCtrl::serialize(ar);

        /* [0x5C] unknown */

        ar.readOrWrite(&unknown_5C, 0x04);
    }

}
