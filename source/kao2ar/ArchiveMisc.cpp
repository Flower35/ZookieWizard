#include <kao2ar/Archive.h>
#include <kao2ar/eDrawContext.h>

#include <ZookieWizard/WindowsManager.h>
#include <kao2engine/Log.h>

#include <kao2engine/eScene.h>
#include <kao2engine/eXRefTarget.h>
#include <kao2engine/eXRefProxy.h>
#include <kao2engine/eGeometry.h>
#include <kao2engine/eMaterial.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // Archive: destroy parent (if it is "eNode")
    ////////////////////////////////////////////////////////////////
    void Archive::destroyParent()
    {
        eString message;
        char number_buffer[16];

        eNode* test_node;

        if (nullptr != parentObject)
        {
            if (0 == (AR_MODE_IS_PROXY & modeFlags))
            {
                if (parentObject->getType()->checkHierarchy(&E_NODE_TYPEINFO))
                {
                    test_node = (eNode*)parentObject;
                    test_node->destroyNode();
                }
            }

            parentObject->decRef();
            parentObject = nullptr;

            sprintf_s(number_buffer, 16, "%d", theNodesCounter);

            message += " - archive's root object destroyed! [";
            message += number_buffer;
            message += " nodes still exist]\n";

            theLog.print(message);
        }
    }


    ////////////////////////////////////////////////////////////////
    // Archive: change global scene
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
    // Archive: Dereference string copies
    ////////////////////////////////////////////////////////////////
    void Archive::deleteTempStrPtrs()
    {
        int32_t i;

        for (i = 0; i < tempStrCount; i++)
        {
            tempStrList[i]->decRef();
        }

        tempStrCount = 0;
    }


    ////////////////////////////////////////////////////////////////
    // Archive: render scene, starting from selected object
    ////////////////////////////////////////////////////////////////
    void Archive::renderScene(uint32_t draw_flags) const
    {
        if ((nullptr != selectedObject) && selectedObject->getType()->checkHierarchy(&E_NODE_TYPEINFO))
        {
            eNode* selected_node = (eNode*)selectedObject;

            eSRP default_srp;
            eMatrix4x4 default_matrix;

            eDrawContext draw_context;
            draw_context.setDrawFlags(draw_flags);
            draw_context.setParentSRP(&default_srp);
            draw_context.setParentMatrix(&default_matrix);
            draw_context.setMarkedId(markedChildId);

            selected_node->updateBeforeRendering(draw_context);

            uint32_t node_flags = (GUI::drawFlags::DRAW_FLAG_INVISIBLE & draw_flags) ? 0x00 : 0x09;

            for (int32_t draw_pass = 0; draw_pass < 3; draw_pass++)
            {
                if ((GUI::drawFlags::DRAW_FLAG_DRAWPASS1 << draw_pass) & draw_flags)
                {
                    draw_context.setNodeFlags(node_flags | (0x10000000 << draw_pass));
                    selected_node->renderNode(draw_context);
                }
            }

            draw_context.useMaterial(nullptr, 0);
        }
    }


    ////////////////////////////////////////////////////////////////
    // Ar: change selected object (applies mostly to "eNode")
    ////////////////////////////////////////////////////////////////
    void Archive::changeSelectedObject(int32_t child_id, void* param)
    {
        int32_t a, b, c;
        bool update_name = true;
        bool update_label = false;
        bool update_list = false;
        bool reset_editable_transform = false;
        uint8_t change_camera = 0;
        bool change_scene = false;
        char bufor[LARGE_BUFFER_SIZE];

        eString test_string;
        eSRP test_srp;

        TypeInfo* test_typeinfo = nullptr;
        eGroup *test_group, *test_root;
        eNode *test_node = nullptr;
        eTransform* parent_xform = nullptr;
        eGeometry* test_geometry;
        eMaterial* test_material;

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

                                    if (nullptr != test_node)
                                    {
                                        test_group->appendChild(test_node);
                                        test_node->editingNewNodeSetup();

                                        sprintf_s
                                        (
                                            bufor, LARGE_BUFFER_SIZE,
                                            "Node (type \"%s\") added to group \"%s\".",
                                            (char*)param,
                                            test_group->getStringRepresentation().getText()
                                        );
                                    }
                                    else
                                    {
                                        sprintf_s
                                        (
                                            bufor, LARGE_BUFFER_SIZE,
                                            "Cannot create a node of selected type. Class \"%s\" is abstract.",
                                            test_typeinfo->name
                                        );
                                    }

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
                    test_node->editingClearCollision(false);
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

            case NODES_LISTBOX_DELETE_CURRENT:
            case NODES_LISTBOX_PARENT:
            {
                if (nullptr != test_node)
                {
                    test_group = (eGroup*)test_node->getParentNode();

                    if (nullptr != test_group)
                    {
                        /* Remember the option from this switch case */

                        c = child_id;

                        /* Find current child ID to set selection in listbox */

                        child_id = test_group->findChildId(test_node);

                        if (NODES_LISTBOX_DELETE_CURRENT == c)
                        {
                            sprintf_s
                            (
                                bufor, LARGE_BUFFER_SIZE,
                                    "You are about to delete this node:\n\n" \
                                    "(%s) \"%s\"\n\n" \
                                    "This operation cannot be undone! Are you sure you want to continue?",
                                test_node->getType()->name,
                                test_node->getDebugName().getText()
                            );

                            if (false == GUI::theWindowsManager.askQuestion(bufor))
                            {
                                return;
                            }

                            theLog.print
                            (
                                "================================\n" \
                                "==        NODE DELETING       ==\n" \
                                "==            BEGIN           ==\n" \
                                "================================\n"
                            );

                            nodesManager_RemoveChild(test_group, child_id, nullptr);

                            theLog.print
                            (
                                "================================\n" \
                                "==        NODE DELETING       ==\n" \
                                "==          FINISHED          ==\n" \
                                "================================\n"
                            );
                        }

                        b = test_group->getNodesCount() - 1;
                        child_id = (child_id > b) ? b : child_id;

                        /* updating editable transform (before updating the list) */
                        markedChildId = child_id;

                        parent_xform = (eTransform*)test_group;
                        change_camera = 0x02; // backwards

                        selectedObject = test_group;

                        change_scene = true;
                        update_list = true;
                    }
                }

                break;
            }

            case NODES_LISTBOX_DELETE_CHILDREN:
            case NODES_LISTBOX_DELETE_SELECTED:
            {
                if (selectedObject->getType()->checkHierarchy(&E_GROUP_TYPEINFO))
                {
                    test_group = (eGroup*)selectedObject;

                    theLog.print
                    (
                        "================================\n" \
                        "==        NODE DELETING       ==\n" \
                        "==            BEGIN           ==\n" \
                        "================================\n"
                    );

                    if (NODES_LISTBOX_DELETE_CHILDREN == child_id)
                    {
                        sprintf_s
                        (
                            bufor, LARGE_BUFFER_SIZE,
                                "You are about to delete ALL of the children of this group:\n\n" \
                                "(%s) \"%s\"\n\n" \
                                "This operation cannot be undone! Are you sure you want to continue?",
                            test_group->getType()->name,
                            test_group->getDebugName().getText()
                        );

                        if (false == GUI::theWindowsManager.askQuestion(bufor))
                        {
                            return;
                        }

                        test_root = test_group->getRootNode();

                        test_group->deleteNodesWithMultiRefs(false, test_root);

                        while (test_group->getNodesCount() > 0)
                        {
                            if ((nullptr != test_root) && (nullptr != (test_node = test_group->getIthChild(0))))
                            {
                                test_root->findAndDereference(test_node);
                            }

                            test_group->deleteIthChild(0);
                        }

                        child_id = (-1);
                    }
                    else if ((markedChildId >= 0) && (markedChildId < test_group->getNodesCount()))
                    {
                        test_node = test_group->getIthChild(markedChildId);

                        if (nullptr != test_node)
                        {
                            sprintf_s
                            (
                                bufor, LARGE_BUFFER_SIZE,
                                    "You are about to delete this node:\n\n" \
                                    "(%s) \"%s\"\n\n" \
                                    "This operation cannot be undone! Are you sure you want to continue?",
                                test_node->getType()->name,
                                test_node->getDebugName().getText()
                            );

                            if (false == GUI::theWindowsManager.askQuestion(bufor))
                            {
                                return;
                            }

                            if (nullptr != (test_root = test_group->getRootNode()))
                            {
                                if (test_node->getType()->checkHierarchy(&E_GROUP_TYPEINFO))
                                {
                                    ((eGroup*)test_node)->deleteNodesWithMultiRefs(false, test_root);
                                }

                                test_root->findAndDereference(test_node);
                            }
                        }

                        test_group->deleteIthChild(markedChildId);

                        /* Select the next child on the list */

                        b = test_group->getNodesCount() - 1;
                        child_id = (markedChildId > b) ? b : markedChildId;
                    }

                    theLog.print
                    (
                        "================================\n" \
                        "==        NODE DELETING       ==\n" \
                        "==          FINISHED          ==\n" \
                        "================================\n"
                    );

                    /* updating editable transform (before updating the list) */
                    markedChildId = child_id;

                    update_list = true;
                }

                break;
            }

            case NODES_LISTBOX_MOVE_UP:
            {
                if (selectedObject->getType()->checkHierarchy(&E_GROUP_TYPEINFO))
                {
                    if (markedChildId >= 0)
                    {
                        test_group = (eGroup*)selectedObject;

                        test_group->swapBackward(markedChildId);
                        child_id = markedChildId - 1;

                        if (child_id < 0)
                        {
                            child_id = 0;
                        }

                        /* updating editable transform (before updating the list) */
                        markedChildId = child_id;

                        update_list = true;
                    }
                }

                break;
            }

            case NODES_LISTBOX_MOVE_DOWN:
            {
                if (selectedObject->getType()->checkHierarchy(&E_GROUP_TYPEINFO))
                {
                    if (markedChildId >= 0)
                    {
                        test_group = (eGroup*)selectedObject;

                        test_group->swapForward(markedChildId);
                        child_id = markedChildId + 1;

                        b = test_group->getNodesCount() - 1;

                        if (child_id > b)
                        {
                            child_id = b;
                        }

                        /* updating editable transform (before updating the list) */
                        markedChildId = child_id;

                        update_list = true;
                    }
                }

                break;
            }

            case NODES_LISTBOX_MOVE_OUT:
            {
                if (selectedObject->getType()->checkHierarchy(&E_GROUP_TYPEINFO))
                {
                    if (markedChildId >= 0)
                    {
                        test_group = (eGroup*)selectedObject;
                        test_node = test_group->getIthChild(markedChildId);

                        if (nullptr != test_node)
                        {
                            b = test_group->getNodesCount() - 2;

                            test_group = (eGroup*)test_group->getParentNode();

                            if (nullptr != test_group)
                            {
                                test_group->appendChild(test_node);

                                child_id = (markedChildId > b) ? b : markedChildId;

                                update_list = true;
                            }
                        }
                    }
                }

                break;
            }

            case NODES_LISTBOX_MOVE_IN:
            {
                if (selectedObject->getType()->checkHierarchy(&E_GROUP_TYPEINFO))
                {
                    if (markedChildId >= 1)
                    {
                        test_group = (eGroup*)selectedObject;
                        b = test_group->getNodesCount() - 2;

                        test_node = test_group->getIthChild(markedChildId);
                        test_group = (eGroup*)test_group->getIthChild(markedChildId - 1);

                        if ((nullptr != test_node) && (nullptr != test_group))
                        {
                            if (test_group->getType()->checkHierarchy(&E_GROUP_TYPEINFO))
                            {
                                test_group->appendChild(test_node);

                                /* Keep the marked child ID (helpful when moving many nodes) */
                                child_id = (markedChildId > b) ? b : markedChildId;

                                update_list = true;
                            }
                        }
                    }
                }

                break;
            }

            case NODES_EDITING_CLONE_CURRENT:
            {
                if (nodesManager_CloneChild(test_node, (-1)))
                {
                    sprintf_s
                    (
                        bufor, LARGE_BUFFER_SIZE,
                            "Successfully increased reference to this node:\n\n" \
                            "(%s) \"%s\"",
                        test_node->getType()->name,
                        test_node->getDebugName().getText()
                    );

                    GUI::theWindowsManager.displayMessage(WINDOWS_MANAGER_MESSAGE_INFO, bufor);
                }

                break;
            }

            case NODES_EDITING_CLONE_SELECTED:
            {
                test_group = (eGroup*)test_node;

                if (nodesManager_CloneChild(test_group, markedChildId))
                {
                    test_node = test_group->getIthChild(markedChildId);

                    if (nullptr == test_node)
                    {
                        sprintf_s
                        (
                            bufor, LARGE_BUFFER_SIZE,
                            "Successfully increased reference to a child node of this group:\n\n" \
                            "(%s) \"%s\"",
                            test_group->getType()->name,
                            test_group->getDebugName().getText()
                        );
                    }
                    else
                    {
                        sprintf_s
                        (
                            bufor, LARGE_BUFFER_SIZE,
                            "Successfully increased reference to this node:\n\n" \
                            "(%s) \"%s\"",
                            test_node->getType()->name,
                            test_node->getDebugName().getText()
                        );
                    }

                    GUI::theWindowsManager.displayMessage(WINDOWS_MANAGER_MESSAGE_INFO, bufor);
                }

                break;
            }

            case NODES_EDITING_CLONE_PASTING:
            {
                nodesManager_PasteLastClone(test_node);

                if ((nullptr != test_node) && test_node->getType()->checkHierarchy(&E_GROUP_TYPEINFO))
                {
                    child_id = ((eGroup*)test_node)->getNodesCount() - 1;
                }
                else
                {
                    child_id = (-1);
                }

                /* updating editable transform (before updating the list) */
                markedChildId = child_id;

                update_list = true;

                break;
            }

            case NODES_EDITING_MATERIAL_CLONE:
            case NODES_EDITING_MATERIAL_DELETE:
            case NODES_EDITING_MATERIAL_CHANGE:
            {
                if ((nullptr != test_node) && test_node->getType()->checkHierarchy(&E_GEOMETRY_TYPEINFO))
                {
                    test_geometry = (eGeometry*)test_node;

                    if (NODES_EDITING_MATERIAL_CLONE == child_id)
                    {
                        test_material = test_geometry->getMaterial();

                        if (nullptr != test_material)
                        {
                            test_material = new eMaterial(*(test_material));
                        }
                        else
                        {
                            test_material = new eMaterial(nullptr);
                        }
                    }
                    else if (NODES_EDITING_MATERIAL_DELETE == child_id)
                    {
                        test_material = nullptr;
                    }
                    else
                    {
                        test_material = GUI::materialsManager_GetCurrentMaterial();
                    }

                    test_geometry->setMaterial(test_material);

                    GUI::materialsManager_SetCurrentMaterialFromGeometry(test_geometry->getMaterial());
                }
                else
                {
                    GUI::theWindowsManager.displayMessage(WINDOWS_MANAGER_MESSAGE_WARNING, "Current Node type must be \"eGeometry\" or its child type!");
                }

                break;
            }

            case NODES_EDITING_MATERIAL_OPTIMIZE:
            {
                GUI::materialsManager_ReduceSimilarMaterials(test_node, false);

                break;
            }

            case NODES_EDITING_GROUPS_DPFLAGS:
            {
                if (nullptr != test_node)
                {
                    test_node->updateDrawPassFlags(nullptr);

                    child_id = (-1);
                    update_list = true;
                }

                break;
            }

            case NODES_EDITING_GROUPS_UNREF:
            {
                if (nullptr != test_node)
                {
                    a = theNodesCounter;

                    test_node->removeEmptyAndUnreferencedGroups();

                    a -= theNodesCounter;

                    if (a > 0)
                    {
                        sprintf_s
                        (
                            bufor, LARGE_BUFFER_SIZE,
                            "Removed %d unreferenced groups!",
                            a
                        );

                        child_id = (-1);
                        update_list = true;
                    }
                    else
                    {
                        sprintf_s
                        (
                            bufor, LARGE_BUFFER_SIZE,
                            "No groups removed..."
                        );
                    }

                    GUI::theWindowsManager.displayMessage
                    (
                        WINDOWS_MANAGER_MESSAGE_INFO,
                        bufor
                    );
                }

                break;
            }

            case NODES_LISTBOX_CENTER_CAMERA:
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
                markedChildId = (-1);

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
                    test_srp = parent_xform->getXForm(false);
                    GUI::repositionCamera(true, &test_srp);
                }

                break;
            }

            case 0x02: // backwards
            {
                /* Apply parent's transformation */

                if (parent_xform->getType()->checkHierarchy(&E_TRANSFORM_TYPEINFO))
                {
                    test_srp = parent_xform->getXForm(false);
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
                        test_srp = parent_xform->getXForm(false);
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

            test_srp = eSRP();

            if (nullptr != test_node)
            {
                if (test_node->getType()->checkHierarchy(&E_TRANSFORM_TYPEINFO))
                {
                    parent_xform = (eTransform*)test_node;

                    test_srp = parent_xform->getXForm(false);
                }
            }

            GUI::setMovedSeletedTransform((void*)&test_srp, 0);
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

                /* Update material selection in Materials Manager, if the selected object is a "eGeometry" */

                if (test_node->getType()->checkHierarchy(&E_GEOMETRY_TYPEINFO))
                {
                    test_geometry = (eGeometry*)test_node;

                    GUI::materialsManager_SetCurrentMaterialFromGeometry(test_geometry->getMaterial());
                }
            }

            /* Send back label text */

            sprintf_s(bufor, LARGE_BUFFER_SIZE, "< total nodes: %d >\n", theNodesCounter);

            test_string = bufor;

            sprintf_s(bufor, LARGE_BUFFER_SIZE, "(%s)", selectedObject->getType()->name);

            test_string += "Selected: ";
            test_string += bufor;
            test_string += "\n\"";
            test_string += selectedObject->getStringRepresentation();
            test_string += "\"";

            if (nullptr != test_node)
            {
                a = test_node->getFlags();

                sprintf_s(bufor, LARGE_BUFFER_SIZE, "\n0x%08X [", a);
                test_string += bufor;

                if (0x01 & a)
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
                b = test_group->getNodesCount();

                for (a = 0; a < b; a++)
                {
                    sprintf_s(bufor, LARGE_BUFFER_SIZE, "[%d] ", a);
                    test_string = bufor;

                    test_node = test_group->getIthChild(a);

                    if (nullptr != test_node)
                    {
                        sprintf_s(bufor, LARGE_BUFFER_SIZE, "(%s) ", test_node->getType()->name);
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
                    markedChildId = child_id;
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
        if (parentObject != pointer)
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

}
