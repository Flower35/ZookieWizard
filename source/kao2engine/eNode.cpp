#include <kao2engine/eNode.h>
#include <kao2ar/Archive.h>

#include <ZookieWizard/WindowsManager.h>
#include <kao2engine/Log.h>

#include <kao2engine/eALBox.h>
#include <kao2engine/eLeafCtrl.h>
#include <kao2engine/eMultiCtrl.h>
#include <kao2engine/eScene.h>
#include <kao2engine/eGeometry.h>

namespace ZookieWizard
{
    #ifdef _DEBUG
        /*** Finding memory leaks ***/
        eNode* theNodesDebug[AR_MAX_ITEMS] = {nullptr};
    #endif

    const char* theNodeFlagNames[32] =
    {
        "Visible (node)", // 0x00000001
        "???", // 0x00000002
        "Awoken (actor)", // 0x00000004
        "Enabled (node)", // 0x00000008
        "???", // 0x00000010
        "???", // 0x00000020
        "???", // 0x00000040
        "???", // 0x00000080
        "???", // 0x00000100
        "???", // 0x00000200
        "Can be rendered (node)", // 0x00000400
        "???", // 0x00000800
        "SRP Inheritance (pivot)", // 0x00001000
        "???", // 0x00002000
        "Anim Inheritance (pivot)", // 0x00004000
        "???", // 0x00008000
        "Already loaded (proxy)", // 0x00010000
        "???", // 0x00020000
        "???", // 0x00040000
        "???", // 0x00080000
        "???", // 0x00100000
        "???", // 0x00200000
        "???", // 0x00400000
        "???", // 0x00800000
        "???", // 0x01000000
        "???", // 0x02000000
        "???", // 0x04000000
        "???", // 0x08000000
        "\"WS mesh\" DrawPass #1", // 0x10000000
        "\"WS mesh\" DrawPass #2", // 0x20000000
        "\"WS mesh\" DrawPass #3", // 0x40000000
        "???", // 0x80000000
    };

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
            /* TODO: "kao2.00478B55 -- CALL 00478E00" */
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

        /*[0x08]*/ previousTransform = nullptr;
        /*[0x0C]*/ unknown_0C = 0x00FFFFFF;
        /*[0x10]*/ parent = nullptr;
        /*[0x18]*/ axisListBox = nullptr;
        /*[0x1C]*/ flags = 0x249D;
        /*[0x30]*/ flagsCollisionResponse = 0x00FF;
        /*[0x34]*/ visCtrl = nullptr;
        /*[0x2C]*/ sphBound[3] = -1.0f;

