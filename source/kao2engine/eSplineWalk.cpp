#include <kao2engine/eSplineWalk.h>
#include <kao2ar/Archive.h>

#include <kao2engine/eGroundTest.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSplineWalk interface
    // <kao2.0043E700> (constructor)
    // <kao2.0043E7D0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_SPLINEWALK_TYPEINFO
    (
        E_SPLINEWALK_ID,
        "eSplineWalk",
        &E_SPLINEBASE_TYPEINFO,
        []() -> eObject*
        {
            return new eSplineWalk;
        }
    );

    TypeInfo* eSplineWalk::getType()
    {
        return &E_SPLINEWALK_TYPEINFO;
    }

    eSplineWalk::eSplineWalk()
    : eSplineBase()
    {
        /*[0x28]*/ unknown_28 = nullptr;
    }

    eSplineWalk::~eSplineWalk() 
    {
        if (nullptr != unknown_28)
        {
            unknown_28->decRef();
        }
    }

}
