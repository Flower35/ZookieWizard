#include <kao2engine/ePrimitive.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // ePrimitive interface
    // <kao2.????????> (constructor)
    // <kao2.????????> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_PRIMITIVE_TYPEINFO
    (
        E_PRIMITIVE_ID,
        "ePrimitive",
        &E_REFCOUNTER_TYPEINFO,
        []() -> eObject*
        {
            return nullptr;
        }
    );

    TypeInfo* ePrimitive::getType() const
    {
        return &E_PRIMITIVE_TYPEINFO;
    }

    ePrimitive::ePrimitive()
    : eRefCounter()
    {
        /* (...) */
    }

    ePrimitive::~ePrimitive() {}

}
