#include <kao2engine/eNaviPoint.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eNaviPoint interface
    // <kao2.00461A40> (constructor)
    // <kao2.00428EF0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_NAVIPOINT_TYPEINFO
    (
        E_NAVIPOINT_ID,
        "eNaviPoint",
        &E_TRANSFORM_TYPEINFO,
        []() -> eObject*
        {
            return new eNaviPoint;
        }
    );

    TypeInfo* eNaviPoint::getType() const
    {
        return &E_NAVIPOINT_TYPEINFO;
    }

    eNaviPoint::eNaviPoint()
    : eTransform()
    {
        /*[0x1C]*/ flags |= 0x40000000;
    }

    eNaviPoint::~eNaviPoint() {}

}
