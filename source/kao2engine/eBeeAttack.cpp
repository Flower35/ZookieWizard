#include <kao2engine/eBeeAttack.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eBeeAttack interface
    // <kao2.0042E8A0> (constructor)
    // <kao2.0042E940> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_BEEATTACK_TYPEINFO
    (
        E_BEEATTACK_ID,
        "eBeeAttack",
        &E_PATHCTRL_TYPEINFO,
        []() -> eObject*
        {
            return new eBeeAttack;
        }
    );

    TypeInfo* eBeeAttack::getType()
    {
        return &E_BEEATTACK_TYPEINFO;
    }

    eBeeAttack::eBeeAttack()
    : ePathCtrl()
    {
        /*[0x50]*/ unknown_50 = 0;
        /*[0x54]*/ unknown_54 = 0;
        /*[0x58]*/ unknown_58 = 1.0f;

        /*[0x5C]*/ unknown_5C = 0;
        /*[0x60]*/ unknown_60 = 0;
        /*[0x64]*/ unknown_64 = 0;  
    }

    eBeeAttack::~eBeeAttack() {}


    ////////////////////////////////////////////////////////////////
    // eBeeAttack serialization
    // <kao2.0042ECD0>
    ////////////////////////////////////////////////////////////////
    void eBeeAttack::serialize(Archive &ar)
    {
        ePathCtrl::serialize(ar);

        /* [0x50] unknown values */

        ar.readOrWrite(&unknown_50, 0x04);
        ar.readOrWrite(&unknown_54, 0x04);
        ar.readOrWrite(&unknown_58, 0x04);

        /* [0x5C] unknown values */

        ar.readOrWrite(&unknown_5C, 0x04);
        ar.readOrWrite(&unknown_60, 0x04);
        ar.readOrWrite(&unknown_64, 0x04);
    }

}
