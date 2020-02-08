#include <kao2engine/eFootPrints.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eFootPrints interface
    // <kao2.00442F30> (constructor)
    // <kao2.004431C0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_FOOTPRINTS_TYPEINFO
    (
        E_FOOTPRINTS_ID,
        "eFootPrints",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eFootPrints;
        }
    );

    TypeInfo* eFootPrints::getType() const
    {
        return &E_FOOTPRINTS_TYPEINFO;
    }

    eFootPrints::eFootPrints()
    : Gadget()
    {}

    eFootPrints::~eFootPrints() {}

}
