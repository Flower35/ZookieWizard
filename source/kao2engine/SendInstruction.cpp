#include <kao2engine/SendInstruction.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // SendInstruction interface
    // <kao2.????????> (constructor)
    // <kao2.0057DF50> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_SENDINSTRUCTION_TYPEINFO
    (
        E_SENDINSTRUCTION_ID,
        "SendInstruction",
        &E_VOIDINSTRUCTION_TYPEINFO,
        []() -> eObject*
        {
            return nullptr;
        }
    );

    TypeInfo* SendInstruction::getType() const
    {
        return &E_SENDINSTRUCTION_TYPEINFO;
    }

    SendInstruction::SendInstruction()
    : VoidInstruction()
    {}

    SendInstruction::~SendInstruction() {}


    ////////////////////////////////////////////////////////////////
    // SendInstruction serialization
    // <kao2.0057DF10>
    ////////////////////////////////////////////////////////////////
    void SendInstruction::serialize(Archive &ar)
    {
        /* [0x08] unknown */

        ar.serializeString(unknown_08);
    }

}
