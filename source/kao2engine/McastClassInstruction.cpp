#include <kao2engine/McastClassInstruction.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // McastClassInstruction interface
    // <kao2.00590D51> (constructor)
    // <kao2.0057ED10> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_MCASTCLASSINSTRUCTION_TYPEINFO
    (
        E_MCASTCLASSINSTRUCTION_ID,
        "McastClassInstruction",
        &E_SENDINSTRUCTION_TYPEINFO,
        []() -> eObject*
        {
            return new McastClassInstruction;
        }
    );

    TypeInfo* McastClassInstruction::getType() const
    {
        return &E_MCASTCLASSINSTRUCTION_TYPEINFO;
    }

    McastClassInstruction::McastClassInstruction()
    : SendInstruction()
    {}

    McastClassInstruction::~McastClassInstruction() {}


    ////////////////////////////////////////////////////////////////
    // McastClassInstruction serialization
    // <kao2.0057EB30>
    ////////////////////////////////////////////////////////////////
    void McastClassInstruction::serialize(Archive &ar)
    {
        SendInstruction::serialize(ar);

        /* [0x0C] unknown */

        ar.serializeString(className);
    }


    ////////////////////////////////////////////////////////////////
    // McastClassInstruction: save to text file
    ////////////////////////////////////////////////////////////////
    void McastClassInstruction::saveInstructionToTextFile(FileOperator &file, int32_t indentation) const
    {
        ArFunctions::writeNewLine(file, indentation);

        file << "mcast ";

        file << className;

        file << ".";

        file << unknown_08;

        file << "()";
    }

}
