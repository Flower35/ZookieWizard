#include <kao2engine/eBonusShooting.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eBonusShooting interface
    // <kao_tw.006500D0> (constructor)
    // <kao_tw.006501A0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_BONUSSHOOTING_TYPEINFO
    (
        E_BONUSSHOOTING_ID,
        "eBonusShooting",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eBonusShooting;
        }
    );

    TypeInfo* eBonusShooting::getType()
    {
        return &E_BONUSSHOOTING_TYPEINFO;
    }

    eBonusShooting::eBonusShooting()
    : Gadget()
    {}

    eBonusShooting::~eBonusShooting() {}


    ////////////////////////////////////////////////////////////////
    // eBonusShooting serialization
    ////////////////////////////////////////////////////////////////
    void eBonusShooting::serialize(Archive &ar)
    {
        if (ar.getVersion() < 0x89)
        {
            throw ErrorMessage
            (
                "eBonusShooting::serialize():\n" \
                "ar.version() 137 required!"
            );
        }

        Gadget::serialize(ar);
    }

}
