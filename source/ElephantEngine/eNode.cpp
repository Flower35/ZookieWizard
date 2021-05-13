#include <ElephantEngine/eNode.h>
#include <ElephantBase/Archive.h>
#include <ElephantBase/eDrawContext.h>

#include <ZookieWizard/WindowsManager.h>
#include <ElephantEngine/Log.h>

#include <ElephantEngine/eALBox.h>
#include <ElephantEngine/eLeafCtrl.h>
#include <ElephantEngine/eMultiCtrl.h>
#include <ElephantEngine/eScene.h>
#include <ElephantEngine/eGeometry.h>

namespace ZookieWizard
{
    #ifdef _DEBUG
        /*** Finding memory leaks ***/
        eNode* theNodesDebug[AR_MAX_ITEMS] = {nullptr};
    #endif


    ////////////////////////////////////////////////////////////////
    // eNode: helper definitions and structures
    ////////////////////////////////////////////////////////////////

    const char* theNodeFlagNames[32] =
    {
        "Visible (node)", // 0x00000001
        "???", // 0x00000002
        "Awoken (actor)", // 0x00000004
        "Enabled (node)", // 0x00000008
        "???", // 0x00000010
        "???", // 0x00000020
        "???", // 0x00000040
        "\"SD\" ???", // 0x00000080
        "???", // 0x00000100
        "???", // 0x00000200
        "Update (node)", // 0x00000400
        "???", // 0x00000800
        "SRP Inheritance (pivot)", // 0x00001000
        "???", // 0x00002000
        "Anim Inheritance (pivot)", // 0x00004000
        "???", // 0x00008000
        "Relative Ctrl (pivot) / Ready (proxy)", // 0x00010000
        "??? (pivot)", // 0x00020000
        "Ctrl Blend (pivot)", // 0x00040000
        "???", // 0x00080000
        "???", // 0x00100000
        "???", // 0x00200000
        "???", // 0x00400000
        "???", // 0x00800000
        "???", // 0x01000000
        "???", // 0x02000000
        "???", // 0x04000000
        "???", // 0x08000000
        "DrawPass #1", // 0x10000000
        "DrawPass #2", // 0x20000000
        "DrawPass #3", // 0x40000000
        "???", // 0x80000000
    };

    TxtParsingNodeProp::TxtParsingNodeProp()
    {
        type = TXT_PARSING_NODE_PROPTYPE_UNKNOWN;

        nodeValue = nullptr;
    }

    TxtParsingNodeProp::~TxtParsingNodeProp()
    {
        nodeValue->decRef();
    }

    void TxtParsingNodeProp::createFromOtherObject(const TxtParsingNodeProp &other)
    {
        type = other.type;
        name = other.name;

        intValue = other.intValue;
        floatValues[0] = other.floatValues[0];
        floatValues[1] = other.floatValues[1];
        floatValues[2] = other.floatValues[2];
        floatValues[3] = other.floatValues[3];
        strValue = other.strValue;

        nodeValue = other.nodeValue;
        if (nullptr != nodeValue)
        {
            nodeValue->incRef();
        }
    }

    TxtParsingNodeProp::TxtParsingNodeProp(const TxtParsingNodeProp &other)
    {
        createFromOtherObject(other);
    }

    TxtParsingNodeProp& TxtParsingNodeProp::operator = (const TxtParsingNodeProp &other)
    {
        if ((&other) != this)
        {
            nodeValue->decRef();

            createFromOtherObject(other);
        }

        return (*this);
    }

    eString TxtParsingNodeProp::getName() const
    {
        return name;
    }

    void TxtParsingNodeProp::setName(eString new_name)
    {
        name = new_name;
    }

    bool TxtParsingNodeProp::checkType(int32_t expected_type) const
    {
        return (type == expected_type);
    }

    bool TxtParsingNodeProp::getValue(void* result_ptr) const
    {
        if (nullptr != result_ptr)
        {
            switch (type)
            {
                case TXT_PARSING_NODE_PROPTYPE_INTEGER:
                {
                    *(int32_t*)result_ptr = intValue;
                    return true;
                }

                case TXT_PARSING_NODE_PROPTYPE_FLOAT1:
                {
                    ((float*)result_ptr)[0] = floatValues[0];
                    return true;
                }

                case TXT_PARSING_NODE_PROPTYPE_FLOAT2:
                {
                    ((float*)result_ptr)[0] = floatValues[0];
                    ((float*)result_ptr)[1] = floatValues[1];
                    return true;
                }

                case TXT_PARSING_NODE_PROPTYPE_FLOAT3:
                {
                    ((float*)result_ptr)[0] = floatValues[0];
                    ((float*)result_ptr)[1] = floatValues[1];
                    ((float*)result_ptr)[2] = floatValues[2];
                    return true;
                }

                case TXT_PARSING_NODE_PROPTYPE_FLOAT4:
                {
                    ((float*)result_ptr)[0] = floatValues[0];
                    ((float*)result_ptr)[1] = floatValues[1];
                    ((float*)result_ptr)[2] = floatValues[2];
                    ((float*)result_ptr)[3] = floatValues[3];
                    return true;
                }

                case TXT_PARSING_NODE_PROPTYPE_STRING:
                {
                    *(eString*)result_ptr = strValue;
                    return true;
                }

                case TXT_PARSING_NODE_PROPTYPE_NODEREF:
                {
                    *(eNode**)result_ptr = nodeValue;
                    return true;
                }
            }
        }

        return false;
    }

