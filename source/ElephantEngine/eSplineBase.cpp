#include <ElephantEngine/eSplineBase.h>
#include <ElephantBase/Archive.h>

#include <ElephantEngine/eBezierSplineNode.h>

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

    TypeInfo* eSplineBase::getType() const
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
        unknown_10->decRef();
    }


    ////////////////////////////////////////////////////////////////
    // eSplineBase: cloning the object
    ////////////////////////////////////////////////////////////////

    void eSplineBase::createFromOtherObject(const eSplineBase &other)
    {
        unknown_10 = other.unknown_10;

        if (nullptr != unknown_10)
        {
            unknown_10->incRef();
        }
    }

    eSplineBase::eSplineBase(const eSplineBase &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eSplineBase& eSplineBase::operator = (const eSplineBase &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            unknown_10->decRef();

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eSplineBase::cloneFromMe() const
    {
        return new eSplineBase(*this);
    }

}
