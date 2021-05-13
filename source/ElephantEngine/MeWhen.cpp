#include <ElephantEngine/MeWhen.h>
#include <ElephantBase/Archive.h>

#include <ElephantEngine/VoidInstruction.h>

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

    TypeInfo* MeWhen::getType() const
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
    void MeWhen::saveWhenToTextFile(FileOperator &file, int32_t indentation) const
    {
        ArFunctions::writeNewLine(file, indentation);

        file << "when me.";
        file << message;
        file << "()";

        instruction->saveInstructionToTextFile(file, (1 + indentation));
    }

}
