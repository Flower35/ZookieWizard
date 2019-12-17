#include <kao2engine/eAnimNotyfier.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eAnimNotyfier interface
    // <kao2.00444AD0> (constructor)
    // <kao2.00444B60> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_ANIMNOTYFIER_TYPEINFO
    (
        E_ANIMNOTYFIER_ID,
        "eAnimNotyfier",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eAnimNotyfier;
        }
    );

    TypeInfo* eAnimNotyfier::getType()
    {
        return &E_ANIMNOTYFIER_TYPEINFO;
    }

    eAnimNotyfier::eAnimNotyfier()
    : Gadget()
    {}

    eAnimNotyfier::~eAnimNotyfier() {}

}
