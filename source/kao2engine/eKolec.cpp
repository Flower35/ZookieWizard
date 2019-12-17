#include <kao2engine/eKolec.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eKolec interface
    // <kao2.????????> (constructor)
    // <kao2.004514C0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_KOLEC_TYPEINFO
    (
        E_KOLEC_ID,
        "eKolec",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eKolec;
        }
    );

    TypeInfo* eKolec::getType()
    {
        return &E_KOLEC_TYPEINFO;
    }

    eKolec::eKolec()
    : Gadget()
    {}

    eKolec::~eKolec() {}

}
