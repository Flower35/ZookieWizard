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
    }

    eProxy::~eProxy() {}


    ////////////////////////////////////////////////////////////////
    // eProxy serialization
    // <kao2.004846C0>
    ////////////////////////////////////////////////////////////////
    void eProxy::serialize(Archive &ar)
    {
        int32_t ar_flags;
        eXRefTarget* test_xref_taget;
        eXRefProxy* test_xref_proxy;

        if ((0 == (0x00010000 & flags)) && (false == ar.isInReadMode()))
        {
            /* Serialize "eNode" and "eTransform" (zero elements in "eGroup!") */

            eNode::serialize(ar);

            ar_flags = 0;
            ar.readOrWrite(&ar_flags, 0x04);

            defaultTransform[0].serialize(ar);
            defaultTransform[1].serialize(ar);

            ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&ctrl, &E_CTRL_ESRP_TYPEINFO);
        }
        else
        {
            eTransform::serialize(ar);
        }

        ar.serializeString(targetFile);

        ar.readOrWrite(&category, 0x04);

        /********************************/
        /* Loading external models... */

        if ((0 == (0x00010000 & flags)) && ar.isInReadMode())
        {
            if (nodes.getSize() <= 0)
            {
                if (canBeLoadedOrExported(ar_flags))
                {
                    test_xref_taget = new eXRefTarget;
                    test_xref_taget->incRef();

                    if (test_xref_taget->loadTarget(ar, ar_flags, targetFile))
                    {
                        test_xref_proxy = new eXRefProxy(test_xref_taget);
                        test_xref_proxy->incRef();

                        nodes.appendChild(test_xref_proxy);

                        test_xref_proxy->decRef();
                    }

                    test_xref_taget->decRef();
                }
            }
        }

        /********************************/
        /* Saving external models... */

        if (ar.isInExportProxiesMode())
        {
            if (canBeLoadedOrExported(ar_flags))
            {
                test_xref_proxy = (eXRefProxy*)nodes.getIthChild(0);

                if (nullptr != test_xref_proxy)
                {
                    /* Child node could be "eTriMesh" */

                    if (test_xref_proxy->getType()->checkHierarchy(&E_XREFPROXY_TYPEINFO))
                    {
                        test_xref_taget = test_xref_proxy->getXRefTarget();

                        if (nullptr != test_xref_taget)
                        {
                            test_xref_taget->exportTarget(ar, ar_flags);
                        }
                    }
                }
            }
        }
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
    bool eProxy::renderObject(int32_t draw_flags, eAnimate* anim, eSRP &parent_srp, int32_t marked_id)
    {
        bool is_selected_or_marked;

        const float CUBE_WIDTH = (64.0f / 2);

        /* Inactive color (blue) */
        float color[3] = {0, 0, 1.0f};

        eSRP rendered_srp;
        float test_matrix[16];

        if (GUI::drawFlags::DRAW_FLAG_PROXIES & draw_flags)
        {
            if (false == eTransform::renderObject(draw_flags, anim, parent_srp, marked_id))
            {
                return false;
            }

            is_selected_or_marked = (((-2) == marked_id) || ((-1) == marked_id));

            if (is_selected_or_marked)
            {
                /* This object is selected (-1) or marked (-2) and can be moved around */
                glPushMatrix();
                GUI::multiplyBySelectedObjectTransform();
            }
            else
            {
                rendered_srp = modifiedTransform[0];
            }

            if ((GUI::drawFlags::DRAW_FLAG_OUTLINE & draw_flags) && (((-2) == marked_id) || ((-3) == marked_id)))
            {
                /* Active color */
                GUI::colorOfMarkedObject(color[0], color[1], color[2]);
            }

            if ((GUI::drawFlags::DRAW_FLAG_SPECIAL & draw_flags) && (1 == category))
            {
                if (false == is_selected_or_marked)
                {
                    rendered_srp.getMatrix().transpose(test_matrix);
                    glPushMatrix();
                    glMultMatrixf(test_matrix);
                }

                GUI::renderSpecialModel(ZOOKIEWIZARD_SPECIALMODEL_KAO);

                if (false == is_selected_or_marked)
                {
                    glPopMatrix();
                }
            }

            GUI::renderBoundingBox
            (
                2.0f,
                color[0], color[1], color[2],
                (rendered_srp.pos.x - CUBE_WIDTH),
                (rendered_srp.pos.y - CUBE_WIDTH),
                (rendered_srp.pos.z - CUBE_WIDTH),
                (rendered_srp.pos.x + CUBE_WIDTH),
                (rendered_srp.pos.y + CUBE_WIDTH),
                (rendered_srp.pos.z + CUBE_WIDTH)
            );

            if (is_selected_or_marked)
            {
                glPopMatrix();
            }
        }

        return true;
    }

}
