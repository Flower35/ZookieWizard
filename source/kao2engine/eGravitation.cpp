#include <kao2engine/eGravitation.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eGravitation interface
    // <kao2.00440940> (constructor)
    // <kao2.004409C0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_GRAVITATION_TYPEINFO
    (
        E_GRAVITATION_ID,
        "eGravitation",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eGravitation;
        }
    );

    TypeInfo* eGravitation::getType()
    {
        return &E_GRAVITATION_TYPEINFO;
    }

    eGravitation::eGravitation()
    : Gadget()
    {}

    eGravitation::~eGravitation() {}

}
