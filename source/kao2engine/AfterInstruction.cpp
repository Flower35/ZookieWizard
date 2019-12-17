#include <kao2engine/AfterInstruction.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // AfterInstruction interface
    // <kao2.00591930> (constructor)
    // <kao2.00591A20> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_AFTERINSTRUCTION_TYPEINFO
    (
        E_AFTERINSTRUCTION_ID,
        "AfterInstruction",
        &E_VOIDINSTRUCTION_TYPEINFO,
        []() -> eObject*
        {
            return new AfterInstruction;
        }
    );

    TypeInfo* AfterInstruction::getType()
    {
        return &E_AFTERINSTRUCTION_TYPEINFO;
    }

    AfterInstruction::AfterInstruction()
    : VoidInstruction()
    {
        /* unknown_08 = OFFSET 005D8014 */
        
        /*[0x0C]*/ time = 1.0f;
        
        /*[0x10]*/ instruction = nullptr;
    }

    AfterInstruction::~AfterInstruction()
    {
        instruction->decRef();
    }


    ////////////////////////////////////////////////////////////////
    // AfterInstruction serialization
    // <kao2.00591BA0>
    ////////////////////////////////////////////////////////////////
    void AfterInstruction::serialize(Archive &ar)
    {
        /* [0x0C] unknown */
        ar.readOrWrite(&time, 0x04);

        /* [0x10] unknown */
        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&instruction, &E_VOIDINSTRUCTION_TYPEINFO);
    }


    ////////////////////////////////////////////////////////////////
    // AfterInstruction: save to text file
    ////////////////////////////////////////////////////////////////
    void AfterInstruction::saveInstructionToTextFile(FileOperator &file, int32_t indentation)
    {
        char bufor[32];

        sprintf_s(bufor, 32, "%.1f", time);

        ArFunctions::writeNewLine(file, indentation);

        file << "after (";
        file << bufor;
        file << ")";

        instruction->saveInstructionToTextFile(file, (1 + indentation));
    }

}
