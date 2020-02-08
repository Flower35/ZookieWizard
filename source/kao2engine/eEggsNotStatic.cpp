#include <kao2engine/eEggsNotStatic.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eEggsNotStatic interface
    // <kao2.005069D1> (constructor)
    // <kao2.00506A50> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_EGGSNOTSTATIC_TYPEINFO
    (
        E_EGGSNOTSTATIC_ID,
        "eEggsNotStatic",
        &E_EGGSFACTORY_TYPEINFO,
        []() -> eObject*
        {
            return new eEggsNotStatic;
        }
    );

    TypeInfo* eEggsNotStatic::getType() const
    {
        return &E_EGGSNOTSTATIC_TYPEINFO;
    }

    eEggsNotStatic::eEggsNotStatic()
    : eEggsFactory()
    {}

    eEggsNotStatic::~eEggsNotStatic() {}

}
