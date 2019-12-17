#include <kao2engine/Timer.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // Timer interface
    // <kao2.0059C7F0> (constructor)
    // <kao2.0059C8C0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_TIMER_TYPEINFO
    (
        E_TIMER_ID,
        "Timer",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new Timer;
        }
    );

    TypeInfo* Timer::getType()
    {
        return &E_TIMER_TYPEINFO;
    }

    Timer::Timer()
    : Gadget()
    {
        name = "timer";
    }

    Timer::~Timer() {}


    ////////////////////////////////////////////////////////////////
    // Timer serialization
    // <kao2.0059C8D0>
    ////////////////////////////////////////////////////////////////
    void Timer::serialize(Archive &ar)
    {
        Gadget::serialize(ar);

        /* [0x10] unknown */
        ar.readOrWrite(&unknown_10, 0x01);

        /* [0x14] unknown */
        ar.readOrWrite(&unknown_14, 0x04);
    }


    ////////////////////////////////////////////////////////////////
    // Timer: get default name (scripting shenanigans)
    ////////////////////////////////////////////////////////////////
    eString Timer::getDefaultGadgetName()
    {
        return "timer";
    }

}