    void TxtParsingNodeProp::setValue(int32_t new_type, void* new_value_ptr)
    {
        if (nullptr == new_value_ptr)
        {
            new_type = TXT_PARSING_NODE_PROPTYPE_UNKNOWN;
            return;
        }

        switch (new_type)
        {
            case TXT_PARSING_NODE_PROPTYPE_INTEGER:
            {
                intValue = *(int32_t*)new_value_ptr;
                break;
            }

            case TXT_PARSING_NODE_PROPTYPE_FLOAT1:
            {
                floatValues[0] = ((float*)new_value_ptr)[0];
                break;
            }

            case TXT_PARSING_NODE_PROPTYPE_FLOAT2:
            {
                floatValues[0] = ((float*)new_value_ptr)[0];
                floatValues[1] = ((float*)new_value_ptr)[1];
                break;
            }

            case TXT_PARSING_NODE_PROPTYPE_FLOAT3:
            {
                floatValues[0] = ((float*)new_value_ptr)[0];
                floatValues[1] = ((float*)new_value_ptr)[1];
                floatValues[2] = ((float*)new_value_ptr)[2];
                break;
            }

            case TXT_PARSING_NODE_PROPTYPE_FLOAT4:
            {
                floatValues[0] = ((float*)new_value_ptr)[0];
                floatValues[1] = ((float*)new_value_ptr)[1];
                floatValues[2] = ((float*)new_value_ptr)[2];
                floatValues[3] = ((float*)new_value_ptr)[3];
                break;
            }

            case TXT_PARSING_NODE_PROPTYPE_STRING:
            {
                strValue = *(eString*)new_value_ptr;
                break;
            }

            case TXT_PARSING_NODE_PROPTYPE_NODEREF:
            {
                nodeValue->decRef();

                nodeValue = *(eNode**)new_value_ptr;
                if (nullptr != nodeValue)
                {
                    nodeValue->incRef();
                }

                break;
            }

            default:
            {
                new_type = TXT_PARSING_NODE_PROPTYPE_UNKNOWN;
                return;
            }
        }

        type = new_type;
    }

    void TxtParsingNode_ErrorArgCount(char* result, const char* current_msg, int32_t expected)
    {
        if (expected <= 0)
        {
            sprintf_s(result, LARGE_BUFFER_SIZE, "\"%s\" message takes no arguments!", current_msg);
        }
        else
        {
            sprintf_s(result, LARGE_BUFFER_SIZE, "\"%s\" message: incorrect number of arguments! (Expected %d)", current_msg, expected);
        }
    }

    void TxtParsingNode_ErrorArgType(char* result, const char* current_msg, int32_t arg_num, int32_t expected_type)
    {
        const char* which_arg;
        const char* which_type;

        switch (arg_num)
        {
            case 1:
            {
                which_arg = " first";
                break;
            }

            case 2:
            {
                which_arg = " second";
                break;
            }

            case 3:
            {
                which_arg = " third";
                break;
            }

            case 4:
            {
                which_arg = " fourth";
                break;
            }

            case 5:
            {
                which_arg = " fifth";
                break;
            }

            case 6:
            {
                which_arg = " sixth";
                break;
            }

            default:
            {
                which_arg = "";
                break;
            }
        }

        switch (expected_type)
        {
            case TXT_PARSING_NODE_PROPTYPE_INTEGER:
            {
                which_type = "an integer";
                break;
            }

            case TXT_PARSING_NODE_PROPTYPE_FLOAT1:
            {
                which_type = "an integer or floating-point";
                break;
            }

            case TXT_PARSING_NODE_PROPTYPE_FLOAT2:
            {
                which_type = "a floating-point pair";
                break;
            }

            case TXT_PARSING_NODE_PROPTYPE_FLOAT3:
            {
                which_type = "a floating-point triple";
                break;
            }

            case TXT_PARSING_NODE_PROPTYPE_FLOAT4:
            {
                which_type = "a floating-point quadruple";
                break;
            }

            case TXT_PARSING_NODE_PROPTYPE_STRING:
            {
                which_type = "a string";
                break;
            }

            case TXT_PARSING_NODE_PROPTYPE_NODEREF:
            {
                which_type = "a NodeRef";
                break;
            }

            default:
            {
                which_type = "something";
                break;
            }
        }

        sprintf_s(result, LARGE_BUFFER_SIZE, "\"%s\" message: expected the%s argument to be %s!", current_msg, which_arg, which_type);
    }

    void TxtParsingNode_ErrorPropType(char* result, const char* current_prop, int32_t expected_type)
    {
        const char* which_type;

        switch (expected_type)
        {
            case TXT_PARSING_NODE_PROPTYPE_INTEGER:
            {
                which_type = "an integer";
                break;
            }

            case TXT_PARSING_NODE_PROPTYPE_FLOAT1:
            {
                which_type = "an integer or floating-point";
                break;
            }

            case TXT_PARSING_NODE_PROPTYPE_FLOAT2:
            {
                which_type = "a floating-point pair";
                break;
            }

            case TXT_PARSING_NODE_PROPTYPE_FLOAT3:
            {
                which_type = "a floating-point triple";
                break;
            }

            case TXT_PARSING_NODE_PROPTYPE_FLOAT4:
            {
                which_type = "a floating-point quadruple";
                break;
            }

            case TXT_PARSING_NODE_PROPTYPE_STRING:
            {
                which_type = "a string";
                break;
            }

            case TXT_PARSING_NODE_PROPTYPE_NODEREF:
            {
                which_type = "a NodeRef";
                break;
            }

            default:
            {
                which_type = "something";
                break;
            }
        }

        sprintf_s(result, LARGE_BUFFER_SIZE, "Expected \"%s\" property to be %s!", current_prop, which_type);
    }


