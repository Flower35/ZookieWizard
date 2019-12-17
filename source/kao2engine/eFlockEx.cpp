#include <kao2engine/eFlockEx.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eFlockEx interface
    // <kao2.0044A3E6> (constructor)
    // <kao2.0044A480> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_FLOCKEX_TYPEINFO
    (
        E_FLOCKEX_ID,
        "eFlockEx",
        &E_FLOCK_TYPEINFO,
        []() -> eObject*
        {
            return new eFlockEx;
        }
    );

    TypeInfo* eFlockEx::getType()
    {
        return &E_FLOCKEX_TYPEINFO;
    }

    eFlockEx::eFlockEx()
    : eFlock()
    {}

    eFlockEx::~eFlockEx() {}

}
