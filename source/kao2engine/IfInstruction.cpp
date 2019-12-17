#include <kao2engine/IfInstruction.h>
#include <kao2ar/Archive.h>

#include <kao2engine/BoolInstruction.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // IfInstruction interface
    // <kao2.0058C540> (constructor)
    // <kao2.0058C630> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_IFINSTRUCTION_TYPEINFO
    (
        E_IFINSTRUCTION_ID,
        "IfInstruction",
        &E_VOIDINSTRUCTION_TYPEINFO,
        []() -> eObject*
        {
            return new IfInstruction(nullptr, nullptr);
        }
    );

    TypeInfo* IfInstruction::getType()
    {
        return &E_IFINSTRUCTION_TYPEINFO;
    }

    IfInstruction::IfInstruction(BoolInstruction* x, VoidInstruction* y)
    : VoidInstruction()
    {
        /*[0x08]*/ condition = x;

        if (nullptr != condition)
        {
            condition->incRef();
        }

        /*[0x0C]*/ instruction = y;

        if (nullptr != instruction)
        {
            instruction->incRef();
        }
    }

    IfInstruction::~IfInstruction()
    {
        instruction->decRef();

        condition->decRef();
    }


    ////////////////////////////////////////////////////////////////
    // IfInstruction serialization
    // <kao2.0058C8F0>
    ////////////////////////////////////////////////////////////////
    void IfInstruction::serialize(Archive &ar)
    {
        /* [0x08] condition */
        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&condition, &E_BOOLINSTRUCTION_TYPEINFO);

        /* [0x0C] instruction */
        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&instruction, &E_VOIDINSTRUCTION_TYPEINFO);
    }


    ////////////////////////////////////////////////////////////////
    // IfInstruction: save to text file
    ////////////////////////////////////////////////////////////////
    void IfInstruction::saveInstructionToTextFile(FileOperator &file, int32_t indentation)
    {
        /* Empty line (beginning) for better readability */

        ArFunctions::writeNewLine(file, 0);

        ArFunctions::writeNewLine(file, indentation);

        file << "if (";

        if (nullptr != condition)
        {
            file << condition->generateScriptText();
        }

        file << ")";

        if (nullptr != instruction)
        {
            instruction->saveInstructionToTextFile(file, (1 + indentation));
        }

        /* Empty line (ending) for better readability */
        /* Also required for `IfElseInstruction` class */

        ArFunctions::writeNewLine(file, 0);
    }

}
