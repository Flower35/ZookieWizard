#include <kao2engine/eBoids.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eBoids interface
    // <kao2.00433590> (constructor)
    // <kao2.00433660> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_BOIDS_TYPEINFO
    (
        E_BOIDS_ID,
        "eBoids",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eBoids;
        }
    );

    TypeInfo* eBoids::getType() const
    {
        return &E_BOIDS_TYPEINFO;
    }

    eBoids::eBoids()
    : Gadget()
    {}

    eBoids::~eBoids() {}

}
