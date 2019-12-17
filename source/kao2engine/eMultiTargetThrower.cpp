#include <kao2engine/eMultiTargetThrower.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eMultiTargetThrower interface
    // <kao2.00504780> (constructor)
    // <kao2.00504850> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_MULTITARGETTHROWER_TYPEINFO
    (
        E_MULTITARGETTHROWER_ID,
        "eMultiTargetThrower",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eMultiTargetThrower;
        }
    );

    TypeInfo* eMultiTargetThrower::getType()
    {
        return &E_MULTITARGETTHROWER_TYPEINFO;
    }

    eMultiTargetThrower::eMultiTargetThrower()
    : Gadget()
    {}

    eMultiTargetThrower::~eMultiTargetThrower() {}

}
