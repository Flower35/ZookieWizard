#include <ElephantEngine/When.h>
#include <ElephantBase/Archive.h>

#include <ElephantEngine/VoidInstruction.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // When interface
    // <kao2.0059D8B0> (constructor)
    // <kao2.0059D950> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_WHEN_TYPEINFO
    (
        E_WHEN_ID,
        "When",
        &E_REFCOUNTER_TYPEINFO,
        []() -> eObject*
        {
            return nullptr;
        }
    );

    TypeInfo* When::getType() const
    {
        return &E_WHEN_TYPEINFO;
    }

    When::When()
    : eRefCounter()
    {
        /*[0x0C]*/ instruction = nullptr;
    }

    When::~When()
    {
        instruction->decRef();
    }


    ////////////////////////////////////////////////////////////////
    // When serialization
    // <kao2.0059DCF0>
    ////////////////////////////////////////////////////////////////
    void When::serialize(Archive &ar)
    {
        /* [0x08] caller */
        ar.serializeString(message);

        /* [0x0C] instruction */
        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&instruction, &E_VOIDINSTRUCTION_TYPEINFO);
    }

}
