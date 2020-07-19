#include <kao2engine/eTransform.h>
#include <kao2ar/Archive.h>

#include <kao2engine/eLeafCtrl.h>
#include <kao2engine/eSRPCombineCtrl.h>
#include <kao2engine/eMultiCtrl.h>

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

        if (ar.isInWriteMode())
        {
            deserializationCorrection();
        }

        defaultTransform.serialize(ar);
        worldTransform.serialize(ar);

        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&ctrl, &E_CTRL_ESRP_TYPEINFO);

        if (ar.isInReadMode())
        {
            setXForm(defaultTransform);
        }
    }


    ////////////////////////////////////////////////////////////////
    // eTransform: setting the correct "global" transformation during deserialization
    ////////////////////////////////////////////////////////////////
    void eTransform::deserializationCorrection()
    {
        const int SETTING_XFORM_MAX_PARENTS = 64;
        eTransform* parents_list[SETTING_XFORM_MAX_PARENTS];
        eTransform* test_parent;
        int32_t parents_index = 0;

        worldTransform = eSRP();

        /* Finding the parents with "eTransform" type, to set the second version of `defaultTransform` */

        test_parent = (eTransform*)parent;

        while ((nullptr != test_parent) && (parents_index < SETTING_XFORM_MAX_PARENTS))
        {
            if (test_parent->getType()->checkHierarchy(&E_TRANSFORM_TYPEINFO))
            {
                parents_list[parents_index] = test_parent;
                parents_index++;
            }

            test_parent = (eTransform*)(test_parent->parent);
        }

        for (int32_t i = parents_index - 1; i >= 0; i--)
        {
            worldTransform = worldTransform.applyAnotherSRP(parents_list[i]->getXForm(false));
        }

        if ((0 == (flags & 0x00001000)) && (nullptr != ctrl))
        {
            ctrl->ctrlApplyTransform(&defaultTransform, 0);
        }

        worldTransform = defaultTransform.applyAnotherSRP(worldTransform);
    }


    ////////////////////////////////////////////////////////////////
    // eTransform: set xform
    ////////////////////////////////////////////////////////////////
    void eTransform::setXForm(eSRP &new_xform)
    {
        if ((0 == (flags & 0x00001000)) && (nullptr != ctrl))
        {
            /* If "eTransform" has an animation controller attached, */
            /* then any changes to the default "SRP" are discarded. */

            ctrl->ctrlApplyTransform(&defaultTransform, 0);
        }
        else
        {
            defaultTransform = new_xform;
        }

        /* Create a matrix that represents current transformation */

        currentMatrix = defaultTransform.getMatrix();
        currentMatrix.transpose(transposedMatrix);
    }


    ////////////////////////////////////////////////////////////////
    // eTransform: get current xform
    ////////////////////////////////////////////////////////////////
    eSRP eTransform::getXForm(bool animated) const
    {
        /* animated: [0] = current transformation,
            [1] = all transformations applied (world transform). */

        if (animated)
        {
            return worldTransform;
        }

        if ((0 == (flags & 0x00001000)) && (nullptr != ctrl))
        {
            eSRP dummy_srp;

            ctrl->ctrlApplyTransform(&dummy_srp, 0);

            return dummy_srp;
        }

        return defaultTransform;
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

        eGroup::renderObject(draw_flags, anim, worldTransform, render_matrix, marked_id);

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

        if (update)
        {
            if ((0 == (flags & 0x00001000)) && (nullptr != ctrl))
            {
                if (nullptr != anim)
                {
                    defaultTransform = ctrl->ctrlGetTransform(test_srp, anim);

                    /* Update render matrix */

                    currentMatrix = defaultTransform.getMatrix();
                    currentMatrix.transpose(transposedMatrix);
                }
            }

            /* Update world transformation matrix */

            worldTransform = defaultTransform.applyAnotherSRP(parent_srp);

            /* (--dsp--) <kao2.0047BD9A> (update "eALBox" if exists) */
        }
        else
        {
            worldTransform = test_srp;
        }
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
        return defaultTransform.pos;
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
    // eTransform: add empty animation track (if the node uses "eMultiCtrl")
    ////////////////////////////////////////////////////////////////
    void eTransform::ctrlExpandAnimTracks(int32_t new_size)
    {
        eMultiCtrl<eSRP>* multi_ctrl;

        if (nullptr != ctrl)
        {
            /* We only want to modify the `ctrl` that already has multiple tracks */

            if (ctrl->getType()->checkHierarchy(&E_MULTICTRL_ESRP_TYPEINFO))
            {
                multi_ctrl = (eMultiCtrl<eSRP>*)ctrl;

                multi_ctrl->multiCtrl_SetSize(new_size);
            }
        }

        eGroup::ctrlExpandAnimTracks(new_size);
    }


    ////////////////////////////////////////////////////////////////
    // eTransform: remove specific animation track (if the node uses "eMultiCtrl")
    ////////////////////////////////////////////////////////////////
    void eTransform::ctrlRemoveAnimTrack(int32_t deleted_id)
    {
        eMultiCtrl<eSRP>* multi_ctrl;

        if (nullptr != ctrl)
        {
            if (ctrl->getType()->checkHierarchy(&E_MULTICTRL_ESRP_TYPEINFO))
            {
                multi_ctrl = (eMultiCtrl<eSRP>*)ctrl;

                multi_ctrl->multiCtrl_DeleteTrack(deleted_id);
            }
        }

        eGroup::ctrlRemoveAnimTrack(deleted_id);
    }


    ////////////////////////////////////////////////////////////////
    // eTransform: export readable structure
    ////////////////////////////////////////////////////////////////
    void eTransform::writeStructureToTextFile(FileOperator &file, int32_t indentation) const
    {
        int32_t i;
        eNode* test_node;

        char bufor[128];

        /* "eNode" parent class */

        eNode::writeStructureToTextFile(file, indentation);

        /* "eTransform" additional info */

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

                alpha = defaultTransform.scale;
                sprintf_s(bufor, 64, "%f %f %f", alpha, alpha, alpha);
                exporter.openTag("scale");
                exporter.writeInsideTag(bufor);
                exporter.closeTag();

                defaultTransform.rot.toEulerAngles(true, alpha, beta, gamma);

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

                alpha = defaultTransform.pos.x;
                beta = defaultTransform.pos.y;
                gamma = defaultTransform.pos.z;
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


    ////////////////////////////////////////////////////////////////
    // eTransform: editing animation tracks
    ////////////////////////////////////////////////////////////////

    void eTransform::ctrlSetStaticScale(float new_value)
    {
        eSRP dummy_srp;

        dummy_srp.scale = new_value;

        if (nullptr == ctrl)
        {
            ctrl = new eSRPCombineCtrl;
            ctrl->incRef();
        }

        ctrl->ctrlSetStaticKeyframe(dummy_srp, (0x01 << 0));
    }

    void eTransform::ctrlSetStaticRotation(eQuat new_value)
    {
        eSRP dummy_srp;

        dummy_srp.rot = new_value;

        if (nullptr == ctrl)
        {
            ctrl = new eSRPCombineCtrl;
            ctrl->incRef();
        }

        ctrl->ctrlSetStaticKeyframe(dummy_srp, (0x01 << 1));
    }

    void eTransform::ctrlSetStaticPosition(ePoint3 new_value)
    {
        eSRP dummy_srp;

        dummy_srp.pos = new_value;

        if (nullptr == ctrl)
        {
            ctrl = new eSRPCombineCtrl;
            ctrl->incRef();
        }

        ctrl->ctrlSetStaticKeyframe(dummy_srp, (0x01 << 2));
    }

    void eTransform::ctrlSetLoopType(int32_t anim_id, int32_t loop_type, int32_t param)
    {
        if (nullptr != ctrl)
        {
            ctrl->ctrlSetLoopType(anim_id, loop_type, param);
        }
    }

    void eTransform::ctrlClearKeyframes(int32_t anim_id)
    {
        if (nullptr != ctrl)
        {
            if (anim_id < 0)
            {
                ctrl->decRef();
                ctrl = nullptr;
            }
            else
            {
                ctrl->ctrlClearKeyframes(anim_id);
            }
        }
    }

    void eTransform::ctrlAddKeyframe(int32_t anim_id, float new_time, eSRP new_data, int32_t param)
    {
        eMultiCtrl<eSRP>* multi_ctrl;

        if (anim_id < 0)
        {
            if (nullptr == ctrl)
            {
                ctrl = new eSRPCombineCtrl;
                ctrl->incRef();
            }

            ctrl->ctrlAddKeyframe(0, new_time, new_data, param);
        }
        else
        {
            /* "anim_id" corresponds to a specific track in "eMultiCtrl" */

            if (nullptr == ctrl)
            {
                multi_ctrl = new eMultiCtrl<eSRP>;

                multi_ctrl->multiCtrl_SetSize(1 + anim_id);

                ctrl = multi_ctrl;
                ctrl->incRef();
            }
            else if (false == ctrl->getType()->checkHierarchy(&E_MULTICTRL_FLOAT_TYPEINFO))
            {
                multi_ctrl = new eMultiCtrl<eSRP>;

                multi_ctrl->multiCtrl_SetSize(1 + anim_id);
                multi_ctrl->multiCtrl_SetTrack(anim_id, ctrl);

                ctrl->decRef();
                ctrl = multi_ctrl;
                ctrl->incRef();
            }

            ctrl->ctrlAddKeyframe(anim_id, new_time, new_data, param);
        }
    }

}
