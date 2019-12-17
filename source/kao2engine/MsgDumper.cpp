#include <kao2engine/MsgDumper.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // MsgDumper interface
    // <kao2.005B00D1> (constructor)
    // <kao2.005B0140> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_MSGDUMPER_TYPEINFO
    (
        E_MSGDUMPER_ID,
        "MsgDumper",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new MsgDumper;
        }
    );

    TypeInfo* MsgDumper::getType()
    {
        return &E_MSGDUMPER_TYPEINFO;
    }

    MsgDumper::MsgDumper()
    : Gadget()
    {}

    MsgDumper::~MsgDumper() {}

}
