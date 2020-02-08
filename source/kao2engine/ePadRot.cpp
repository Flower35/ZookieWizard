#include <kao2engine/ePadRot.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // ePadRot interface
    // <kao2.004DBDD3> (constructor)
    // <kao2.004DC1D0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_PADROT_TYPEINFO
    (
        E_PADROT_ID,
        "ePadRot",
        &E_LOOKATCTRL_TYPEINFO,
        []() -> eObject*
        {
            return new ePadRot;
        }
    );

    TypeInfo* ePadRot::getType() const
    {
        return &E_PADROT_TYPEINFO;
    }

    ePadRot::ePadRot()
    : eLookAtCtrl()
    {}

    ePadRot::~ePadRot() {}

}
