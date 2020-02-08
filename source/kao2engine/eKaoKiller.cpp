#include <kao2engine/eKaoKiller.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eKaoKiller interface
    // <kao2.0050BD00> (constructor)
    // <kao2.0050BD70> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_KAOKILLER_TYPEINFO
    (
        E_KAOKILLER_ID,
        "eKaoKiller",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eKaoKiller;
        }
    );

    TypeInfo* eKaoKiller::getType() const
    {
        return &E_KAOKILLER_TYPEINFO;
    }

    eKaoKiller::eKaoKiller()
    : Gadget()
    {}

    eKaoKiller::~eKaoKiller() {}


    ////////////////////////////////////////////////////////////////
    // eKaoKiller: get default name (scripting shenanigans)
    ////////////////////////////////////////////////////////////////
    eString eKaoKiller::getDefaultGadgetName() const
    {
        return "hero";
    }

}
