#include <kao2engine/eHistory.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eHistory interface
    // <kao2.004D2190> (constructor)
    // <kao2.004D22E0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_HISTORY_TYPEINFO
    (
        E_HISTORY_ID,
        "eHistory",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eHistory;
        }
    );

    TypeInfo* eHistory::getType()
    {
        return &E_HISTORY_TYPEINFO;
    }

    eHistory::eHistory()
    : Gadget()
    {}

    eHistory::~eHistory() {}


    ////////////////////////////////////////////////////////////////
    // eHistory: get default name (scripting shenanigans)
    ////////////////////////////////////////////////////////////////
    eString eHistory::getDefaultGadgetName()
    {
        return "history";
    }

}
