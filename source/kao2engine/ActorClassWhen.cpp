#include <kao2engine/ActorClassWhen.h>
#include <kao2ar/Archive.h>

#include <kao2engine/VoidInstruction.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // ActorClassWhen interface
    // <kao2.0059ED90> (constructor)
    // <kao2.0059EE80> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_ACTORCLASSWHEN_TYPEINFO
    (
        E_ACTORCLASSWHEN_ID,
        "ActorClassWhen",
        &E_WHEN_TYPEINFO,
        []() -> eObject*
        {
            return new ActorClassWhen;
        }
    );

    TypeInfo* ActorClassWhen::getType() const
    {
        return &E_ACTORCLASSWHEN_TYPEINFO;
    }

    ActorClassWhen::ActorClassWhen()
    : When()
    {}

    ActorClassWhen::~ActorClassWhen() {}


    ////////////////////////////////////////////////////////////////
    // ActorClassWhen serialization
    // <kao2.0059EFF0>
    ////////////////////////////////////////////////////////////////
    void ActorClassWhen::serialize(Archive &ar)
    {
        When::serialize(ar);

        /* [0x10] unknown */
        ar.serializeString(className);
    }


    ////////////////////////////////////////////////////////////////
    // ActorClassWhen: save to text file
    ////////////////////////////////////////////////////////////////
    void ActorClassWhen::saveWhenToTextFile(FileOperator &file, int32_t indentation) const
    {
        ArFunctions::writeNewLine(file, indentation);

        file << "when ";
        file << className;
        file << ".";
        file << message;
        file << "()";

        instruction->saveInstructionToTextFile(file, (1 + indentation));
    }

}
