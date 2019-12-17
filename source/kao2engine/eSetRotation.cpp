#include <kao2engine/eSetRotation.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSetRotation interface
    // <kao2.00523511> (constructor)
    // <kao2.00523580> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_SETROTATION_TYPEINFO
    (
        E_SETROTATION_ID,
        "eSetRotation",
        &E_LOOKATCTRL_TYPEINFO,
        []() -> eObject*
        {
            return new eSetRotation;
        }
    );

    TypeInfo* eSetRotation::getType()
    {
        return &E_SETROTATION_TYPEINFO;
    }

    eSetRotation::eSetRotation()
    : eLookAtCtrl()
    {}

    eSetRotation::~eSetRotation() {}

}
