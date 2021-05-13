#include <ElephantEngine/OwnerUpdateInstruction.h>
#include <ElephantBase/Archive.h>

#include <ElephantEngine/State.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // OwnerUpdateInstruction interface
    // <kao2.005903F0> (constructor)
    // <kao2.005904D0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_OWNERUPDATEINSTRUCTION_TYPEINFO
    (
        E_OWNERUPDATEINSTRUCTION_ID,
        "OwnerUpdateInstruction",
        &E_VOIDINSTRUCTION_TYPEINFO,
        []() -> eObject*
        {
            return new OwnerUpdateInstruction(nullptr);
        }
    );

    TypeInfo* OwnerUpdateInstruction::getType() const
    {
        return &E_OWNERUPDATEINSTRUCTION_TYPEINFO;
    }

    OwnerUpdateInstruction::OwnerUpdateInstruction(State* x)
    : VoidInstruction()
    {
        /*[0x08]*/ unknown_08 = x;
    }

    OwnerUpdateInstruction::~OwnerUpdateInstruction() {}


    ////////////////////////////////////////////////////////////////
    // OwnerUpdateInstruction serialization
    // <kao2.005905A0>
    ////////////////////////////////////////////////////////////////
    void OwnerUpdateInstruction::serialize(Archive &ar)
    {
        /* [0x08] unknown link */
        ar.serialize((eObject**)&unknown_08, &E_STATE_TYPEINFO);
    }


    ////////////////////////////////////////////////////////////////
    // OwnerUpdateInstruction: save to text file
    ////////////////////////////////////////////////////////////////
    void OwnerUpdateInstruction::saveInstructionToTextFile(FileOperator &file, int32_t indentation) const
    {
        ArFunctions::writeNewLine(file, indentation);

        file << "owner";
    }

}
