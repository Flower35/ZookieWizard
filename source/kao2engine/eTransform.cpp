#include <kao2engine/eTransform.h>
#include <kao2ar/Archive.h>

#include <kao2engine/eCamera.h>

#include <utilities/ColladaExporter.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eTransform interface
    // <kao2.0047BAA0> (constructor)
    // <kao2.0047BC80> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_TRANSFORM_TYPEINFO
    (
        E_TRANSFORM_ID,
        "eTransform",
        &E_GROUP_TYPEINFO,
        []() -> eObject*
        {
            return new eTransform;
        }
    );

    TypeInfo* eTransform::getType() const
    {
        return &E_TRANSFORM_TYPEINFO;
    }

    eTransform::eTransform()
    : eGroup()
    {
        /*[0xA8]*/ ctrl = nullptr;

        currentMatrix = defaultTransform[0].getMatrix();
        currentMatrix.transpose(transposedMatrix);

        jointType = false;
    }

    eTransform::~eTransform()
    {
        ctrl->decRef();
    }


    ////////////////////////////////////////////////////////////////
    // eTransform serialization
    // <kao2.0047BE00>
    ////////////////////////////////////////////////////////////////
    void eTransform::serialize(Archive &ar)
    {
        eGroup::serialize(ar);

        defaultTransform[0].serialize(ar);
        defaultTransform[1].serialize(ar);

        if (ar.isInReadMode())
        {
            setXForm(defaultTransform[0]);
        }

        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&ctrl, &E_CTRL_ESRP_TYPEINFO);
    }


    ////////////////////////////////////////////////////////////////
    // eTransform: set xform
    ////////////////////////////////////////////////////////////////
    void eTransform::setXForm(eSRP &new_xform)
    {
        defaultTransform[0] = new_xform;
        defaultTransform[1] = defaultTransform[0];

        modifiedTransform[0] = defaultTransform[0];
        modifiedTransform[1] = defaultTransform[1];

        currentMatrix = modifiedTransform[0].getMatrix();
        currentMatrix.transpose(transposedMatrix);
    }



    ////////////////////////////////////////////////////////////////
    // eTransform: get current xform
    ////////////////////////////////////////////////////////////////
    eSRP eTransform::getXForm(bool modified, bool animated) const
    {
        /* animated: [0] = current transformation,
            [1] = all transformations applied (world transform). */

        if (modified)
        {
            if (animated)
            {
                return modifiedTransform[1];
            }

            return modifiedTransform[0];
        }
        else if (animated)
        {
            return defaultTransform[1];
        }

        return defaultTransform[0];
    }


    ////////////////////////////////////////////////////////////////
    // eTransform: reposition the model in 3D space
    ////////////////////////////////////////////////////////////////
    bool eTransform::renderObject(int32_t draw_flags, eAnimate* anim, eSRP &parent_srp, eMatrix4x4 &parent_matrix, int32_t marked_id)
    {
        bool is_selected_or_marked;
        bool use_outline;

        if (false == eNode::renderObject(draw_flags, anim, parent_srp, parent_matrix, marked_id))
        {
            return false;
        }

        /* Calculate transformation (for animations and for culling) */

        updateSRP((GUI::drawFlags::DRAW_FLAG_ANIMS & draw_flags), anim, parent_srp);

        eMatrix4x4 render_matrix(parent_matrix * currentMatrix);

        /* Apply Transformation (on top of previous ones) */

        glPushMatrix();

        is_selected_or_marked = (((-2) == marked_id) || ((-1) == marked_id));
        use_outline = ((GUI::drawFlags::DRAW_FLAG_OUTLINE & draw_flags) && (((-2) == marked_id) || ((-3) == marked_id)));

        if (is_selected_or_marked)
        {
            /* This object is selected (-1) or marked (-2) and can be moved around */
            GUI::multiplyBySelectedObjectTransform();
        }
        else
        {
            glMultMatrixf(transposedMatrix);
        }

        if (GUI::drawFlags::DRAW_FLAG_SPECIAL & draw_flags)
        {
            if (use_outline)
            {
                glColor3f(0, 1.0f, 0);
            }

            /* Draw helper arrow or helper camera */
            GUI::renderSpecialModel
            (
                (!use_outline),
                getType()->checkHierarchy(&E_CAMERA_TYPEINFO)
                    ? ZOOKIEWIZARD_SPECIALMODEL_CAMERA
                    : ZOOKIEWIZARD_SPECIALMODEL_ARROW
            );

            if (use_outline)
            {
                glColor3f(1.0f, 1.0f, 1.0f);
            }
        }

        /* Draw children nodes */

        eGroup::renderObject(draw_flags, anim, modifiedTransform[1], render_matrix, marked_id);

        /* Restore parent matrix */

        glPopMatrix();

        return true;
    }


    ////////////////////////////////////////////////////////////////
    // eTransform: update SRP structure
    // <kao2.0047BCF0>
    ////////////////////////////////////////////////////////////////
    void eTransform::updateSRP(bool update, eAnimate* anim, eSRP &parent_srp)
    {
        eSRP test_srp;
        eSRP previous_srp;

        if (update)
        {
            if ((nullptr != ctrl) && (nullptr != anim))
            {
                previous_srp = modifiedTransform[0];

                modifiedTransform[0] = ctrl->ctrlGetTransform(test_srp, anim);

                /* (--dsp--) Checking if `previous_srp != form01` and changing some "eNode" flags */
            }
            else
            {
                modifiedTransform[0] = defaultTransform[0];
            }

            /* Update render matrix */

            currentMatrix = modifiedTransform[0].getMatrix();
            currentMatrix.transpose(transposedMatrix);
        }

        /* Update world transformation matrix */

        modifiedTransform[1] = modifiedTransform[0].applyAnotherSRP(parent_srp);

        /* (--dsp--) <kao2.0047BD9A> (update "eALBox" if exists) */
    }


    ////////////////////////////////////////////////////////////////
    // eTransform: (editor option) rebuild collision
    ////////////////////////////////////////////////////////////////
    void eTransform::editingRebuildCollision()
    {
        if ((nullptr != ctrl) || jointType)
        {
            /* Don't update animated objects */

            return;
        }

        eGroup::editingRebuildCollision();
    }


    ////////////////////////////////////////////////////////////////
    // eTransform: (editor option) find object in 3D space
    ////////////////////////////////////////////////////////////////
    ePoint3 eTransform::editingGetCenterPoint() const
    {
        return modifiedTransform[1].pos;
    }


    ////////////////////////////////////////////////////////////////
    // eTransform: (editor option) apply new transformation
    ////////////////////////////////////////////////////////////////
    void eTransform::editingApplyNewTransform(eSRP &new_transform, int32_t marked_id)
    {
        if (marked_id >= 0)
        {
            eGroup::editingApplyNewTransform(new_transform, marked_id);
        }
        else
        {
            setXForm(new_transform);
        }
    }


    ////////////////////////////////////////////////////////////////
    // eTransform: COLLADA exporting
    ////////////////////////////////////////////////////////////////
    void eTransform::writeNodeToXmlFile(ColladaExporter &exporter) const
    {
        int32_t i;
        float alpha, beta, gamma;
        char bufor[64];
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
                /* Collecting objects for COLLADA libraries... */

                eGroup::writeNodeToXmlFile(exporter);

                break;
            }

            case COLLADA_EXPORTER_STATE_VISUAL_SCENES:
            {
                exporter.openTag("node");

                i = exporter.getObjectRefId(COLLADA_EXPORTER_OBJ_NODE, this, true);
                sprintf_s(bufor, 64, "Node%d", i);
                exporter.insertTagAttrib("id", bufor);
                exporter.insertTagAttrib("name", name);

                if (jointType)
                {
                    exporter.insertTagAttrib("sid", bufor);
                    exporter.insertTagAttrib("type", "JOINT");
                }
                else
                {
                    exporter.insertTagAttrib("type", "NODE");
                }

                alpha = modifiedTransform[0].scale;
                sprintf_s(bufor, 64, "%f %f %f", alpha, alpha, alpha);
                exporter.openTag("scale");
                exporter.writeInsideTag(bufor);
                exporter.closeTag();

                modifiedTransform[0].rot.toEulerAngles(true, alpha, beta, gamma);

                sprintf_s(bufor, 64, "0 0 1 %f", (gamma / 180.0 * M_PI));
                exporter.openTag("rotate");
                exporter.writeInsideTag(bufor);
                exporter.closeTag();

                sprintf_s(bufor, 64, "0 1 0 %f", (beta / 180.0 * M_PI));
                exporter.openTag("rotate");
                exporter.writeInsideTag(bufor);
                exporter.closeTag();

                sprintf_s(bufor, 64, "1 0 0 %f", (alpha / 180.0 * M_PI));
                exporter.openTag("rotate");
                exporter.writeInsideTag(bufor);
                exporter.closeTag();

                alpha = defaultTransform[0].pos.x;
                beta = defaultTransform[0].pos.y;
                gamma = defaultTransform[0].pos.z;
                sprintf_s(bufor, 64, "%f %f %f", alpha, beta, gamma);
                exporter.openTag("translate");
                exporter.writeInsideTag(bufor);
                exporter.closeTag();

                /* "eGroup" could exist as independent node (without parent "eTransform") */
                /* That's why we are not calling `eGroup::writeNodeToXmlFile()` */

                for (i = 0; i < nodes.getSize(); i++)
                {
                    test_node = (eNode*)nodes.getIthChild(i);

                    if (nullptr != test_node)
                    {
                        test_node->writeNodeToXmlFile(exporter);
                    }
                }

                exporter.closeTag(); // "node"

                break;
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eTransform: set node type (helpful when exporting)
    ////////////////////////////////////////////////////////////////

    void eTransform::setTypeToJoint(bool is_joint)
    {
        jointType = is_joint;
    }

    bool eTransform::isJointNode() const
    {
        return jointType;
    }

}
