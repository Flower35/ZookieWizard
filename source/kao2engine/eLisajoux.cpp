#include <kao2engine/eLisajoux.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eLisajoux interface
    // <kao2.005642B0> (constructor)
    // <kao2.00564430> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_LISAJOUX_TYPEINFO
    (
        E_LISAJOUX_ID,
        "eLisajoux",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eLisajoux;
        }
    );

    TypeInfo* eLisajoux::getType() const
    {
        return &E_LISAJOUX_TYPEINFO;
    }

    eLisajoux::eLisajoux()
    : Gadget()
    {}

    eLisajoux::~eLisajoux() {}

}
