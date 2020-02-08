#include <kao2engine/eFlockAway.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eFlockAway interface
    // <kao2.004311F0> (constructor)
    // <kao2.00431280> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_FLOCKAWAY_TYPEINFO
    (
        E_FLOCKAWAY_ID,
        "eFlockAway",
        &E_FLOCK_TYPEINFO,
        []() -> eObject*
        {
            return new eFlockAway;
        }
    );

    TypeInfo* eFlockAway::getType() const
    {
        return &E_FLOCKAWAY_TYPEINFO;
    }

    eFlockAway::eFlockAway()
    : eFlock()
    {}

    eFlockAway::~eFlockAway() {}

}
