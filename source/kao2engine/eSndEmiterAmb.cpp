#include <kao2engine/eSndEmiterAmb.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSndEmiterAmb interface
    // <kao2.0056C4FC> (constructor)
    // <kao2.0043A170> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_SNDEMITERAMB_TYPEINFO
    (
        E_SNDEMITERAMB_ID,
        "eSndEmiterAmb",
        &E_SNDEMITER_TYPEINFO,
        []() -> eObject*
        {
            return new eSndEmiterAmb;
        }
    );

    TypeInfo* eSndEmiterAmb::getType()
    {
        return &E_SNDEMITERAMB_TYPEINFO;
    }

    eSndEmiterAmb::eSndEmiterAmb()
    : eSndEmiter()
    {}

    eSndEmiterAmb::~eSndEmiterAmb() {}

}
