#include <ElephantEngine/eFlockEx.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eFlockEx interface
    // <kao2.0044A3E6> (constructor)
    // <kao2.0044A480> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_FLOCKEX_TYPEINFO
    (
        E_FLOCKEX_ID,
        "eFlockEx",
        &E_FLOCK_TYPEINFO,
        []() -> eObject*
        {
            return new eFlockEx;
        }
    );

    const TypeInfo* eFlockEx::getType() const
    {
        return &E_FLOCKEX_TYPEINFO;
    }

    eFlockEx::eFlockEx()
    : eFlock()
    {}

    eFlockEx::~eFlockEx()
    {}


    ////////////////////////////////////////////////////////////////
    // eFlockEx: cloning the object
    ////////////////////////////////////////////////////////////////

    void eFlockEx::createFromOtherObject(const eFlockEx &other)
    {}

    eFlockEx::eFlockEx(const eFlockEx &other)
    : eFlock(other)
    {
        createFromOtherObject(other);
    }

    eFlockEx& eFlockEx::operator = (const eFlockEx &other)
    {
        if ((&other) != this)
        {
            eFlock::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eFlockEx::cloneFromMe() const
    {
        return new eFlockEx(*this);
    }

}
