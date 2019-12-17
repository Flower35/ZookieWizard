#include <kao2engine/ePlanktonFlakes.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // ePlanktonFlakes interface
    // <kao2.005658B0> (constructor)
    // <kao2.00565970> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_PLANKTONFLAKES_TYPEINFO
    (
        E_PLANKTONFLAKES_ID,
        "ePlanktonFlakes",
        &E_FORRESTFLAKES_TYPEINFO,
        []() -> eObject*
        {
            return new ePlanktonFlakes;
        }
    );

    TypeInfo* ePlanktonFlakes::getType()
    {
        return &E_PLANKTONFLAKES_TYPEINFO;
    }

    ePlanktonFlakes::ePlanktonFlakes()
    : eForrestFlakes()
    {}

    ePlanktonFlakes::~ePlanktonFlakes() {}

}
