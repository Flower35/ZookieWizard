#include <kao2engine/eDoubleCameraTarget.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eDoubleCameraTarget interface
    // <kao2.00516754> (constructor)
    // <kao2.00516BB0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_DOUBLECAMERATARGET_TYPEINFO
    (
        E_DOUBLECAMERATARGET_ID,
        "eDoubleCameraTarget",
        &E_CAMERATARGET_TYPEINFO,
        []() -> eObject*
        {
            return new eDoubleCameraTarget;
        }
    );

    TypeInfo* eDoubleCameraTarget::getType()
    {
        return &E_DOUBLECAMERATARGET_TYPEINFO;
    }

    eDoubleCameraTarget::eDoubleCameraTarget()
    : eCameraTarget()
    {}

    eDoubleCameraTarget::~eDoubleCameraTarget() {}

}
