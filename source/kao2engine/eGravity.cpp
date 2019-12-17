#include <kao2engine/eGravity.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eGravity interface
    // <kao2.0052FCF0> (constructor)
    // <kao2.0052FD60> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_GRAVITY_TYPEINFO
    (
        E_GRAVITY_ID,
        "eGravity",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eGravity;
        }
    );

    TypeInfo* eGravity::getType()
    {
        return &E_GRAVITY_TYPEINFO;
    }

    eGravity::eGravity()
    : Gadget()
    {}

    eGravity::~eGravity() {}

}
