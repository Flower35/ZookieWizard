#include <ElephantEngine/eParticleManager.h>
#include <ElephantBase/Archive.h>

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

    eParticleManager::~eParticleManager()
    {}


    ////////////////////////////////////////////////////////////////
    // eParticleManager: cloning the object
    ////////////////////////////////////////////////////////////////

    void eParticleManager::createFromOtherObject(const eParticleManager &other)
    {}

    eParticleManager::eParticleManager(const eParticleManager &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eParticleManager& eParticleManager::operator = (const eParticleManager &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eParticleManager::cloneFromMe() const
    {
        return new eParticleManager(*this);
    }

}
