#include <ElephantEngine/eFlockAway.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eFlockAway interface
    // <kao2.004311F0> (constructor)
    // <kao2.00431280> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_FLOCKAWAY_TYPEINFO
    (
        E_FLOCKAWAY_ID,
        "eFlockAway",
        &E_FLOCK_TYPEINFO,
        []() -> eObject*
        {
            return new eFlockAway;
        }
    );

    const TypeInfo* eFlockAway::getType() const
    {
        return &E_FLOCKAWAY_TYPEINFO;
    }

    eFlockAway::eFlockAway()
    : eFlock()
    {}

    eFlockAway::~eFlockAway()
    {}


    ////////////////////////////////////////////////////////////////
    // eFlockAway: cloning the object
    ////////////////////////////////////////////////////////////////

    void eFlockAway::createFromOtherObject(const eFlockAway &other)
    {}

    eFlockAway::eFlockAway(const eFlockAway &other)
    : eFlock(other)
    {
        createFromOtherObject(other);
    }

    eFlockAway& eFlockAway::operator = (const eFlockAway &other)
    {
        if ((&other) != this)
        {
            eFlock::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eFlockAway::cloneFromMe() const
    {
        return new eFlockAway(*this);
    }

}
