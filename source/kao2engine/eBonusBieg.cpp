#include <kao2engine/eBonusBieg.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eBonusBieg interface
    // <kao2.00458F40> (constructor)
    // <kao2.004590D0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_BONUSBIEG_TYPEINFO
    (
        E_BONUSBIEG_ID,
        "eBonusBieg",
        &E_BASEBALLBIEG_TYPEINFO,
        []() -> eObject*
        {
            return new eBonusBieg;
        }
    );

    TypeInfo* eBonusBieg::getType()
    {
        return &E_BONUSBIEG_TYPEINFO;
    }

    eBonusBieg::eBonusBieg()
    : eBaseballBieg()
    {}

    eBonusBieg::~eBonusBieg() {}

}
