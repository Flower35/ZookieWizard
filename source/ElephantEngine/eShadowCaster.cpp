#include <ElephantEngine/eShadowCaster.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eShadowCaster interface
    // <kao2.00556F01> (constructor)
    // <kao2.00556F90> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_SHADOWCASTER_TYPEINFO
    (
        E_SHADOWCASTER_ID,
        "eShadowCaster",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eShadowCaster;
        }
    );

    const TypeInfo* eShadowCaster::getType() const
    {
        return &E_SHADOWCASTER_TYPEINFO;
    }

    eShadowCaster::eShadowCaster()
    : Gadget()
    {}

    eShadowCaster::~eShadowCaster()
    {}


    ////////////////////////////////////////////////////////////////
    // eShadowCaster: cloning the object
    ////////////////////////////////////////////////////////////////

    void eShadowCaster::createFromOtherObject(const eShadowCaster &other)
    {}

    eShadowCaster::eShadowCaster(const eShadowCaster &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eShadowCaster& eShadowCaster::operator = (const eShadowCaster &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eShadowCaster::cloneFromMe() const
    {
        return new eShadowCaster(*this);
    }

}
