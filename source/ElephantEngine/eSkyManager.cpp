#include <ElephantEngine/eSkyManager.h>
#include <ElephantBase/Archive.h>

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

    TypeInfo* eSkyManager::getType() const
    {
        return &E_SKYMANAGER_TYPEINFO;
    }

    eSkyManager::eSkyManager()
    : Gadget()
    {}

    eSkyManager::~eSkyManager() {}

}
