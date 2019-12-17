#include <kao2engine/eTimerGadget.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eTimerGadget interface
    // <kao2.0051E990> (constructor)
    // <kao2.0051EA60> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_TIMERGADGET_TYPEINFO
    (
        E_TIMERGADGET_ID,
        "eTimerGadget",
        &E_TEXTWRITERFIELDS2_TYPEINFO,
        []() -> eObject*
        {
            return new eTimerGadget;
        }
    );

    TypeInfo* eTimerGadget::getType()
    {
        return &E_TIMERGADGET_TYPEINFO;
    }

    eTimerGadget::eTimerGadget()
    : eTextWriterFields2()
    {}

    eTimerGadget::~eTimerGadget() {}

}
