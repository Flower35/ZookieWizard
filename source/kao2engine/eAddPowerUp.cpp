#include <kao2engine/eAddPowerUp.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eAddPowerUp interface
    // <kao2.005A4942> (constructor)
    // <kao2.005A49D0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_ADDPOWERUP_TYPEINFO
    (
        E_ADDPOWERUP_ID,
        "eAddPowerUp",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eAddPowerUp;
        }
    );

    TypeInfo* eAddPowerUp::getType()
    {
        return &E_ADDPOWERUP_TYPEINFO;
    }

    eAddPowerUp::eAddPowerUp()
    : Gadget()
    {}

    eAddPowerUp::~eAddPowerUp() {}

}
