#include <kao2engine/eModifier.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eModifier interface
    ////////////////////////////////////////////////////////////////

    TypeInfo E_MODIFIER_TYPEINFO
    (
        E_MODIFIER_ID,
        "eModifier",
        &E_REFCOUNTER_TYPEINFO,
        []() -> eObject*
        {
            return nullptr;
        }
    );

    TypeInfo* eModifier::getType()
    {
        return &E_MODIFIER_TYPEINFO;
    }

    eModifier::eModifier()
    : eRefCounter()
    {}

    eModifier::~eModifier() {}

}
