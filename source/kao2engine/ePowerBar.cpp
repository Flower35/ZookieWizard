#include <kao2engine/ePowerBar.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // ePowerBar interface
    // <kao2.00453BC0> (constructor)
    // <kao2.00453C60> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_POWERBAR_TYPEINFO
    (
        E_POWERBAR_ID,
        "ePowerBar",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new ePowerBar;
        }
    );

    TypeInfo* ePowerBar::getType()
    {
        return &E_POWERBAR_TYPEINFO;
    }

    ePowerBar::ePowerBar()
    : Gadget()
    {}

    ePowerBar::~ePowerBar() {}

}
