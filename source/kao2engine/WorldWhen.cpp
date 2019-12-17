#include <kao2engine/WorldWhen.h>
#include <kao2ar/Archive.h>

#include <kao2engine/VoidInstruction.h>

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

    TypeInfo* WorldWhen::getType()
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
    void WorldWhen::saveWhenToTextFile(FileOperator &file, int32_t indentation)
    {
        ArFunctions::writeNewLine(file, indentation);

        file << "when world.";
        file << message;
        file << "()";

        instruction->saveInstructionToTextFile(file, (1 + indentation));
    }

}
