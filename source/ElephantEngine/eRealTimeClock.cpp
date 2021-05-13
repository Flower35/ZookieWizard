#include <ElephantEngine/eRealTimeClock.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eRealTimeClock interface
    // <kao2.00445240> (constructor)
    // <kao2.004452E0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_REALTIMECLOCK_TYPEINFO
    (
        E_REALTIMECLOCK_ID,
        "eRealTimeClock",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eRealTimeClock;
        }
    );

    TypeInfo* eRealTimeClock::getType() const
    {
        return &E_REALTIMECLOCK_TYPEINFO;
    }

    eRealTimeClock::eRealTimeClock()
    : Gadget()
    {}

    eRealTimeClock::~eRealTimeClock()
    {}


    ////////////////////////////////////////////////////////////////
    // eRealTimeClock: cloning the object
    ////////////////////////////////////////////////////////////////

    void eRealTimeClock::createFromOtherObject(const eRealTimeClock &other)
    {}

    eRealTimeClock::eRealTimeClock(const eRealTimeClock &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eRealTimeClock& eRealTimeClock::operator = (const eRealTimeClock &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eRealTimeClock::cloneFromMe() const
    {
        return new eRealTimeClock(*this);
    }

}
