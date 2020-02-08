#include <kao2engine/eMusicManager.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eMusicManager interface
    // <kao2.0041AB20> (constructor)
    // <kao2.0041AC70> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_MUSICMANAGER_TYPEINFO
    (
        E_MUSICMANAGER_ID,
        "eMusicManager",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eMusicManager;
        }
    );

    TypeInfo* eMusicManager::getType() const
    {
        return &E_MUSICMANAGER_TYPEINFO;
    }

    eMusicManager::eMusicManager()
    : Gadget()
    {
        name = "musicManager";
    }

    eMusicManager::~eMusicManager() {}


    ////////////////////////////////////////////////////////////////
    // Static Gadget
    ////////////////////////////////////////////////////////////////

    eMusicManager theMusicManager;

}
