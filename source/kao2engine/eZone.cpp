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

        new eALZoneSensor(this, boxBound);
    }

    eZone::~eZone()
    {}


    ////////////////////////////////////////////////////////////////
    // eZone: cloning the object
    ////////////////////////////////////////////////////////////////

    void eZone::createFromOtherObject(const eZone &other)
    {
        enterActions = other.enterActions;
        leaveActions = other.leaveActions;

        boxBoundMin = other.boxBoundMin;
        boxBoundMax = other.boxBoundMax;
    }

    eZone::eZone(const eZone &other)
    : eNode(other)
    {
        createFromOtherObject(other);
    }

    eZone& eZone::operator = (const eZone &other)
    {
        if ((&other) != this)
        {
            eNode::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eZone::cloneFromMe() const
    {
        return nullptr;
    }


    ////////////////////////////////////////////////////////////////
    // eZone: serialization
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
    void eZone::writeStructureToTextFile(FileOperator &file, int32_t indentation, bool group_written) const
    {
        char bufor[64];

        /* "eNode" parent class */
        eNode::writeStructureToTextFile(file, indentation, true);

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

        enterActions.writeStructureToTextFile(file, indentation, true);

        ArFunctions::writeIndentation(file, indentation);
        file << " - leave actions:";
        ArFunctions::writeNewLine(file, 0);

        leaveActions.writeStructureToTextFile(file, indentation, true);
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
    // eZone: create collision entry
    ////////////////////////////////////////////////////////////////
    bool eZone::createCollisionEntry()
    {
        float boundaries[6] =
        {
            boxBoundMin.x, boxBoundMin.y, boxBoundMin.z,
            boxBoundMax.x, boxBoundMax.y, boxBoundMax.z
        };

        new eALZoneSensor(this, boundaries);

        return true;
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
    // eZone: preparing just-created node
    ////////////////////////////////////////////////////////////////
    void eZone::editingNewNodeSetup()
    {
        createCollisionEntry();

        eNode::editingNewNodeSetup();
    }


    ////////////////////////////////////////////////////////////////
    // eZone: custom TXT parser methods
    ////////////////////////////////////////////////////////////////

    int32_t eZone::parsingSetProperty(char* result_msg, const TxtParsingNodeProp &property)
    {
        int32_t test;
        float dummy_floats[3];
        eString prop_name;

        if (1 != (test = eNode::parsingSetProperty(result_msg, property)))
        {
            return test;
        }

        prop_name = property.getName();

        if (prop_name.compareExact("min", true))
        {
            if (!property.checkType(TXT_PARSING_NODE_PROPTYPE_FLOAT3))
            {
                TxtParsingNode_ErrorPropType(result_msg, "min", TXT_PARSING_NODE_PROPTYPE_FLOAT3);
                return 2;
            }

            property.getValue(dummy_floats);

            boxBoundMin.x = dummy_floats[0];
            boxBoundMin.y = dummy_floats[1];
            boxBoundMin.z = dummy_floats[2];
            return 0;
        }
        else if (prop_name.compareExact("max", true))
        {
            if (!property.checkType(TXT_PARSING_NODE_PROPTYPE_FLOAT3))
            {
                TxtParsingNode_ErrorPropType(result_msg, "max", TXT_PARSING_NODE_PROPTYPE_FLOAT3);
                return 2;
            }

            property.getValue(dummy_floats);

            boxBoundMax.x = dummy_floats[0];
            boxBoundMax.y = dummy_floats[1];
            boxBoundMax.z = dummy_floats[2];
            return 0;
        }

        return 1;
    }

    int32_t eZone::parsingCustomMessage(char* result_msg, const eString &message, int32_t params_count, const TxtParsingNodeProp* params)
    {
        int32_t test;
        float dummy_floats[3];
        eActionBase dummy_action;

        if (1 != (test = eNode::parsingCustomMessage(result_msg, message, params_count, params)))
        {
            return test;
        }

        if (message.compareExact("setBoundaryBox", true))
        {
            if (2 != params_count)
            {
                TxtParsingNode_ErrorArgCount(result_msg, "setBoundaryBox", 2);
                return 2;
            }

            /********************************/

            if (!params[0].checkType(TXT_PARSING_NODE_PROPTYPE_FLOAT3))
            {
                TxtParsingNode_ErrorArgType(result_msg, "setBoundaryBox", 1, TXT_PARSING_NODE_PROPTYPE_FLOAT3);
                return 2;
            }

            params[0].getValue(dummy_floats);

            boxBoundMin.x = dummy_floats[0];
            boxBoundMin.y = dummy_floats[1];
            boxBoundMin.z = dummy_floats[2];

            /********************************/

            if (!params[1].checkType(TXT_PARSING_NODE_PROPTYPE_FLOAT3))
            {
                TxtParsingNode_ErrorArgType(result_msg, "setBoundaryBox", 2, TXT_PARSING_NODE_PROPTYPE_FLOAT3);
                return 2;
            }

            params[1].getValue(dummy_floats);

            boxBoundMax.x = dummy_floats[0];
            boxBoundMax.y = dummy_floats[1];
            boxBoundMax.z = dummy_floats[2];

            /********************************/

            createCollisionEntry();
            return 0;
        }
        else if (message.compareExact("clearEnterActions", true))
        {
            if (0 != params_count)
            {
                TxtParsingNode_ErrorArgCount(result_msg, "clearEnterActions", 0);
                return 2;
            }

            /********************************/

            enterActions.clearActions();
            return 0;
        }
        else if (message.compareExact("clearLeaveActions", true))
        {
            if (0 != params_count)
            {
                TxtParsingNode_ErrorArgCount(result_msg, "clearLeaveActions", 0);
                return 2;
            }

            /********************************/

            leaveActions.clearActions();
            return 0;
        }
        else if (message.compareExact("addEnterAction", true))
        {
            if (2 != params_count)
            {
                TxtParsingNode_ErrorArgCount(result_msg, "addEnterAction", 2);
                return 2;
            }

            /********************************/

            if (params[0].checkType(TXT_PARSING_NODE_PROPTYPE_NODEREF))
            {
                params[0].getValue(&(dummy_action.nodeTarget));

                if (nullptr == dummy_action.nodeTarget)
                {
                    sprintf_s(result_msg, LARGE_BUFFER_SIZE, "\"addEnterAction\" message: noderef is not set!");
                    return 2;
                }

                dummy_action.nodeTarget->incRef();
            }
            else if (params[0].checkType(TXT_PARSING_NODE_PROPTYPE_STRING))
            {
                params[0].getValue(&(dummy_action.actorName));
            }
            else
            {
                sprintf_s(result_msg, LARGE_BUFFER_SIZE, "\"addEnterAction\" message: expected the first argument to be a noderef or string!");
                return 2;
            }

            /********************************/

            if (!params[1].checkType(TXT_PARSING_NODE_PROPTYPE_STRING))
            {
                TxtParsingNode_ErrorArgType(result_msg, "addEnterAction", 2, TXT_PARSING_NODE_PROPTYPE_STRING);
                return 2;
            }

            params[1].getValue(&(dummy_action.message));

            /********************************/

            enterActions.addAction(dummy_action);
            return 0;
        }
        else if (message.compareExact("addLeaveAction", true))
        {
            if (2 != params_count)
            {
                TxtParsingNode_ErrorArgCount(result_msg, "addLeaveAction", 2);
                return 2;
            }

            /********************************/

            if (params[0].checkType(TXT_PARSING_NODE_PROPTYPE_NODEREF))
            {
                params[0].getValue(&(dummy_action.nodeTarget));

                if (nullptr == dummy_action.nodeTarget)
                {
                    sprintf_s(result_msg, LARGE_BUFFER_SIZE, "\"addLeaveAction\" message: noderef is not set!");
                    return 2;
                }

                dummy_action.nodeTarget->incRef();
            }
            else if (params[0].checkType(TXT_PARSING_NODE_PROPTYPE_STRING))
            {
                params[0].getValue(&(dummy_action.actorName));
            }
            else
            {
                sprintf_s(result_msg, LARGE_BUFFER_SIZE, "\"addLeaveAction\" message: expected the first argument to be a noderef or string!");
                return 2;
            }

            /********************************/

            if (!params[1].checkType(TXT_PARSING_NODE_PROPTYPE_STRING))
            {
                TxtParsingNode_ErrorArgType(result_msg, "addLeaveAction", 2, TXT_PARSING_NODE_PROPTYPE_STRING);
                return 2;
            }

            params[1].getValue(&(dummy_action.message));

            /********************************/

            leaveActions.addAction(dummy_action);
            return 0;
        }

        return 1;
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
