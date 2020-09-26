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

    eMusicManager::~eMusicManager()
    {}


    ////////////////////////////////////////////////////////////////
    // eMusicManager: cloning the object
    ////////////////////////////////////////////////////////////////

    void eMusicManager::createFromOtherObject(const eMusicManager &other)
    {}

    eMusicManager::eMusicManager(const eMusicManager &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eMusicManager& eMusicManager::operator = (const eMusicManager &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eMusicManager::cloneFromMe() const
    {
        return new eMusicManager(*this);
    }


    ////////////////////////////////////////////////////////////////
    // Static Gadget
    ////////////////////////////////////////////////////////////////

    eMusicManager theMusicManager;

}
