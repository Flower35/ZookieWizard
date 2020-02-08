#include <kao2engine/eParticleManager.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eParticleManager interface
    // <kao2.00445D00> (constructor)
    // <kao2.00445DF0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_PARTICLEMANAGER_TYPEINFO
    (
        E_PARTICLEMANAGER_ID,
        "eParticleManager",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eParticleManager;
        }
    );

    TypeInfo* eParticleManager::getType() const
    {
        return &E_PARTICLEMANAGER_TYPEINFO;
    }

    eParticleManager::eParticleManager()
    : Gadget()
    {}

    eParticleManager::~eParticleManager() {}

}
