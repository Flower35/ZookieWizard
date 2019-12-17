#include <kao2engine/eHeroParent.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eHeroParent interface
    // <kao2.00518172> (constructor)
    // <kao2.00518230> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_HEROPARENT_TYPEINFO
    (
        E_HEROPARENT_ID,
        "eHeroParent",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eHeroParent;
        }
    );

    TypeInfo* eHeroParent::getType()
    {
        return &E_HEROPARENT_TYPEINFO;
    }

    eHeroParent::eHeroParent()
    : Gadget()
    {}

    eHeroParent::~eHeroParent() {}

}
