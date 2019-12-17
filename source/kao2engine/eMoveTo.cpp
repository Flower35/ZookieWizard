#include <kao2engine/eMoveTo.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eMoveTo interface
    // <kao2.0051F8D0> (constructor)
    // <kao2.0051F950> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_MOVETO_TYPEINFO
    (
        E_MOVETO_ID,
        "eMoveTo",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eMoveTo;
        }
    );

    TypeInfo* eMoveTo::getType()
    {
        return &E_MOVETO_TYPEINFO;
    }

    eMoveTo::eMoveTo()
    : Gadget()
    {}

    eMoveTo::~eMoveTo() {}

}