    ////////////////////////////////////////////////////////////////
    // eNode interface
    // <kao2.00478AD0> (overloaded constructor)
    // <kao2.004789C0> (constructor)
    // <kao2.00478D50> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_NODE_TYPEINFO
    (
        E_NODE_ID,
        "eNode",
        &E_REFCOUNTER_TYPEINFO,
        []() -> eObject*
        {
            return new eNode;
        }
    );

    TypeInfo* eNode::getType() const
    {
        return &E_NODE_TYPEINFO;
    }

    eNode::eNode(eString s, eNode* x)
    : eNode()
    {
        /*[0x14]*/ name = s;

        if (nullptr != x)
        {
            /* (...) */
            /* "kao2.00478B55 -- CALL 00478E00" */
        }
    }

    eNode::eNode()
    : ePrimitive()
    {
        theNodesCounter++;

        #ifdef _DEBUG
            /*** Finding memory leaks ***/
            for (int i = 0; i < AR_MAX_ITEMS; i++)
            {
                if (nullptr == theNodesDebug[i])
                {
                    theNodesDebug[i] = this;
                    break;
                }
            }
        #endif

        /****************/

        /*[0x08]*/ previousTransform = nullptr;
        /*[0x0C]*/ unknown_0C = 0x00FFFFFF;
        /*[0x10]*/ parent = nullptr;
        /*[0x18]*/ axisListBox = nullptr;
        /*[0x1C]*/ flags = 0x249D;
        /*[0x30]*/ flagsCollisionResponse = 0x00FF;
        /*[0x34]*/ visCtrl = nullptr;
        /*[0x38]*/ visRate = 1.0f;
        /*[0x2C]*/ sphBound.w = (-1.0f);

        visGroup = (-1);
    }

    eNode::~eNode()
    {
        visCtrl->decRef();

        axisListBox->decRef();

        /****************/

        theNodesCounter--;

        #ifdef _DEBUG
            /*** Finding memory leaks ***/
            for (int i = 0; i < AR_MAX_ITEMS; i++)
            {
                if (this == theNodesDebug[i])
                {
                    theNodesDebug[i] = nullptr;
                    break;
                }
            }
        #endif

    }


    ////////////////////////////////////////////////////////////////
    // eNode: cloning the object
    ////////////////////////////////////////////////////////////////

    void eNode::createFromOtherObject(const eNode &other)
    {
        /* << MUST BE RESOLVED! >> */
        previousTransform = nullptr;

        unknown_0C = other.unknown_0C;

        /* << MUST BE RESOLVED! >> */
        parent = nullptr;

        name = other.name;

        /* << MUST BE RESOLVED! >> */
        axisListBox = nullptr;
        if (nullptr != other.axisListBox)
        {
            nodesManager_InsertNodeWithMissingAxisListBox(this);
        }

        flags = other.flags;

        sphBound = other.sphBound;

        flagsCollisionResponse = other.flagsCollisionResponse;

        visCtrl = other.visCtrl;
        if (nullptr != visCtrl)
        {
            visCtrl->incRef();
        }

        visRate = 1.0f;

        visGroup = other.visGroup;
    }

    eNode::eNode(const eNode &other)
    : ePrimitive(other)
    {
        theNodesCounter++;

        /****************/

        createFromOtherObject(other);
    }

    eNode& eNode::operator = (const eNode &other)
    {
        if ((&other) != this)
        {
            ePrimitive::operator = (other);

            /****************/

            eTransform* my_prev_xform = previousTransform;
            eGroup* my_parent = parent;

            axisListBox->decRef();

            visCtrl->decRef();

            /****************/

            createFromOtherObject(other);

            /****************/

            parent = my_parent;
            previousTransform = my_prev_xform;
        }

        return (*this);
    }

    eObject* eNode::cloneFromMe() const
    {
        return new eNode(*this);
    }


    ////////////////////////////////////////////////////////////////
    // eNode: serialization
    // <kao2.00478FF0>
    ////////////////////////////////////////////////////////////////
    void eNode::serialize(Archive &ar)
    {
        ePoint3 test_boundary[2];

        /* [0x14] Node Name */
        ar.serializeString(name);

        /* [0x10] Node Parent Link */
        ar.serialize((eObject**)&parent, &E_GROUP_TYPEINFO);

        /* ASSERTIONS */
        ar.setLastSerializedNode(this);

        /* Serializing other values */

        ar.readOrWrite(&unknown_0C, 0x04);

        if (ar.getVersion() <= 0x55)
        {
            throw ErrorMessage
            (
                "eNode::serialize():\n" \
                "ar.version() 86 required!"
            );
        }

        if (ar.getVersion() < 0x82)
        {
            test_boundary[0].serialize(ar);
            test_boundary[1].serialize(ar);

            if (getType()->checkHierarchy(&E_GEOMETRY_TYPEINFO))
            {
                ((eGeometry*)this)->oldNodeSerialization(test_boundary);
            }
        }

        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&axisListBox, &E_ALBOX_TYPEINFO);

