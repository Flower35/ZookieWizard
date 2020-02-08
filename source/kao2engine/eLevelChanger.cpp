#include <kao2engine/eLevelChanger.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eLevelChanger interface
    // <kao2.00456EE0> (constructor)
    // <kao2.00456F50> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_LEVELCHANGER_TYPEINFO
    (
        E_LEVELCHANGER_ID,
        "eLevelChanger",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eLevelChanger;
        }
    );

    TypeInfo* eLevelChanger::getType() const
    {
        return &E_LEVELCHANGER_TYPEINFO;
    }

    eLevelChanger::eLevelChanger()
    : Gadget()
    {}

    eLevelChanger::~eLevelChanger() {}

}
