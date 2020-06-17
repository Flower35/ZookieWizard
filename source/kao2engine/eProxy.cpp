#include <kao2engine/eProxy.h>
#include <kao2ar/Archive.h>

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

        externalContent = false;
    }

    eProxy::~eProxy() {}


    ////////////////////////////////////////////////////////////////
    // eProxy serialization
    // <kao2.004846C0>
    ////////////////////////////////////////////////////////////////
    void eProxy::serialize(Archive &ar)
    {
        int32_t a, b;
        eXRefTarget* test_xref_taget;
        eXRefProxy* test_xref_proxy;
        eNode* test_node;

        if (externalContent && (false == ar.isInReadMode()))
        {
            /* Serialize "eNode" part, skip the last element in "eGroup", */
            /* and then serialize "eTransform" part. */

            eNode::serialize(ar);

            b = nodes.getSize() - 1;
            ar.readOrWrite(&b, 0x04);

            for (a = 0; a < b; a++)
            {
                test_node = (eNode*)nodes.getIthChild(a);

                ar.serialize((eObject**)&test_node, &E_NODE_TYPEINFO);
            }

            defaultTransform[0].serialize(ar);
            defaultTransform[1].serialize(ar);

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
            /* Checking for proxies that have scripts in place of the name */
            /* and usually contain some children nodes */

            a = true;

            switch (category)
            {
                case 1: // "hero"
                case 2: // "powerup"
                case 3: // "enemy"
                case 4: // "fluff"
                case 6: // "object"
                {
                    a = false; // just skip loading anything external

                    break;
                }
            }

            /* Is this "eProxy" NOT already loaded? */

            if (a && (0 == (0x00010000 & flags)))
            {
                if (nodes.getSize() <= 0)
                {
                    if (canBeLoadedOrExported(b))
                    {
                        test_xref_taget = new eXRefTarget;
                        test_xref_taget->incRef();

                        if (test_xref_taget->loadTarget(ar, b, targetFile))
                        {
                            test_xref_proxy = new eXRefProxy(test_xref_taget);
                            test_xref_proxy->incRef();

                            nodes.appendChild(test_xref_proxy);

                            test_xref_proxy->decRef();

                            externalContent = true;
                        }

                        test_xref_taget->decRef();
                    }
                }
            }
        }

        /********************************/
        /* Saving external models... */

        if (externalContent && ar.isInExportProxiesMode())
        {
            if (canBeLoadedOrExported(b))
            {
                test_xref_proxy = (eXRefProxy*)nodes.getIthChild(nodes.getSize() - 1);

                if (nullptr != test_xref_proxy)
                {
                    /* Child node could be "eTriMesh" */

                    if (test_xref_proxy->getType()->checkHierarchy(&E_XREFPROXY_TYPEINFO))
                    {
                        test_xref_taget = test_xref_proxy->getXRefTarget();

                        if (nullptr != test_xref_taget)
                        {
                            test_xref_taget->exportTarget(ar, b);
                        }
                    }
                }
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eProxy: destroy before dereferencing
    ////////////////////////////////////////////////////////////////
    void eProxy::destroyNode()
    {
        eXRefTarget* test_xref_taget;
        eXRefProxy* test_xref_proxy;
        eNode* nested_scene;

        test_xref_proxy = (eXRefProxy*)nodes.getIthChild(nodes.getSize() - 1);

        if (nullptr != test_xref_proxy)
        {
            if (test_xref_proxy->getType()->checkHierarchy(&E_XREFPROXY_TYPEINFO))
            {
                test_xref_taget = test_xref_proxy->getXRefTarget();

                if (nullptr != test_xref_taget)
                {
                    nested_scene = (eNode*)test_xref_taget->getLocalScene();

                    if (nullptr != nested_scene)
                    {
                        nested_scene->destroyNode();
                    }
                }
            }
        }

        eTransform::destroyNode();
    }


    ////////////////////////////////////////////////////////////////
    // eProxy: set archive flags and file extension
    ////////////////////////////////////////////////////////////////
    bool eProxy::canBeLoadedOrExported(int32_t &ar_flags)
    {
        if (targetFile.getLength() > 0)
        {
            if ('?' == targetFile.getText()[0])
            {
                return false;
            }
        }

        if (false == targetFile.hasExtension("ar"))
        {
            return false;
        }

        switch (category)
        {
            case 0: // (particle)
            {
                ar_flags = (AR_MODE_XREF_PATH);

                return true;
            }

            case 3: // (enemy)
            case 4: // (fluff)
            case 5: // (geoproxy)
            case 6: // (object)
            {
                ar_flags = 0;

                return true;
            }
        }

        return false;
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
                    bufor,
                    128,
                    " - proxy target: [%d] \"%s\"",
                    category,
                    targetFile.getText()
                );

                ArFunctions::writeIndentation(file, indentation);
                file << bufor;
                ArFunctions::writeNewLine(file, 0);
            }
        }

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
    // eProxy: render
    ////////////////////////////////////////////////////////////////
    bool eProxy::renderObject(int32_t draw_flags, eAnimate* anim, eSRP &parent_srp, eMatrix4x4 &parent_matrix, int32_t marked_id)
    {
        bool is_selected_or_marked;
        bool use_outline;

        const float CUBE_HALF_WIDTH = (64.0f / 2);

        /* Inactive color (blue) */
        float color[3] = {0, 0, 1.0f};

        if (GUI::drawFlags::DRAW_FLAG_PROXIES & draw_flags)
        {
            if (false == eTransform::renderObject(draw_flags, anim, parent_srp, parent_matrix, marked_id))
            {
                return false;
            }

            is_selected_or_marked = (((-2) == marked_id) || ((-1) == marked_id));
            use_outline = ((GUI::drawFlags::DRAW_FLAG_OUTLINE & draw_flags) && (((-2) == marked_id) || ((-3) == marked_id)));

            glPushMatrix();

            if (is_selected_or_marked)
            {
                /* This object is selected (-1) or marked (-2) and can be moved around */
                GUI::multiplyBySelectedObjectTransform();
            }
            else
            {
                glMultMatrixf(transposedMatrix);
            }

            if ((GUI::drawFlags::DRAW_FLAG_SPECIAL & draw_flags) && (1 == category))
            {
                if (use_outline)
                {
                    glColor3f(0, 1.0f, 0);
                }

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

        return true;
    }

}
