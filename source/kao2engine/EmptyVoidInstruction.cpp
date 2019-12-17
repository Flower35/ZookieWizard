#include <kao2engine/EmptyVoidInstruction.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // EmptyVoidInstruction interface
    // <kao2.005918E1> (constructor)
    // <kao2.0057D290> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_EMPTYVOIDINSTRUCTION_TYPEINFO
    (
        E_EMPTYVOIDINSTRUCTION_ID,
        "EmptyVoidInstruction",
        &E_VOIDINSTRUCTION_TYPEINFO,
        []() -> eObject*
        {
            return new EmptyVoidInstruction;
        }
    );

    TypeInfo* EmptyVoidInstruction::getType()
    {
        return &E_EMPTYVOIDINSTRUCTION_TYPEINFO;
    }

    EmptyVoidInstruction::EmptyVoidInstruction()
    : VoidInstruction()
    {}

    EmptyVoidInstruction::~EmptyVoidInstruction() {}
    

    ////////////////////////////////////////////////////////////////
    // EmptyVoidInstruction: save to text file
    ////////////////////////////////////////////////////////////////
    void EmptyVoidInstruction::saveInstructionToTextFile(FileOperator &file, int32_t indentation)
    {
        ArFunctions::writeNewLine(file, indentation);

        file << "{}";
    }

}
