#include <kao2engine/eVibrate.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eVibrate interface
    // <kao2.004CFBB0> (constructor)
    // <kao2.004CFC40> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_VIBRATE_TYPEINFO
    (
        E_VIBRATE_ID,
        "eVibrate",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eVibrate;
        }
    );

    TypeInfo* eVibrate::getType() const
    {
        return &E_VIBRATE_TYPEINFO;
    }

    eVibrate::eVibrate()
    : Gadget()
    {}

    eVibrate::~eVibrate() {}

}
