#include <kao2engine/BaseStatusInstruction.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // BaseStatusInstruction interface
    // <kao2.0058D930> (constructor)
    // <kao2.0058D9B0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_BASESTATUSINSTRUCTION_TYPEINFO
    (
        E_BASESTATUSINSTRUCTION_ID,
        "BaseStatusInstruction",
        &E_BOOLINSTRUCTION_TYPEINFO,
        []() -> eObject*
        {
            return nullptr;
        }
    );

    TypeInfo* BaseStatusInstruction::getType()
    {
        return &E_BASESTATUSINSTRUCTION_TYPEINFO;
    }

    BaseStatusInstruction::BaseStatusInstruction()
    : BoolInstruction()
    {
        unknown_0C = nullptr;
    }

    BaseStatusInstruction::~BaseStatusInstruction()
    {
        unknown_0C->decRef();
    }


    ////////////////////////////////////////////////////////////////
    // BaseStatusInstruction serialization
    // <kao2.0058DC90>
    ////////////////////////////////////////////////////////////////
    void BaseStatusInstruction::serialize(Archive &ar)
    {
        /* [0x08] unknown */
        ar.serializeString(unknown_08);

        /* [0x0C] unknown */
        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&unknown_0C, &E_REFCOUNTER_TYPEINFO);
    }

}
