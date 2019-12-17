#include <kao2engine/eSplineBase.h>
#include <kao2ar/Archive.h>

#include <kao2engine/eBezierSplineNode.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSplineBase interface
    // <kao2.0043DCB0> (constructor)
    // <kao2.0043DD40> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_SPLINEBASE_TYPEINFO
    (
        E_SPLINEBASE_ID,
        "eSplineBase",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eSplineBase;
        }
    );

    TypeInfo* eSplineBase::getType()
    {
        return &E_SPLINEBASE_TYPEINFO;
    }

    eSplineBase::eSplineBase()
    : Gadget()
    {
        unknown_10 = nullptr;
    }

    eSplineBase::~eSplineBase()
    {
        if (nullptr != unknown_10)
        {
            unknown_10->decRef();
        }
    }

}
