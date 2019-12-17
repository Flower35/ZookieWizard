#include <kao2engine/AndInstruction.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // AndInstruction interface
    // <kao2.0058CAA0> (constructor)
    // <kao2.0058CB90> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_ANDINSTRUCTION_TYPEINFO
    (
        E_ANDINSTRUCTION_ID,
        "AndInstruction",
        &E_BOOLINSTRUCTION_TYPEINFO,
        []() -> eObject*
        {
            return new AndInstruction(nullptr, nullptr);
        }
    );

    TypeInfo* AndInstruction::getType()
    {
        return &E_ANDINSTRUCTION_TYPEINFO;
    }

    AndInstruction::AndInstruction(BoolInstruction* x, BoolInstruction* y)
    : BoolInstruction()
    {
        unknown_08 = x;
        unknown_0C = y;
    }

    AndInstruction::~AndInstruction()
    {
        unknown_0C->decRef();
        unknown_08->decRef();
    }


    ////////////////////////////////////////////////////////////////
    // AndInstruction serialization
    // <kao2.0058CE30>
    ////////////////////////////////////////////////////////////////
    void AndInstruction::serialize(Archive &ar)
    {
        /* [0x08] unknown */
        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&unknown_08, &E_BOOLINSTRUCTION_TYPEINFO);

        /* [0x0C] unknown */
        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&unknown_0C, &E_BOOLINSTRUCTION_TYPEINFO);
    }


    ////////////////////////////////////////////////////////////////
    // AndInstruction: get script representation
    ////////////////////////////////////////////////////////////////
    eString AndInstruction::generateScriptText()
    {
        eString result;

        result += unknown_08->generateScriptText();

        result += " && ";

        result += unknown_0C->generateScriptText();

        return result;
    }

}
