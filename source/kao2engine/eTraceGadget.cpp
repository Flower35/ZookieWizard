#include <kao2engine/eTraceGadget.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eTraceGadget interface
    // <kao2.0050D8C0> (constructor)
    // <kao2.0050D9C0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_TRACEGADGET_TYPEINFO
    (
        E_TRACEGADGET_ID,
        "eTraceGadget",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eTraceGadget;
        }
    );

    TypeInfo* eTraceGadget::getType() const
    {
        return &E_TRACEGADGET_TYPEINFO;
    }

    eTraceGadget::eTraceGadget()
    : Gadget()
    {}

    eTraceGadget::~eTraceGadget() {}

}
