#include <kao2engine/eRain.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eRain interface
    // <kao2.00562530> (constructor)
    // <kao2.005626B0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_RAIN_TYPEINFO
    (
        E_RAIN_ID,
        "eRain",
        &E_SNOW_TYPEINFO,
        []() -> eObject*
        {
            return new eRain;
        }
    );

    TypeInfo* eRain::getType()
    {
        return &E_RAIN_TYPEINFO;
    }

    eRain::eRain()
    : eSnow()
    {}

    eRain::~eRain() {}

}
