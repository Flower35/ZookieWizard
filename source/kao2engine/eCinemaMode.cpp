#include <kao2engine/eCinemaMode.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eCinemaMode interface
    // <kao2.0043B360> (constructor)
    // <kao2.0043B400> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_CINEMAMODE_TYPEINFO
    (
        E_CINEMAMODE_ID,
        "eCinemaMode",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eCinemaMode;
        }
    );

    TypeInfo* eCinemaMode::getType() const
    {
        return &E_CINEMAMODE_TYPEINFO;
    }

    eCinemaMode::eCinemaMode()
    : Gadget()
    {}

    eCinemaMode::~eCinemaMode() {}

}
