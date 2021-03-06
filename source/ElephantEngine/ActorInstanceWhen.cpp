#include <ElephantEngine/ActorInstanceWhen.h>
#include <ElephantBase/Archive.h>

#include <ElephantEngine/VoidInstruction.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // ActorInstanceWhen interface
    // <kao2.0059F280> (constructor)
    // <kao2.0059F370> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_ACTORINSTANCEWHEN_TYPEINFO
    (
        E_ACTORINSTANCEWHEN_ID,
        "ActorInstanceWhen",
        &E_WHEN_TYPEINFO,
        []() -> eObject*
        {
            return new ActorInstanceWhen;
        }
    );

    const TypeInfo* ActorInstanceWhen::getType() const
    {
        return &E_ACTORINSTANCEWHEN_TYPEINFO;
    }

    ActorInstanceWhen::ActorInstanceWhen()
    : When()
    {}

    ActorInstanceWhen::~ActorInstanceWhen() {}


    ////////////////////////////////////////////////////////////////
    // ActorInstanceWhen serialization
    // <kao2.0059F540>
    ////////////////////////////////////////////////////////////////
    void ActorInstanceWhen::serialize(Archive &ar)
    {
        When::serialize(ar);

        /* [0x10] unknown */
        ar.serializeString(instanceName);
    }


    ////////////////////////////////////////////////////////////////
    // ActorInstanceWhen: save to text file
    ////////////////////////////////////////////////////////////////
    void ActorInstanceWhen::saveWhenToTextFile(FileOperator &file, int32_t indentation) const
    {
        ArFunctions::writeNewLine(file, indentation);

        file << "when ";
        file << instanceName;
        file << ".";
        file << message;
        file << "()";

        instruction->saveInstructionToTextFile(file, (1 + indentation));
    }

}
