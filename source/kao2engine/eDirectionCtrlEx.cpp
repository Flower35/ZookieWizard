#include <kao2engine/eDirectionCtrlEx.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eDirectionCtrlEx interface
    // <kao2.00461981> (constructor)
    // <kao2.00461A00> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_DIRECTIONCTRLEX_TYPEINFO
    (
        E_DIRECTIONCTRLEX_ID,
        "eDirectionCtrlEx",
        &E_DIRECTIONCTRL_TYPEINFO,
        []() -> eObject*
        {
            return new eDirectionCtrlEx;
        }
    );

    TypeInfo* eDirectionCtrlEx::getType()
    {
        return &E_DIRECTIONCTRLEX_TYPEINFO;
    }

    eDirectionCtrlEx::eDirectionCtrlEx()
    : eDirectionCtrl()
    {}

    eDirectionCtrlEx::~eDirectionCtrlEx() {}

}
