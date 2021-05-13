#include <ElephantEngine/eWhaleManager.h>
#include <ElephantBase/Archive.h>

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

    const TypeInfo* eWhaleManager::getType() const
    {
        return &E_WHALEMANAGER_TYPEINFO;
    }

    eWhaleManager::eWhaleManager()
    : Gadget()
    {}

    eWhaleManager::~eWhaleManager()
    {}


    ////////////////////////////////////////////////////////////////
    // eWhaleManager: cloning the object
    ////////////////////////////////////////////////////////////////

    void eWhaleManager::createFromOtherObject(const eWhaleManager &other)
    {}

    eWhaleManager::eWhaleManager(const eWhaleManager &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eWhaleManager& eWhaleManager::operator = (const eWhaleManager &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eWhaleManager::cloneFromMe() const
    {
        return new eWhaleManager(*this);
    }

}
