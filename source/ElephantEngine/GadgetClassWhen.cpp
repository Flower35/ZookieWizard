#include <ElephantEngine/GadgetClassWhen.h>
#include <ElephantBase/Archive.h>

#include <ElephantEngine/VoidInstruction.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // GadgetClassWhen interface
    // <kao2.0059DE70> (constructor)
    // <kao2.0059DF50> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_GADGETCLASSWHEN_TYPEINFO
    (
        E_GADGETCLASSWHEN_ID,
        "GadgetClassWhen",
        &E_WHEN_TYPEINFO,
        []() -> eObject*
        {
            return new GadgetClassWhen;
        }
    );

    const TypeInfo* GadgetClassWhen::getType() const
    {
        return &E_GADGETCLASSWHEN_TYPEINFO;
    }

    GadgetClassWhen::GadgetClassWhen()
    : When()
    {
        /*[0x10]*/ unknown_10 = nullptr;
    }

    GadgetClassWhen::~GadgetClassWhen()
    {}


    ////////////////////////////////////////////////////////////////
    // GadgetClassWhen serialization
    // <kao2.0059E090>
    ////////////////////////////////////////////////////////////////
    void GadgetClassWhen::serialize(Archive &ar)
    {
        When::serialize(ar);

        ar.Archive::checkTypeInfo(&unknown_10);
    }


    ////////////////////////////////////////////////////////////////
    // GadgetClassWhen: save to text file
    ////////////////////////////////////////////////////////////////
    void GadgetClassWhen::saveWhenToTextFile(FileOperator &file, int32_t indentation) const
    {
        ArFunctions::writeNewLine(file, indentation);

        file << "when ";

        if (nullptr != unknown_10)
        {
            file << unknown_10->name;
        }
        else
        {
            file << "< !!! >";
        }

        file << ".";
        file << message;
        file << "()";

        instruction->saveInstructionToTextFile(file, (1 + indentation));
    }

}
