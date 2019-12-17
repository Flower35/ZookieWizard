#include <kao2engine/ePowerUp.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // ePowerUp interface
    // <kao2.00507BA0> (constructor)
    // <kao2.00507C20> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_POWERUP_TYPEINFO
    (
        E_POWERUP_ID,
        "ePowerUp",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new ePowerUp;
        }
    );

    TypeInfo* ePowerUp::getType()
    {
        return &E_POWERUP_TYPEINFO;
    }

    ePowerUp::ePowerUp()
    : Gadget()
    {}

    ePowerUp::~ePowerUp() {}


    ////////////////////////////////////////////////////////////////
    // ePowerUp: get default name (scripting shenanigans)
    ////////////////////////////////////////////////////////////////
    eString ePowerUp::getDefaultGadgetName()
    {
        return "powerUp";
    }

}
