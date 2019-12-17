#include <kao2engine/NotInstruction.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // NotInstruction interface
    // <kao2.0058CFE0> (constructor)
    // <kao2.0058D0D0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_NOTINSTRUCTION_TYPEINFO
    (
        E_NOTINSTRUCTION_ID,
        "NotInstruction",
        &E_BOOLINSTRUCTION_TYPEINFO,
        []() -> eObject*
        {
            return new NotInstruction(nullptr);
        }
    );

    TypeInfo* NotInstruction::getType()
    {
        return &E_NOTINSTRUCTION_TYPEINFO;
    }

    NotInstruction::NotInstruction(BoolInstruction* x)
    : BoolInstruction()
    {
        unknown_08 = x;
    }

    NotInstruction::~NotInstruction() {}


    ////////////////////////////////////////////////////////////////
    // NotInstruction serialization
    // <kao2.0058D290>
    ////////////////////////////////////////////////////////////////
    void NotInstruction::serialize(Archive &ar)
    {
        /* [0x08] unknown */
        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&unknown_08, &E_BOOLINSTRUCTION_TYPEINFO);
    }


    ////////////////////////////////////////////////////////////////
    // NotInstruction: get script representation
    ////////////////////////////////////////////////////////////////
    eString NotInstruction::generateScriptText()
    {
        eString result;

        result += "!";

        result += unknown_08->generateScriptText();

        return result;
    }

}
