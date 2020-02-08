#include <kao2engine/eCameraShaker.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eCameraShaker interface
    // <kao2.004D59E1> (constructor)
    // <kao2.004D5B10> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_CAMERASHAKER_TYPEINFO
    (
        E_CAMERASHAKER_ID,
        "eCameraShaker",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eCameraShaker;
        }
    );

    TypeInfo* eCameraShaker::getType() const
    {
        return &E_CAMERASHAKER_TYPEINFO;
    }

    eCameraShaker::eCameraShaker()
    : Gadget()
    {}

    eCameraShaker::~eCameraShaker() {}

}
