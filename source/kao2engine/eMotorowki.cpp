#include <kao2engine/eMotorowki.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eMotorowki interface
    // <kao2.0045D650> (constructor)
    // <kao2.0045D750> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_MOTOROWKI_TYPEINFO
    (
        E_MOTOROWKI_ID,
        "eMotorowki",
        &E_SPLINEWALK_TYPEINFO,
        []() -> eObject*
        {
            return new eMotorowki;
        }
    );

    TypeInfo* eMotorowki::getType()
    {
        return &E_MOTOROWKI_TYPEINFO;
    }

    eMotorowki::eMotorowki()
    : eSplineWalk()
    {}

    eMotorowki::~eMotorowki() {}

}
