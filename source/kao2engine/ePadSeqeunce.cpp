#include <kao2engine/ePadSeqeunce.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // ePadSeqeunce interface
    // <kao2.005239D1> (constructor)
    // <kao2.00523B70> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_PADSEQEUNCE_TYPEINFO
    (
        E_PADSEQEUNCE_ID,
        "ePadSeqeunce",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new ePadSeqeunce;
        }
    );

    TypeInfo* ePadSeqeunce::getType()
    {
        return &E_PADSEQEUNCE_TYPEINFO;
    }

    ePadSeqeunce::ePadSeqeunce()
    : Gadget()
    {}

    ePadSeqeunce::~ePadSeqeunce() {}

}
