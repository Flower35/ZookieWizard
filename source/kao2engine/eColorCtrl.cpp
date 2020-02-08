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

    eColorCtrl::~eColorCtrl() {}


    ////////////////////////////////////////////////////////////////
    // eColorCtrl serialization
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
