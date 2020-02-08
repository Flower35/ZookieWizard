#include <kao2engine/eButterfly.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eButterfly interface
    // <kao2.00435A80> (constructor)
    // <kao2.00435B10> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_BUTTERFLY_TYPEINFO
    (
        E_BUTTERFLY_ID,
        "eButterfly",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eButterfly;
        }
    );

    TypeInfo* eButterfly::getType() const
    {
        return &E_BUTTERFLY_TYPEINFO;
    }

    eButterfly::eButterfly()
    : Gadget()
    {}

    eButterfly::~eButterfly() {}

}
