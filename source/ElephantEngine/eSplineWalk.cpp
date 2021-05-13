#include <ElephantEngine/eSplineWalk.h>
#include <ElephantBase/Archive.h>

#include <ElephantEngine/eGroundTest.h>

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

    const TypeInfo* eSplineWalk::getType() const
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
        unknown_28->decRef();
    }


    ////////////////////////////////////////////////////////////////
    // eSplineWalk: cloning the object
    ////////////////////////////////////////////////////////////////

    void eSplineWalk::createFromOtherObject(const eSplineWalk &other)
    {
        unknown_28 = other.unknown_28;

        if (nullptr != unknown_28)
        {
            unknown_28->incRef();
        }
    }

    eSplineWalk::eSplineWalk(const eSplineWalk &other)
    : eSplineBase(other)
    {
        createFromOtherObject(other);
    }

    eSplineWalk& eSplineWalk::operator = (const eSplineWalk &other)
    {
        if ((&other) != this)
        {
            eSplineBase::operator = (other);

            /****************/

            unknown_28->decRef();

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eSplineWalk::cloneFromMe() const
    {
        return new eSplineWalk(*this);
    }

}
