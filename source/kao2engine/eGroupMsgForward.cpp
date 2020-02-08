#include <kao2engine/eGroupMsgForward.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eGroupMsgForward interface
    // <kao2.005282B2> (constructor)
    // <kao2.00528430> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_GROUPMSGFORWARD_TYPEINFO
    (
        E_GROUPMSGFORWARD_ID,
        "eGroupMsgForward",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eGroupMsgForward;
        }
    );

    TypeInfo* eGroupMsgForward::getType() const
    {
        return &E_GROUPMSGFORWARD_TYPEINFO;
    }

    eGroupMsgForward::eGroupMsgForward()
    : Gadget()
    {}

    eGroupMsgForward::~eGroupMsgForward() {}

}
