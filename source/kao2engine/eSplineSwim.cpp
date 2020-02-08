#include <kao2engine/eSplineSwim.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSplineSwim interface
    // <kao2.0044BAF0> (constructor)
    // <kao2.0044BB80> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_SPLINESWIM_TYPEINFO
    (
        E_SPLINESWIM_ID,
        "eSplineSwim",
        &E_SPLINEBASE_TYPEINFO,
        []() -> eObject*
        {
            return new eSplineSwim;
        }
    );

    TypeInfo* eSplineSwim::getType() const
    {
        return &E_SPLINESWIM_TYPEINFO;
    }

    eSplineSwim::eSplineSwim()
    : eSplineBase()
    {}

    eSplineSwim::~eSplineSwim() {}

}