        ar.readOrWrite(&flags, 0x04);

        sphBound.serialize(ar);

        /* Node's visibility controller (`GL_DIFFUSE` alpha channel, from 0 to 1.0) */

        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&visCtrl, &E_CTRL_FLOAT_TYPEINFO);

        /* Some almost-deprecated flags. */
        /* Object's collision is checked only when this valuse is NOT `0x00FF`. */

        ar.readOrWrite(&flagsCollisionResponse, 0x02);

        /* Visibility groups from "Kao Challengers" */

        if (ar.getVersion() < 0x8D)
        {
            visGroup = (-1);
        }
        else if (ar.getVersion() < 0x90)
        {
            int16_t x = visGroup;
            ar.readOrWrite(&x, 0x02);
            visGroup = x;
        }
        else
        {
            ar.readOrWrite(&visGroup, 0x04);
        }

        if (ar.isInReadMode())
        {
            flags |= 0x00002000;

            /* Setup for animations */
            setPreviousTransform();
        }
    }


    ////////////////////////////////////////////////////////////////
    // eNode: print
    ////////////////////////////////////////////////////////////////
    eString eNode::getLogPrintMessage() const
    {
        eString result = eObject::getLogPrintMessage();

        result += "\n - \"";
        result += name;
        result += "\"";

        return result;
    }


    ////////////////////////////////////////////////////////////////
    // eNode: export readable structure
    ////////////////////////////////////////////////////////////////
    void eNode::writeStructureToTextFile(FileOperator &file, int32_t indentation, bool group_written) const
    {
        char bufor[1024];
        TypeInfo* info = getType();

        sprintf_s
        (
            bufor, 1024,
            "[%08X] %s (\"%s\")",
            info->id,
            info->name,
            getDebugName(1024 - 64).getText()
        );

        ArFunctions::writeNewLine(file, indentation);
        file << bufor;

        sprintf_s
        (
            bufor, 1024,
            " - flags: %08X %08X %04X (visGroup: %d)",
            unknown_0C,
            flags,
            flagsCollisionResponse,
            visGroup
        );

        ArFunctions::writeNewLine(file, indentation);
        file << bufor;

        if (nullptr != parent)
        {
            info = parent->getType();

            sprintf_s
            (
                bufor, 1024,
                " - parent: [%08X] %s (\"%s\")",
                info->id,
                info->name,
                parent->getStringRepresentation().getText()
            );

            ArFunctions::writeNewLine(file, indentation);
            file << bufor;
        }

        if (nullptr != axisListBox)
        {
            info = axisListBox->getType();

            sprintf_s
            (
                bufor, 1024,
                " - albox: [%08X] %s (id=%08X)",
                info->id,
                info->name,
                axisListBox->getCollisionId()
            );

            ArFunctions::writeNewLine(file, indentation);
            file << bufor;
        }

        ArFunctions::writeNewLine(file, 0);
    }


    ////////////////////////////////////////////////////////////////
    // eNode: get name for debug purposes
    // (no whitespaces, trimmed if too long)
    ////////////////////////////////////////////////////////////////
    eString eNode::getDebugName(int32_t trim) const
    {
        return name.trimWhitespace().getSubstring(0, trim);
    }


    ////////////////////////////////////////////////////////////////
    // eNode: destroy before dereferencing
    ////////////////////////////////////////////////////////////////
    void eNode::destroyNode()
    {
        editingClearCollision(true);
    }


    ////////////////////////////////////////////////////////////////
    // eNode: empty function (for "eGroup" / "eZone")
    ////////////////////////////////////////////////////////////////
    void eNode::findAndDereference(eNode* target)
    {}


    ////////////////////////////////////////////////////////////////
    // eNode: find node by name
    // <kao2.00483900>
    ////////////////////////////////////////////////////////////////
    eNode* eNode::findNode(eString &searched_name) const
    {
        if (name.compareExact(searched_name, true))
        {
            return (eNode*)this;
        }

        return nullptr;
    }


    ////////////////////////////////////////////////////////////////
    // eNode: set `previousTransform` gradually
    ////////////////////////////////////////////////////////////////
    void eNode::setPreviousTransformGradually(eTransform* last_xform)
    {
        previousTransform = last_xform;
    }


    ////////////////////////////////////////////////////////////////
    // eNode: update DrawPass flags from children nodes
    ////////////////////////////////////////////////////////////////
    void eNode::updateDrawPassFlags(uint32_t* parent_flags)
    {
        if (nullptr != parent_flags)
        {
            (*parent_flags) |= (0x70000000 & flags);
        }
    }


    ////////////////////////////////////////////////////////////////
    // eNode: empty function (for "eGroup")
    ////////////////////////////////////////////////////////////////
    bool eNode::removeEmptyAndUnreferencedGroups()
    {
        /* Not a Group in the first place */
        return false;
    }


    ////////////////////////////////////////////////////////////////
    // eNode: empty function (for "eGroup" / "eDirectionalLight" / "eCamera")
    ////////////////////////////////////////////////////////////////
    void eNode::assertNodeLinksSameArchive()
    {}


    ////////////////////////////////////////////////////////////////
    // eNode: update before rendering [[vptr]+0x38]
    // <kao2.00479220>
    ////////////////////////////////////////////////////////////////
    void eNode::updateBeforeRendering(eDrawContext &draw_context)
    {
        if (nullptr != visCtrl)
        {
            visRate = visCtrl->ctrlGetTransform(visRate, draw_context.getAnimateObject());

            if (visRate <= 0)
            {
                flags &= (~ 0x00000001);
            }
            else
            {
                flags |= 0x00000001;
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eNode: default message for "AxisList" rebuilding ("eGeometry" / "eZone")
    ////////////////////////////////////////////////////////////////
    bool eNode::createCollisionEntry()
    {
        char bufor[LARGE_BUFFER_SIZE];

        sprintf_s
        (
            bufor, LARGE_BUFFER_SIZE,
            "WARNING: Don't know how to create Collision Entry for \"%s\" (\"%s\")...",
            getType()->name,
            name.getText()
        );

        GUI::theWindowsManager.displayMessage
        (
            WINDOWS_MANAGER_MESSAGE_WARNING,
            bufor
        );

        return false;
    }


    ////////////////////////////////////////////////////////////////
    // eNode: render this node
    ////////////////////////////////////////////////////////////////
    void eNode::renderNode(eDrawContext &draw_context) const
    {}


    ////////////////////////////////////////////////////////////////
    // eNode: empty function (for "eTransform" / "eTriMesh")
    ////////////////////////////////////////////////////////////////
    ePoint3 eNode::editingGetCenterPoint() const
    {
        return {0};
    }


    ////////////////////////////////////////////////////////////////
    // eNode: empty function (for "eGroup" / "eTriMesh")
    ////////////////////////////////////////////////////////////////
    void eNode::editingRebuildCollision()
    {}


    ////////////////////////////////////////////////////////////////
    // eNode: (editor function) clear collision
    ////////////////////////////////////////////////////////////////
    void eNode::editingClearCollision(bool create_empty_pointer)
    {
        if (nullptr != axisListBox)
        {
            axisListBox->decRef();

            /* "Nodes Manager" compatibility */
            axisListBox = create_empty_pointer ? (new eALBox()) : nullptr;
        }

        flagsCollisionResponse = 0x00FF;
    }


    ////////////////////////////////////////////////////////////////
    // eNode: empty function (for "eBoxZone" / "eTransform" / "eTriMesh")
    ////////////////////////////////////////////////////////////////
    void eNode::editingApplyNewTransform(eSRP &new_transform, int32_t marked_id)
    {}


    ////////////////////////////////////////////////////////////////
    // eNode: empty function (for "eCamera" / "eGeometry" / "eNPCMap" / "ePivot" / "eZone")
    ////////////////////////////////////////////////////////////////
    void eNode::editingNewNodeSetup()
    {}


    ////////////////////////////////////////////////////////////////
    // eNode: custom TXT parser methods
    // (returns 1 if no property / message was found
    //  2 for general errors, 0 otherwise)
    ////////////////////////////////////////////////////////////////

    int32_t eNode::parsingSetProperty(char* result_msg, const TxtParsingNodeProp &property)
    {
        int32_t test;
        eString prop_name = property.getName();
        eNode* dummy_node = nullptr;

        if (prop_name.compareExact("parent", true))
        {
            if (!property.checkType(TXT_PARSING_NODE_PROPTYPE_NODEREF))
            {
                TxtParsingNode_ErrorPropType(result_msg, "parent", TXT_PARSING_NODE_PROPTYPE_NODEREF);
                return 2;
            }

            property.getValue(&dummy_node);

            if (nullptr == dummy_node)
            {
                sprintf_s(result_msg, LARGE_BUFFER_SIZE, "Noderef for \"parent\" property is not set!");
                return 2;
            }

            if (!(dummy_node->getType()->checkHierarchy(&E_GROUP_TYPEINFO)))
            {
                sprintf_s(result_msg, LARGE_BUFFER_SIZE, "Expected the noderef of \"parent\" property to be a \"eGroup\" or its child!");
                return 2;
            }

            ((eGroup*)dummy_node)->appendChild(this);
            return 0;
        }
        else if (prop_name.compareExact("name", true))
        {
            if (!property.checkType(TXT_PARSING_NODE_PROPTYPE_STRING))
            {
                TxtParsingNode_ErrorPropType(result_msg, "name", TXT_PARSING_NODE_PROPTYPE_STRING);
                return 2;
            }

            property.getValue(&name);
            return 0;
        }
        else if (prop_name.compareExact("flags", true))
        {
            if (!property.checkType(TXT_PARSING_NODE_PROPTYPE_INTEGER))
            {
                TxtParsingNode_ErrorPropType(result_msg, "flags", TXT_PARSING_NODE_PROPTYPE_INTEGER);
                return 2;
            }

            property.getValue(&flags);
            return 0;
        }
        else if (prop_name.compareExact("collisionFlags", true))
        {
            if (!property.checkType(TXT_PARSING_NODE_PROPTYPE_INTEGER))
            {
                TxtParsingNode_ErrorPropType(result_msg, "collisionFlags", TXT_PARSING_NODE_PROPTYPE_INTEGER);
                return 2;
            }

            property.getValue(&test);
            flagsCollisionResponse = test & 0x00FF;
            return 0;
        }

        return 1;
    }

    int32_t eNode::parsingCustomMessage(char* result_msg, const eString &message, int32_t params_count, const TxtParsingNodeProp* params)
    {
        int32_t test[2];
        float dummy_floats[2];
        eNode* dummy_node = nullptr;

        if (message.compareExact("setParent", true))
        {
            if (1 != params_count)
            {
                TxtParsingNode_ErrorArgCount(result_msg, "setParent", 1);
                return 2;
            }

            /********************************/

            if (!params[0].checkType(TXT_PARSING_NODE_PROPTYPE_NODEREF))
            {
                TxtParsingNode_ErrorArgType(result_msg, "setParent", 0, TXT_PARSING_NODE_PROPTYPE_NODEREF);
                return 2;
            }

            /********************************/

            params[0].getValue(&dummy_node);

            if (nullptr == dummy_node)
            {
                sprintf_s(result_msg, LARGE_BUFFER_SIZE, "\"setParent\" message: noderef is not set!");
                return 2;
            }

            if (!(dummy_node->getType()->checkHierarchy(&E_GROUP_TYPEINFO)))
            {
                sprintf_s(result_msg, LARGE_BUFFER_SIZE, "\"setParent\" message: expected the noderef to be a \"eGroup\" or its child!");
                return 2;
            }

            /********************************/

            ((eGroup*)dummy_node)->appendChild(this);
            return 0;
        }
        else if (message.compareExact("setName", true))
        {
            if (1 != params_count)
            {
                TxtParsingNode_ErrorArgCount(result_msg, "setName", 1);
                return 2;
            }

            /********************************/

            if (!params[0].checkType(TXT_PARSING_NODE_PROPTYPE_STRING))
            {
                TxtParsingNode_ErrorArgType(result_msg, "setName", 0, TXT_PARSING_NODE_PROPTYPE_STRING);
                return 2;
            }

            /********************************/

            params[0].getValue(&name);
            return 0;
        }
        else if (message.compareExact("setFlags", true))
        {
            if (1 != params_count)
            {
                TxtParsingNode_ErrorArgCount(result_msg, "setFlags", 1);
                return 2;
            }

            /********************************/

            if (!params[0].checkType(TXT_PARSING_NODE_PROPTYPE_INTEGER))
            {
                TxtParsingNode_ErrorArgType(result_msg, "setFlags", 0, TXT_PARSING_NODE_PROPTYPE_INTEGER);
                return 2;
            }

            /********************************/

            params[0].getValue(&flags);
            return 0;
        }
        else if (message.compareExact("setCollisionFlags", true))
        {
            if (1 != params_count)
            {
                TxtParsingNode_ErrorArgCount(result_msg, "setCollisionFlags", 1);
                return 2;
            }

            /********************************/

            if (!params[0].checkType(TXT_PARSING_NODE_PROPTYPE_INTEGER))
            {
                TxtParsingNode_ErrorArgType(result_msg, "setCollisionFlags", 0, TXT_PARSING_NODE_PROPTYPE_INTEGER);
                return 2;
            }

            /********************************/

            params[0].getValue(&(test[0]));
            flagsCollisionResponse = test[0] & 0x00FF;
            return 0;
        }
        else if (message.compareExact("visCtrlClear", true))
        {
            if (1 != params_count)
            {
                TxtParsingNode_ErrorArgCount(result_msg, "visCtrlClear", 1);
                return 2;
            }

            /********************************/

            if (!params[0].checkType(TXT_PARSING_NODE_PROPTYPE_INTEGER))
            {
                TxtParsingNode_ErrorArgType(result_msg, "visCtrlClear", 0, TXT_PARSING_NODE_PROPTYPE_INTEGER);
                return 2;
            }

            params[0].getValue(&(test[0]));

            /********************************/

            visCtrlClear(test[0]);
            return 0;
        }
        else if (message.compareExact("visCtrlSetStatic", true))
        {
            if (1 != params_count)
            {
                TxtParsingNode_ErrorArgCount(result_msg, "visCtrlSetStatic", 1);
                return 2;
            }

            /********************************/

            if (params[0].checkType(TXT_PARSING_NODE_PROPTYPE_INTEGER))
            {
                params[0].getValue(&(test[0]));
                dummy_floats[0] = (float)test[0];
            }
            else if (params[0].checkType(TXT_PARSING_NODE_PROPTYPE_FLOAT1))
            {
                params[0].getValue(&(dummy_floats[0]));
            }
            else
            {
                TxtParsingNode_ErrorArgType(result_msg, "visCtrlSetStatic", 0, TXT_PARSING_NODE_PROPTYPE_FLOAT1);
                return 2;
            }

            /********************************/

            visCtrlSetStatic(dummy_floats[0]);
            return 0;
        }
        else if (message.compareExact("visCtrlSetLoopType", true))
        {
            if (2 != params_count)
            {
                TxtParsingNode_ErrorArgCount(result_msg, "visCtrlSetLoopType", 2);
                return 2;
            }

            /********************************/

            if (!params[0].checkType(TXT_PARSING_NODE_PROPTYPE_INTEGER))
            {
                TxtParsingNode_ErrorArgType(result_msg, "visCtrlSetLoopType", 1, TXT_PARSING_NODE_PROPTYPE_INTEGER);
                return 2;
            }

            params[0].getValue(&(test[0]));

            /********************************/

            if (!params[1].checkType(TXT_PARSING_NODE_PROPTYPE_INTEGER))
            {
                TxtParsingNode_ErrorArgType(result_msg, "visCtrlSetLoopType", 2, TXT_PARSING_NODE_PROPTYPE_INTEGER);
                return 2;
            }

            params[1].getValue(&(test[1]));

            /********************************/

            visCtrlSetLoopType(test[0], test[1]);
            return 0;
        }
        else if (message.compareExact("visCtrlAddKeyframe", true))
        {
            if (3 != params_count)
            {
                TxtParsingNode_ErrorArgCount(result_msg, "visCtrlAddKeyframe", 3);
                return 2;
            }

            /********************************/

            if (!params[0].checkType(TXT_PARSING_NODE_PROPTYPE_INTEGER))
            {
                TxtParsingNode_ErrorArgType(result_msg, "visCtrlAddKeyframe", 1, TXT_PARSING_NODE_PROPTYPE_INTEGER);
                return 2;
            }

            params[0].getValue(&(test[0]));

            /********************************/

            if (params[1].checkType(TXT_PARSING_NODE_PROPTYPE_INTEGER))
            {
                params[1].getValue(&(test[1]));
                dummy_floats[0] = (float)test[1];
            }
            else if (params[1].checkType(TXT_PARSING_NODE_PROPTYPE_FLOAT1))
            {
                params[1].getValue(&(dummy_floats[0]));
            }
            else
            {
                TxtParsingNode_ErrorArgType(result_msg, "visCtrlAddKeyframe", 2, TXT_PARSING_NODE_PROPTYPE_FLOAT1);
                return 2;
            }

            /********************************/

            if (params[2].checkType(TXT_PARSING_NODE_PROPTYPE_INTEGER))
            {
                params[2].getValue(&(test[1]));
                dummy_floats[1] = (float)test[1];
            }
            else if (params[2].checkType(TXT_PARSING_NODE_PROPTYPE_FLOAT1))
            {
                params[2].getValue(&(dummy_floats[1]));
            }
            else
            {
                TxtParsingNode_ErrorArgType(result_msg, "visCtrlAddKeyframe", 3, TXT_PARSING_NODE_PROPTYPE_FLOAT1);
                return 2;
            }

            /********************************/

            visCtrlAddKeyframe(test[0], dummy_floats[0], dummy_floats[1]);
            return 0;
        }

        return 1;
    }


    ////////////////////////////////////////////////////////////////
    // eNode: collecting nodes of some type (copies have increased references!)
    ////////////////////////////////////////////////////////////////
    void eNode::collectNodesOfSomeType(const TypeInfo* type, Collection<ArFunctions::serialize_eRefCounter> &collection)
    {
        if (getType()->checkHierarchy(type))
        {
            collection.appendChild(this);
        }
    }



    ////////////////////////////////////////////////////////////////
    // eNode: empty function (for "eGroup" / "Actor")
    ////////////////////////////////////////////////////////////////
    void eNode::exportScripts(const eString &media_dir) const
    {}


    ////////////////////////////////////////////////////////////////
    // eNode: empty functions (for "eGroup" / "eProxy")
    ////////////////////////////////////////////////////////////////

    void eNode::reloadXRef(const eString &media_dir, int32_t engine_version)
    {}

    void eNode::exportXRef(const eString &media_dir, int32_t engine_version) const
    {}


    ////////////////////////////////////////////////////////////////
    // eNode: add empty animation track (if the node uses "eMultiCtrl")
    ////////////////////////////////////////////////////////////////
    void eNode::ctrlExpandAnimTracks(int32_t new_size)
    {
        eMultiCtrl<float>* multi_ctrl;

        if (nullptr != visCtrl)
        {
            /* We only want to modify the `visCtrl` that already has multiple tracks */

            if (visCtrl->getType()->checkHierarchy(&E_MULTICTRL_FLOAT_TYPEINFO))
            {
                multi_ctrl = (eMultiCtrl<float>*)visCtrl;

                multi_ctrl->multiCtrl_SetSize(new_size);
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eNode: remove specific animation track (if the node uses "eMultiCtrl")
    ////////////////////////////////////////////////////////////////
    void eNode::ctrlRemoveAnimTrack(int32_t deleted_id)
    {
        eMultiCtrl<float>* multi_ctrl;

        if (nullptr != visCtrl)
        {
            if (visCtrl->getType()->checkHierarchy(&E_MULTICTRL_FLOAT_TYPEINFO))
            {
                multi_ctrl = (eMultiCtrl<float>*)visCtrl;

                multi_ctrl->multiCtrl_DeleteTrack(deleted_id);
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eNode: get or set the name
    ////////////////////////////////////////////////////////////////

    eString eNode::getStringRepresentation() const
    {
        return name;
    }

    void eNode::setName(eString new_name)
    {
        name = new_name;
    }


    ////////////////////////////////////////////////////////////////
    // eNode: get full Archive access path
    ////////////////////////////////////////////////////////////////
    eString eNode::getArchivePath(eNode* final_root) const
    {
        eString result;

        if ((nullptr != parent) && ((nullptr == final_root) || (this != final_root)))
        {
            result = parent->getArchivePath(final_root) + "::";
        }

        if (name.isEmpty())
        {
            result += "???";
        }
        else
        {
            result += name.getSubstring(0, 32);
        }

        return result;
    }


    ////////////////////////////////////////////////////////////////
    // eNode: get or set parent node
    ////////////////////////////////////////////////////////////////

    eGroup* eNode::getRootNode() const
    {
        eGroup* last_parent = nullptr;
        eGroup* test_parent = parent;

        while (nullptr != test_parent)
        {
            last_parent = test_parent;

            test_parent = test_parent->getParentNode();
        }

        if (nullptr == last_parent)
        {
            if (getType()->checkHierarchy(&E_GROUP_TYPEINFO))
            {
                return (eGroup*)this;
            }
        }

        return last_parent;
    }

    eGroup* eNode::getParentNode() const
    {
        return parent;
    }

    void eNode::setParentNode(eGroup* new_parent)
    {
        parent = new_parent;
    }


    ////////////////////////////////////////////////////////////////
    // eNode: get or set previous transform
    // <kao2.00477A20> (setup)
    ////////////////////////////////////////////////////////////////

    eTransform* eNode::getPreviousTransform() const
    {
        return previousTransform;
    }

    void eNode::setPreviousTransform()
    {
        eNode* test_node = parent;

        while (nullptr != test_node)
        {
            if (test_node->getType()->checkHierarchy(&E_TRANSFORM_TYPEINFO))
            {
                break;
            }
            else
            {
                test_node = test_node->parent;
            }
        }

        previousTransform = (eTransform*)test_node;
    }


    ////////////////////////////////////////////////////////////////
    // eNode: apply or erase flag bits
    ////////////////////////////////////////////////////////////////

    uint32_t eNode::getFlags() const
    {
        return flags;
    }

    void eNode::setFlags(uint32_t bits_to_apply)
    {
        flags |= bits_to_apply;
    }

    void eNode::unsetFlags(uint32_t bits_to_erase)
    {
        flags &= (~bits_to_erase);
    }


    ////////////////////////////////////////////////////////////////
    // eNode: get or set axis list box
    // <kao2.00479270> (set)
    ////////////////////////////////////////////////////////////////

    eALBox* eNode::getAxisListBox() const
    {
        return axisListBox;
    }

    void eNode::setAxisListBox(eALBox* box)
    {
        if (axisListBox != box)
        {
            if (nullptr != axisListBox)
            {
                axisListBox->decRef();
            }

            axisListBox = box;

            if (nullptr != axisListBox)
            {
                axisListBox->incRef();
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eNode: get or set the Alpha channel Controller
    ////////////////////////////////////////////////////////////////

    eCtrl<float>* eNode::getVisCtrl() const
    {
        return visCtrl;
    }

    void eNode::setVisCtrl(eCtrl<float>* new_visctrl)
    {
        if (visCtrl != new_visctrl)
        {
            if (nullptr != visCtrl)
            {
                visCtrl->decRef();
            }

            visCtrl = new_visctrl;

            if (nullptr != visCtrl)
            {
                visCtrl->incRef();
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eNode: editing the Alpha channel Controller
    ////////////////////////////////////////////////////////////////

    void eNode::visCtrlClear(int32_t anim_id)
    {
        if (nullptr != visCtrl)
        {
            if (anim_id < 0)
            {
                visCtrl->decRef();
                visCtrl = nullptr;
            }
            else
            {
                visCtrl->ctrlClearKeyframes(anim_id);
            }
        }
    }

    void eNode::visCtrlSetStatic(float opacity)
    {
        if (nullptr == visCtrl)
        {
            visCtrl = new eLeafCtrl<float>;
            visCtrl->incRef();
        }

        visCtrl->ctrlSetStaticKeyframe(opacity, 0x01);
    }

    void eNode::visCtrlSetLoopType(int32_t anim_id, int32_t loop_type)
    {
        if (nullptr != visCtrl)
        {
            visCtrl->ctrlSetLoopType(anim_id, loop_type, 0x01);
        }
    }

    void eNode::visCtrlAddKeyframe(int32_t anim_id, float time, float opacity)
    {
        eMultiCtrl<float>* multi_ctrl;

        if (anim_id < 0)
        {
            if (nullptr == visCtrl)
            {
                visCtrl = new eLeafCtrl<float>;
                visCtrl->incRef();
            }

            visCtrl->ctrlAddKeyframe(0, time, opacity, 0x01);
        }
        else
        {
            /* "anim_id" corresponds to a specific track in "eMultiCtrl" */

            if (nullptr == visCtrl)
            {
                multi_ctrl = new eMultiCtrl<float>;

                multi_ctrl->multiCtrl_SetSize(1 + anim_id);

                visCtrl = multi_ctrl;
                visCtrl->incRef();
            }
            else if (false == visCtrl->getType()->checkHierarchy(&E_MULTICTRL_FLOAT_TYPEINFO))
            {
                multi_ctrl = new eMultiCtrl<float>;

                multi_ctrl->multiCtrl_SetSize(1 + anim_id);
                multi_ctrl->multiCtrl_SetTrack(anim_id, visCtrl);

                visCtrl->decRef();
                visCtrl = multi_ctrl;
                visCtrl->incRef();
            }
            else
            {
                ((eMultiCtrl<float>*)visCtrl)->multiCtrl_SetSize(1 + anim_id);
            }

            visCtrl->ctrlAddKeyframe(anim_id, time, opacity, 0x01);
        }
    }


    ////////////////////////////////////////////////////////////////
    // Global Nodes counter
    ////////////////////////////////////////////////////////////////

    int32_t theNodesCounter = 0;

}
