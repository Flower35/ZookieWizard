#include <kao2engine/eEnergy.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eEnergy interface
    // <kao2.0050AF80> (constructor)
    // <kao2.0050B010> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_ENERGY_TYPEINFO
    (
        E_ENERGY_ID,
        "eEnergy",
        &E_POWERBAR_TYPEINFO,
        []() -> eObject*
        {
            return new eEnergy;
        }
    );

    TypeInfo* eEnergy::getType()
    {
        return &E_ENERGY_TYPEINFO;
    }

    eEnergy::eEnergy()
    : ePowerBar()
    {}

    eEnergy::~eEnergy() {}

}
