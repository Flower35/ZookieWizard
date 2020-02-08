#include <kao2engine/eSetCollisionFlags.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSetCollisionFlags interface
    // <kao2.0059A301> (constructor)
    // <kao2.0059A4C0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_SETCOLLISIONFLAGS_TYPEINFO
    (
        E_SETCOLLISIONFLAGS_ID,
        "eSetCollisionFlags",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eSetCollisionFlags;
        }
    );

    TypeInfo* eSetCollisionFlags::getType() const
    {
        return &E_SETCOLLISIONFLAGS_TYPEINFO;
    }

    eSetCollisionFlags::eSetCollisionFlags()
    : Gadget()
    {}

    eSetCollisionFlags::~eSetCollisionFlags() {}

}
