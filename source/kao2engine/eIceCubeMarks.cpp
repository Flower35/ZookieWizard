#include <kao2engine/eIceCubeMarks.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eIceCubeMarks interface
    // <kao2.0055AF70> (constructor)
    // <kao2.0055B000> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_ICECUBEMARKS_TYPEINFO
    (
        E_ICECUBEMARKS_ID,
        "eIceCubeMarks",
        &E_MARKS_TYPEINFO,
        []() -> eObject*
        {
            return new eIceCubeMarks;
        }
    );

    TypeInfo* eIceCubeMarks::getType()
    {
        return &E_ICECUBEMARKS_TYPEINFO;
    }

    eIceCubeMarks::eIceCubeMarks()
    : eMarks()
    {}

    eIceCubeMarks::~eIceCubeMarks() {}

}
