#include <ElephantEngine/eGroupManager.h>
#include <ElephantBase/Archive.h>

#include <ElephantEngine/eGroup.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eGroupManager interface
    // <kao2.0042C962> (constructor)
    // <kao2.00420080> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_GROUPMANAGER_TYPEINFO
    (
        E_GROUPMANAGER_ID,
        "eGroupManager",
        &E_REFCOUNTER_TYPEINFO,
        []() -> eObject*
        {
            return new eGroupManager;
        }
    );

    const TypeInfo* eGroupManager::getType() const
    {
        return &E_GROUPMANAGER_TYPEINFO;
    }

    eGroupManager::eGroupManager()
    : eRefCounter()
    {
        /*[0x08]*/ groupsCount = 0;
        /*[0x0C]*/ groupsMaxLength = 0;
        /*[0x10]*/ groups = nullptr;
    }

    eGroupManager::~eGroupManager()
    {
        if (nullptr != groups)
        {
            delete[](groups);
        }
    }


    ////////////////////////////////////////////////////////////////
    // eGroupManager: cloning the object
    ////////////////////////////////////////////////////////////////

    void eGroupManager::createFromOtherObject(const eGroupManager &other)
    {
        if (other.groupsCount > 0)
        {
            groupsMaxLength = other.groupsCount;
            groups = new eGroup* [groupsMaxLength];

            for (groupsCount = 0; groupsCount < groupsMaxLength; groupsCount++)
            {
                groups[groupsCount] = (eGroup*) other.groups[groupsCount]->cloneFromMe();
            }
        }
        else
        {
            groupsCount = 0;
            groupsMaxLength = 0;
            groups = nullptr;
        }
    }

    eGroupManager::eGroupManager(const eGroupManager &other)
    : eRefCounter(other)
    {
        createFromOtherObject(other);
    }

    eGroupManager& eGroupManager::operator = (const eGroupManager &other)
    {
        if ((&other) != this)
        {
            eRefCounter::operator = (other);

            /****************/

            if (nullptr != groups)
            {
                delete[](groups);
            }

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eGroupManager::cloneFromMe() const
    {
        return new eGroupManager(*this);
    }


    ////////////////////////////////////////////////////////////////
    // eGroupManager: serialization
    // <kao2.0042C340>
    ////////////////////////////////////////////////////////////////
    void eGroupManager::serialize(Archive &ar)
    {
        int32_t i;

        /* [0x08] unknown group ("eGroup" type is assumed !!!) */

        if (ar.isInReadMode())
        {
            if (nullptr != groups)
            {
                delete[](groups);
                groups = nullptr;

                groupsCount = 0;
                groupsMaxLength = 0;
            }

            ar.readOrWrite(&groupsMaxLength, 0x04);

            for (i = 0; i < groupsMaxLength; i++)
            {
                groups[i] = nullptr;

                groupsCount = (i+1);

                ar.serialize((eObject**)&(groups[i]), &E_GROUP_TYPEINFO);
            }
        }
        else
        {
            ar.readOrWrite(&groupsCount, 0x04);

            for (i = 0; i < groupsCount; i++)
            {
                groups[i] = nullptr;

                ar.serialize((eObject**)&(groups[i]), &E_GROUP_TYPEINFO);
            }

        }
    }

}
