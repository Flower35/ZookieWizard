#include <ElephantEngine/eNaviPoint.h>
#include <ElephantBase/Archive.h>

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

    const TypeInfo* eNaviPoint::getType() const
    {
        return &E_NAVIPOINT_TYPEINFO;
    }

    eNaviPoint::eNaviPoint()
    : eTransform()
    {
        /*[0x1C]*/
        flags |= 0x40000000;
        flags &= (~0x00000400);
    }

    eNaviPoint::~eNaviPoint()
    {}


    ////////////////////////////////////////////////////////////////
    // eNaviPoint: cloning the object
    ////////////////////////////////////////////////////////////////

    void eNaviPoint::createFromOtherObject(const eNaviPoint &other)
    {
        flags |= 0x40000000;
    }

    eNaviPoint::eNaviPoint(const eNaviPoint &other)
    : eTransform(other)
    {
        createFromOtherObject(other);
    }

    eNaviPoint& eNaviPoint::operator = (const eNaviPoint &other)
    {
        if ((&other) != this)
        {
            eTransform::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eNaviPoint::cloneFromMe() const
    {
        return new eNaviPoint(*this);
    }

}
