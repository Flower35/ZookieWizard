#include <kao2engine/ePlaszczka.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // ePlaszczka interface
    // <kao2.0044DB54> (constructor)
    // <kao2.0044DBD0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_PLASZCZKA_TYPEINFO
    (
        E_PLASZCZKA_ID,
        "ePlaszczka",
        &E_WALK_TYPEINFO,
        []() -> eObject*
        {
            return new ePlaszczka;
        }
    );

    TypeInfo* ePlaszczka::getType()
    {
        return &E_PLASZCZKA_TYPEINFO;
    }

    ePlaszczka::ePlaszczka()
    : eWalk()
    {}

    ePlaszczka::~ePlaszczka() {}

}
