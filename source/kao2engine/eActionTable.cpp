#include <kao2engine/eActionTable.h>
#include <kao2ar/Archive.h>

#include <kao2engine/eNode.h>
#include <kao2engine/eCameraZonePacket.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eActionTable interface
    // <kao2.004AF9A9> (constructor)
    // <kao2.0049D6F0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_ACTIONTABLE_TYPEINFO
    (
        E_ACTIONTABLE_ID,
        "eActionTable",
        &E_REFCOUNTER_TYPEINFO,
        []() -> eObject*
        {
            return new eActionTable;
        }
    );

    TypeInfo* eActionTable::getType() const
    {
        return &E_ACTIONTABLE_TYPEINFO;
    }

    eActionTable::eActionTable()
    : eRefCounter()
    {
        /*[0x08]*/ actionsCount = 0;
        /*[0x0C]*/ actionsMaxLength = 0;
        /*[0x10]*/ actions = nullptr;
    }

    eActionTable::~eActionTable()
    {
        if (nullptr != actions)
        {
            delete[](actions);
        }
    }


    ////////////////////////////////////////////////////////////////
    // eActionTable: cloning the object
    ////////////////////////////////////////////////////////////////

    void eActionTable::createFromOtherObject(const eActionTable &other)
    {
        if (other.actionsCount > 0)
        {
            actionsCount = other.actionsCount;
            actionsMaxLength = actionsCount;

            actions = new eActionBase [actionsMaxLength];

            for (int32_t a = 0; a < actionsCount; a++)
            {
                addAction(other.actions[a]);
            }
        }
        else
        {
            actionsCount = 0;
            actionsMaxLength = 0;
            actions = nullptr;
        }
    }

    eActionTable::eActionTable(const eActionTable &other)
    : eRefCounter(other)
    {
        createFromOtherObject(other);
    }

    eActionTable& eActionTable::operator = (const eActionTable &other)
    {
        if ((&other) != this)
        {
            eRefCounter::operator = (other);

            /****************/

            clearActions();

            if (nullptr != actions)
            {
                delete[](actions);
                actions = nullptr;
            }

            actionsMaxLength = 0;

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eActionTable::cloneFromMe() const
    {
        return new eActionTable(*this);
    }


    ////////////////////////////////////////////////////////////////
    // Action Structure
    // <kao2.004AF0C0> (constructor)
    // <kao2.004AF470> (serialization)
    ////////////////////////////////////////////////////////////////

    eActionBase::eActionBase()
    {
        /*[0x04]*/ nodeTarget = nullptr;
        /*[0x0C]*/ cameraPacket = nullptr;
        /*[0x10]*/ unknown_10 = 0;
        /*[0x14]*/ unknown_14 = 0x00;
        /*[0x15]*/ unknown_15 = 0x01;
    }

    eActionBase::~eActionBase()
    {
        /*[0x0C]*/ cameraPacket->decRef();
        cameraPacket = nullptr;

        /*[0x04]*/ nodeTarget->decRef();
        nodeTarget = nullptr;
    }

    void eActionBase::createFromOtherObject(const eActionBase &other)
    {
        message = other.message;
        unknown_10 = other.unknown_10;
        unknown_14 = other.unknown_14;
        unknown_15 = other.unknown_15;
        actorName = other.actorName;

        nodeTarget = other.nodeTarget;
        if (nullptr != nodeTarget)
        {
            nodeTarget->incRef();
        }

        cameraPacket = other.cameraPacket;
        if (nullptr != cameraPacket)
        {
            cameraPacket->incRef();
        }
    }

    eActionBase::eActionBase(const eActionBase &other)
    {
        createFromOtherObject(other);
    }

    eActionBase& eActionBase::operator = (const eActionBase &other)
    {
        if ((&other) != this)
        {
            nodeTarget->decRef();

            cameraPacket->decRef();

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    void eActionBase::serializeAction(Archive &ar)
    {
        /* [0x04] The actor who receives the message */
        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&nodeTarget, &E_NODE_TYPEINFO);

        /* [0x18] If actor doesn't exits in this scene, serialize its name */
        if (nullptr == nodeTarget)
        {
            ar.serializeString(actorName);
        }
        else
        {
            actorName = "";
        }

        /* [0x08] The message to send */
        ar.serializeString(message);

        /* [0x0C] Camera? */
        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&cameraPacket, &E_CAMERAZONEPACKET_TYPEINFO);

        /* [0x10] Unknown values */
        ar.readOrWrite(&unknown_10, 0x04);
        ar.readOrWrite(&unknown_14, 0x01);
        ar.readOrWrite(&unknown_15, 0x01);
    }


    ////////////////////////////////////////////////////////////////
    // eActionTable: serialization
    // <kao2.004AF910>
    ////////////////////////////////////////////////////////////////
    void eActionTable::serialize(Archive &ar)
    {
        int32_t i;

        if (ar.isInReadMode())
        {
            if (nullptr != actions)
            {
                delete[](actions);
            }

            ar.readOrWrite(&actionsMaxLength, 0x04);

            actions = new eActionBase [actionsMaxLength];

            for (i = 0; i < actionsMaxLength; i++)
            {
                actions[i].serializeAction(ar);

                actionsCount = (i+1);
            }
        }
        else
        {
            ar.readOrWrite(&actionsCount, 0x04);

            for (i = 0; i < actionsCount; i++)
            {
                actions[i].serializeAction(ar);
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eActionTable: export readable structure
    ////////////////////////////////////////////////////////////////
    void eActionTable::writeStructureToTextFile(FileOperator &file, int32_t indentation, bool group_written) const
    {
        eString target_name;

        char bufor[LARGE_BUFFER_SIZE];

        for (int i = 0; i < actionsCount; i++)
        {
            if (nullptr != actions[i].nodeTarget)
            {
                target_name = actions[i].nodeTarget->getStringRepresentation();
            }
            else
            {
                target_name = actions[i].actorName;
            }

            if (target_name.getLength() <= 0)
            {
                target_name = "<UNNAMED TARGET>";
            }

            sprintf_s
            (
                bufor, LARGE_BUFFER_SIZE,
                "    [%d/%d]: \"%s\".%s()",
                (i + 1),
                actionsCount,
                target_name.getText(),
                actions[i].message.getText()
            );

            ArFunctions::writeIndentation(file, indentation);
            file << bufor;
            ArFunctions::writeNewLine(file, 0);
        }
    }


    ////////////////////////////////////////////////////////////////
    // eActionTable: delete i-th action from the list
    ////////////////////////////////////////////////////////////////
    void eActionTable::deleteIthAction(int32_t i)
    {
        if ((i >= 0) && (i < actionsCount))
        {
            for (i++; i < actionsCount; i++)
            {
                actions[i - 1] = actions[i];
            }

            actionsCount--;

            /* Reset the last action after shiftng */
            actions[actionsCount] = eActionBase();
        }
    }


    ////////////////////////////////////////////////////////////////
    // eActionTable: find reference to some node when deleting it
    ////////////////////////////////////////////////////////////////
    void eActionTable::findAndDeleteActionsWithNode(const eNode* target)
    {
        int32_t i;

        for (i = 0; i < actionsCount; i++)
        {
            if (target == actions[i].nodeTarget)
            {
                deleteIthAction(i);

                /* Actions were shifted to the left */
                i--;
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eActionTable: clear all the actions
    ////////////////////////////////////////////////////////////////
    void eActionTable::clearActions()
    {
        while (actionsCount > 0)
        {
            deleteIthAction(0);

            /* Actions are shifted to the first position */
        }
    }


    ////////////////////////////////////////////////////////////////
    // eActionTable: insert a new action
    ////////////////////////////////////////////////////////////////
    void eActionTable::addAction(eActionBase &new_action)
    {
        if ((actionsCount + 1) >= actionsMaxLength)
        {
            eActionBase* dummy_actions = new eActionBase [actionsMaxLength + 1];

            if (nullptr != actions)
            {
                for (int i = 0; i < actionsCount; i++)
                {
                    dummy_actions[i] = actions[i];
                }

                delete[](actions);
            }

            actions = dummy_actions;

            actionsMaxLength++;
        }

        actions[actionsCount] = new_action;
        actionsCount++;
    }

}
