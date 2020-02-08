#include <kao2engine/eBillboard.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eBillboard interface
    // <kao2.004AC9F6> (constructor)
    // <kao2.004ACAF0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_BILLBOARD_TYPEINFO
    (
        E_BILLBOARD_ID,
        "eBillboard",
        &E_TRANSFORM_TYPEINFO,
        []() -> eObject*
        {
            return new eBillboard;
        }
    );

    TypeInfo* eBillboard::getType() const
    {
        return &E_BILLBOARD_TYPEINFO;
    }

    eBillboard::eBillboard()
    : eTransform()
    {
        /*[0xAC]*/ enabled = false;
    }

    eBillboard::~eBillboard() {}


    ////////////////////////////////////////////////////////////////
    // eBillboard serialization
    // <kao2.????????>
    ////////////////////////////////////////////////////////////////
    void eBillboard::serialize(Archive &ar)
    {
        eTransform::serialize(ar);

        ar.readOrWrite(&enabled, 0x01);
    }

}
