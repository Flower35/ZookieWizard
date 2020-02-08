#include <kao2engine/eBaseballBieg.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eBaseballBieg interface
    // <kao2.00459E10> (constructor)
    // <kao2.00458FF0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_BASEBALLBIEG_TYPEINFO
    (
        E_BASEBALLBIEG_ID,
        "eBaseballBieg",
        &E_SPLINEWALK_TYPEINFO,
        []() -> eObject*
        {
            return new eBaseballBieg;
        }
    );

    TypeInfo* eBaseballBieg::getType() const
    {
        return &E_BASEBALLBIEG_TYPEINFO;
    }

    eBaseballBieg::eBaseballBieg()
    : eSplineWalk()
    {}

    eBaseballBieg::~eBaseballBieg() {}

}
