#include <kao2engine/BlockInstruction.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // BlockInstruction interface
    // <kao2.0058EEF0> (constructor)
    // <kao2.0058EFF0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_BLOCKINSTRUCTION_TYPEINFO
    (
        E_BLOCKINSTRUCTION_ID,
        "BlockInstruction",
        &E_VOIDINSTRUCTION_TYPEINFO,
        []() -> eObject*
        {
            return new BlockInstruction;
        }
    );

    TypeInfo* BlockInstruction::getType() const
    {
        return &E_BLOCKINSTRUCTION_TYPEINFO;
    }

    BlockInstruction::BlockInstruction()
    : VoidInstruction()
    {}

    BlockInstruction::~BlockInstruction() {}


    ////////////////////////////////////////////////////////////////
    // BlockInstruction serialization
    // <kao2.0058F350>
    ////////////////////////////////////////////////////////////////
    void BlockInstruction::serialize(Archive &ar)
    {
        instructions.serialize(ar, &E_VOIDINSTRUCTION_TYPEINFO);
    }


    ////////////////////////////////////////////////////////////////
    // BlockInstruction: save to text file
    ////////////////////////////////////////////////////////////////
    void BlockInstruction::saveInstructionToTextFile(FileOperator &file, int32_t indentation) const
    {
        int32_t i;
        bool has_empty_body = true;

        /* Block opening starts by one indent less */

        indentation--;
        ArFunctions::writeNewLine(file, indentation);
        file << "{";
        indentation++;

        for (i = 0; i < instructions.getSize(); i++)
        {
            VoidInstruction* test_instruction = (VoidInstruction*)instructions.getIthChild(i);

            if (nullptr != test_instruction)
            {
                has_empty_body = false;

                test_instruction->saveInstructionToTextFile(file, indentation);
            }
        }

        indentation--;

        if (false == has_empty_body)
        {
            ArFunctions::writeNewLine(file, indentation);
        }

        file << "}";
    }

}
