#include <kao2engine/MeWhen.h>
#include <kao2ar/Archive.h>

#include <kao2engine/VoidInstruction.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // MeWhen interface
    // <kao2.0059E5F0> (constructor)
    // <kao2.0059E6D0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_MEWHEN_TYPEINFO
    (
        E_MEWHEN_ID,
        "MeWhen",
        &E_WHEN_TYPEINFO,
        []() -> eObject*
        {
            return new MeWhen;
        }
    );

    TypeInfo* MeWhen::getType()
    {
        return &E_MEWHEN_TYPEINFO;
    }

    MeWhen::MeWhen()
    : When()
    {}

    MeWhen::~MeWhen() {}


    ////////////////////////////////////////////////////////////////
    // MeWhen: save to text file
    ////////////////////////////////////////////////////////////////
    void MeWhen::saveWhenToTextFile(FileOperator &file, int32_t indentation)
    {
        ArFunctions::writeNewLine(file, indentation);

        file << "when me.";
        file << message;
        file << "()";

        instruction->saveInstructionToTextFile(file, (1 + indentation));
    }

}
