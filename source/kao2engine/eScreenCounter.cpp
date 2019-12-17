#include <kao2engine/eScreenCounter.h>
#include <kao2ar/Archive.h>

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

    TypeInfo* eScreenCounter::getType()
    {
        return &E_SCREENCOUNTER_TYPEINFO;
    }

    eScreenCounter::eScreenCounter()
    : eTextWriterFields2()
    {}

    eScreenCounter::~eScreenCounter() {}

}
