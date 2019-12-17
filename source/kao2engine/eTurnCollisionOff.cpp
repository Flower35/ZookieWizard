#include <kao2engine/eTurnCollisionOff.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eTurnCollisionOff interface
    // <kao2.0059A1E1> (constructor)
    // <kao2.0059A250> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_TURNCOLLISIONOFF_TYPEINFO
    (
        E_TURNCOLLISIONOFF_ID,
        "eTurnCollisionOff",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eTurnCollisionOff;
        }
    );

    TypeInfo* eTurnCollisionOff::getType()
    {
        return &E_TURNCOLLISIONOFF_TYPEINFO;
    }

    eTurnCollisionOff::eTurnCollisionOff()
    : Gadget()
    {}

    eTurnCollisionOff::~eTurnCollisionOff() {}

}
