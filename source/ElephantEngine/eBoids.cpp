#include <ElephantEngine/eBoids.h>
#include <ElephantBase/Archive.h>

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

    const TypeInfo* eBoids::getType() const
    {
        return &E_BOIDS_TYPEINFO;
    }

    eBoids::eBoids()
    : Gadget()
    {}

    eBoids::~eBoids()
    {}


    ////////////////////////////////////////////////////////////////
    // eBoids: cloning the object
    ////////////////////////////////////////////////////////////////

    void eBoids::createFromOtherObject(const eBoids &other)
    {}

    eBoids::eBoids(const eBoids &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eBoids& eBoids::operator = (const eBoids &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eBoids::cloneFromMe() const
    {
        return new eBoids(*this);
    }

}
