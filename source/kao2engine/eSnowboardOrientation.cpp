#include <kao2engine/eSnowboardOrientation.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSnowboardOrientation interface
    // <kao2.004E1176> (constructor)
    // <kao2.004E1240> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_SNOWBOARDORIENTATION_TYPEINFO
    (
        E_SNOWBOARDORIENTATION_ID,
        "eSnowboardOrientation",
        &E_BASEPHYSICS_TYPEINFO,
        []() -> eObject*
        {
            return new eSnowboardOrientation;
        }
    );

    TypeInfo* eSnowboardOrientation::getType() const
    {
        return &E_SNOWBOARDORIENTATION_TYPEINFO;
    }

    eSnowboardOrientation::eSnowboardOrientation()
    : eBasePhysics()
    {}

    eSnowboardOrientation::~eSnowboardOrientation() {}

}
