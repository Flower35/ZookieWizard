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

    TypeInfo* Timer::getType() const
    {
        return &E_TIMER_TYPEINFO;
    }

    Timer::Timer()
    : Gadget()
    {
        name = "timer";
    }

    Timer::~Timer()
    {}


    ////////////////////////////////////////////////////////////////
    // Timer: cloning the object
    ////////////////////////////////////////////////////////////////

    void Timer::createFromOtherObject(const Timer &other)
    {
        unknown_10 = other.unknown_10;
        unknown_14 = other.unknown_14;
    }

    Timer::Timer(const Timer &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    Timer& Timer::operator = (const Timer &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* Timer::cloneFromMe() const
    {
        return new Timer(*this);
    }


    ////////////////////////////////////////////////////////////////
    // Timer: serialization
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
    eString Timer::getDefaultGadgetName() const
    {
        return "timer";
    }

}
