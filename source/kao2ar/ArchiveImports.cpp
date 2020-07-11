#include <kao2ar/Archive.h>

#include <kao2engine/eScene.h>
#include <kao2engine/NodeRefLinker.h>

#include <kao2engine/eTransform.h>
#include <kao2engine/eBoxZone.h>
#include <kao2engine/eBillboard.h>
#include <kao2engine/eNaviPoint.h>
#include <kao2engine/eProxy.h>
#include <kao2engine/ePathCamCtrl.h>
#include <kao2engine/eCamera.h>
#include <kao2engine/eDirectionalLight.h>
#include <kao2engine/eOmniLight.h>
#include <kao2engine/eNPCMap.h>

#include <kao2engine/eEnvironment.h>

#include <utilities/ColladaExporter.h>
#include <utilities/WavefrontObjExporter.h>
#include <utilities/WavefrontObjImporter.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // Ar: show scene as a structured text file
    ////////////////////////////////////////////////////////////////
    void Archive::writeStructureToTextFile(const char* output_path) const
    {
        FileOperator text_file;

        if (nullptr != parentObject)
        {
            text_file.setDir((char*)output_path);
            text_file.createDir();

            if (!text_file.open(output_path, 0))
            {
                throw ErrorMessage
                (
                    "Archive::writeStructureToTextFile():\n\n" \
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
            if (exporter.openObj(filename, selectedObject))
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

                changeSelectedObject(NODES_LISTBOX_UPDATE_CURRENT, nullptr);
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // Ar: create Nodes and add them to selected Group from TXT file
    ////////////////////////////////////////////////////////////////
    int32_t Archive::appendNodesFromTxtFile(const char* filename)
    {
        int a, b, line_counter, parser_state, result = 0;
        float f[3];
        ePoint3 box_points[2];
        eString keywords[6];

        bool file_is_valid;
        bool line_is_valid;
        FileOperator text_file;
        eGroup* dummy_group[2];
        eEnvironment* dummy_env;
        eSRP dummy_srp;
        int32_t dummy_count;

        uint32_t node_flags_to_apply;
        uint32_t node_flags_to_remove;

        NodeRefLinker noderef_linker;

        /********************************/
        /* Prepare some definitions */

        const int NUMBER_OF_CLASSES = 9;

        int current_object = (-1);

        eTransform* dummy_xform = nullptr;
        eBoxZone* dummy_boxzone = nullptr;
        eBillboard* dummy_billboard = nullptr;
        eNaviPoint* dummy_navi = nullptr;
        eProxy* dummy_proxy = nullptr;
        ePathCamCtrl* dummy_pathcamctrl = nullptr;
        eCamera* dummy_camera = nullptr;
        eLight* dummy_light = nullptr;
        eDirectionalLight* dummy_dir_light = nullptr;
        eOmniLight* dummy_omni_light = nullptr;
        eNPCMap* dummy_npcmap = nullptr;

        const char* class_names[NUMBER_OF_CLASSES] =
        {
            "<eTransform>",
            "<eBoxZone>",
            "<eBillboard>",
            "<eNaviPoint>",
            "<eProxy>",
            "<eCamera>",
            "<eDirectionalLight>",
            "<eOmniLight>",
            "<eNPCMap>"
        };

        const int PARSER_OBJECT_ID_TRANSFORM = 0;
        const int PARSER_OBJECT_ID_BOXZONE = 1;
        const int PARSER_OBJECT_ID_BILLBOARD = 2;
        const int PARSER_OBJECT_ID_NAVIPOINT = 3;
        const int PARSER_OBJECT_ID_PROXY = 4;
        const int PARSER_OBJECT_ID_CAMERA = 5;
        const int PARSER_OBJECT_ID_DIRLIGHT = 6;
        const int PARSER_OBJECT_ID_OMNILIGHT = 7;
        const int PARSER_OBJECT_ID_NPCMAP = 8;

        eNode** class_pointers[NUMBER_OF_CLASSES] =
        {
            (eNode**)&dummy_xform,
            (eNode**)&dummy_boxzone,
            (eNode**)&dummy_billboard,
            (eNode**)&dummy_navi,
            (eNode**)&dummy_proxy,
            (eNode**)&dummy_camera,
            (eNode**)&dummy_dir_light,
            (eNode**)&dummy_omni_light,
            (eNode**)&dummy_npcmap
        };

        const int NUMBER_OF_PROPERTIES = 17;

        const char* properties[NUMBER_OF_PROPERTIES] =
        {
            "parent", "name", "pos", "rot", "scl",
            "link", "category",
            "fov", "nearPlane", "farPlane", "useCurrentFollow",
            "diffuse", "ambient", "specular",
            "min", "max", "count"
        };

        const int PARSER_PROPERTY_ID_PARENT = 0;
        const int PARSER_PROPERTY_ID_NAME = 1;
        const int PARSER_PROPERTY_ID_POS = 2;
        const int PARSER_PROPERTY_ID_ROT = 3;
        const int PARSER_PROPERTY_ID_SCL = 4;
        const int PARSER_PROPERTY_ID_LINK = 5;
        const int PARSER_PROPERTY_ID_CATEGORY = 6;
        const int PARSER_PROPERTY_ID_FOV = 7;
        const int PARSER_PROPERTY_ID_NEARPLANE = 8;
        const int PARSER_PROPERTY_ID_FARPLANE = 9;
        const int PARSER_PROPERTY_ID_USECURRENTFOLLOW = 10;
        const int PARSER_PROPERTY_ID_DIFFUSE = 11;
        const int PARSER_PROPERTY_ID_AMBIENT = 12;
        const int PARSER_PROPERTY_ID_SPECULAR = 13;
        const int PARSER_PROPERTY_ID_MIN = 14;
        const int PARSER_PROPERTY_ID_MAX = 15;
        const int PARSER_PROPERTY_ID_COUNT = 16;

        const int properties_args[NUMBER_OF_PROPERTIES] =
        {
            1, 1, 3, 3, 1,
            1, 1,
            1, 1, 1, 1,
            3, 3, 3,
            3, 3, 1
        };

        const bool properties_of_classes[NUMBER_OF_CLASSES][NUMBER_OF_PROPERTIES] =
        {
            {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // eTransform
            {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0}, // eBoxZone
            {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // eBillbord
            {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // eNaviPoint
            {1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // eProxy
            {1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0}, // eCamera
            {1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0}, // eDirectionalLight
            {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0}, // eOmniLight
            {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1}  // eNPCMap
        };

        bool found_any_property;
        bool property_duplicate[NUMBER_OF_PROPERTIES];

        const int PROXY_CATEGORIES_COUNT = 7;

        const char* proxy_category_names[PROXY_CATEGORIES_COUNT] =
        {
            "particle", "hero", "powerup", "enemy", "fluff", "geoproxy", "object"
        };

        /********************************/
        /* Check selected object and open text file */

        if (nullptr != selectedObject)
        {
            if (false == selectedObject->getType()->checkHierarchy(&E_GROUP_TYPEINFO))
            {
                throw ErrorMessage
                (
                    "Archive::appendNodesFromTxtFile():\n\n" \
                    "Selected object is not a \"eGroup\" type!"
                );
            }

            dummy_group[0] = (eGroup*)selectedObject;

            if (!text_file.open(filename, FILE_OPERATOR_MODE_READ))
            {
                throw ErrorMessage
                (
                    "Archive::appendNodesFromTxtFile():\n\n" \
                    "Could not open file: \"%s\"",
                    filename
                );
            }

            /********************************/
            /* Begin reading */

            line_counter = 0;

            while ((file_is_valid = !text_file.endOfFileReached()) || (current_object >= 0))
            {
                line_is_valid = false;
                parser_state = (-1);

                if (file_is_valid)
                {
                    keywords[0] << text_file;
                    line_counter++;

                    keywords[0] = ArFunctions::removeComment(keywords[0], true);

                    if (ArFunctions::splitString(keywords[0], &(keywords[1]), 2) >= 1)
                    {
                        /* Minimal lenght of 3: "?=?" or "<?>" */

                        if (line_is_valid = (keywords[1].getLength() >= 3))
                        {
                            if ('<' == keywords[1].getText()[0])
                            {
                                for (a = 0; (parser_state < 0) && (a < NUMBER_OF_CLASSES); a++)
                                {
                                    if (keywords[1].compareExact(class_names[a],  true))
                                    {
                                        parser_state = a;
                                    }
                                }

                                if (parser_state < 0)
                                {
                                    throw ErrorMessage
                                    (
                                        "Archive::appendNodesFromTxtFile():\n\n" \
                                        "Unrecognized class identifier \"%s\"!\n\n" \
                                        "(line %d)",
                                        keywords[1].getText(),
                                        line_counter
                                    );
                                }
                            }
                        }
                    }
                }

                /* Should previous object be saved? */
                /* (end of file reached OR new object is waiting) */

                if ((current_object >= 0) && ((false == file_is_valid) || (parser_state >= 0)))
                {
                    if (found_any_property)
                    {


                        switch (current_object)
                        {
                            case PARSER_OBJECT_ID_TRANSFORM:
                            case PARSER_OBJECT_ID_BILLBOARD:
                            case PARSER_OBJECT_ID_NAVIPOINT:
                            case PARSER_OBJECT_ID_PROXY:
                            case PARSER_OBJECT_ID_CAMERA:
                            {
                                ((eTransform*)*(class_pointers[current_object]))->setXForm(dummy_srp);

                                if (PARSER_OBJECT_ID_CAMERA == current_object)
                                {
                                    dummy_camera->setCameraTarget(dummy_xform);

                                    dummy_pathcamctrl->setCameraLink(dummy_camera);
                                    dummy_pathcamctrl->setPosition(dummy_srp.pos);

                                    dummy_camera->setPathCamCtrl(dummy_pathcamctrl);
                                }
                                else if (PARSER_OBJECT_ID_PROXY == current_object)
                                {
                                    dummy_proxy->reloadXRef(*this);
                                }

                                break;
                            }

                            case PARSER_OBJECT_ID_BOXZONE:
                            {
                                dummy_boxzone->setBoundaryBox(box_points[0], box_points[1]);

                                break;
                            }

                            case PARSER_OBJECT_ID_DIRLIGHT:
                            case PARSER_OBJECT_ID_OMNILIGHT:
                            {
                                switch (current_object)
                                {
                                    case PARSER_OBJECT_ID_DIRLIGHT:
                                    {
                                        dummy_dir_light->setPosition(dummy_srp.pos);

                                        dummy_dir_light->setLightTarget(dummy_xform);

                                        break;
                                    }

                                    case PARSER_OBJECT_ID_OMNILIGHT:
                                    {
                                        dummy_omni_light->setPosition(dummy_srp.pos);

                                        break;
                                    }

                                    default:
                                    {
                                        dummy_light = nullptr;
                                    }
                                }

                                if (dummy_light != nullptr)
                                {
                                    dummy_env = (eEnvironment*)dummy_group[1];

                                    while ((nullptr != dummy_env) && (dummy_env->getType() != &E_ENVIRONMENT_TYPEINFO))
                                    {
                                        dummy_env = (eEnvironment*)dummy_env->getParentNode();
                                    }

                                    if (nullptr != dummy_env)
                                    {
                                        dummy_env->addLighting(dummy_light);
                                    }
                                }

                                break;
                            }

                            case PARSER_OBJECT_ID_NPCMAP:
                            {
                                dummy_npcmap->customSetup(box_points[0], box_points[1], dummy_count);

                                break;
                            }
                        }

                        dummy_group[1]->appendChild(*(class_pointers[current_object]));

                        result++;
                    }

                    (*(class_pointers[current_object]))->decRef();
                    (*(class_pointers[current_object])) = nullptr;

                    current_object = (-1);
                }

                /* Should new object be created? */

                if (parser_state >= 0)
                {
                    /* Rest parser settings */

                    dummy_group[1] = dummy_group[0];

                    found_any_property = false;

                    for (a = 0; a < NUMBER_OF_PROPERTIES; a++)
                    {
                        property_duplicate[a] = false;
                    }

                    dummy_srp = eSRP();
                    box_points[0] = {0, 0, 0};
                    box_points[1] = {1.0f, 1.0f, 1.0f};
                    dummy_count = 0;

                    node_flags_to_apply = 0x00000000;
                    node_flags_to_remove = 0x00000000;

                    /* Instancize */

                    switch (parser_state)
                    {
                        case PARSER_OBJECT_ID_TRANSFORM:
                        {
                            dummy_xform = new eTransform();

                            break;
                        }

                        case PARSER_OBJECT_ID_BOXZONE:
                        {
                            dummy_boxzone = new eBoxZone();

                            node_flags_to_apply = 0x40000000;
                            break;
                        }

                        case PARSER_OBJECT_ID_BILLBOARD:
                        {
                            dummy_billboard = new eBillboard();

                            node_flags_to_apply = 0x20000000;
                            break;
                        }

                        case PARSER_OBJECT_ID_NAVIPOINT:
                        {
                            dummy_navi = new eNaviPoint();

                            node_flags_to_apply = 0x40000000;
                            node_flags_to_remove = 0x00000400;
                            break;
                        }

                        case PARSER_OBJECT_ID_PROXY:
                        {
                            dummy_proxy = new eProxy();

                            break;
                        }

                        case PARSER_OBJECT_ID_CAMERA:
                        {
                            dummy_xform = nullptr;

                            dummy_camera = new eCamera();

                            dummy_pathcamctrl = new ePathCamCtrl();

                            node_flags_to_apply = 0x40000040;
                            break;
                        }

                        case PARSER_OBJECT_ID_DIRLIGHT:
                        {
                            dummy_xform = nullptr;

                            dummy_light = dummy_dir_light = new eDirectionalLight();

                            node_flags_to_apply = 0x40000000;
                            node_flags_to_remove = 0x00000400;
                            break;
                        }

                        case PARSER_OBJECT_ID_OMNILIGHT:
                        {
                            dummy_light = dummy_omni_light = new eOmniLight();

                            node_flags_to_apply = 0x40000000;
                            node_flags_to_remove = 0x00000400;
                            break;
                        }

                        case PARSER_OBJECT_ID_NPCMAP:
                        {
                            dummy_npcmap = new eNPCMap();

                            node_flags_to_apply = 0x40000000;
                            break;
                        }

                        default:
                        {
                            parser_state = (-1);
                        }
                    }

                    if (parser_state >= 0)
                    {
                        current_object = parser_state;

                        (*(class_pointers[current_object]))->incRef();

                        (*(class_pointers[current_object]))->setFlags(node_flags_to_apply);
                        (*(class_pointers[current_object]))->unsetFlags(node_flags_to_remove);
                    }
                }
                else if ((current_object >= 0) && line_is_valid)
                {
                    /********************************/
                    /* Parsing properties... */

                    b = ArFunctions::propertyString(keywords[0], &(keywords[1]), 5, line_counter);

                    parser_state = (-1);

                    for (a = 0; (parser_state < 0) && (a < NUMBER_OF_PROPERTIES); a++)
                    {
                        if (properties_of_classes[current_object][a])
                        {
                            if (keywords[1].compareExact(properties[a], false))
                            {
                                if (property_duplicate[a])
                                {
                                    throw ErrorMessage
                                    (
                                        "Archive::appendNodesFromTxtFile():\n\n" \
                                        "Duplicate property \"%s\"!\n\n" \
                                        "(line %d)",
                                        keywords[1].getText(),
                                        line_counter
                                    );
                                }
                                else if (b >= properties_args[a])
                                {
                                    property_duplicate[a] = true;
                                    parser_state = a;
                                }
                                else
                                {
                                    throw ErrorMessage
                                    (
                                        "Archive::appendNodesFromTxtFile():\n\n" \
                                        "Not enough arguments for property \"%s\"!\n\n" \
                                        "(line %d)",
                                        keywords[1].getText(),
                                        line_counter
                                    );
                                }
                            }
                        }
                    }

                    if (parser_state < 0)
                    {
                        throw ErrorMessage
                        (
                            "Archive::appendNodesFromTxtFile():\n\n" \
                            "Unrecognized property \"%s\" for class %s!\n\n" \
                            "(line %d)",
                            keywords[1].getText(),
                            class_names[current_object],
                            line_counter
                        );
                    }

                    /********************************/
                    /* Given property is valid for current object */

                    switch (parser_state)
                    {
                        case PARSER_PROPERTY_ID_PARENT:
                        {
                            dummy_group[1] = (eGroup*)noderef_linker.findLink
                            (
                                ArFunctions::getCurrentScene(),
                                dummy_group[0],
                                "Parent",
                                keywords[2],
                                &E_GROUP_TYPEINFO
                            );

                            break;
                        }

                        case PARSER_PROPERTY_ID_NAME:
                        {
                            (*(class_pointers[current_object]))->setName(keywords[2]);
                            break;
                        }

                        case PARSER_PROPERTY_ID_POS:
                        {
                            dummy_srp.pos.x = (float)std::atof(keywords[2].getText());
                            dummy_srp.pos.y = (float)std::atof(keywords[3].getText());
                            dummy_srp.pos.z = (float)std::atof(keywords[4].getText());

                            break;
                        }

                        case PARSER_PROPERTY_ID_ROT:
                        {
                            f[0] = (float)std::atof(keywords[2].getText()) / 180.0f * (float)M_PI;
                            f[1] = (float)std::atof(keywords[3].getText()) / 180.0f * (float)M_PI;
                            f[2] = (float)std::atof(keywords[4].getText()) / 180.0f * (float)M_PI;

                            dummy_srp.rot.fromEulerAngles(true, f[0], f[1], f[2]);

                            break;
                        }

                        case PARSER_PROPERTY_ID_SCL:
                        {
                            dummy_srp.scale = (float)std::atof(keywords[2].getText());

                            break;
                        }

                        case PARSER_PROPERTY_ID_LINK:
                        {
                            switch (current_object)
                            {
                                case PARSER_OBJECT_ID_PROXY:
                                {
                                    dummy_proxy->setTargetName(keywords[2]);
                                    break;
                                }

                                case PARSER_OBJECT_ID_CAMERA:
                                case PARSER_OBJECT_ID_DIRLIGHT:
                                {
                                    dummy_xform = (eTransform*)noderef_linker.findLink
                                    (
                                        ArFunctions::getCurrentScene(),
                                        dummy_group[1],
                                        "Target",
                                        keywords[2],
                                        &E_TRANSFORM_TYPEINFO
                                    );

                                    break;
                                }
                            }

                            break;
                        }

                        case PARSER_PROPERTY_ID_CATEGORY:
                        {
                            parser_state = 0;

                            for (a = 0; (!parser_state) && (a < PROXY_CATEGORIES_COUNT); a++)
                            {
                                if (keywords[2].compareExact(proxy_category_names[a], false))
                                {
                                    dummy_proxy->setCategory(a);

                                    parser_state = 1;
                                }
                            }

                            if (!parser_state)
                            {
                                throw ErrorMessage
                                (
                                    "Archive::appendNodesFromTxtFile():\n\n" \
                                    "Unrecognized <eProxy> category \"%s\"!\n\n" \
                                    "(line %d)",
                                    keywords[2].getText(),
                                    line_counter
                                );
                            }

                            break;
                        }

                        case PARSER_PROPERTY_ID_FOV:
                        {
                            f[0] = (float)std::atof(keywords[2].getText());

                            dummy_camera->setFieldOfView(f[0]);

                            break;
                        }

                        case PARSER_PROPERTY_ID_NEARPLANE:
                        {
                            f[0] = (float)std::atof(keywords[2].getText());

                            dummy_camera->setNearPlane(f[0]);

                            break;
                        }

                        case PARSER_PROPERTY_ID_FARPLANE:
                        {
                            f[0] = (float)std::atof(keywords[2].getText());

                            dummy_camera->setFarPlane(f[0]);

                            break;
                        }

                        case PARSER_PROPERTY_ID_USECURRENTFOLLOW:
                        {
                            if (keywords[2].compareExact("true", false))
                            {
                                a = 1;
                            }
                            else
                            {
                                a = std::atoi(keywords[2].getText());
                            }

                            dummy_camera->setLookingAtFollowCamera((bool)a);

                            break;
                        }

                        case PARSER_PROPERTY_ID_DIFFUSE:
                        {
                            f[0] = (float)std::atof(keywords[2].getText());
                            f[1] = (float)std::atof(keywords[3].getText());
                            f[2] = (float)std::atof(keywords[4].getText());

                            dummy_light->setDiffuseColor(f);

                            break;
                        }

                        case PARSER_PROPERTY_ID_AMBIENT:
                        {
                            f[0] = (float)std::atof(keywords[2].getText());
                            f[1] = (float)std::atof(keywords[3].getText());
                            f[2] = (float)std::atof(keywords[4].getText());

                            dummy_light->setAmbientColor(f);

                            break;
                        }

                        case PARSER_PROPERTY_ID_SPECULAR:
                        {
                            f[0] = (float)std::atof(keywords[2].getText());
                            f[1] = (float)std::atof(keywords[3].getText());
                            f[2] = (float)std::atof(keywords[4].getText());

                            dummy_light->setSpecularColor(f);

                            break;
                        }

                        case PARSER_PROPERTY_ID_MIN:
                        {
                            box_points[0].x = (float)std::atof(keywords[2].getText());
                            box_points[0].y = (float)std::atof(keywords[3].getText());
                            box_points[0].z = (float)std::atof(keywords[4].getText());

                            break;
                        }

                        case PARSER_PROPERTY_ID_MAX:
                        {
                            box_points[1].x = (float)std::atof(keywords[2].getText());
                            box_points[1].y = (float)std::atof(keywords[3].getText());
                            box_points[1].z = (float)std::atof(keywords[4].getText());

                            break;
                        }

                        case PARSER_PROPERTY_ID_COUNT:
                        {
                            dummy_count = std::atoi(keywords[2].getText());

                            break;
                        }
                    }

                    found_any_property = true;
                }
            }

            changeSelectedObject(NODES_LISTBOX_UPDATE_CURRENT, nullptr);
        }

        return result;
    }


    ////////////////////////////////////////////////////////////////
    // Ar: change Nodes with specific instructions from a TXT file
    ////////////////////////////////////////////////////////////////
    int32_t Archive::changeNodesWithTxtFile(const char* filename)
    {
        int a, b, c, start_pos, end_pos;
        float f[3];
        int i[3];

        int line_counter, parser_state, result = 0;

        FileOperator text_file;
        eString strings[2];
        char* line_text;
        int line_length;

        int current_keyword;
        bool keyword_parsed;
        int noderef_send_id;
        int message_send_id;

        const int MESSAGES_MAX_PARAMS = 10;
        eString message_params[MESSAGES_MAX_PARAMS];

        eGroup* dummy_group;
        eSRP dummy_srp;

        eNode* dummy_node = nullptr;
        eTransform* dummy_xform = nullptr;
        ePivot* dummy_pivot = nullptr;
        eEnvironment* dummy_env = nullptr;
        eZone* dummy_zone = nullptr;
        eActionBase dummy_zone_action;

        const int NUMBER_OF_NODEREFS = 32;

        int noderefs_count = 0;
        eNode* noderefs_pointers[NUMBER_OF_NODEREFS];
        eString noderefs_names[NUMBER_OF_NODEREFS];
        TypeInfo* noderefs_types[NUMBER_OF_NODEREFS];

        NodeRefLinker noderef_linker;

        /********************************/
        /* Prepare some definitions */

        const int NUMBER_OF_KEYWORDS = 2;

        const char* keyword_names[NUMBER_OF_KEYWORDS] =
        {
            "node", "send"
        };

        const int PARSER_KEYWORD_ID_NODE = 0;
        const int PARSER_KEYWORD_ID_SEND = 1;

        const int NUMBER_OF_MESSAGES = 21;

        const char* messages_strings[NUMBER_OF_MESSAGES] =
        {
            "visCtrlClear",
            "visCtrlSetStatic",
            "visCtrlAddKeyframe",
            "setPos",
            "setRot",
            "setScl",
            "ctrlClearKeyframes",
            "ctrlSetStaticScale",
            "ctrlSetStaticRotation",
            "ctrlSetStaticPosition",
            "ctrlAddKeyframe",
            "animAddTrack",
            "animRemoveTrack",
            "setFogColor",
            "setFogStart",
            "setFogEnd",
            "setFogMax",
            "clearEnterActions",
            "clearLeaveActions",
            "addEnterAction",
            "addLeaveAction"
        };

        const int PARSER_MESSAGE_ID_VISCTRLCLEAR = 0;
        const int PARSER_MESSAGE_ID_VISCTRLSETSTATIC = 1;
        const int PARSER_MESSAGE_ID_VISCTRLADDKEYFRAME = 2;
        const int PARSER_MESSAGE_ID_SETPOS = 3;
        const int PARSER_MESSAGE_ID_SETROT = 4;
        const int PARSER_MESSAGE_ID_SETSCL = 5;
        const int PARSER_MESSAGE_ID_CTRLCLEARKEYFRAMES = 6;
        const int PARSER_MESSAGE_ID_CTRLSETSTATICSCALE = 7;
        const int PARSER_MESSAGE_ID_CTRLSETSTATICROTATION = 8;
        const int PARSER_MESSAGE_ID_CTRLSETSTATICPOSITION = 9;
        const int PARSER_MESSAGE_ID_CTRLADDKEYFRAME = 10;
        const int PARSER_MESSAGE_ID_ANIMADDTRACK = 11;
        const int PARSER_MESSAGE_ID_ANIMREMOVETRACK = 12;
        const int PARSER_MESSAGE_ID_SETFOGCOLOR = 13;
        const int PARSER_MESSAGE_ID_SETFOGCSTART = 14;
        const int PARSER_MESSAGE_ID_SETFOGEND = 15;
        const int PARSER_MESSAGE_ID_SETFOGMAX = 16;
        const int PARSER_MESSAGE_ID_CLEARENTERACTIONS = 17;
        const int PARSER_MESSAGE_ID_CLEARLEAVEACTIONS = 18;
        const int PARSER_MESSAGE_ID_ADDENTERACTION = 19;
        const int PARSER_MESSAGE_ID_ADDLEAVEACTION = 20;

        TypeInfo* messages_object_types[NUMBER_OF_MESSAGES] =
        {
            &E_NODE_TYPEINFO, // `visCtrlClear()`
            &E_NODE_TYPEINFO, // `visCtrlSetStatic()`
            &E_NODE_TYPEINFO, // `visCtrlAddKeyframe()`
            &E_TRANSFORM_TYPEINFO, // `setPos()`
            &E_TRANSFORM_TYPEINFO, // `setRot()`
            &E_TRANSFORM_TYPEINFO, // `setScl()`
            &E_TRANSFORM_TYPEINFO, // `ctrlClearKeyframes()`
            &E_TRANSFORM_TYPEINFO, // `ctrlSetStaticScale()`
            &E_TRANSFORM_TYPEINFO, // `ctrlSetStaticRotation()`
            &E_TRANSFORM_TYPEINFO, // `ctrlSetStaticPosition()`
            &E_TRANSFORM_TYPEINFO, // `ctrlAddKeyframe()`
            &E_PIVOT_TYPEINFO, // `animAddTrack()`
            &E_PIVOT_TYPEINFO, // `animRemoveTrack()`
            &E_ENVIRONMENT_TYPEINFO, // `setFogColor()`
            &E_ENVIRONMENT_TYPEINFO, // `setFogStart()`
            &E_ENVIRONMENT_TYPEINFO, // `setFogEnd()`
            &E_ENVIRONMENT_TYPEINFO, // `setFogMax()`
            &E_ZONE_TYPEINFO, // `clearEnterActions()`
            &E_ZONE_TYPEINFO, // `clearLeaveActions()`
            &E_ZONE_TYPEINFO, // `addEnterAction()`
            &E_ZONE_TYPEINFO  // `addLeaveAction()`
        };

        const uint8_t messages_params_count[NUMBER_OF_MESSAGES] =
        {
            1,  // `visCtrlClear()`
            1,  // `visCtrlSetStatic()`
            3,  // `visCtrlAddKeyframe()`
            3,  // `setPos()`
            3,  // `setRot()`
            1,  // `setScl()`
            1,  // `ctrlClearKeyframes()`
            1,  // `ctrlSetStaticScale()`
            3,  // `ctrlSetStaticRotation()`
            3,  // `ctrlSetStaticPosition()`
            10, // `ctrlAddKeyframe()`
            3,  // `animAddTrack()`
            1,  // `animRemoveTrack()`
            3,  // `setFogColor()`
            1,  // `setFogStart()`
            1,  // `setFogEnd()`
            1,  // `setFogMax()`
            0,  // `clearEnterActions()`
            0,  // `clearLeaveActions()`
            2,  // `addEnterAction()`
            2   // `addLeaveAction()`
        };

        /********************************/
        /* Check selected object and open text file */

        if (nullptr != selectedObject)
        {
            if (false == selectedObject->getType()->checkHierarchy(&E_GROUP_TYPEINFO))
            {
                throw ErrorMessage
                (
                    "Archive::changeNodesWithTxtFile():\n\n" \
                    "Selected object is not a \"eGroup\" type!"
                );
            }

            dummy_group = (eGroup*)selectedObject;

            if (false == text_file.open(filename, FILE_OPERATOR_MODE_READ))
            {
                throw ErrorMessage
                (
                    "Archive::changeNodesWithTxtFile():\n\n" \
                    "Could not open file: \"%s\"",
                    filename
                );
            }

            /********************************/
            /* Begin reading */

            line_counter = 0;

            while (false == text_file.endOfFileReached())
            {
                strings[0] << text_file;
                line_counter++;

                strings[0] = ArFunctions::removeComment(strings[0], false);

                line_text = strings[0].getText();
                line_length = strings[0].getLength();

                /* Parse current line */

                start_pos = (-1);
                end_pos = (-1);
                current_keyword = (-1);
                keyword_parsed = true;
                parser_state = 0;

                a = 0;

                while (a < line_length)
                {
                    if (current_keyword < 0)
                    {
                        if ((line_text[a] >= 'a') && (line_text[a] <= 'z'))
                        {
                            if (start_pos < 0)
                            {
                                start_pos = a;
                            }
                        }
                        else if (' ' == line_text[a])
                        {
                            if ((start_pos >= 0) && (end_pos < 0))
                            {
                                end_pos = a;
                            }
                        }
                        else
                        {
                            throw ErrorMessage
                            (
                                "Archive::changeNodesWithTxtFile():\n\n" \
                                "invalid character\n\n" \
                                "(line %d, position %d)",
                                line_counter,
                                (a + 1)
                            );
                        }

                        if ((start_pos >= 0) && (end_pos >= 0))
                        {
                            strings[1] = strings[0].getSubstring(start_pos, end_pos - start_pos);

                            for (b = 0; (current_keyword < 0) && (b < NUMBER_OF_KEYWORDS); b++)
                            {
                                if (strings[1].compareExact(keyword_names[b], true))
                                {
                                    current_keyword = b;
                                }
                            }

                            if (current_keyword < 0)
                            {
                                throw ErrorMessage
                                (
                                    "Archive::changeNodesWithTxtFile():\n\n" \
                                    "unrecognized keyword\n\n" \
                                    "(line %d, position %d)",
                                    line_counter,
                                    (start_pos + 1)
                                );
                            }

                            if ((PARSER_KEYWORD_ID_NODE == current_keyword) && (noderefs_count >= NUMBER_OF_NODEREFS))
                            {
                                throw ErrorMessage
                                (
                                    "Archive::changeNodesWithTxtFile():\n\n" \
                                    "too many nodeRefs! (max %d)",
                                    NUMBER_OF_NODEREFS
                                );
                            }

                            /* Before continuing with a keyword */

                            start_pos = (-1);
                            end_pos = (-1);
                            keyword_parsed = false;
                        }
                    }
                    else
                    {
                        if (PARSER_KEYWORD_ID_NODE == current_keyword)
                        {
                            if (0 == parser_state)
                            {
                                /* "TypeInfo" identifier */

                                if (((line_text[a] >= 'a') && (line_text[a] <= 'z')) || ((line_text[a] >= 'A') && (line_text[a] <= 'Z')))
                                {
                                    if (start_pos < 0)
                                    {
                                        start_pos = a;
                                    }
                                }
                                else
                                {
                                    if (start_pos < 0)
                                    {
                                        if (' ' != line_text[a])
                                        {
                                            throw ErrorMessage
                                            (
                                                "Archive::changeNodesWithTxtFile():\n\n" \
                                                "\"node\" keyword: TypeInfo must be alphabetic!\n\n" \
                                                "(line %d, position %d)",
                                                line_counter,
                                                (a + 1)
                                            );
                                        }
                                    }
                                    else
                                    {
                                        strings[1] = strings[0].getSubstring(start_pos, a - start_pos);

                                        noderefs_types[noderefs_count] = InterfaceManager.getTypeInfo(strings[1].getText());

                                        if (false == noderefs_types[noderefs_count]->checkHierarchy(&E_NODE_TYPEINFO))
                                        {
                                            throw ErrorMessage
                                            (
                                                "Archive::changeNodesWithTxtFile():\n\n" \
                                                "\"node\" keyword: TypeInfo is not eNode or its child!\n\n" \
                                                "(line %d, position %d)",
                                                line_counter,
                                                (start_pos + 1)
                                            );
                                        }

                                        /* Next state */
                                        a--;
                                        parser_state++;
                                        start_pos = (-1);
                                    }
                                }
                            }
                            else if (1 == parser_state)
                            {
                                /* "nodeRef" identifier */

                                if (start_pos < 0)
                                {
                                    if (('_' == line_text[a])
                                        || ((line_text[a] >= 'a') && (line_text[a] <= 'z'))
                                        || ((line_text[a] >= 'A') && (line_text[a] <= 'Z')))
                                    {
                                        start_pos = a;
                                    }
                                    else if (' ' != line_text[a])
                                    {
                                        throw ErrorMessage
                                        (
                                            "Archive::changeNodesWithTxtFile():\n\n" \
                                            "\"node\" keyword: nodeRef must be an identifier!\n\n" \
                                            "(line %d, position %d)",
                                            line_counter,
                                            (a + 1)
                                        );
                                    }
                                }
                                else if (('_' != line_text[a])
                                    && ((line_text[a] < '0') || (line_text[a] > '9'))
                                    && ((line_text[a] < 'a') || (line_text[a] > 'z'))
                                    && ((line_text[a] < 'A') || (line_text[a] > 'Z')))
                                {
                                    noderefs_names[noderefs_count] = strings[0].getSubstring(start_pos, a - start_pos);

                                    for (b = 0; b < noderefs_count; b++)
                                    {
                                        if (noderefs_names[noderefs_count].compareExact(noderefs_names[b], true))
                                        {
                                            throw ErrorMessage
                                            (
                                                "Archive::changeNodesWithTxtFile():\n\n" \
                                                "\"node\" keyword: nodeRef \"%s\" already defined!\n\n" \
                                                "(line %d, position %d)",
                                                noderefs_names[noderefs_count].getText(),
                                                line_counter,
                                                (start_pos + 1)
                                            );
                                        }
                                    }

                                    /* Next state */
                                    a--;
                                    parser_state++;
                                    start_pos = (-1);
                                    b = 0;
                                }
                            }
                            else if (2 == parser_state)
                            {
                                /* "mask" string */

                                if (0 == b)
                                {
                                    if ('(' == line_text[a])
                                    {
                                        b++;
                                    }
                                    else if (' ' != line_text[a])
                                    {
                                        throw ErrorMessage
                                        (
                                            "Archive::changeNodesWithTxtFile():\n\n" \
                                            "\"node\" keyword: '(' expected!\n\n" \
                                            "(line %d, position %d)",
                                            line_counter,
                                            (a + 1)
                                        );
                                    }
                                }
                                else if ((1 == b) || (2 == b))
                                {
                                    if ('"' == line_text[a])
                                    {
                                        if (start_pos < 0)
                                        {
                                            start_pos = a + 1;
                                        }
                                        else
                                        {
                                            end_pos = a;
                                        }

                                        b++;
                                    }
                                    else if ((1 == b) && (' ' != line_text[a]))
                                    {
                                        throw ErrorMessage
                                        (
                                            "Archive::changeNodesWithTxtFile():\n\n" \
                                            "\"node\" keyword: '\"' expected!\n\n" \
                                            "(line %d, position %d)",
                                            line_counter,
                                            (a + 1)
                                        );
                                    }
                                }
                                else if (3 == b)
                                {
                                    if (')' == line_text[a])
                                    {
                                        strings[1] = strings[0].getSubstring(start_pos, end_pos - start_pos);

                                        noderefs_pointers[noderefs_count] = noderef_linker.findLink
                                        (
                                            ArFunctions::getCurrentScene(),
                                            dummy_group,
                                            noderefs_names[noderefs_count],
                                            strings[1],
                                            noderefs_types[noderefs_count]
                                        );

                                        /* Parsing complete! */

                                        noderefs_count++;

                                        start_pos = (-1);
                                        end_pos = (-1);
                                        current_keyword = (-1);
                                        keyword_parsed = true;
                                        parser_state = 0;
                                    }
                                    else if (' ' != line_text[a])
                                    {
                                        throw ErrorMessage
                                        (
                                            "Archive::changeNodesWithTxtFile():\n\n" \
                                            "\"node\" keyword: ')' expected!\n\n" \
                                            "(line %d, position %d)",
                                            line_counter,
                                            (a + 1)
                                        );
                                    }
                                }
                            }
                        }
                        else if (PARSER_KEYWORD_ID_SEND == current_keyword)
                        {
                            if (0 == parser_state)
                            {
                                /* "nodeRef" identifier */

                                if (start_pos < 0)
                                {
                                    if (('_' == line_text[a])
                                        || ((line_text[a] >= 'a') && (line_text[a] <= 'z'))
                                        || ((line_text[a] >= 'A') && (line_text[a] <= 'Z')))
                                    {
                                        start_pos = a;
                                    }
                                    else if (' ' != line_text[a])
                                    {
                                        throw ErrorMessage
                                        (
                                            "Archive::changeNodesWithTxtFile():\n\n" \
                                            "\"send\" keyword: nodeRef must be an identifier!\n\n" \
                                            "(line %d, position %d)",
                                            line_counter,
                                            (a + 1)
                                        );
                                    }
                                }
                                else if (('_' != line_text[a])
                                    && ((line_text[a] < '0') || (line_text[a] > '9'))
                                    && ((line_text[a] < 'a') || (line_text[a] > 'z'))
                                    && ((line_text[a] < 'A') || (line_text[a] > 'Z')))
                                {
                                    strings[1] = strings[0].getSubstring(start_pos, a - start_pos);

                                    noderef_send_id = (-1);

                                    for (b = 0; (noderef_send_id < 0) && (b < noderefs_count); b++)
                                    {
                                        if (strings[1].compareExact(noderefs_names[b], true))
                                        {
                                            noderef_send_id = b;
                                        }
                                    }

                                    if (noderef_send_id < 0)
                                    {
                                        throw ErrorMessage
                                        (
                                            "Archive::changeNodesWithTxtFile():\n\n" \
                                            "\"send\" keyword: nodeRef \"%s\" not found!\n\n" \
                                            "(line %d, position %d)",
                                            strings[1].getText(),
                                            line_counter,
                                            (start_pos + 1)
                                        );
                                    }

                                    /* Next state */
                                    a--;
                                    parser_state++;
                                }
                            }
                            else if (1 == parser_state)
                            {
                                /* Dot separator */

                                if ('.' == line_text[a])
                                {
                                    parser_state++;
                                    start_pos = (-1);
                                }
                                else if (' ' != line_text[a])
                                {
                                    throw ErrorMessage
                                    (
                                        "Archive::changeNodesWithTxtFile():\n\n" \
                                        "\"send\" keyword: '.' expected!\n\n" \
                                        "(line %d, position %d)",
                                        line_counter,
                                        (a + 1)
                                    );
                                }
                            }
                            else if (2 == parser_state)
                            {
                                /* "message" identifier */

                                if (((line_text[a] >= 'a') && (line_text[a] <= 'z')) || ((line_text[a] >= 'A') && (line_text[a] <= 'Z')))
                                {
                                    if (start_pos < 0)
                                    {
                                        start_pos = a;
                                    }
                                }
                                else
                                {
                                    if (start_pos < 0)
                                    {
                                        if (' ' != line_text[a])
                                        {
                                            throw ErrorMessage
                                            (
                                                "Archive::changeNodesWithTxtFile():\n\n" \
                                                "\"send\" keyword: message must be alphabetic!\n\n" \
                                                "(line %d, position %d)",
                                                line_counter,
                                                (a + 1)
                                            );
                                        }
                                    }
                                    else
                                    {
                                        strings[1] = strings[0].getSubstring(start_pos, a - start_pos);

                                        message_send_id = (-1);

                                        for (b = 0; (message_send_id < 0) && (b < NUMBER_OF_MESSAGES); b++)
                                        {
                                            if (noderefs_types[noderef_send_id]->checkHierarchy(messages_object_types[b]))
                                            {
                                                if (strings[1].compareExact(messages_strings[b], true))
                                                {
                                                    message_send_id = b;
                                                }
                                            }
                                        }

                                        if (message_send_id < 0)
                                        {
                                            throw ErrorMessage
                                            (
                                                "Archive::changeNodesWithTxtFile():\n\n" \
                                                "\"send\" keyword: invalid message \"%s\"!\n\n" \
                                                "(line %d, position %d)",
                                                strings[1].getText(),
                                                line_counter,
                                                (start_pos + 1)
                                            );
                                        }

                                        /* Next state */
                                        a--;
                                        parser_state++;
                                        b = 0;
                                    }
                                }
                            }
                            else if (3 == parser_state)
                            {
                                /* message arguments, left bracket */

                                if ('(' == line_text[a])
                                {
                                    start_pos = a + 1;
                                    parser_state++;

                                }
                                else if (' ' != line_text[a])
                                {
                                    throw ErrorMessage
                                    (
                                        "Archive::changeNodesWithTxtFile():\n\n" \
                                        "\"send\" keyword: '(' expected!\n\n" \
                                        "(line %d, position %d)",
                                        line_counter,
                                        (a + 1)
                                    );
                                }
                            }
                            else if (4 == parser_state)
                            {
                                /* message arguments, right bracket */

                                if (')' == line_text[a])
                                {
                                    strings[1] = strings[0].getSubstring(start_pos, a - start_pos);

                                    b = ArFunctions::splitParams(strings[1], message_params, MESSAGES_MAX_PARAMS);

                                    if (messages_params_count[message_send_id] != b)
                                    {
                                        throw ErrorMessage
                                        (
                                            "Archive::changeNodesWithTxtFile():\n\n" \
                                            "\"send\" keyword: invalid number of params for message \"%s\"!\n" \
                                            "Expected %d, found %d.\n\n" \
                                            "(line %d, position %d)",
                                            messages_strings[message_send_id],
                                            messages_params_count[message_send_id],
                                            b,
                                            line_counter,
                                            (start_pos + 1)
                                        );
                                    }

                                    /********************************/
                                    /* Prepare before finishing sending the message */

                                    switch (message_send_id)
                                    {
                                        case PARSER_MESSAGE_ID_VISCTRLCLEAR:
                                        case PARSER_MESSAGE_ID_VISCTRLSETSTATIC:
                                        case PARSER_MESSAGE_ID_VISCTRLADDKEYFRAME:
                                        {
                                            dummy_node = (eNode*)noderefs_pointers[noderef_send_id];

                                            break;
                                        }

                                        case PARSER_MESSAGE_ID_SETPOS:
                                        case PARSER_MESSAGE_ID_SETROT:
                                        case PARSER_MESSAGE_ID_SETSCL:
                                        case PARSER_MESSAGE_ID_CTRLCLEARKEYFRAMES:
                                        case PARSER_MESSAGE_ID_CTRLSETSTATICSCALE:
                                        case PARSER_MESSAGE_ID_CTRLSETSTATICROTATION:
                                        case PARSER_MESSAGE_ID_CTRLSETSTATICPOSITION:
                                        case PARSER_MESSAGE_ID_CTRLADDKEYFRAME:
                                        {
                                            dummy_xform = (eTransform*)noderefs_pointers[noderef_send_id];

                                            break;
                                        }

                                        case PARSER_MESSAGE_ID_ANIMADDTRACK:
                                        case PARSER_MESSAGE_ID_ANIMREMOVETRACK:
                                        {
                                            dummy_pivot = (ePivot*)noderefs_pointers[noderef_send_id];

                                            break;
                                        }

                                        case PARSER_MESSAGE_ID_SETFOGCOLOR:
                                        case PARSER_MESSAGE_ID_SETFOGCSTART:
                                        case PARSER_MESSAGE_ID_SETFOGEND:
                                        case PARSER_MESSAGE_ID_SETFOGMAX:
                                        {
                                            dummy_env = (eEnvironment*)noderefs_pointers[noderef_send_id];

                                            break;
                                        }

                                        case PARSER_MESSAGE_ID_CLEARENTERACTIONS:
                                        case PARSER_MESSAGE_ID_CLEARLEAVEACTIONS:
                                        case PARSER_MESSAGE_ID_ADDENTERACTION:
                                        case PARSER_MESSAGE_ID_ADDLEAVEACTION:
                                        {
                                            dummy_zone = (eZone*)noderefs_pointers[noderef_send_id];

                                            break;
                                        }
                                    }

                                    /********************************/
                                    /* Do the right action with the given message */

                                    switch (message_send_id)
                                    {
                                        case PARSER_MESSAGE_ID_VISCTRLCLEAR:
                                        {
                                            i[0] = std::atoi(message_params[0].getText());

                                            dummy_node->visCtrlClear(i[0]);

                                            break;
                                        }

                                        case PARSER_MESSAGE_ID_VISCTRLSETSTATIC:
                                        {
                                            f[0] = (float)std::atof(message_params[0].getText());

                                            dummy_node->visCtrlSetStatic(f[0]);

                                            break;
                                        }

                                        case PARSER_MESSAGE_ID_VISCTRLADDKEYFRAME:
                                        {
                                            i[0] = std::atoi(message_params[0].getText());
                                            f[0] = (float)std::atof(message_params[1].getText());
                                            f[1] = (float)std::atof(message_params[2].getText());

                                            dummy_node->visCtrlAddKeyframe(i[0], f[0], f[1]);

                                            break;
                                        }

                                        case PARSER_MESSAGE_ID_SETPOS:
                                        {
                                            f[0] = (float)std::atof(message_params[0].getText());
                                            f[1] = (float)std::atof(message_params[1].getText());
                                            f[2] = (float)std::atof(message_params[2].getText());

                                            dummy_srp = dummy_xform->getXForm(true, false);
                                            dummy_srp.pos = ePoint3(f[0], f[1], f[2]);
                                            dummy_xform->setXForm(dummy_srp);

                                            break;
                                        }

                                        case PARSER_MESSAGE_ID_SETROT:
                                        {
                                            f[0] = (float)std::atof(message_params[0].getText()) / 180.0f * (float)M_PI;
                                            f[1] = (float)std::atof(message_params[1].getText()) / 180.0f * (float)M_PI;
                                            f[2] = (float)std::atof(message_params[2].getText()) / 180.0f * (float)M_PI;

                                            dummy_srp = dummy_xform->getXForm(true, false);
                                            dummy_srp.rot.fromEulerAngles(true, f[0], f[1], f[2]);
                                            dummy_xform->setXForm(dummy_srp);

                                            break;
                                        }

                                        case PARSER_MESSAGE_ID_SETSCL:
                                        {
                                            f[0] = (float)std::atof(message_params[0].getText());

                                            dummy_srp = dummy_xform->getXForm(true, false);
                                            dummy_srp.scale = f[0];
                                            dummy_xform->setXForm(dummy_srp);

                                            break;
                                        }

                                        case PARSER_MESSAGE_ID_CTRLCLEARKEYFRAMES:
                                        {
                                            i[0] = std::atoi(message_params[0].getText());

                                            dummy_xform->ctrlClearKeyframes(i[0]);

                                            break;
                                        }

                                        case PARSER_MESSAGE_ID_CTRLSETSTATICSCALE:
                                        {
                                            f[0] = (float)std::atof(message_params[0].getText());

                                            dummy_xform->ctrlSetStaticScale(f[0]);

                                            break;
                                        }

                                        case PARSER_MESSAGE_ID_CTRLSETSTATICROTATION:
                                        {
                                            f[0] = (float)std::atof(message_params[0].getText()) / 180.0f * (float)M_PI;
                                            f[1] = (float)std::atof(message_params[1].getText()) / 180.0f * (float)M_PI;
                                            f[2] = (float)std::atof(message_params[2].getText()) / 180.0f * (float)M_PI;

                                            dummy_srp.rot.fromEulerAngles(true, f[0], f[1], f[2]);

                                            dummy_xform->ctrlSetStaticRotation(dummy_srp.rot);

                                            break;
                                        }

                                        case PARSER_MESSAGE_ID_CTRLSETSTATICPOSITION:
                                        {
                                            f[0] = (float)std::atof(message_params[0].getText());
                                            f[1] = (float)std::atof(message_params[1].getText());
                                            f[2] = (float)std::atof(message_params[2].getText());

                                            dummy_srp.pos = ePoint3(f[0], f[1], f[2]);

                                            dummy_xform->ctrlSetStaticPosition(dummy_srp.pos);

                                            break;
                                        }

                                        case PARSER_MESSAGE_ID_CTRLADDKEYFRAME:
                                        {
                                            i[0] = std::atoi(message_params[0].getText());
                                            i[1] = std::atoi(message_params[9].getText());

                                            f[0] = (float)std::atof(message_params[2].getText());
                                            f[1] = (float)std::atof(message_params[3].getText());
                                            f[2] = (float)std::atof(message_params[4].getText());

                                            dummy_srp.pos = ePoint3(f[0], f[1], f[2]);

                                            f[0] = (float)std::atof(message_params[5].getText()) / 180.0f * (float)M_PI;
                                            f[1] = (float)std::atof(message_params[6].getText()) / 180.0f * (float)M_PI;
                                            f[2] = (float)std::atof(message_params[7].getText()) / 180.0f * (float)M_PI;

                                            dummy_srp.rot.fromEulerAngles(true, f[0], f[1], f[2]);

                                            f[0] = (float)std::atof(message_params[8].getText());

                                            dummy_srp.scale = f[0];

                                            f[0] = (float)std::atof(message_params[1].getText());

                                            dummy_xform->ctrlAddKeyframe(i[0], f[0], dummy_srp, i[1]);

                                            break;
                                        }

                                        case PARSER_MESSAGE_ID_ANIMADDTRACK:
                                        {
                                            if ((message_params[0].getLength() > 2)
                                                && message_params[0].compare("\"", 0, 1, true)
                                                && message_params[0].compare("\"", (-1), 1, true))
                                            {
                                                message_params[0] = message_params[0].getSubstring(1, (-2));
                                            }
                                            else
                                            {
                                                throw ErrorMessage
                                                (
                                                    "Archive::changeNodesWithTxtFile():\n\n" \
                                                    "`ePivot.animAddTrack()` message: expected the first parameter to be a string!\n\n" \
                                                    "(line %d, position %d)",
                                                    line_counter,
                                                    (start_pos + 1)
                                                );
                                            }

                                            f[0] = (float)std::atof(message_params[1].getText());
                                            f[1] = (float)std::atof(message_params[2].getText());

                                            dummy_pivot->animAddTrack(message_params[0], f[0], f[1]);

                                            break;
                                        }

                                        case PARSER_MESSAGE_ID_ANIMREMOVETRACK:
                                        {
                                            if ((message_params[0].getLength() > 2)
                                                && message_params[0].compare("\"", 0, 1, true)
                                                && message_params[0].compare("\"", (-1), 1, true))
                                            {
                                                message_params[0] = message_params[0].getSubstring(1, (-2));
                                            }
                                            else
                                            {
                                                throw ErrorMessage
                                                (
                                                    "Archive::changeNodesWithTxtFile():\n\n" \
                                                    "`ePivot.animRemoveTrack()` message: expected the first parameter to be a string!\n\n" \
                                                    "(line %d, position %d)",
                                                    line_counter,
                                                    (start_pos + 1)
                                                );
                                            }

                                            dummy_pivot->animRemoveTrack(message_params[0]);

                                            break;
                                        }

                                        case PARSER_MESSAGE_ID_SETFOGCOLOR:
                                        {
                                            f[0] = (float)std::atof(message_params[0].getText());
                                            f[1] = (float)std::atof(message_params[1].getText());
                                            f[2] = (float)std::atof(message_params[2].getText());

                                            dummy_env->setFogColor(f);

                                            break;
                                        }

                                        case PARSER_MESSAGE_ID_SETFOGCSTART:
                                        {
                                            f[0] = (float)std::atof(message_params[0].getText());

                                            dummy_env->setFogStart(f[0]);

                                            break;
                                        }

                                        case PARSER_MESSAGE_ID_SETFOGEND:
                                        {
                                            f[0] = (float)std::atof(message_params[0].getText());

                                            dummy_env->setFogEnd(f[0]);

                                            break;
                                        }

                                        case PARSER_MESSAGE_ID_SETFOGMAX:
                                        {
                                            f[0] = (float)std::atof(message_params[0].getText());

                                            dummy_env->setFogMax(f[0]);

                                            break;
                                        }

                                        case PARSER_MESSAGE_ID_CLEARENTERACTIONS:
                                        case PARSER_MESSAGE_ID_CLEARLEAVEACTIONS:
                                        {
                                            dummy_zone->zoneClearActions
                                            (
                                                PARSER_MESSAGE_ID_CLEARENTERACTIONS == message_send_id
                                            );

                                            break;
                                        }

                                        case PARSER_MESSAGE_ID_ADDENTERACTION:
                                        case PARSER_MESSAGE_ID_ADDLEAVEACTION:
                                        {
                                            dummy_zone_action = eActionBase();

                                            if ((message_params[0].getLength() > 2)
                                                && message_params[0].compare("\"", 0, 1, true)
                                                && message_params[0].compare("\"", (-1), 1, true))
                                            {
                                                dummy_zone_action.actorName = message_params[0].getSubstring(1, (-2));
                                            }
                                            else
                                            {
                                                c = (-1);

                                                for (b = 0; (c < 0) && (b < noderefs_count); b++)
                                                {
                                                    if (message_params[0].compareExact(noderefs_names[b], true))
                                                    {
                                                        c = b;
                                                    }
                                                }

                                                if (c < 0)
                                                {
                                                    throw ErrorMessage
                                                    (
                                                        "Archive::changeNodesWithTxtFile():\n\n" \
                                                        "`eZone.add*Action()` message: nodeRef \"%s\" not found!\n\n" \
                                                        "(line %d, position %d)",
                                                        message_params[0].getText(),
                                                        line_counter,
                                                        (start_pos + 1)
                                                    );
                                                }

                                                dummy_zone_action.nodeTarget = noderefs_pointers[c];
                                                dummy_zone_action.nodeTarget->incRef();
                                            }

                                            if ((message_params[1].getLength() > 2)
                                                && message_params[1].compare("\"", 0, 1, true)
                                                && message_params[1].compare("\"", (-1), 1, true))
                                            {
                                                dummy_zone_action.message = message_params[1].getSubstring(1, (-2));
                                            }
                                            else
                                            {
                                                /* Reset `eActionBase` before leaving! */
                                                dummy_zone_action = eActionBase();

                                                throw ErrorMessage
                                                (
                                                    "Archive::changeNodesWithTxtFile():\n\n" \
                                                    "`eZone.add*Action()` message: expected the second parameter to be a string!\n\n" \
                                                    "(line %d, position %d)",
                                                    line_counter,
                                                    (start_pos + 1)
                                                );
                                            }

                                            dummy_zone->zoneAddAction
                                            (
                                                PARSER_MESSAGE_ID_ADDENTERACTION == message_send_id,
                                                dummy_zone_action
                                            );

                                            /* Reset `eActionBase` before leaving! */
                                            dummy_zone_action = eActionBase();

                                            break;
                                        }

                                        default:
                                        {
                                            throw ErrorMessage
                                            (
                                                "Archive::changeNodesWithTxtFile():\n\n" \
                                                "message \"%d\" not implemented!\n\n" \
                                                "(line %d, position %d)",
                                                messages_strings[message_send_id],
                                                line_counter,
                                                (start_pos + 1)
                                            );
                                        }
                                    }

                                    /* Parsing complete! */

                                    result++;

                                    start_pos = (-1);
                                    end_pos = (-1);
                                    current_keyword = (-1);
                                    keyword_parsed = true;
                                    parser_state = 0;
                                }
                            }
                        }
                    }

                    a++;
                }

                /* Check if a keywords was parsed succesfully */

                if ((current_keyword >= 0) && (!keyword_parsed))
                {
                    throw ErrorMessage
                    (
                        "Archive::changeNodesWithTxtFile():\n\n" \
                        "could not parse the \"%s\" keyword!\n\n" \
                        "(line %d)",
                        keyword_names[current_keyword],
                        line_counter
                    );
                }
            }
        }

        return result;
    }

}
