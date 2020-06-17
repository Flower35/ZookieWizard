#include <kao2ar/Archive.h>

#include <kao2engine/eTransform.h>
#include <kao2engine/eBillboard.h>
#include <kao2engine/eNaviPoint.h>
#include <kao2engine/eProxy.h>
#include <kao2engine/eCamera.h>
#include <kao2engine/eDirectionalLight.h>
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
        eGroup* dummy_group;
        eEnvironment* dummy_env;
        eSRP dummy_srp;
        int32_t dummy_count;

        /********************************/
        /* Prepare some definitions */

        const int NUMBER_OF_CLASSES = 7;

        int current_object = (-1);

        eTransform* dummy_xform = nullptr;
        eBillboard* dummy_billboard = nullptr;
        eNaviPoint* dummy_navi = nullptr;
        eProxy* dummy_proxy = nullptr;
        eCamera* dummy_camera = nullptr;
        eDirectionalLight* dummy_light = nullptr;
        eNPCMap* dummy_npcmap = nullptr;

        const char* class_names[NUMBER_OF_CLASSES] =
        {
            "<eTransform>",
            "<eBillboard>",
            "<eNaviPoint>",
            "<eProxy>",
            "<eCamera>",
            "<eDirectionalLight>",
            "<eNPCMap>"
        };

        const int PARSER_OBJECT_ID_TRANSFORM = 0;
        const int PARSER_OBJECT_ID_BILLBOARD = 1;
        const int PARSER_OBJECT_ID_NAVIPOINT = 2;
        const int PARSER_OBJECT_ID_PROXY = 3;
        const int PARSER_OBJECT_ID_CAMERA = 4;
        const int PARSER_OBJECT_ID_LIGHT = 5;
        const int PARSER_OBJECT_ID_NPCMAP = 6;

        eNode** class_pointers[NUMBER_OF_CLASSES] =
        {
            (eNode**)&dummy_xform,
            (eNode**)&dummy_billboard,
            (eNode**)&dummy_navi,
            (eNode**)&dummy_proxy,
            (eNode**)&dummy_camera,
            (eNode**)&dummy_light,
            (eNode**)&dummy_npcmap
        };

        const int NUMBER_OF_PROPERTIES = 15;

        const char* properties[NUMBER_OF_PROPERTIES] =
        {
            "name", "pos", "rot", "scl",
            "link", "category",
            "fov", "nearPlane", "farPlane",
            "diffuse", "ambient", "specular",
            "min", "max", "count"
        };

        const int PARSER_PROPERTY_ID_NAME = 0;
        const int PARSER_PROPERTY_ID_POS = 1;
        const int PARSER_PROPERTY_ID_ROT = 2;
        const int PARSER_PROPERTY_ID_SCL = 3;
        const int PARSER_PROPERTY_ID_LINK = 4;
        const int PARSER_PROPERTY_ID_CATEGORY = 5;
        const int PARSER_PROPERTY_ID_FOV = 6;
        const int PARSER_PROPERTY_ID_NEARPLANE = 7;
        const int PARSER_PROPERTY_ID_FARPLANE = 8;
        const int PARSER_PROPERTY_ID_DIFFUSE = 9;
        const int PARSER_PROPERTY_ID_AMBIENT = 10;
        const int PARSER_PROPERTY_ID_SPECULAR = 11;
        const int PARSER_PROPERTY_ID_MIN = 12;
        const int PARSER_PROPERTY_ID_MAX = 13;
        const int PARSER_PROPERTY_ID_COUNT = 14;

        const int properties_args[NUMBER_OF_PROPERTIES] =
        {
            1, 3, 3, 1,
            1, 1,
            1, 1, 1,
            3, 3, 3,
            3, 3, 1
        };

        const bool properties_of_classes[NUMBER_OF_CLASSES][NUMBER_OF_PROPERTIES] =
        {
            {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // eTransform
            {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // eBillbord
            {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // eNaviPoint
            {1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // eProxy
            {1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0}, // eCamera
            {1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0}, // eDirectionalLight
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1}  // eNPCMap
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
                    "Archive::appendProxiesFromTxtFile():\n" \
                    "Selected object is not a \"eGroup\" type!"
                );
            }

            dummy_group = (eGroup*)selectedObject;

            if (!text_file.open(filename, FILE_OPERATOR_MODE_READ))
            {
                throw ErrorMessage
                (
                    "Archive::appendProxiesFromTxtFile():\n" \
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

                    if (ArFunctions::splitString(keywords[0], &(keywords[1]), 2) >= 1)
                    {
                        /* NOT an empty line or line with a comment */
                        /* Minimal lenght of 3: "?=?" or "<?>" */

                        if (line_is_valid = (keywords[1].getLength() >= 3) && ('#' != keywords[1].getText()[0]))
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
                                        "Archive::appendProxiesFromTxtFile():\n" \
                                        "Unrecognized class identifier \"%s\"!\n" \
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
                                break;
                            }

                            case PARSER_OBJECT_ID_LIGHT:
                            {
                                dummy_light->setPosition(dummy_srp.pos);

                                dummy_env = (eEnvironment*)dummy_group;

                                while ((nullptr != dummy_env) && (dummy_env->getType() != &E_ENVIRONMENT_TYPEINFO))
                                {
                                    dummy_env = (eEnvironment*)dummy_env->getParentNode();
                                }

                                if (nullptr != dummy_env)
                                {
                                    dummy_env->addLighting(dummy_light);
                                }

                                break;
                            }

                            case PARSER_OBJECT_ID_NPCMAP:
                            {
                                dummy_npcmap->customSetup(box_points[0], box_points[1], dummy_count);

                                break;
                            }
                        }

                        dummy_group->appendChild(*(class_pointers[current_object]));

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

                    found_any_property = false;

                    for (a = 0; a < NUMBER_OF_PROPERTIES; a++)
                    {
                        property_duplicate[a] = false;
                    }

                    dummy_srp = eSRP();
                    box_points[0] = {0, 0, 0};
                    box_points[1] = {0, 0, 0};
                    dummy_count = 0;

                    /* Instancize */

                    switch (parser_state)
                    {
                        case PARSER_OBJECT_ID_TRANSFORM:
                        {
                            dummy_xform = new eTransform();
                            break;
                        }

                        case PARSER_OBJECT_ID_BILLBOARD:
                        {
                            dummy_billboard = new eBillboard();
                            break;
                        }

                        case PARSER_OBJECT_ID_NAVIPOINT:
                        {
                            dummy_navi = new eNaviPoint();
                            break;
                        }

                        case PARSER_OBJECT_ID_PROXY:
                        {
                            dummy_proxy = new eProxy();
                            break;
                        }

                        case PARSER_OBJECT_ID_CAMERA:
                        {
                            dummy_camera = new eCamera();
                            break;
                        }

                        case PARSER_OBJECT_ID_LIGHT:
                        {
                            dummy_light = new eDirectionalLight();
                            break;
                        }

                        case PARSER_OBJECT_ID_NPCMAP:
                        {
                            dummy_npcmap = new eNPCMap();
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

                        (*(class_pointers[current_object]))->setFlags(0x70000009);
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
                                        "Archive::appendNodesFromTxtFile():\n" \
                                        "Duplicate property \"%s\"!\n" \
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
                                        "Archive::appendNodesFromTxtFile():\n" \
                                        "Not enough arguments for property \"%s\"!\n" \
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
                            "Archive::appendProxiesFromTxtFile():\n" \
                            "Unrecognized property \"%s\" for class %s!\n" \
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
                            dummy_proxy->setTargetName(keywords[2]);

                            break;
                        }

                        case PARSER_PROPERTY_ID_CATEGORY:
                        {
                            parser_state = 0;

                            for (a = 0; (!parser_state) && (a < PROXY_CATEGORIES_COUNT); a++)
                            {
                                if (keywords[2].compare(proxy_category_names[a], 0, (-1), false))
                                {
                                    dummy_proxy->setCategory(a);

                                    parser_state = 1;
                                }
                            }

                            if (!parser_state)
                            {
                                throw ErrorMessage
                                (
                                    "Archive::appendProxiesFromTxtFile():\n" \
                                    "Unrecognized <eProxy> category \"%s\"!\n" \
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

}
