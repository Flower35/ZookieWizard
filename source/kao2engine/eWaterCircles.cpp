#include <kao2engine/eWaterCircles.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eWaterCircles interface
    // <kao2.00447550> (constructor)
    // <kao2.004475F0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_WATERCIRCLES_TYPEINFO
    (
        E_WATERCIRCLES_ID,
        "eWaterCircles",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eWaterCircles;
        }
    );

    TypeInfo* eWaterCircles::getType()
    {
        return &E_WATERCIRCLES_TYPEINFO;
    }

    eWaterCircles::eWaterCircles()
    : Gadget()
    {}

    eWaterCircles::~eWaterCircles() {}

}
