#include <kao2engine/eTargeting.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eTargeting interface
    // <kao2.0042E701> (constructor)
    // <kao2.0042E770> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_TARGETING_TYPEINFO
    (
        E_TARGETING_ID,
        "eTargeting",
        &E_EMPTYCTRL_TYPEINFO,
        []() -> eObject*
        {
            return new eTargeting;
        }
    );

    TypeInfo* eTargeting::getType()
    {
        return &E_TARGETING_TYPEINFO;
    }

    eTargeting::eTargeting()
    : eEmptyCtrl()
    {}

    eTargeting::~eTargeting() {}

}
