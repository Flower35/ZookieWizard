#include <kao2engine/eWalk.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eWalk interface
    // <kao2.00425270> (constructor)
    // <kao2.004252F0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_WALK_TYPEINFO
    (
        E_WALK_ID,
        "eWalk",
        &E_PATHCTRL_TYPEINFO,
        []() -> eObject*
        {
            return new eWalk;
        }
    );

    TypeInfo* eWalk::getType()
    {
        return &E_WALK_TYPEINFO;
    }

    eWalk::eWalk()
    : ePathCtrl()
    {}

    eWalk::~eWalk() {}

}
