#include <kao2engine/eLightBlinker.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eLightBlinker interface
    // <kao2.00529435> (constructor)
    // <kao2.005294E0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_LIGHTBLINKER_TYPEINFO
    (
        E_LIGHTBLINKER_ID,
        "eLightBlinker",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eLightBlinker;
        }
    );

    TypeInfo* eLightBlinker::getType() const
    {
        return &E_LIGHTBLINKER_TYPEINFO;
    }

    eLightBlinker::eLightBlinker()
    : Gadget()
    {}

    eLightBlinker::~eLightBlinker() {}

}
