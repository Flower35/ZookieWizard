#include <kao2engine/eZone.h>
#include <kao2ar/Archive.h>

#include <kao2engine/eALZoneSensor.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eZone interface
    // <kao2.0049D4F0> (constructor)
    // <kao2.0049D830> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_ZONE_TYPEINFO
    (
        E_ZONE_ID,
        "eZone",
        &E_NODE_TYPEINFO,
        []() -> eObject*
        {
            return nullptr;
        }
    );

    TypeInfo* eZone::getType() const
    {
        return &E_ZONE_TYPEINFO;
    }

    eZone::eZone()
    : eNode()
    {
        eALZoneSensor* test_sensor;

        /*[0x64] empty group */
        /*[0x68] empty group */
        /*[0x6C] empty group */

        /*[0x1C]*/ flags |= 0x40000000;

        /*[0x14]*/ name = "Zone";

        float boxBound[6] =
        {
            0, 0, 0,
            1.0f, 1.0f, 1.0f
        };

        test_sensor = new eALZoneSensor(this, boxBound);

        /* [0x18] replace "eALZoneSensor" */

        setAxisListBox(test_sensor);
    }

    eZone::~eZone()
    {}


    ////////////////////////////////////////////////////////////////
    // eZone serialization
    // <kao2.0049DD20>
    ////////////////////////////////////////////////////////////////
    void eZone::serialize(Archive &ar)
    {
        int32_t a;

        eNode::serialize(ar);

        /* Something deprecated */
        a = 0x01;
        ar.readOrWrite(&a, 0x01);

        /* [0x64] unknown group */
        a = 0;
        ar.readOrWrite(&a, 0x04);
        if (0 != a)
        {
            throw ErrorMessage
            (
                "eZone::serialize():\n" \
                "non-empty group is not supported !!!"
            );
        }

        /* [0x3C] [0x50] Enter actions and Leave actions */
        enterActions.serialize(ar);
        leaveActions.serialize(ar);

        if (ar.isInReadMode())
        {
            flags |= 0x00000004;
        }
    }


    ////////////////////////////////////////////////////////////////
    // eZone: export readable structure
    ////////////////////////////////////////////////////////////////
    void eZone::writeStructureToTextFile(FileOperator &file, int32_t indentation) const
    {
        char bufor[64];
        /* "eNode" parent class */

        eNode::writeStructureToTextFile(file, indentation);

        /* "eZone" additional info */

        sprintf_s(bufor, 64, " - boxBoundMin: (%f, %f, %f)", boxBoundMin.x, boxBoundMin.y, boxBoundMin.z);

        ArFunctions::writeIndentation(file, indentation);
        file << bufor;
        ArFunctions::writeNewLine(file, 0);

        sprintf_s(bufor, 64, " - boxBoundMax: (%f, %f, %f)", boxBoundMax.x, boxBoundMax.y, boxBoundMax.z);

        ArFunctions::writeIndentation(file, indentation);
        file << bufor;
        ArFunctions::writeNewLine(file, 0);

        ArFunctions::writeIndentation(file, indentation);
        file << " - enter actions:";
        ArFunctions::writeNewLine(file, 0);

        enterActions.writeStructureToTextFile(file, indentation);

        ArFunctions::writeIndentation(file, indentation);
        file << " - leave actions:";
        ArFunctions::writeNewLine(file, 0);

        leaveActions.writeStructureToTextFile(file, indentation);
    }


    ////////////////////////////////////////////////////////////////
    // eZone: (editor option) find object in 3D space
    ////////////////////////////////////////////////////////////////
    ePoint3 eZone::editingGetCenterPoint() const
    {
        return (boxBoundMax + boxBoundMin) * 0.5f;
    }


    ////////////////////////////////////////////////////////////////
    // eZone: (editor option) rebuild collision
    ////////////////////////////////////////////////////////////////
    void eZone::editingRebuildCollision()
    {
        createCollisionEntry();
    }


    ////////////////////////////////////////////////////////////////
    // eZone: (editor option) apply new transformation
    ////////////////////////////////////////////////////////////////
    void eZone::editingApplyNewTransform(eSRP &new_transform, int32_t marked_id)
    {
        eMatrix4x4 matrix = new_transform.getMatrix();

        boxBoundMin = (matrix * ePoint4(boxBoundMin.x, boxBoundMin.y, boxBoundMin.z, 1.0f));

        boxBoundMax = (matrix * ePoint4(boxBoundMax.x, boxBoundMax.y, boxBoundMax.z, 1.0f));

        createCollisionEntry();
    }


    ////////////////////////////////////////////////////////////////
    // eZone: set boundary box
    ////////////////////////////////////////////////////////////////
    void eZone::setBoundaryBox(ePoint3 &new_min, ePoint3 &new_max)
    {
        boxBoundMin = new_min;
        boxBoundMax = new_max;

        createCollisionEntry();
    }


    ////////////////////////////////////////////////////////////////
    // eZone: create collision entry
    ////////////////////////////////////////////////////////////////
    void eZone::createCollisionEntry()
    {
        eALZoneSensor* new_sensor = nullptr;

        float boundaries[6] =
        {
            boxBoundMin.x, boxBoundMin.y, boxBoundMin.z,
            boxBoundMax.x, boxBoundMax.y, boxBoundMax.z
        };

        new_sensor = new eALZoneSensor(this, boundaries);
    }


    ////////////////////////////////////////////////////////////////
    // eZone: clear actions (zone could reference its own group)
    ////////////////////////////////////////////////////////////////
    void eZone::destroyNode()
    {
        enterActions.clearActions();

        leaveActions.clearActions();

        eNode::destroyNode();
    }


    ////////////////////////////////////////////////////////////////
    // eZone: find reference to some node when deleting it
    ////////////////////////////////////////////////////////////////
    void eZone::findAndDereference(eNode* target)
    {
        enterActions.findAndDeleteActionsWithNode(target);

        leaveActions.findAndDeleteActionsWithNode(target);
    }


    ////////////////////////////////////////////////////////////////
    // eZone: clear all the actions ("enterActions" or "leaveActions")
    ////////////////////////////////////////////////////////////////
    void eZone::zoneClearActions(bool enter_or_leave)
    {
        if (enter_or_leave)
        {
            enterActions.clearActions();
        }
        else
        {
            leaveActions.clearActions();
        }
    }


    ////////////////////////////////////////////////////////////////
    // eZone: insert a new action ("enterActions" or "leaveActions")
    ////////////////////////////////////////////////////////////////
    void eZone::zoneAddAction(bool enter_or_leave, eActionBase &new_action)
    {
        if (enter_or_leave)
        {
            enterActions.addAction(new_action);
        }
        else
        {
            leaveActions.addAction(new_action);
        }
    }

}
