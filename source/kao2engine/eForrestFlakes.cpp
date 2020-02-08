#include <kao2engine/eForrestFlakes.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eForrestFlakes interface
    // <kao2.00560D10> (constructor)
    // <kao2.00560DD0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_FORRESTFLAKES_TYPEINFO
    (
        E_FORRESTFLAKES_ID,
        "eForrestFlakes",
        &E_SNOW_TYPEINFO,
        []() -> eObject*
        {
            return new eForrestFlakes;
        }
    );

    TypeInfo* eForrestFlakes::getType() const
    {
        return &E_FORRESTFLAKES_TYPEINFO;
    }

    eForrestFlakes::eForrestFlakes()
    : eSnow()
    {}

    eForrestFlakes::~eForrestFlakes() {}

}
