#include <kao2engine/eRealTimeClock.h>
#include <kao2ar/Archive.h>

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

    TypeInfo* eRealTimeClock::getType()
    {
        return &E_REALTIMECLOCK_TYPEINFO;
    }

    eRealTimeClock::eRealTimeClock()
    : Gadget()
    {}

    eRealTimeClock::~eRealTimeClock() {}

}
