#include <kao2engine/MsgInstruction.h>
#include <kao2ar/Archive.h>

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // MsgInstruction interface
    // <kao2.0058E8F0> (constructor)
    // <kao2.0058E9E0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_MSGINSTRUCTION_TYPEINFO
    (
        E_MSGINSTRUCTION_ID,
        "MsgInstruction",
        &E_BASEMSGINSTRUCTION_TYPEINFO,
        []() -> eObject*
        {
            return new MsgInstruction;
        }
    );

    TypeInfo* MsgInstruction::getType()
    {
        return &E_MSGINSTRUCTION_TYPEINFO;
    }

    MsgInstruction::MsgInstruction()
    : BaseMsgInstruction()
    {
        /*[0x10]*/ receiver = nullptr;
    }

    MsgInstruction::~MsgInstruction()
    {
        receiver->decRef();
    }


    ////////////////////////////////////////////////////////////////
    // MsgInstruction serialization
    // <kao2.0058EB60>
    ////////////////////////////////////////////////////////////////
    void MsgInstruction::serialize(Archive &ar)
    {
        if (ar.getVersion() <= 0x88)
        {
            /* [0x10] Message Receiver */
            ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&receiver, &E_GADGET_TYPEINFO);
        }

        BaseMsgInstruction::serialize(ar);

        if (ar.getVersion() >= 0x89)
        {
            /* unknown id */
            ar.readOrWrite(&unknown_new_id, 0x04);
        }
    }


    ////////////////////////////////////////////////////////////////
    // MsgInstruction: save to text file
    ////////////////////////////////////////////////////////////////
    void MsgInstruction::saveInstructionToTextFile(FileOperator &file, int32_t indentation)
    {
        ArFunctions::writeNewLine(file, indentation);

        if (nullptr != receiver)
        {
            file << receiver->getStringRepresentation();
        }
        else
        {
            file << "< EMPTY_GADGET >";
        }

        file << ".";

        file << message;

        file << "(";

        if (nullptr != argument)
        {
            file << argument->getStringRepresentation();
        }

        file << ")";
    }

}
