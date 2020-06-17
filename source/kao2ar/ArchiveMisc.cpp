#include <kao2ar/Archive.h>

#include <ZookieWizard/WindowsManager.h>
#include <kao2engine/Log.h>

#include <kao2engine/eScene.h>
#include <kao2engine/eXRefTarget.h>
#include <kao2engine/eXRefProxy.h>
#include <kao2engine/eTriMesh.h>
#include <kao2engine/eGeoSet.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // Ar: destroy parent (if it is "eNode")
    ////////////////////////////////////////////////////////////////
    void Archive::destroyParent()
    {
        eNode* test_node;

        if (nullptr != parentObject)
        {
            if (!isLoadedAsProxy)
            {
                if (parentObject->getType()->checkHierarchy(&E_NODE_TYPEINFO))
                {
                    test_node = (eNode*)parentObject;
                    test_node->destroyNode();
                }
            }

            parentObject->decRef();
            parentObject = nullptr;
        }
    }


    ////////////////////////////////////////////////////////////////
    // Ar: change global scene
    ////////////////////////////////////////////////////////////////
    void Archive::changeGlobalScene() const
    {
        eXRefProxy* test_xref_proxy;
        eXRefTarget* test_xref_target;

        if (nullptr != selectedObject)
        {
            if (selectedObject->getType()->checkHierarchy(&E_SCENE_TYPEINFO))
            {
                ArFunctions::setCurrentScene((eScene*)selectedObject);

                return;
            }
            else if (selectedObject->getType()->checkHierarchy(&E_XREFPROXY_TYPEINFO))
            {
                test_xref_proxy = (eXRefProxy*)selectedObject;
                test_xref_target = test_xref_proxy->getXRefTarget();

                if (nullptr != test_xref_target)
                {
                    ArFunctions::setCurrentScene(test_xref_target->getLocalScene());
                }
            }
        }

        if (nullptr != parentObject)
        {
            if (parentObject->getType()->checkHierarchy(&E_SCENE_TYPEINFO))
            {
                ArFunctions::setCurrentScene((eScene*)parentObject);

                return;
            }
        }

        ArFunctions::setCurrentScene(nullptr);
    }


    ////////////////////////////////////////////////////////////////
    // Ar: render scene, starting from selected object
    ////////////////////////////////////////////////////////////////
    void Archive::renderScene(int32_t draw_flags) const
    {
        eSRP default_srp;
        eMatrix4x4 default_matrix;

        if (nullptr != selectedObject)
        {
            selectedObject->renderObject(draw_flags, nullptr, default_srp, default_matrix, markedChildId);
        }
    }


    ////////////////////////////////////////////////////////////////
    // Ar: change selected object (applies mostly to "eNode")
    ////////////////////////////////////////////////////////////////
    void Archive::changeSelectedObject(int32_t child_id, void* param)
    {
        int32_t i;
        bool update_name = true;
        bool update_label = false;
        bool update_list = false;
        bool reset_editable_transform = false;
        uint8_t change_camera = 0;
        bool change_scene = false;
        char bufor[128];

        eString test_string;
        eSRP test_srp;

        TypeInfo* test_typeinfo = nullptr;
        eGroup* test_group;
        eNode *test_root, *test_node = nullptr;
        eTransform* parent_xform = nullptr;

        /********************************/
        /* If no object is selected, and we are not updating List or Root, then cancel this function */

        switch (child_id)
        {
            case NODES_LISTBOX_ROOT:
            case NODES_LISTBOX_UPDATE_CURRENT:
            case NODES_LISTBOX_SET_MARKED_CHILD:
            {
                break;
            }

            default:
            {
                if (nullptr == selectedObject)
                {
                    return;
                }
            }
        }

        /********************************/
        /* Assing selected object to "eNode" pointer */

        if ((nullptr != selectedObject) && (selectedObject->getType()->checkHierarchy(&E_NODE_TYPEINFO)))
        {
            test_node = (eNode*)selectedObject;
        }

        switch (child_id)
        {
            case NODES_LISTBOX_SET_MARKED_CHILD:
            {
                markedChildId = (int32_t)param;
                reset_editable_transform = true;
                break;
            }

            case NODES_EDITING_RESET_TRANSFORM:
            {
                reset_editable_transform = true;
                break;
            }

            case NODES_EDITING_APPLY_TRANSFORM:
            {
                if (nullptr != test_node)
                {
                    GUI::getMovedSeletedTransform((void*)&test_srp);
                    test_node->editingApplyNewTransform(test_srp, markedChildId);
                }

                reset_editable_transform = true;

                break;
            }

            case NODES_EDITING_CHANGE_TYPE:
            {
                /* (...) */
                break;
            }

            case NODES_EDITING_INSERT:
            {
                if (nullptr != test_node)
                {
                    try
                    {
                        if (test_node->getType()->checkHierarchy(&E_GROUP_TYPEINFO))
                        {
                            test_group = (eGroup*)test_node;

                            test_typeinfo = InterfaceManager.getTypeInfo((char*)param);

                            if (nullptr != test_typeinfo)
                            {
                                if (test_typeinfo->checkHierarchy(&E_NODE_TYPEINFO))
                                {
                                    test_node = (eNode*)test_typeinfo->create();
                                    test_group->appendChild(test_node);

                                    sprintf_s
                                    (
                                        bufor, 128,
                                        "Node (type \"%s\") added to group \"%s\".",
                                        (char*)param,
                                        test_group->getStringRepresentation().getText()
                                    );

                                    GUI::theWindowsManager.displayMessage
                                    (
                                        WINDOWS_MANAGER_MESSAGE_INFO,
                                        bufor
                                    );

                                    update_list = true;
                                }
                                else
                                {
                                    throw ErrorMessage
                                    (
                                        "Unable to add new node:\n" \
                                        "\"%s\" is not derived from \"eNode\"!",
                                        (char*)param
                                    );
                                }
                            }
                        }
                        else
                        {
                            throw ErrorMessage
                            (
                                "Unable to add new node:\n" \
                                "Selected object is not derived from \"eGroup\"!"
                            );
                        }
                    }
                    catch (ErrorMessage &err)
                    {
                        err.display();
                    }
                }

                break;
            }

            case NODES_EDITING_CHANGE_NAME:
            {
                if (nullptr != test_node)
                {
                    test_node->setName(eString((char*)param));

                    update_name = false;
                    update_label = true;
                }

                break;
            }

            case NODES_EDITING_SET_FLAG:
            case NODES_EDITING_UNSET_FLAG:
            {
                if (nullptr != test_node)
                {
                    if (NODES_EDITING_SET_FLAG == child_id)
                    {
                        test_node->setFlags((int32_t)param);
                    }
                    else
                    {
                        test_node->unsetFlags((int32_t)param);
                    }

                    update_label = true;
                }

                break;
            }

            case NODES_LISTBOX_COLLISION_CLEAR:
            {
                if (nullptr != test_node)
                {
                    test_node->editingClearCollision();
                }

                break;
            }

            case NODES_LISTBOX_COLLISION_REBUILD:
            {
                if (nullptr != test_node)
                {
                    test_node->editingRebuildCollision();
                }

                break;
            }

            case NODES_LISTBOX_DELETE:
            case NODES_LISTBOX_PARENT:
            {
                if (nullptr != test_node)
                {
                    test_group = (eGroup*)test_node->getParentNode();

                    if (nullptr != test_group)
                    {
                        if (NODES_LISTBOX_DELETE == child_id)
                        {
                            theLog.print
                            (
                                "================================\n" \
                                "==        NODE DELETING       ==\n" \
                                "==            BEGIN           ==\n" \
                                "================================\n"
                            );

                            if (test_group->getType()->checkHierarchy(&E_GROUP_TYPEINFO))
                            {
                                if (test_node->getReferenceCount() >= 2)
                                {
                                    test_root = test_node->getRootNode();

                                    if (nullptr == test_root)
                                    {
                                        test_root = test_group->getRootNode();
                                    }

                                    if (nullptr != test_root)
                                    {
                                        test_root->findAndDereference(test_node);
                                        /* (--dsp--) delete from scripts as well! */
                                    }
                                }

                                test_group->findAndDeleteChild(test_node);
                            }

                            theLog.print
                            (
                                "================================\n" \
                                "==        NODE DELETING       ==\n" \
                                "==          FINISHED          ==\n" \
                                "================================\n"
                            );
                        }
                        else
                        {
                            /* Find current child ID to set selection in listbox */

                            for (i = 0; (child_id < 0) && (i < test_group->getNodesCount()); i++)
                            {
                                if (test_group->getIthChild(i) == test_node)
                                {
                                    child_id = i;
                                }
                            }
                        }

                        parent_xform = (eTransform*)test_group;
                        change_camera = 0x02; // backwards

                        selectedObject = test_group;

                        change_scene = true;
                        update_list = true;
                    }
                }

                break;
            }

            case NODES_LISTBOX_FIND:
            {
                if (nullptr != test_node)
                {
                    test_srp.pos = test_node->editingGetCenterPoint();
                    GUI::testCamera.reset(test_srp.pos.x, test_srp.pos.y, test_srp.pos.z);
                }

                break;
            }

            case NODES_LISTBOX_ROOT:
            {
                if (nullptr != test_node)
                {
                    parent_xform = (eTransform*)test_node->getParentNode();
                }
                change_camera = 0x03;

                selectedObject = parentObject;

                change_scene = true;
                update_list = true;
                break;
            }

            case NODES_LISTBOX_UPDATE_CURRENT:
            {
                update_list = true;
                break;
            }

            default: // SWITCH TO A CHILD NODE
            {
                markedChildId = (-1);

                if (selectedObject->getType()->checkHierarchy(&E_GROUP_TYPEINFO))
                {
                    test_group = (eGroup*)selectedObject;
                    test_node = test_group->getIthChild(child_id);

                    /* Don't update listbox selection */
                    child_id = (-1);

                    if (nullptr != test_node)
                    {
                        parent_xform = (eTransform*)test_group;
                        change_camera = 0x01; // forwards

                        selectedObject = test_node;

                        change_scene = true;
                        update_list = true;
                    }
                }
            }
        }

        /********************************/
        /* Update pointer to current scene */

        if (change_scene)
        {
            changeGlobalScene();
        }

        /********************************/
        /* Transform camera */

        switch (change_camera)
        {
            case 0x01: // forwards
            {
                /* Cancel parent's transformation */

                if (parent_xform->getType()->checkHierarchy(&E_TRANSFORM_TYPEINFO))
                {
                    test_srp = parent_xform->getXForm(true, false);
                    GUI::repositionCamera(true, &test_srp);
                }

                break;
            }

            case 0x02: // backwards
            {
                /* Apply parent's transformation */

                if (parent_xform->getType()->checkHierarchy(&E_TRANSFORM_TYPEINFO))
                {
                    test_srp = parent_xform->getXForm(true, false);
                    GUI::repositionCamera(false, &test_srp);
                }

                break;
            }

            case 0x03: // reset to root
            {
                while (nullptr != parent_xform)
                {
                    if (parent_xform->getType()->checkHierarchy(&E_TRANSFORM_TYPEINFO))
                    {
                        test_srp = parent_xform->getXForm(true, false);
                        GUI::repositionCamera(false, &test_srp);
                    }

                    parent_xform = (eTransform*)parent_xform->getParentNode();
                }

                break;
            }
        }

        /********************************/
        /* Reset editable transformation */

        if (update_list || reset_editable_transform || (0 != change_camera))
        {
            test_node = nullptr;

            if ((nullptr != selectedObject) && (markedChildId >= 0))
            {
                if (selectedObject->getType()->checkHierarchy(&E_GROUP_TYPEINFO))
                {
                    test_group = (eGroup*)selectedObject;
                    test_node = test_group->getIthChild(markedChildId);
                }
            }
            else
            {
                test_node = (eNode*)selectedObject;
            }

            if ((nullptr != test_node) && (test_node->getType()->checkHierarchy(&E_TRANSFORM_TYPEINFO)))
            {
                parent_xform = (eTransform*)test_node;

                test_srp = parent_xform->getXForm(true, false);
            }
            else
            {
                test_srp = eSRP();
            }

            GUI::setMovedSeletedTransform((void*)&test_srp);
        }

        /********************************/
        /* Send back current node info */

        if (update_list || update_label)
        {
            /* Reset label */
            GUI::updateNodesList((-3), nullptr);

            if (update_list)
            {
                /* Reset listbox */
                GUI::updateNodesList((-2), nullptr);
                markedChildId = (-1);
            }

            if (nullptr == selectedObject)
            {
                return;
            }
            else if (selectedObject->getType()->checkHierarchy(&E_NODE_TYPEINFO))
            {
                test_node = (eNode*)selectedObject;
            }
            else
            {
                test_node = nullptr;
            }

            /* Send node name and node flags */
            if (nullptr != test_node)
            {
                GUI::updateNodesList(1, (void*)test_node->getType()->name);

                if (update_name)
                {
                    GUI::updateNodesList(2, (void*)test_node->getStringRepresentation().getText());
                }

                GUI::updateNodesList(3, (void*)test_node->getFlags());
            }

            /* Send back label text */

            sprintf_s(bufor, 128, "< total nodes: %d >\n", theNodesCounter);

            test_string = bufor;

            sprintf_s(bufor, 128, "(%s)", selectedObject->getType()->name);

            test_string += "Selected: ";
            test_string += bufor;
            test_string += "\n\"";
            test_string += selectedObject->getStringRepresentation();
            test_string += "\"";

            if (nullptr != test_node)
            {
                i = test_node->getFlags();

                sprintf_s(bufor, 128, "\n0x%08X [", i);
                test_string += bufor;

                if (0x01 & i)
                {
                    test_string += "Enabled]";
                }
                else
                {
                    test_string += "Disabled]";
                }
            }

            GUI::updateNodesList((-3), test_string.getText());
        }

        /********************************/
        /* Sent back each child node name */

        if (update_list)
        {
            if (selectedObject->getType()->checkHierarchy(&E_GROUP_TYPEINFO))
            {
                test_group = (eGroup*)selectedObject;

                for (i = 0; i < test_group->getNodesCount(); i++)
                {
                    sprintf_s(bufor, 128, "[%d] ", i);
                    test_string = bufor;

                    test_node = test_group->getIthChild(i);

                    if (nullptr != test_node)
                    {
                        sprintf_s(bufor, 128, "(%s) ", test_node->getType()->name);
                        test_string += bufor;
                        test_string += test_node->getStringRepresentation();
                    }
                    else
                    {
                        test_string += "<< NULL >>";
                    }

                    /* Insert children names to the listbox */
                    GUI::updateNodesList(0, test_string.getText());
                }

                /* Update selection of previous child when switching to the parent */
                if (child_id >= 0)
                {
                    GUI::updateNodesList((-1), (void*)child_id);
                }
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // Ar: copy scene pointer (used by eXRefTarget)
    ////////////////////////////////////////////////////////////////
    void Archive::copySceneFromMe(eScene** target) const
    {
        if (nullptr != parentObject)
        {
            eScene* test_scene = (eScene*)parentObject;

            if (test_scene->getType()->checkHierarchy(&E_SCENE_TYPEINFO))
            {
                if (nullptr != (*target))
                {
                    (*target)->decRef();
                }

                (*target) = test_scene;

                test_scene->incRef();
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // Ar: set scene pointer (used by eXRefTarget)
    ////////////////////////////////////////////////////////////////
    void Archive::setMyParentScene(eScene* pointer)
    {
        if (nullptr != parentObject)
        {
            destroyParent();
        }

        parentObject = pointer;

        if (nullptr != parentObject)
        {
            parentObject->incRef();

            selectedObject = parentObject;
        }
    }

}
