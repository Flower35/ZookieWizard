#include <kao2engine/BaseMsgInstruction.h>
#include <kao2ar/Archive.h>

#include <kao2engine/eFloat.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // BaseMsgInstruction interface
    // <kao2.0058E370> (constructor)
    // <kao2.0058E3F0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_BASEMSGINSTRUCTION_TYPEINFO
    (
        E_BASEMSGINSTRUCTION_ID,
        "BaseMsgInstruction",
        &E_VOIDINSTRUCTION_TYPEINFO,
        []() -> eObject*
        {
            return nullptr;
        }
    );

    TypeInfo* BaseMsgInstruction::getType()
    {
        return &E_BASEMSGINSTRUCTION_TYPEINFO;
    }

    BaseMsgInstruction::BaseMsgInstruction()
    : VoidInstruction()
    {
        /*[0x0C]*/ argument = nullptr;
    }

    BaseMsgInstruction::~BaseMsgInstruction()
    {
        argument->decRef();
    }


    ////////////////////////////////////////////////////////////////
    // BaseMsgInstruction serialization
    // <kao2.0058E810>
    ////////////////////////////////////////////////////////////////
    void BaseMsgInstruction::serialize(Archive &ar)
    {
        /* [0x08] message */
        ar.serializeString(message);

        /* [0x0C] argument */
        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&argument, &E_REFCOUNTER_TYPEINFO);
    }

}
