#include <ElephantEngine/eRain.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eRain interface
    // <kao2.00562530> (constructor)
    // <kao2.005626B0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_RAIN_TYPEINFO
    (
        E_RAIN_ID,
        "eRain",
        &E_SNOW_TYPEINFO,
        []() -> eObject*
        {
            return new eRain;
        }
    );

    TypeInfo* eRain::getType() const
    {
        return &E_RAIN_TYPEINFO;
    }

    eRain::eRain()
    : eSnow()
    {}

    eRain::~eRain()
    {}


    ////////////////////////////////////////////////////////////////
    // eRain: cloning the object
    ////////////////////////////////////////////////////////////////

    void eRain::createFromOtherObject(const eRain &other)
    {}

    eRain::eRain(const eRain &other)
    : eSnow(other)
    {
        createFromOtherObject(other);
    }

    eRain& eRain::operator = (const eRain &other)
    {
        if ((&other) != this)
        {
            eSnow::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eRain::cloneFromMe() const
    {
        return new eRain(*this);
    }

}
