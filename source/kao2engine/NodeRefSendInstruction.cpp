#include <kao2engine/NodeRefSendInstruction.h>
#include <kao2ar/Archive.h>

#include <kao2engine/NodeRef.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // NodeRefSendInstruction interface
    // <kao2.00590EB0> (constructor)
    // <kao2.00590FA0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_NODEREFSENDINSTRUCTION_TYPEINFO
    (
        E_NODEREFSENDINSTRUCTION_ID,
        "NodeRefSendInstruction",
        &E_VOIDINSTRUCTION_TYPEINFO,
        []() -> eObject*
        {
            return new NodeRefSendInstruction;
        }
    );

    TypeInfo* NodeRefSendInstruction::getType()
    {
        return &E_NODEREFSENDINSTRUCTION_TYPEINFO;
    }

    NodeRefSendInstruction::NodeRefSendInstruction()
    : VoidInstruction()
    {
        /*[0x08]*/ receiver = nullptr;
        /*[0x10]*/ argument = nullptr;
    }

    NodeRefSendInstruction::~NodeRefSendInstruction()
    {
        /*[0x10]*/ argument->decRef();
        /*[0x08]*/ receiver->decRef();
    }


    ////////////////////////////////////////////////////////////////
    // NodeRefSendInstruction serialization
    // <kao2.005911E0>
    ////////////////////////////////////////////////////////////////
    void NodeRefSendInstruction::serialize(Archive &ar)
    {
        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&receiver, &E_NODEREF_TYPEINFO);

        ar.serializeString(message);

        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&argument, &E_REFCOUNTER_TYPEINFO);
    }


    ////////////////////////////////////////////////////////////////
    // NodeRefSendInstruction: save to text file
    ////////////////////////////////////////////////////////////////
    void NodeRefSendInstruction::saveInstructionToTextFile(FileOperator &file, int32_t indentation)
    {
        ArFunctions::writeNewLine(file, indentation);

        file << "send ";

        if (nullptr != receiver)
        {
            file << receiver->getStringRepresentation();
        }
        else
        {
            file << "< EMPTY_NODEREF >";
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
