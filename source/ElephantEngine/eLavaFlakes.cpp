#include <ElephantEngine/eLavaFlakes.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eLavaFlakes interface
    // <kao2.00561290> (constructor)
    // <kao2.00561350> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_LAVAFLAKES_TYPEINFO
    (
        E_LAVAFLAKES_ID,
        "eLavaFlakes",
        &E_SNOW_TYPEINFO,
        []() -> eObject*
        {
            return new eLavaFlakes;
        }
    );

    TypeInfo* eLavaFlakes::getType() const
    {
        return &E_LAVAFLAKES_TYPEINFO;
    }

    eLavaFlakes::eLavaFlakes()
    : eSnow()
    {}

    eLavaFlakes::~eLavaFlakes()
    {}


    ////////////////////////////////////////////////////////////////
    // eLavaFlakes: cloning the object
    ////////////////////////////////////////////////////////////////

    void eLavaFlakes::createFromOtherObject(const eLavaFlakes &other)
    {}

    eLavaFlakes::eLavaFlakes(const eLavaFlakes &other)
    : eSnow(other)
    {
        createFromOtherObject(other);
    }

    eLavaFlakes& eLavaFlakes::operator = (const eLavaFlakes &other)
    {
        if ((&other) != this)
        {
            eSnow::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eLavaFlakes::cloneFromMe() const
    {
        return new eLavaFlakes(*this);
    }

}
