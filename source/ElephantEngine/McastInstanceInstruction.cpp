#include <ElephantEngine/McastInstanceInstruction.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // McastInstanceInstruction interface
    // <kao2.00590C61> (constructor)
    // <kao2.0057EAA0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_MCASTINSTANCEINSTRUCTION_TYPEINFO
    (
        E_MCASTINSTANCEINSTRUCTION_ID,
        "McastInstanceInstruction",
        &E_SENDINSTRUCTION_TYPEINFO,
        []() -> eObject*
        {
            return new McastInstanceInstruction;
        }
    );

    const TypeInfo* McastInstanceInstruction::getType() const
    {
        return &E_MCASTINSTANCEINSTRUCTION_TYPEINFO;
    }

    McastInstanceInstruction::McastInstanceInstruction()
    : SendInstruction()
    {}

    McastInstanceInstruction::~McastInstanceInstruction() {}


    ////////////////////////////////////////////////////////////////
    // McastInstanceInstruction serialization
    // <kao20057E870
    ////////////////////////////////////////////////////////////////
    void McastInstanceInstruction::serialize(Archive &ar)
    {
        SendInstruction::serialize(ar);

        /* [0x0C] unknown */

        ar.serializeString(instanceName);
    }


    ////////////////////////////////////////////////////////////////
    // McastInstanceInstruction: save to text file
    ////////////////////////////////////////////////////////////////
    void McastInstanceInstruction::saveInstructionToTextFile(FileOperator &file, int32_t indentation) const
    {
        ArFunctions::writeNewLine(file, indentation);

        file << "mcast ";

        file << instanceName;

        file << ".";

        file << unknown_08;

        file << "()";
    }

}