        visGroup = (-1);
    }

    eNode::~eNode()
    {
        //// eString result;
        //// char bufor[16];

        visCtrl->decRef();
        axisListBox->decRef();

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

        /* Leave a message! */

        //// sprintf_s(bufor, 16, "%d", theNodesCounter);

        //// result += " - node \"";
        //// result += name;
        //// result += "\" destroyed! [";
        //// result += bufor;
        //// result += " still exist]\n";

        //// theLog.print(result);
    }


    ////////////////////////////////////////////////////////////////
    // eNode serialization
    // <kao2.00478FF0>
    ////////////////////////////////////////////////////////////////
    void eNode::serialize(Archive &ar)
    {
        char bufor[256];
        eGeometry* test_object;
        ePoint3 test_boundary[2];

        /* Node name and node parent */

        ar.serializeString(name);

        ar.serialize((eObject**)&parent, &E_GROUP_TYPEINFO);

        if (ar.isInDebugMode() && (nullptr == parent))
        {
            if ((false == getType()->checkHierarchy(&E_SCENE_TYPEINFO))
              && (false == ar.compareWithMyRoot(this)))
            {
                sprintf_s
                (
                    bufor, 256,
                    "eNode::serialize():\n" \
                    "there is no parent attached to this node!\n" \
                    "\"%s\"",
                    name.getText()
                );

                GUI::theWindowsManager.displayMessage(WINDOWS_MANAGER_MESSAGE_WARNING, bufor);
            }
        }

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
                test_object = (eGeometry*)this;

                test_object->oldNodeSerialization(test_boundary);
            }
        }

        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&axisListBox, &E_ALBOX_TYPEINFO);

        ar.readOrWrite(&flags, 0x04);

        ar.readOrWrite(&(sphBound[0]), 0x04);
        ar.readOrWrite(&(sphBound[1]), 0x04);
        ar.readOrWrite(&(sphBound[2]), 0x04);
        ar.readOrWrite(&(sphBound[3]), 0x04);

        /* Node's visibility controller (`GL_DIFFUSE` alpha channel, from 0 to 1.0) */

        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&visCtrl, &E_CTRL_FLOAT_TYPEINFO);

        /* Some almost-deprecated flags. */
        /* Object's collision is checked only when this valuse is NOT `0x00FF`. */

        ar.readOrWrite(&flagsCollisionResponse, 0x02);

        if (ar.isInReadMode())
        {
            flags |= 0x00002000;
        }

        /* From "Kao Challengers" */

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
            /* Setup for animations */
            setPreviousTransform();
        }
    }


    ////////////////////////////////////////////////////////////////
    // eNode: destroy before dereferencing
    ////////////////////////////////////////////////////////////////
    void eNode::destroyNode()
    {
        editingClearCollision();
    }


    ////////////////////////////////////////////////////////////////
    // eNode: empty function (for "eTransform" / "eTriMesh")
    ////////////////////////////////////////////////////////////////
    ePoint3 eNode::editingGetCenterPoint() const
    {
        return {0, 0, 0};
    }


    ////////////////////////////////////////////////////////////////
    // eNode: empty function (for "eGroup" / "eTriMesh")
    ////////////////////////////////////////////////////////////////
    void eNode::editingRebuildCollision()
    {}


    ////////////////////////////////////////////////////////////////
    // eNode: (editor function) clear collision
    ////////////////////////////////////////////////////////////////
    void eNode::editingClearCollision()
    {
        if (nullptr != axisListBox)
        {
            axisListBox->decRef();
            axisListBox = nullptr;
        }

        flagsCollisionResponse = 0x00FF;
    }


    ////////////////////////////////////////////////////////////////
    // eNode: empty function (for "eBoxZone" / "eTransform" / "eTriMesh")
    ////////////////////////////////////////////////////////////////
    void eNode::editingApplyNewTransform(eSRP &new_transform, int32_t marked_id)
    {}


    ////////////////////////////////////////////////////////////////
    // eNode: empty function (for "eGroup" / "eTransform")
    ////////////////////////////////////////////////////////////////
    void eNode::updateSRP(bool update, eAnimate* anim, eSRP &parent_srp)
    {}


    ////////////////////////////////////////////////////////////////
    // eNode: empty function (for "eGroup" / "eZone")
    ////////////////////////////////////////////////////////////////
    void eNode::findAndDereference(eNode* target)
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
    // eNode: get name
    ////////////////////////////////////////////////////////////////
    eString eNode::getStringRepresentation() const
    {
        return name;
    }


    ////////////////////////////////////////////////////////////////
    // eNode: internal rendering check
    ////////////////////////////////////////////////////////////////
    bool eNode::renderObject(int32_t draw_flags, eAnimate* anim, eSRP &parent_srp, eMatrix4x4 &parent_matrix, int32_t marked_id)
    {
        if (0 == (GUI::drawFlags::DRAW_FLAG_INVISIBLE & draw_flags))
        {
            if (0 == (0x01 & flags))
            {
                return false;
            }
        }

        return true;
    }


    ////////////////////////////////////////////////////////////////
    // eNode: set name
    ////////////////////////////////////////////////////////////////
    void eNode::setName(eString new_name)
    {
        name = new_name;
    }


    ////////////////////////////////////////////////////////////////
    // eNode: get or set parent node
    ////////////////////////////////////////////////////////////////

    eNode* eNode::getRootNode() const
    {
        const eNode *root, *test_root;

        root = nullptr;
        test_root = this;

        while (nullptr != test_root)
        {
            test_root = test_root->getParentNode();

            if (nullptr != test_root)
            {
                root = test_root;
            }
        }

        return (eNode*)root;
    }

    eNode* eNode::getParentNode() const
    {
        return parent;
    }

    void eNode::setParentNode(eNode* new_parent)
    {
        parent = new_parent;
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

    void eNode::visCtrlClear(int anim_id)
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

    void eNode::visCtrlAddKeyframe(int anim_id, float time, float opacity)
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

            visCtrl->ctrlAddKeyframe(anim_id, time, opacity, 0x01);
        }
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
    // eNode: find material by path
    ////////////////////////////////////////////////////////////////
    eMaterial* eNode::findMaterial(eString &searched_path) const
    {
        return nullptr;
    }


    ////////////////////////////////////////////////////////////////
    // eNode: apply or erase flag bits
    ////////////////////////////////////////////////////////////////

    void eNode::setFlags(int32_t bits_to_apply)
    {
        flags |= bits_to_apply;
    }

    void eNode::unsetFlags(int32_t bits_to_erase)
    {
        flags &= (~bits_to_erase);
    }

    int32_t eNode::getFlags() const
    {
        return flags;
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
    void eNode::writeStructureToTextFile(FileOperator &file, int32_t indentation) const
    {
        char bufor[1024];
        TypeInfo* info = getType();

        sprintf_s
        (
            bufor,
            1024,
            "[%08X] %s (\"%s\")",
            info->id,
            info->name,
            name.getSubstring(0, 1024 - 64).getText()
        );

        ArFunctions::writeNewLine(file, indentation);
        file << bufor;

        sprintf_s
        (
            bufor,
            512,
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
                bufor,
                512,
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
                bufor,
                512,
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
    // Global Nodes counter
    ////////////////////////////////////////////////////////////////

    int32_t theNodesCounter = 0;

}
