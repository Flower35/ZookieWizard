#include <kao2engine/eLavaFlakes.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eLavaFlakes interface
    // <kao2.00561290> (constructor)
    // <kao2.00561350> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_LAVAFLAKES_TYPEINFO
    (
        E_LAVAFLAKES_ID,
        "eLavaFlakes",
        &E_SNOW_TYPEINFO,
        []() -> eObject*
        {
            return new eLavaFlakes;
        }
    );

    TypeInfo* eLavaFlakes::getType()
    {
        return &E_LAVAFLAKES_TYPEINFO;
    }

    eLavaFlakes::eLavaFlakes()
    : eSnow()
    {}

    eLavaFlakes::~eLavaFlakes() {}

}
