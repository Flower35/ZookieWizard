#include <kao2engine/eExtraAlbox.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eExtraAlbox interface
    // <kao2.004EEB60> (constructor)
    // <kao2.004EEC20> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_EXTRAALBOX_TYPEINFO
    (
        E_EXTRAALBOX_ID,
        "eExtraAlbox",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eExtraAlbox;
        }
    );

    TypeInfo* eExtraAlbox::getType() const
    {
        return &E_EXTRAALBOX_TYPEINFO;
    }

    eExtraAlbox::eExtraAlbox()
    : Gadget()
    {}

    eExtraAlbox::~eExtraAlbox() {}

}
