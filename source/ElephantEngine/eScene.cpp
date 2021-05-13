#include <ElephantEngine/eScene.h>
#include <ElephantBase/Archive.h>

#include <utilities/ColladaExporter.h>
#include <ZookieWizard/WindowsManager.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eScene interface
    // <kao2.004984D0> (constructor)
    // <kao2.00498860> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_SCENE_TYPEINFO
    (
        E_SCENE_ID,
        "eScene",
        &E_PIVOT_TYPEINFO,
        []() -> eObject*
        {
            return new eScene;
        }
    );

    const TypeInfo* eScene::getType() const
    {
        return &E_SCENE_TYPEINFO;
    }

    eScene::eScene()
    : ePivot()
    {
        /*[0x0170]*/ color[0] = 0.5f;
        /*[0x0174]*/ color[1] = 0.5f;
        /*[0x0178]*/ color[2] = 0.5f;

        /*[0x017C]*/ ambient[0] = 0;
        /*[0x0180]*/ ambient[1] = 0;
        /*[0x0184]*/ ambient[2] = 0;
        /*[0x0188]*/ ambient[3] = 1.0f;

        /*(kao3)[0x02A8]*/ visGroups_unknown = 0x00;

        /*(kao3)[0x02AC]*/ visSetA_count = 0;
        /*(kao3)[0x02B0]*/ visSetA_maxLength = 0;
        /*(kao3)[0x02B4]*/ visSetA = nullptr;

        /*(kao3)[0x02B8]*/ visSetB_count = 0;
        /*(kao3)[0x02BC]*/ visSetB_maxLength = 0;
        /*(kao3)[0x02C0]*/ visSetB = nullptr;

        ArFunctions::setCurrentScene(this);

        /*[0x14]*/ name = "Scene Root";
    }

    eScene::~eScene()
    {
        function_00498B20();

        if (this == ArFunctions::getCurrentScene())
        {
            ArFunctions::setCurrentScene(nullptr);
        }

        if (nullptr != visSetA)
        {
            delete[](visSetA);
        }

        if (nullptr != visSetB)
        {
            delete[](visSetB);
        }
    }


    ////////////////////////////////////////////////////////////////
    // eScene: cloning the object
    ////////////////////////////////////////////////////////////////

    void eScene::createFromOtherObject(const eScene &other)
    {
        throw ErrorMessage
        (
            "CRITICAL ERROR while cloning the \"eScene\" object:\n" \
            "cloning << scenes >> without context is not supported!!!"
        );
    }

    eScene::eScene(const eScene &other)
    : ePivot(other)
    {
        visSetA_count = 0;
        visSetA_maxLength = 0;
        visSetA = nullptr;

        visSetB_count = 0;
        visSetB_maxLength = 0;
        visSetB = nullptr;

        /****************/

        createFromOtherObject(other);
    }

    eScene& eScene::operator = (const eScene &other)
    {
        if ((&other) != this)
        {
            ePivot::operator = (other);

            /****************/

            if (nullptr != visSetB)
            {
                delete[](visSetB);
                visSetB = nullptr;
            }

            visSetB_count = 0;
            visSetB_maxLength = 0;

            if (nullptr != visSetA)
            {
                delete[](visSetA);
                visSetA = nullptr;
            }

            visSetA_count = 0;
            visSetA_maxLength = 0;

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eScene::cloneFromMe() const
    {
        /* Disable cloning (memory-leak friendly) */
        return nullptr;
    }


    ////////////////////////////////////////////////////////////////
    // eScene portal structures
    // <kao_tw.004BF0E0> (first struct, constructor)
    // <kao_tw.004BF500> (first struct, serialization)
    // <kao_tw.00486C79> (second struct, constructor)
    // <kao_tw.004BFA80> (second struct, serialization)
    ////////////////////////////////////////////////////////////////

    void ScenePortalBaseA::serialize(Archive &ar)
    {
        ar.readOrWrite(&unknown_00, 0x01);
        ar.readOrWrite(&unknown_01, 0x01);
        ar.readOrWrite(&unknown_02, 0x01);

        unknown_04.serialize(ar);
        unknown_10.serialize(ar);

        if (0x02 & unknown_02)
        {
            unknown_1C.serialize(ar);
        }

        ar.serializeString(unknown_28);
    }

    ScenePortalBaseB::ScenePortalBaseB()
    {
        /*[0x00]*/ unknown_00 = 0;

        /*[0x08]*/ groupA_count = 0;
        /*[0x0C]*/ groupA_maxLength = 0;
        /*[0x10]*/ groupA = nullptr;

        /*[0x14]*/ groupB_count = 0;
        /*[0x18]*/ groupB_maxLength = 0;
        /*[0x1C]*/ groupB = nullptr;
    }

    ScenePortalBaseB::~ScenePortalBaseB()
    {
        if (nullptr != groupA)
        {
            delete[](groupA);
        }

        if (nullptr != groupB)
        {
            delete[](groupB);
        }
    }

    void ScenePortalBaseB::serialize(Archive &ar)
    {
        int32_t i;

        /* [0x04] portal name */
        ar.serializeString(name);

        /* [0x08] group (4 floats) */

        if (ar.isInReadMode())
        {
            if (nullptr != groupA)
            {
                delete[](groupA);
                groupA = nullptr;

                groupA_maxLength = 0;
                groupA_count = 0;
            }

            ar.readOrWrite(&groupA_maxLength, 0x04);

            groupA = new ePoint4 [groupA_maxLength];

            for (i = 0; i < groupA_maxLength; i++)
            {
                groupA[i].serialize(ar);

                groupA_count = (i+1);
            }
        }
        else
        {
            ar.readOrWrite(&groupA_count, 0x04);

            for (i = 0; i < groupA_count; i++)
            {
                groupA[i].serialize(ar);
            }
        }

        /* [0x14] group (bytes) */

        if (ar.isInReadMode())
        {
            if (nullptr != groupB)
            {
                delete[](groupB);
                groupB = nullptr;

                groupB_maxLength = 0;
                groupB_count = 0;
            }

            ar.readOrWrite(&groupB_maxLength, 0x04);

            groupB = new uint8_t [groupB_maxLength];

            ar.readOrWrite(groupB, groupB_maxLength);

            groupB_count = groupB_maxLength;
        }
        else
        {
            ar.readOrWrite(&groupB_count, 0x04);

            ar.readOrWrite(groupB, groupB_count);
        }

        /* [0x00] unknown */

        if (ar.getVersion() >= 0x8E)
        {
            ar.readOrWrite(&unknown_00, 0x04);
        }
    }


    ////////////////////////////////////////////////////////////////
    // eScene: serialization
    // <kao2.00498FB0>
    ////////////////////////////////////////////////////////////////
    void eScene::serialize(Archive &ar)
    {
        int32_t i;

        /* "ar_compile" string, level name */
        ar.serializeString(compileStrB);

        /* "ar_compile" string, ".COMPILED." */
        ar.serializeString(compileStrA);

        if (ar.isInReadMode())
        {
            function_00498B20();
        }

        collision.lockDuringSerialize(true);

        /* Collision Manager */
        collision.serialize(ar);

        /* Pivot (animation tracks, transformation and children nodes) */
        ePivot::serialize(ar);

        if (ar.isInReadMode())
        {
            collision.prepare_ALBox_links();

            //// (--TODO--) call eScene::[[vptr]+0x44], two times.
        }

        collision.lockDuringSerialize(false);

        /* [0x0170] Scene background colors */
        ar.readOrWrite(&(color[0]), 0x04);
        ar.readOrWrite(&(color[1]), 0x04);
        ar.readOrWrite(&(color[2]), 0x04);

        /* Unknown group */
        unknown0194.serialize(ar, &E_PIVOT_TYPEINFO);

        /* [0x017C] Ambient intensity */
        if (ar.getVersion() < 0x73)
        {
            ambient[0] = 0;
            ambient[1] = 0;
            ambient[2] = 0;
            ambient[3] = 1.0f;
        }
        else
        {
            ar.readOrWrite(&(ambient[0]), 0x04);
            ar.readOrWrite(&(ambient[1]), 0x04);
            ar.readOrWrite(&(ambient[2]), 0x04);
            ar.readOrWrite(&(ambient[3]), 0x04);
        }

        if (ar.getVersion() >= 0x8C)
        {
            ar.readOrWrite(&visGroups_unknown, 0x01);

            visGroups.serialize(ar, &E_NODE_TYPEINFO);

            i = visGroups.getSize();

            if (i > 512)
            {
                throw ErrorMessage
                (
                    "eScene::serialize():\n" \
                    "Too many visibility nodes/groups - %i. (max 512).",
                    i
                );
            }
        }

        if (ar.getVersion() >= 0x8D)
        {
            /* Portals 1*/

            if (ar.isInReadMode())
            {
                if (nullptr != visSetA)
                {
                    delete[](visSetA);
                    visSetA = nullptr;

                    visSetA_maxLength = 0;
                    visSetA_count = 0;
                }

                ar.readOrWrite(&visSetA_maxLength, 0x04);

                if (visSetA_maxLength > 0)
                {
                    visSetA = new ScenePortalBaseA [visSetA_maxLength];

                    for (i = 0; i < visSetA_maxLength; i++)
                    {
                        visSetA[i].serialize(ar);

                        visSetA_count = (i+1);
                    }
                }
            }
            else
            {
                ar.readOrWrite(&visSetA_count, 0x04);

                for (i = 0; i < visSetA_count; i++)
                {
                    visSetA[i].serialize(ar);
                }
            }

            /* Portals 2 */

            if (ar.isInReadMode())
            {
                if (nullptr != visSetB)
                {
                    delete[](visSetB);
                    visSetB = nullptr;

                    visSetB_maxLength = 0;
                    visSetB_count = 0;
                }

                ar.readOrWrite(&visSetB_maxLength, 0x04);

                if (visSetB_maxLength > 0)
                {
                    visSetB = new ScenePortalBaseB [visSetB_maxLength];

                    for (i = 0; i < visSetB_maxLength; i++)
                    {
                        visSetB[i].serialize(ar);

                        visSetB_count = (i+1);
                    }
                }
            }
            else
            {
                ar.readOrWrite(&visSetB_count, 0x04);

                for (i = 0; i < visSetB_count; i++)
                {
                    visSetB[i].serialize(ar);
                }
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eScene: COLLADA exporting
    ////////////////////////////////////////////////////////////////
    void eScene::writeNodeToXmlFile(ColladaExporter &exporter) const
    {
        int32_t i;
        char bufor[16];
        eNode* test_node;

        switch (exporter.getState())
        {
            case COLLADA_EXPORTER_STATE_LIGHTS:
            case COLLADA_EXPORTER_STATE_CAMERAS:
            case COLLADA_EXPORTER_STATE_EFFECTS:
            case COLLADA_EXPORTER_STATE_IMAGES:
            case COLLADA_EXPORTER_STATE_MATERIALS:
            case COLLADA_EXPORTER_STATE_GEOMETRIES:
            case COLLADA_EXPORTER_STATE_CONTROLLERS:
            case COLLADA_EXPORTER_STATE_ANIMATIONS:
            {
                eGroup::writeNodeToXmlFile(exporter);

                break;
            }

            case COLLADA_EXPORTER_STATE_VISUAL_SCENES:
            {
                exporter.openTag("visual_scene");

                i = exporter.getObjectRefId(COLLADA_EXPORTER_OBJ_SCENE, this, true);
                sprintf_s(bufor, 16, "Scene%d", i);
                exporter.insertTagAttrib("id", bufor);
                exporter.insertTagAttrib("name", name);

                /* "eGroup" could exist as independent node (without parent "eTransform") */
                /* That's why we are not calling `eGroup::writeNodeToXmlFile()` */

                for (i = 0; i < nodes.getSize(); i++)
                {
                    if (nullptr != (test_node = (eNode*)nodes.getIthChild(i)))
                    {
                        test_node->writeNodeToXmlFile(exporter);
                    }
                }

                exporter.closeTag(); // "visual_scene"

                break;
            }

            case COLLADA_EXPORTER_STATE_SCENE:
            {
                i = exporter.getObjectRefId(COLLADA_EXPORTER_OBJ_SCENE, this, false);
                sprintf_s(bufor, 16, "#Scene%d", i);

                exporter.openTag("instance_visual_scene");
                exporter.insertTagAttrib("url", bufor);
                exporter.closeTag();

                break;
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eScene: find reference to some node when deleting it
    ////////////////////////////////////////////////////////////////
    void eScene::findAndDereference(eNode* target)
    {
        unknown0194.findAndDeleteChild((eRefCounter*)target);

        eGroup::findAndDereference(target);
    }


    ////////////////////////////////////////////////////////////////
    // eScene: preparing just-created node
    ////////////////////////////////////////////////////////////////
    void eScene::editingNewNodeSetup()
    {
        GUI::theWindowsManager.displayMessage
        (
            WINDOWS_MANAGER_MESSAGE_ERROR,
            "\"eScene\" object that is not a root of the Archive will cause the game to crash!\n" \
            "Dereferencing node..."
        );

        decRef();
    }


    ////////////////////////////////////////////////////////////////
    // eScene: custom TXT parser
    ////////////////////////////////////////////////////////////////
    int32_t eScene::parsingCustomMessage(char* result_msg, const eString &message, int32_t params_count, const TxtParsingNodeProp* params)
    {
        int32_t test;
        float dummy_floats[3];

        if (1 != (test = ePivot::parsingCustomMessage(result_msg, message, params_count, params)))
        {
            return test;
        }

        if (message.compareExact("setBackgroundColor", true))
        {
            if (1 != params_count)
            {
                TxtParsingNode_ErrorArgCount(result_msg, "setBackgroundColor", 1);
                return 2;
            }

            /********************************/

            if (!params[0].checkType(TXT_PARSING_NODE_PROPTYPE_FLOAT3))
            {
                TxtParsingNode_ErrorArgType(result_msg, "setBackgroundColor", 0, TXT_PARSING_NODE_PROPTYPE_FLOAT3);
            }

            params[0].getValue(dummy_floats);

            /********************************/

            setBackgroundColor(dummy_floats);
            return 0;
        }
        else if (message.compareExact("setAmbientColor", true))
        {
            if (1 != params_count)
            {
                TxtParsingNode_ErrorArgCount(result_msg, "setAmbientColor", 1);
                return 2;
            }

            /********************************/

            if (!params[0].checkType(TXT_PARSING_NODE_PROPTYPE_FLOAT3))
            {
                TxtParsingNode_ErrorArgType(result_msg, "setAmbientColor", 0, TXT_PARSING_NODE_PROPTYPE_FLOAT3);
            }

            params[0].getValue(dummy_floats);

            /********************************/

            setAmbientColor(dummy_floats);
            return 0;
        }
        else if (message.compareExact("setCompileStrings", true))
        {
            if (2 != params_count)
            {
                TxtParsingNode_ErrorArgCount(result_msg, "setCompileStrings", 2);
                return 2;
            }

            /********************************/

            if (!params[0].checkType(TXT_PARSING_NODE_PROPTYPE_STRING))
            {
                TxtParsingNode_ErrorArgType(result_msg, "setCompileStrings", 1, TXT_PARSING_NODE_PROPTYPE_STRING);
            }

            params[0].getValue(&compileStrA);

            /********************************/

            if (!params[1].checkType(TXT_PARSING_NODE_PROPTYPE_STRING))
            {
                TxtParsingNode_ErrorArgType(result_msg, "setCompileStrings", 2, TXT_PARSING_NODE_PROPTYPE_STRING);
            }

            params[1].getValue(&compileStrB);

            /********************************/

            return 0;
        }
        else if (message.compareExact("clearVisPortals", true))
        {
            if (0 != params_count)
            {
                TxtParsingNode_ErrorArgCount(result_msg, "clearVisPortals", 0);
                return 2;
            }

            /********************************/

            visGroups.clear();
            visGroups_unknown = 0x00;

            if (nullptr != visSetA)
            {
                delete[](visSetA);
                visSetA = nullptr;
            }

            visSetA_maxLength = 0;
            visSetA_count = 0;

            if (nullptr != visSetB)
            {
                delete[](visSetB);
                visSetB = nullptr;
            }

            visSetB_maxLength = 0;
            visSetB_count = 0;
        }

        return 1;
    }


    ////////////////////////////////////////////////////////////////
    // eScene: set background color
    ////////////////////////////////////////////////////////////////
    void eScene::setBackgroundColor(GLfloat new_color[3])
    {
        color[0] = new_color[0];
        color[1] = new_color[1];
        color[2] = new_color[2];
    }


    ////////////////////////////////////////////////////////////////
    // eScene: set ambient color
    ////////////////////////////////////////////////////////////////
    void eScene::setAmbientColor(GLfloat new_color[3])
    {
        ambient[0] = new_color[0];
        ambient[1] = new_color[1];
        ambient[2] = new_color[2];
        ambient[3] = 1.0f;
    }


    ////////////////////////////////////////////////////////////////
    // eScene: set compile strings (while creating new level)
    ////////////////////////////////////////////////////////////////
    void eScene::setCompileStrings(eString &str_a, eString &str_b)
    {
        compileStrA = str_a;
        compileStrB = str_b;
    }


    ////////////////////////////////////////////////////////////////
    // eScene: get collision manager
    ////////////////////////////////////////////////////////////////
    eCollisionMgr* eScene::getCollisionManager() const
    {
        return (eCollisionMgr*)&collision;
    }


    ////////////////////////////////////////////////////////////////
    // eScene: unknown function
    // <kao2.00498B20>
    ////////////////////////////////////////////////////////////////
    void eScene::function_00498B20()
    {
        int32_t i;

        for (i = 0; i < nodes.getSize(); i++)
        {
            //// (--TODO--) eScene::[[vptr]+0x74](arg1 = nodes.getChild[i]);
        }

        collision.resetCounters();
    }


    ////////////////////////////////////////////////////////////////
    // Global Scene pointer
    ////////////////////////////////////////////////////////////////

    eScene* theScene;

    void ArFunctions::setCurrentScene(eScene* scene)
    {
        theScene = scene;
    }

    eScene* ArFunctions::getCurrentScene()
    {
        return theScene;
    }

}
