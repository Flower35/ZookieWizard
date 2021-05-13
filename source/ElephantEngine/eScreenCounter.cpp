#include <ElephantEngine/eScreenCounter.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eScreenCounter interface
    // <kao2.0051F1D0> (constructor)
    // <kao2.0051F2A0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_SCREENCOUNTER_TYPEINFO
    (
        E_SCREENCOUNTER_ID,
        "eScreenCounter",
        &E_TEXTWRITERFIELDS2_TYPEINFO,
        []() -> eObject*
        {
            return new eScreenCounter;
        }
    );

    TypeInfo* eScreenCounter::getType() const
    {
        return &E_SCREENCOUNTER_TYPEINFO;
    }

    eScreenCounter::eScreenCounter()
    : eTextWriterFields2()
    {}

    eScreenCounter::~eScreenCounter()
    {}


    ////////////////////////////////////////////////////////////////
    // eScreenCounter: cloning the object
    ////////////////////////////////////////////////////////////////

    void eScreenCounter::createFromOtherObject(const eScreenCounter &other)
    {}

    eScreenCounter::eScreenCounter(const eScreenCounter &other)
    : eTextWriterFields2(other)
    {
        createFromOtherObject(other);
    }

    eScreenCounter& eScreenCounter::operator = (const eScreenCounter &other)
    {
        if ((&other) != this)
        {
            eTextWriterFields2::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eScreenCounter::cloneFromMe() const
    {
        return new eScreenCounter(*this);
    }

}
