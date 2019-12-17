#include <kao2engine/eWhaleManager.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eWhaleManager interface
    // <kao2.004FAD70> (constructor)
    // <kao2.004FAE60> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_WHALEMANAGER_TYPEINFO
    (
        E_WHALEMANAGER_ID,
        "eWhaleManager",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eWhaleManager;
        }
    );

    TypeInfo* eWhaleManager::getType()
    {
        return &E_WHALEMANAGER_TYPEINFO;
    }

    eWhaleManager::eWhaleManager()
    : Gadget()
    {}

    eWhaleManager::~eWhaleManager() {}

}
