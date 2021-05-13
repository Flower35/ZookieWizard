#include <ElephantEngine/eWaterCircles.h>
#include <ElephantBase/Archive.h>

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

    const TypeInfo* eWaterCircles::getType() const
    {
        return &E_WATERCIRCLES_TYPEINFO;
    }

    eWaterCircles::eWaterCircles()
    : Gadget()
    {}

    eWaterCircles::~eWaterCircles()
    {}


    ////////////////////////////////////////////////////////////////
    // eWaterCircles: cloning the object
    ////////////////////////////////////////////////////////////////

    void eWaterCircles::createFromOtherObject(const eWaterCircles &other)
    {}

    eWaterCircles::eWaterCircles(const eWaterCircles &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eWaterCircles& eWaterCircles::operator = (const eWaterCircles &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eWaterCircles::cloneFromMe() const
    {
        return new eWaterCircles(*this);
    }

}
