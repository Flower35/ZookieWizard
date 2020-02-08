#include <kao2engine/eSndEmiterBox.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSndEmiterBox interface
    // <kao2.005AEAB0> (constructor)
    // <kao2.005AEB80> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_SNDEMITERBOX_TYPEINFO
    (
        E_SNDEMITERBOX_ID,
        "eSndEmiterBox",
        &E_SNDEMITER_TYPEINFO,
        []() -> eObject*
        {
            return new eSndEmiterBox;
        }
    );

    TypeInfo* eSndEmiterBox::getType() const
    {
        return &E_SNDEMITERBOX_TYPEINFO;
    }

    eSndEmiterBox::eSndEmiterBox()
    : eSndEmiter()
    {
        /*[0xC8]*/ unknown_C8 = 1.0f;
        /*[0xCC]*/ unknown_CC = 1.0f;
        /*[0xD0]*/ unknown_D0 = 1.0f;

        /*[0xD4]*/ unknown_D4 = 2.0f;
        /*[0xD8]*/ unknown_D8 = 2.0f;
        /*[0xDC]*/ unknown_DC = 2.0f;
    }

    eSndEmiterBox::~eSndEmiterBox() {}


    ////////////////////////////////////////////////////////////////
    // eSndEmiterBox serialization
    // <kao2.005AE750>
    ////////////////////////////////////////////////////////////////
    void eSndEmiterBox::serialize(Archive &ar)
    {
        eSndEmiter::serialize(ar);

        /* [0xC8] unknown values */

        ar.readOrWrite(&unknown_C8, 0x04);
        ar.readOrWrite(&unknown_CC, 0x04);
        ar.readOrWrite(&unknown_D0, 0x04);

        /* [0xD4] unknown values */

        ar.readOrWrite(&unknown_D4, 0x04);
        ar.readOrWrite(&unknown_D8, 0x04);
        ar.readOrWrite(&unknown_DC, 0x04);
    }

}
