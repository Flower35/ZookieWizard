#include <ElephantEngine/StaticMsgInstruction.h>
#include <ElephantBase/Archive.h>

#include <ElephantBase/StaticPool.h>
#include <ElephantEngine/Gadget.h>

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

    const TypeInfo* StaticMsgInstruction::getType() const
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
        theElephantStaticPool.serializeGadget(ar, &link);

        BaseMsgInstruction::serialize(ar);
    }


    ////////////////////////////////////////////////////////////////
    // StaticMsgInstruction: save to text file
    ////////////////////////////////////////////////////////////////
    void StaticMsgInstruction::saveInstructionToTextFile(FileOperator &file, int32_t indentation) const
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
