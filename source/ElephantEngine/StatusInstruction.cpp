#include <ElephantEngine/StatusInstruction.h>
#include <ElephantBase/Archive.h>

#include <ElephantEngine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // StatusInstruction interface
    // <kao2.0058DD70> (constructor)
    // <kao2.0058DE60> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_STATUSINSTRUCTION_TYPEINFO
    (
        E_STATUSINSTRUCTION_ID,
        "StatusInstruction",
        &E_BASESTATUSINSTRUCTION_TYPEINFO,
        []() -> eObject*
        {
            return new StatusInstruction;
        }
    );

    const TypeInfo* StatusInstruction::getType() const
    {
        return &E_STATUSINSTRUCTION_TYPEINFO;
    }

    StatusInstruction::StatusInstruction()
    : BaseStatusInstruction()
    {
        unknown_10 = nullptr;
    }

    StatusInstruction::~StatusInstruction()
    {
        unknown_10->decRef();
    }


    ////////////////////////////////////////////////////////////////
    // StatusInstruction serialization
    // <kao2.0058DFE0>
    ////////////////////////////////////////////////////////////////
    void StatusInstruction::serialize(Archive &ar)
    {
        if (ar.getVersion() <= 0x88)
        {
            /* [0x10] unknown */
            ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&unknown_10, &E_GADGET_TYPEINFO);
        }

        BaseStatusInstruction::serialize(ar);

        if (ar.getVersion() >= 0x89)
        {
            /* unknown id */
            ar.readOrWrite(&unknown_new_id, 0x04);
        }
    }


    ////////////////////////////////////////////////////////////////
    // StatusInstruction: get script representation
    ////////////////////////////////////////////////////////////////
    eString StatusInstruction::generateScriptText() const
    {
        eString result;

        if (nullptr != unknown_10)
        {
            result += unknown_10->getStringRepresentation();
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
