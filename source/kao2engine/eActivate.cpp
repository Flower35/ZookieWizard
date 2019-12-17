#include <kao2engine/eActivate.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eActivate interface
    // <kao2.005A2910> (constructor)
    // <kao2.005A29A0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_ACTIVATE_TYPEINFO
    (
        E_ACTIVATE_ID,
        "eActivate",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eActivate;
        }
    );

    TypeInfo* eActivate::getType()
    {
        return &E_ACTIVATE_TYPEINFO;
    }

    eActivate::eActivate()
    : Gadget()
    {}

    eActivate::~eActivate() {}

}
