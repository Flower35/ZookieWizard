#include <kao2engine/eProxy.h>
#include <kao2ar/Archive.h>
#include <kao2ar/eDrawContext.h>

#include <kao2engine/eXRefProxy.h>
#include <kao2engine/eXRefTarget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eProxy interface
    // <kao2.004844A0> (constructor)
    // <kao2.00484590> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_PROXY_TYPEINFO
    (
        E_PROXY_ID,
        "eProxy",
        &E_TRANSFORM_TYPEINFO,
        []() -> eObject*
        {
            return new eProxy;
        }
    );

    TypeInfo* eProxy::getType() const
    {
        return &E_PROXY_TYPEINFO;
    }

    eProxy::eProxy()
    : eTransform()
    {
        category = 0;

        externalContentLink = nullptr;
    }

    eProxy::~eProxy()
    {
        externalContentLink = nullptr;
    }


    ////////////////////////////////////////////////////////////////
    // eProxy serialization
    // <kao2.004846C0>
    ////////////////////////////////////////////////////////////////
    void eProxy::serialize(Archive &ar)
    {
        int32_t a, b;
        eNode* test_node;

        if ((nullptr != externalContentLink) && (false == ar.isInReadMode()))
        {
            /* Serialize the "eNode" part, skip a specific element in the "eGroup" */
            /* that has the "eXRefProxy" type, and then serialize the "eTransform" part. */

            eNode::serialize(ar);

            /****************/

            b = nodes.getSize();

            for (a = 0; a < b; a++)
            {
                if (nodes.getIthChild(a) == externalContentLink)
                {
                    b--;
                }
            }

            ar.readOrWrite(&b, 0x04);

            /****************/

            b = nodes.getSize();

            for (a = 0; a < b; a++)
            {
                test_node = (eNode*)nodes.getIthChild(a);

                if (test_node != externalContentLink)
                {
                    ar.serialize((eObject**)&test_node, &E_NODE_TYPEINFO);
                }
            }

            /****************/

            if (ar.isInWriteMode())
            {
                deserializationCorrection();
            }

            defaultTransform.serialize(ar);
            worldTransform.serialize(ar);

            ar.serialize((eObject**)&ctrl, &E_CTRL_ESRP_TYPEINFO);
        }
        else
        {
            /* No external content - regular parent class serialization */

            eTransform::serialize(ar);
        }

        ar.serializeString(targetFile);

        ar.readOrWrite(&category, 0x04);

        /********************************/
        /* Loading external models... */

        if (ar.isInReadMode())
        {
            reloadXRef(ar.getMediaDir(), ar.getCurrentEngineVersion());
        }

        /********************************/
        /* Saving external models... */

        if (ar.isInExportProxiesMode())
        {
            exportXRef(ar.getMediaDir(), ar.getCurrentEngineVersion());
        }
    }


    ////////////////////////////////////////////////////////////////
    // eProxy: destroy before dereferencing
    ////////////////////////////////////////////////////////////////
    void eProxy::destroyNode()
    {
        int32_t a, b = nodes.getSize();
        eXRefTarget* test_xref_taget;
        eNode* nested_scene;

        for (a = 0; a < b; a++)
        {
            if (nodes.getIthChild(a) == externalContentLink)
            {
                test_xref_taget = externalContentLink->getXRefTarget();

                if (nullptr != test_xref_taget)
                {
                    nested_scene = (eNode*)test_xref_taget->getLocalScene();

                    if (nullptr != nested_scene)
                    {
                        nested_scene->destroyNode();
                    }
                }

                a = b;
            }
        }

        eTransform::destroyNode();
    }


    ////////////////////////////////////////////////////////////////
    // eProxy: find reference to some node when deleting it
    ////////////////////////////////////////////////////////////////
    void eProxy::findAndDereference(eNode* target)
    {
        if (target == externalContentLink)
        {
            externalContentLink = nullptr;
        }

        eGroup::findAndDereference(target);
    }


    ////////////////////////////////////////////////////////////////
    // eProxy: preparing just-created node
    ////////////////////////////////////////////////////////////////
    void eProxy::editingNewNodeSetup()
    {
        eTransform::editingNewNodeSetup();

        reloadXRef(getEditorString(1, false), currentGameVersion);
    }


    ////////////////////////////////////////////////////////////////
    // eProxy: custom TXT parser methods
    ////////////////////////////////////////////////////////////////

    int32_t eProxy::parsingSetProperty(char* result_msg, const TxtParsingNodeProp &property)
    {
        int32_t test;
        eString prop_name, dummy_str;

        if (1 != (test = eTransform::parsingSetProperty(result_msg, property)))
        {
            return test;
        }

        prop_name = property.getName();

        if (prop_name.compareExact("link", true))
        {
            if (!property.checkType(TXT_PARSING_NODE_PROPTYPE_STRING))
            {
                TxtParsingNode_ErrorPropType(result_msg, "link", TXT_PARSING_NODE_PROPTYPE_STRING);
                return 2;
            }

            property.getValue(&targetFile);
            return 0;
        }
        else if (prop_name.compareExact("category", true))
        {
            if (!property.checkType(TXT_PARSING_NODE_PROPTYPE_STRING))
            {
                TxtParsingNode_ErrorPropType(result_msg, "category", TXT_PARSING_NODE_PROPTYPE_STRING);
                return 2;
            }

            property.getValue(&dummy_str);

            if (dummy_str.compareExact("particle", true))
            {
                category = 0;
            }
            else if (dummy_str.compareExact("hero", true))
            {
                category = 1;
            }
            else if (dummy_str.compareExact("powerup", true))
            {
                category = 2;
            }
            else if (dummy_str.compareExact("enemy", true))
            {
                category = 3;
            }
            else if (dummy_str.compareExact("fluff", true))
            {
                category = 4;
            }
            else if (dummy_str.compareExact("geoproxy", true))
            {
                category = 5;
            }
            else if (dummy_str.compareExact("object", true))
            {
                category = 6;
            }
            else
            {
                sprintf_s(result_msg, LARGE_BUFFER_SIZE, "Unknown proxy category for \"category\" property!");
                return 2;
            }

            return 0;
        }

        return 1;
    }

    int32_t eProxy::parsingCustomMessage(char* result_msg, const eString &message, int32_t params_count, const TxtParsingNodeProp* params)
    {
        int32_t test;
        eString dummy_str;

        if (1 != (test = eTransform::parsingCustomMessage(result_msg, message, params_count, params)))
        {
            return test;
        }

        if (message.compareExact("setLinkAndCategory", true))
        {
            if (2 != params_count)
            {
                TxtParsingNode_ErrorArgCount(result_msg, "setLinkAndCategory", 2);
                return 2;
            }

            /********************************/

            if (!params[0].checkType(TXT_PARSING_NODE_PROPTYPE_STRING))
            {
                TxtParsingNode_ErrorArgType(result_msg, "setLinkAndCategory", 1, TXT_PARSING_NODE_PROPTYPE_STRING);
                return 2;
            }

            params[0].getValue(&targetFile);

            /********************************/

            if (!params[1].checkType(TXT_PARSING_NODE_PROPTYPE_STRING))
            {
                TxtParsingNode_ErrorArgType(result_msg, "setLinkAndCategory", 2, TXT_PARSING_NODE_PROPTYPE_STRING);
                return 2;
            }

            params[1].getValue(&dummy_str);

            if (dummy_str.compareExact("particle", true))
            {
                category = 0;
            }
            else if (dummy_str.compareExact("hero", true))
            {
                category = 1;
            }
            else if (dummy_str.compareExact("powerup", true))
            {
                category = 2;
            }
            else if (dummy_str.compareExact("enemy", true))
            {
                category = 3;
            }
            else if (dummy_str.compareExact("fluff", true))
            {
                category = 4;
            }
            else if (dummy_str.compareExact("geoproxy", true))
            {
                category = 5;
            }
            else if (dummy_str.compareExact("object", true))
            {
                category = 6;
            }
            else
            {
                sprintf_s(result_msg, LARGE_BUFFER_SIZE, "\"setLinkAndCategory\" message: unknown proxy category!");
                return 2;
            }

            /********************************/

            if (nullptr != externalContentLink)
            {
                nodes.findAndDeleteChild(externalContentLink);
                externalContentLink = nullptr;
            }

            reloadXRef(getEditorString(1, false), currentGameVersion);

            return 0;
        }

        return 1;
    }


    ////////////////////////////////////////////////////////////////
    // eProxy: reload XRef
    ////////////////////////////////////////////////////////////////
    void eProxy::reloadXRef(eString media_dir, int32_t engine_version)
    {
        int32_t ar_flags;

        eXRefTarget* test_xref_taget;
        eXRefProxy* test_xref_proxy;

        /* The category must be "particle" or "geoproxy" */

        if (0 == category)
        {
            ar_flags = AR_MODE_XREF_PATH;
        }
        else if (5 == category)
        {
            ar_flags = 0;
        }
        else
        {
            return;
        }

        /* Is this "eProxy" NOT already loaded? */

        if ((0 == (0x00010000 & flags)) && (nullptr == externalContentLink))
        {
            test_xref_taget = new eXRefTarget;
            test_xref_taget->incRef();

            if (test_xref_taget->loadTarget(media_dir, engine_version, ar_flags, targetFile))
            {
                test_xref_proxy = new eXRefProxy(test_xref_taget);
                test_xref_proxy->incRef();

                nodes.appendChild(test_xref_proxy);
                externalContentLink = test_xref_proxy;

                test_xref_proxy->decRef();
            }

            test_xref_taget->decRef();
        }
    }


    ////////////////////////////////////////////////////////////////
    // eProxy: export XRef
    ////////////////////////////////////////////////////////////////
    void eProxy::exportXRef(eString media_dir, int32_t engine_version)
    {
        int32_t ar_flags, a, b = nodes.getSize();

        eXRefTarget* test_xref_taget;
        eXRefProxy* test_xref_proxy;

        /* The category must be "particle" or "geoproxy" */

        if (0 == category)
        {
            ar_flags = AR_MODE_XREF_PATH;
        }
        else if (5 == category)
        {
            ar_flags = 0;
        }
        else
        {
            return;
        }

        for (a = 0; a < b; a++)
        {
            test_xref_proxy = (eXRefProxy*)nodes.getIthChild(a);

            if (nullptr != test_xref_proxy)
            {
                /* Child node could be "eTriMesh" */

                if (test_xref_proxy->getType()->checkHierarchy(&E_XREFPROXY_TYPEINFO))
                {
                    test_xref_taget = test_xref_proxy->getXRefTarget();

                    if (nullptr != test_xref_taget)
                    {
                        test_xref_taget->exportTarget(media_dir, engine_version, ar_flags);
                    }
                }
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eProxy: set target name
    ////////////////////////////////////////////////////////////////
    void eProxy::setTargetName(eString new_target)
    {
        targetFile = new_target;
    }


    ////////////////////////////////////////////////////////////////
    // eProxy: set category
    ////////////////////////////////////////////////////////////////
    void eProxy::setCategory(int32_t new_category)
    {
        category = new_category;

        /* For now, set this collision-related flag */
        /* when the category is set to "geoproxy" */

        flagsCollisionResponse = (5 == category) ? 0x0000 : 0x00FF;
    }


    ////////////////////////////////////////////////////////////////
    // eProxy: export readable structure
    ////////////////////////////////////////////////////////////////
    void eProxy::writeStructureToTextFile(FileOperator &file, int32_t indentation) const
    {
        int32_t i;
        eNode* test_node;

        char bufor[128];

        /* "eNode" parent class */

        eNode::writeStructureToTextFile(file, indentation);

        /* "eProxy" additional info */

        if (targetFile.getLength() > 0)
        {
            if ('?' != targetFile.getText()[0])
            {
                sprintf_s
                (
                    bufor, 128,
                    " - proxy target: [%d] \"%s\"",
                    category,
                    targetFile.getText()
                );

                ArFunctions::writeIndentation(file, indentation);
                file << bufor;
                ArFunctions::writeNewLine(file, 0);
            }
        }

        /* "eTransform" parent class */

        sprintf_s
        (
            bufor, 128,
            " - xform pos: (%f, %f, %f)",
            defaultTransform.pos.x,
            defaultTransform.pos.y,
            defaultTransform.pos.z
        );

        ArFunctions::writeIndentation(file, indentation);
        file << bufor;
        ArFunctions::writeNewLine(file, 0);

        sprintf_s
        (
            bufor, 128,
            " - xform rot: (%f, %f, %f, %f)",
            defaultTransform.rot.x,
            defaultTransform.rot.y,
            defaultTransform.rot.z,
            defaultTransform.rot.w
        );

        ArFunctions::writeIndentation(file, indentation);
        file << bufor;
        ArFunctions::writeNewLine(file, 0);

        sprintf_s
        (
            bufor, 128,
            " - xform scl: (%f)",
            defaultTransform.scale
        );

        ArFunctions::writeIndentation(file, indentation);
        file << bufor;
        ArFunctions::writeNewLine(file, 0);

        /* "eGroup" parent class */

        for (i = 0; i < nodes.getSize(); i++)
        {
            test_node = (eNode*)nodes.getIthChild(i);

            if (nullptr != test_node)
            {
                test_node->writeStructureToTextFile(file, (indentation + 1));
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eProxy: render this node
    ////////////////////////////////////////////////////////////////
    void eProxy::renderNode(eDrawContext &draw_context) const
    {
        const float CUBE_HALF_WIDTH = (64.0f / 2);

        int32_t draw_flags = draw_context.getDrawFlags();

        if (GUI::drawFlags::DRAW_FLAG_PROXIES & draw_flags)
        {
            eTransform::renderNode(draw_context);

            /* Inactive color (blue) */
            float color[3] = {0, 0, 1.0f};

            bool is_selected_or_marked = draw_context.isNodeSelectedOrMarked();
            bool use_outline = draw_context.isNodeOutlined();

            glPushMatrix();

            if (is_selected_or_marked)
            {
                GUI::multiplyBySelectedObjectTransform(true);
            }
            else
            {
                glMultMatrixf(transposedMatrix[1]);
            }

            if ((GUI::drawFlags::DRAW_FLAG_SPECIAL & draw_flags) && (1 == category))
            {
                if (use_outline)
                {
                    glColor3f(0, 1.0f, 0);
                }

                draw_context.useMaterial(nullptr, 0);
                GUI::renderSpecialModel(true, ZOOKIEWIZARD_SPECIALMODEL_KAO);
            }

            if (use_outline)
            {
                /* Active color */
                GUI::colorOfMarkedObject(color[0], color[1], color[2]);
            }

            GUI::renderBoundingBox
            (
                2.0f,
                color[0], color[1], color[2],
                (0 - CUBE_HALF_WIDTH),
                (0 - CUBE_HALF_WIDTH),
                (0 - CUBE_HALF_WIDTH),
                (0 + CUBE_HALF_WIDTH),
                (0 + CUBE_HALF_WIDTH),
                (0 + CUBE_HALF_WIDTH)
            );

            glPopMatrix();
        }
    }

}
