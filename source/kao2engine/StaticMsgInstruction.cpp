#include <kao2engine/StaticMsgInstruction.h>
#include <kao2ar/Archive.h>

#include <kao2ar/StaticPool.h>
#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // StaticMsgInstruction interface
    // <kao2.0058EC90> (constructor)
    // <kao2.0058ED20> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_STATICMSGINSTRUCTION_TYPEINFO
    (
        E_STATICMSGINSTRUCTION_ID,
        "StaticMsgInstruction",
        &E_BASEMSGINSTRUCTION_TYPEINFO,
        []() -> eObject*
        {
            return new StaticMsgInstruction;
        }
    );

    TypeInfo* StaticMsgInstruction::getType()
    {
        return &E_STATICMSGINSTRUCTION_TYPEINFO;
    }

    StaticMsgInstruction::StaticMsgInstruction()
    : BaseMsgInstruction()
    {
        link = nullptr;
    }

    StaticMsgInstruction::~StaticMsgInstruction() {}


    ////////////////////////////////////////////////////////////////
    // StaticMsgInstruction serialization
    // <kao2.0058EDF0>
    ////////////////////////////////////////////////////////////////
    void StaticMsgInstruction::serialize(Archive &ar)
    {
        StaticPool.serializeGadget(ar, &link);

        BaseMsgInstruction::serialize(ar);
    }
    

    ////////////////////////////////////////////////////////////////
    // StaticMsgInstruction: save to text file
    ////////////////////////////////////////////////////////////////
    void StaticMsgInstruction::saveInstructionToTextFile(FileOperator &file, int32_t indentation)
    {
        ArFunctions::writeNewLine(file, indentation);

        if (nullptr != link)
        {
            file << link->getStringRepresentation();
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
