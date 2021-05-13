#include <ElephantEngine/GadgetInstanceWhen.h>
#include <ElephantBase/Archive.h>

#include <ElephantEngine/Gadget.h>
#include <ElephantEngine/VoidInstruction.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // GadgetInstanceWhen interface
    // <kao2.0059E970> (constructor)
    // <kao2.0059EA50> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_GADGETINSTANCEWHEN_TYPEINFO
    (
        E_GADGETINSTANCEWHEN_ID,
        "GadgetInstanceWhen",
        &E_WHEN_TYPEINFO,
        []() -> eObject*
        {
            return new GadgetInstanceWhen;
        }
    );

    const TypeInfo* GadgetInstanceWhen::getType() const
    {
        return &E_GADGETINSTANCEWHEN_TYPEINFO;
    }

    GadgetInstanceWhen::GadgetInstanceWhen()
    : When()
    {
        unknown_10 = nullptr;

        unknown_new_id = (-1);
    }

    GadgetInstanceWhen::~GadgetInstanceWhen() {}


    ////////////////////////////////////////////////////////////////
    // GadgetInstanceWhen serialization
    // <kao2.0059EB60>
    ////////////////////////////////////////////////////////////////
    void GadgetInstanceWhen::serialize(Archive &ar)
    {
        When::serialize(ar);

        if (ar.getVersion() <= 0x88)
        {
            /* [0x10] gadget link */
            ar.serialize((eObject**)&unknown_10, &E_GADGET_TYPEINFO);
        }
        else
        {
            /* unknown id */
            ar.readOrWrite(&unknown_new_id, 0x04);
        }
    }


    ////////////////////////////////////////////////////////////////
    // GadgetInstanceWhen: save to text file
    ////////////////////////////////////////////////////////////////
    void GadgetInstanceWhen::saveWhenToTextFile(FileOperator &file, int32_t indentation) const
    {
        ArFunctions::writeNewLine(file, indentation);

        file << "when ";

        if (nullptr != unknown_10)
        {
            file << unknown_10->getStringRepresentation();
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
