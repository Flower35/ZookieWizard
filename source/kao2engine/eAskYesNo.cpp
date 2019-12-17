#include <kao2engine/eAskYesNo.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eAskYesNo interface
    // <kao2.0045EF90> (constructor)
    // <kao2.0045F080> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_ASKYESNO_TYPEINFO
    (
        E_ASKYESNO_ID,
        "eAskYesNo",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eAskYesNo;
        }
    );

    TypeInfo* eAskYesNo::getType()
    {
        return &E_ASKYESNO_TYPEINFO;
    }

    eAskYesNo::eAskYesNo()
    : Gadget()
    {}

    eAskYesNo::~eAskYesNo() {}

}
