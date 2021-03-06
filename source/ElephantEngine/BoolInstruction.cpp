#include <ElephantEngine/BoolInstruction.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // BoolInstruction interface
    // <kao2.????????> (constructor)
    // <kao2.????????> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_BOOLINSTRUCTION_TYPEINFO
    (
        E_BOOLINSTRUCTION_ID,
        "BoolInstruction",
        &E_REFCOUNTER_TYPEINFO,
        []() -> eObject*
        {
            return nullptr;
        }
    );

    const TypeInfo* BoolInstruction::getType() const
    {
        return &E_BOOLINSTRUCTION_TYPEINFO;
    }

    BoolInstruction::BoolInstruction()
    : eRefCounter()
    {}

    BoolInstruction::~BoolInstruction() {}

}
