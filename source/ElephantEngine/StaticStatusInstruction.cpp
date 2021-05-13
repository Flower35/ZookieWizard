#include <ElephantEngine/StaticStatusInstruction.h>
#include <ElephantBase/Archive.h>

#include <ElephantBase/StaticPool.h>
#include <ElephantEngine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // StaticStatusInstruction interface
    // <kao2.0058E110> (constructor)
    // <kao2.0058E1A0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_STATICSTATUSINSTRUCTION_TYPEINFO
    (
        E_STATICSTATUSINSTRUCTION_ID,
        "StaticStatusInstruction",
        &E_BASESTATUSINSTRUCTION_TYPEINFO,
        []() -> eObject*
        {
            return new StaticStatusInstruction;
        }
    );

    const TypeInfo* StaticStatusInstruction::getType() const
    {
        return &E_STATICSTATUSINSTRUCTION_TYPEINFO;
    }

    StaticStatusInstruction::StaticStatusInstruction()
    : BaseStatusInstruction()
    {
        /*[0x10]*/ link = nullptr;
    }

    StaticStatusInstruction::~StaticStatusInstruction() {}


    ////////////////////////////////////////////////////////////////
    // StaticStatusInstruction serialization
    // <kao2.0058E270>
    ////////////////////////////////////////////////////////////////
    void StaticStatusInstruction::serialize(Archive &ar)
    {
        theElephantStaticPool.serializeGadget(ar, &link);

        BaseStatusInstruction::serialize(ar);
    }


    ////////////////////////////////////////////////////////////////
    // StaticStatusInstruction: get script representation
    ////////////////////////////////////////////////////////////////
    eString StaticStatusInstruction::generateScriptText() const
    {
        eString result;

        if (nullptr != link)
        {
            result += link->getStringRepresentation();
        }
        else
        {
            result += "< EMPTY_GADGET >";
        }

        result += ".";
        result += unknown_08;
        result += "(";

        if (nullptr != unknown_0C)
        {
            result += unknown_0C->getStringRepresentation();
        }

        result += ")";

        return result;
    }

}
