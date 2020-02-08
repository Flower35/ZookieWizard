#include <kao2engine/ePersistentFloatRef.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // ePersistentFloatRef interface
    // <kao2.005284D0> (constructor)
    // <kao2.00528540> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_PERSISTENTFLOATREF_TYPEINFO
    (
        E_PERSISTENTFLOATREF_ID,
        "ePersistentFloatRef",
        &E_FLOAT_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new ePersistentFloatRef;
        }
    );

    TypeInfo* ePersistentFloatRef::getType() const
    {
        return &E_PERSISTENTFLOATREF_TYPEINFO;
    }

    ePersistentFloatRef::ePersistentFloatRef()
    : Float()
    {
        id = 0;
    }

    ePersistentFloatRef::~ePersistentFloatRef() {}

}
