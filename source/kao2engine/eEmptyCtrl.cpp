#include <kao2engine/eEmptyCtrl.h>
#include <kao2ar/Archive.h>

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

    TypeInfo* eEmptyCtrl::getType() const
    {
        return &E_EMPTYCTRL_TYPEINFO;
    }

    eEmptyCtrl::eEmptyCtrl()
    : ePathCtrl()
    {}

    eEmptyCtrl::~eEmptyCtrl() {}


    ////////////////////////////////////////////////////////////////
    // eEmptyCtrl serialization
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
