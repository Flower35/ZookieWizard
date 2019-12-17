#include <kao2engine/eSkyManager.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSkyManager interface
    // <kao2.00565483> (constructor)
    // <kao2.00565870> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_SKYMANAGER_TYPEINFO
    (
        E_SKYMANAGER_ID,
        "eSkyManager",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eSkyManager;
        }
    );

    TypeInfo* eSkyManager::getType()
    {
        return &E_SKYMANAGER_TYPEINFO;
    }

    eSkyManager::eSkyManager()
    : Gadget()
    {}

    eSkyManager::~eSkyManager() {}

}
