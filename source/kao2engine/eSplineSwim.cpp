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

    eSplineSwim::~eSplineSwim()
    {}


    ////////////////////////////////////////////////////////////////
    // eSplineSwim: cloning the object
    ////////////////////////////////////////////////////////////////

    void eSplineSwim::createFromOtherObject(const eSplineSwim &other)
    {}

    eSplineSwim::eSplineSwim(const eSplineSwim &other)
    : eSplineBase(other)
    {
        createFromOtherObject(other);
    }

    eSplineSwim& eSplineSwim::operator = (const eSplineSwim &other)
    {
        if ((&other) != this)
        {
            eSplineBase::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eSplineSwim::cloneFromMe() const
    {
        return new eSplineSwim(*this);
    }

}
