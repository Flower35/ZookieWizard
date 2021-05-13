#include <ElephantEngine/WorldWhen.h>
#include <ElephantBase/Archive.h>

#include <ElephantEngine/VoidInstruction.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // WorldWhen interface
    // <kao2.0059E270> (constructor)
    // <kao2.????????> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_WORLDWHEN_TYPEINFO
    (
        E_WORLDWHEN_ID,
        "WorldWhen",
        &E_WHEN_TYPEINFO,
        []() -> eObject*
        {
            return new WorldWhen;
        }
    );

    TypeInfo* WorldWhen::getType() const
    {
        return &E_WORLDWHEN_TYPEINFO;
    }

    WorldWhen::WorldWhen()
    : When()
    {}

    WorldWhen::~WorldWhen() {}


    ////////////////////////////////////////////////////////////////
    // WorldWhen: save to text file
    ////////////////////////////////////////////////////////////////
    void WorldWhen::saveWhenToTextFile(FileOperator &file, int32_t indentation) const
    {
        ArFunctions::writeNewLine(file, indentation);

        file << "when world.";
        file << message;
        file << "()";

        instruction->saveInstructionToTextFile(file, (1 + indentation));
    }

}
