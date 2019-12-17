#include <kao2engine/IfElseInstruction.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // IfElseInstruction interface
    // <kao2.0058D3F0> (constructor)
    // <kao2.0058D4E0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_IFELSEINSTRUCTION_TYPEINFO
    (
        E_IFELSEINSTRUCTION_ID,
        "IfElseInstruction",
        &E_IFINSTRUCTION_TYPEINFO,
        []() -> eObject*
        {
            return new IfElseInstruction(nullptr, nullptr, nullptr);
        }
    );

    TypeInfo* IfElseInstruction::getType()
    {
        return &E_IFELSEINSTRUCTION_TYPEINFO;
    }

    IfElseInstruction::IfElseInstruction(BoolInstruction* x, VoidInstruction* y, VoidInstruction* z)
    : IfInstruction(x, y)
    {
        /*[0x10]*/ otherInstruction = z;

        if (nullptr != otherInstruction)
        {
            otherInstruction->incRef();
        }

    }

    IfElseInstruction::~IfElseInstruction()
    {
        if (nullptr != otherInstruction)
        {
            otherInstruction->decRef();
        }
    }   


    ////////////////////////////////////////////////////////////////
    // IfElseInstruction serialization
    // <kao2.0058D7D0>
    ////////////////////////////////////////////////////////////////
    void IfElseInstruction::serialize(Archive &ar)
    {
        IfInstruction::serialize(ar);

        /* [0x10] other condition */
        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&otherInstruction, &E_VOIDINSTRUCTION_TYPEINFO);
    }


    ////////////////////////////////////////////////////////////////
    // IfElseInstruction: save to text file
    ////////////////////////////////////////////////////////////////
    void IfElseInstruction::saveInstructionToTextFile(FileOperator &file, int32_t indentation)
    {
        IfInstruction::saveInstructionToTextFile(file, indentation);

        if (nullptr != otherInstruction)
        {
            /* Empty line already inserted from `IfInstruction::saveInstructionToTextFile()` */

            ArFunctions::writeIndentation(file, indentation);

            file << "else";

            otherInstruction->saveInstructionToTextFile(file, indentation);

            /* Empty line (ending) for better readability */

            ArFunctions::writeNewLine(file, 0);
        }
    }

}
