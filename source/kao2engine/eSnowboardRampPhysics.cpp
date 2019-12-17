#include <kao2engine/eSnowboardRampPhysics.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSnowboardRampPhysics interface
    // <kao2.004E7490> (constructor)
    // <kao2.004E7500> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_SNOWBOARDRAMPPHYSICS_TYPEINFO
    (
        E_SNOWBOARDRAMPPHYSICS_ID,
        "eSnowboardRampPhysics",
        &E_SNOWBOARDPHYSICS_TYPEINFO,
        []() -> eObject*
        {
            return new eSnowboardRampPhysics;
        }
    );

    TypeInfo* eSnowboardRampPhysics::getType()
    {
        return &E_SNOWBOARDRAMPPHYSICS_TYPEINFO;
    }

    eSnowboardRampPhysics::eSnowboardRampPhysics()
    : eSnowboardPhysics()
    {}

    eSnowboardRampPhysics::~eSnowboardRampPhysics() {}

}
