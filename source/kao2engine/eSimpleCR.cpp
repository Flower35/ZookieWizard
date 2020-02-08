#include <kao2engine/eSimpleCR.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSimpleCR interface
    // <kao2.0051C800> (constructor)
    // <kao2.0051C9F0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_SIMPLECR_TYPEINFO
    (
        E_SIMPLECR_ID,
        "eSimpleCR",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eSimpleCR;
        }
    );

    TypeInfo* eSimpleCR::getType() const
    {
        return &E_SIMPLECR_TYPEINFO;
    }

    eSimpleCR::eSimpleCR()
    : Gadget()
    {}

    eSimpleCR::~eSimpleCR() {}

}
