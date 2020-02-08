#include <kao2ar/Archive.h>

#include <kao2engine/eScene.h>
#include <kao2engine/eXRefTarget.h>
#include <kao2engine/eXRefProxy.h>
#include <kao2engine/eTriMesh.h>
#include <kao2engine/eGeoSet.h>

#include <utilities/ColladaExporter.h>
#include <utilities/WavefrontObjExporter.h>
#include <utilities/WavefrontObjImporter.h>

namespace ZookieWizard
{

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

        if (nullptr != selectedObject)
        {
            selectedObject->renderObject(nullptr, draw_flags, default_srp);
        }
    }


    ////////////////////////////////////////////////////////////////
    // Ar: change selected object
    // (-6) rebuilds collision
    // (-5) deletes current node and updates list for parrent node
    // (-4) toggles node visibility
    // (-3) resets selection to root node
    // (-2) updates list for parrent node
    // (-1) updates list for current selection
    ////////////////////////////////////////////////////////////////
    void Archive::changeSelectedObject(int32_t child_id)
    {
        int32_t i;
        bool update_list = false;
        bool change_scene = false;
        char bufor[32];

        eGroup* test_group;
        eNode* test_node;
        eTriMesh* test_trimesh;
        eString test_str;

        switch (child_id)
        {
            case (-6): // REBUILD COLLISION
            {
                if (nullptr == selectedObject)
                {
                    return;
                }

                if (selectedObject->getType()->checkHierarchy(&E_TRIMESH_TYPEINFO))
                {
                    test_trimesh = (eTriMesh*)selectedObject;

                    test_trimesh->createCollisionEntry();

                    try
                    {
                        test_trimesh->getGeoset()->buildAabbTree();
                    }
                    catch (ErrorMessage &err)
                    {
                        err.display();
                    }
                }
                else if (selectedObject->getType()->checkHierarchy(&E_GROUP_TYPEINFO))
                {
                    test_group = (eGroup*)selectedObject;

                    for (i = 0; i < test_group->getNodesCount(); i++)
                    {
                        test_trimesh = (eTriMesh*)test_group->getIthChild(i);

                        if (test_trimesh->getType()->checkHierarchy(&E_TRIMESH_TYPEINFO))
                        {
                            test_trimesh->createCollisionEntry();

                            try
                            {
                                test_trimesh->getGeoset()->buildAabbTree();
                            }
                            catch (ErrorMessage &err)
                            {
                                err.display();
                            }
                        }
                    }
                }

                break;
            }

            case (-5): // DELETE CURRENT NODE
            case (-2): // CHANGE TO A PARENT NODE
            {
                if (nullptr == selectedObject)
                {
                    return;
                }

                if (selectedObject->getType()->checkHierarchy(&E_NODE_TYPEINFO))
                {
                    test_node = ((eNode*)selectedObject)->getParentNode();
                    if (nullptr != test_node)
                    {
                        if ((-5) == child_id)
                        {
                            if (test_node->getType()->checkHierarchy(&E_GROUP_TYPEINFO))
                            {
                                test_group = (eGroup*)test_node;

                                test_group->findAndDeleteChild((eNode*)selectedObject);
                            }
                        }

                        selectedObject = test_node;
                        change_scene = true;
                        update_list = true;
                    }
                }

                break;
            }

            case (-4): // TOGGLE VISIBILITY
            {
                if (nullptr == selectedObject)
                {
                    return;
                }

                if (selectedObject->getType()->checkHierarchy(&E_NODE_TYPEINFO))
                {
                    test_node = (eNode*)selectedObject;

                    if (0x01 & test_node->getFlags())
                    {
                        test_node->unsetFlags(0x01);
                    }
                    else
                    {
                        test_node->setFlags(0x01);
                    }

                    update_list = true;
                }

                break;
            }

            case (-3): // RESET TO ROOT
            {
                selectedObject = parentObject;

                change_scene = true;
                update_list = true;
                break;
            }

            case (-1): // UPDATE CURRENT NODE
            {
                update_list = true;
                break;
            }

            default: // SWITCH TO A CHILD NODE
            {
                if (nullptr == selectedObject)
                {
                    return;
                }

                if (selectedObject->getType()->checkHierarchy(&E_GROUP_TYPEINFO))
                {
                    test_group = (eGroup*)selectedObject;
                    test_node = test_group->getIthChild(child_id);

                    if (nullptr != test_node)
                    {
                        selectedObject = test_node;
                        change_scene = true;
                        update_list = true;
                    }
                }
            }
        }

        if (change_scene)
        {
            changeGlobalScene();
        }

        if (update_list)
        {
            GUI::updateNodesList((-1), nullptr);

            if (nullptr == selectedObject)
            {
                return;
            }

            sprintf_s(bufor, 32, "(%s)", selectedObject->getType()->name);

            test_str = "Selected node: ";
            test_str += bufor;
            test_str += "\n\"";
            test_str += selectedObject->getStringRepresentation();
            test_str += "\"";

            if (selectedObject->getType()->checkHierarchy(&E_NODE_TYPEINFO))
            {
                test_node = (eNode*)selectedObject;

                if (0x01 & (test_node->getFlags()))
                {
                    test_str += "\n[Enabled]";
                }
                else
                {
                    test_str += "\n[Disabled]";
                }
            }

            GUI::updateNodesList((-1), &test_str);

            if (selectedObject->getType()->checkHierarchy(&E_GROUP_TYPEINFO))
            {
                test_group = (eGroup*)selectedObject;

                for (i = 0; i < test_group->getNodesCount(); i++)
                {
                    sprintf_s(bufor, 32, "[%d] ", i);
                    test_str = bufor;

                    test_node = test_group->getIthChild(i);

                    if (nullptr != test_node)
                    {
                        sprintf_s(bufor, 32, "(%s) ", test_node->getType()->name);
                        test_str += bufor;
                        test_str += test_node->getStringRepresentation();
                    }
                    else
                    {
                        test_str += "<< NULL >>";
                    }

                    GUI::updateNodesList(0, &test_str);
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
            parentObject->decRef();
            parentObject = nullptr;
        }

        parentObject = pointer;

        if (nullptr != parentObject)
        {
            parentObject->incRef();

            selectedObject = parentObject;
        }
    }


    ////////////////////////////////////////////////////////////////
    // Ar: show scene as a structured text file
    ////////////////////////////////////////////////////////////////
    void Archive::writeStructureToTextFile() const
    {
        FileOperator text_file;
        eString output_path_str;
        char* output_path;

        if (nullptr != parentObject)
        {
            output_path_str = mediaDirectory + "ar.log";
            output_path = output_path_str.getText();

            text_file.setDir(output_path);
            text_file.createDir();

            if (!text_file.open(output_path, 0))
            {
                throw ErrorMessage
                (
                    "Archive::writeStructureToTextFile():\n" \
                    "Could not open file: \"%s\"",
                    output_path
                );
            }

            parentObject->writeStructureToTextFile(text_file, 0);
        }
    }


    ////////////////////////////////////////////////////////////////
    // Ar: show scene as XML file
    ////////////////////////////////////////////////////////////////
    void Archive::writeStructureToXmlFile(eString filename) const
    {
        eNode* test_node;
        ColladaExporter exporter;

        if (nullptr != parentObject)
        {
            if (parentObject->getType()->checkHierarchy(&E_NODE_TYPEINFO))
            {
                test_node = (eNode*)parentObject;

                exporter.openXml(filename);

                while (exporter.continueExporting())
                {
                    test_node->writeNodeToXmlFile(exporter);
                }
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // Ar: export selected TriMesh to OBJ file
    ////////////////////////////////////////////////////////////////
    void Archive::writeSelectedObjectToObjFile(eString filename) const
    {
        WavefrontObjExporter exporter;

        if (nullptr != selectedObject)
        {
            if (exporter.openObj(filename, (eTriMesh*)selectedObject))
            {
                exporter.begin();
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // Ar: import TriMesh to selected Group from OBJ file
    ////////////////////////////////////////////////////////////////
    void Archive::appendToSelectedObjectFromObjFile(eString filename)
    {
        WavefrontObjImporter importer;

        if (nullptr != selectedObject)
        {
            if (importer.openObj(filename, (eGroup*)selectedObject))
            {
                importer.begin();

                changeSelectedObject(-1);
            }
        }
    }

}
