#include <ElephantEngine/eTransform.h>
#include <ElephantBase/Archive.h>
#include <ElephantBase/eDrawContext.h>

#include <ElephantEngine/eLeafCtrl.h>
#include <ElephantEngine/eSRPCombineCtrl.h>
#include <ElephantEngine/eMultiCtrl.h>

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

    const TypeInfo* eTransform::getType() const
    {
        return &E_TRANSFORM_TYPEINFO;
    }

    eTransform::eTransform()
    : eGroup()
    {
        /*[0xA8]*/ ctrl = nullptr;

        currentMatrix.transpose(transposedMatrix[0]);
        currentMatrix.transpose(transposedMatrix[1]);

        jointType = false;
    }

    eTransform::~eTransform()
    {
        ctrl->decRef();
    }


    ////////////////////////////////////////////////////////////////
    // eTransform: cloning the object
    ////////////////////////////////////////////////////////////////

    void eTransform::createFromOtherObject(const eTransform &other)
    {
        defaultTransform = other.defaultTransform;

        ctrl = other.ctrl;
        if (nullptr != ctrl)
        {
            ctrl->incRef();
        }

        jointType = other.jointType;

        getTransposedMatrices(defaultTransform);
    }

    eTransform::eTransform(const eTransform &other)
    : eGroup(other)
    {
        createFromOtherObject(other);
    }

    eTransform& eTransform::operator = (const eTransform &other)
    {
        if ((&other) != this)
        {
            eGroup::operator = (other);

            /****************/

            ctrl->decRef();

            /****************/

            createFromOtherObject(other);

            /****************/

            worldTransform = defaultTransform;
        }

        return (*this);
    }

    eObject* eTransform::cloneFromMe() const
    {
        return new eTransform(*this);
    }


    ////////////////////////////////////////////////////////////////
    // eTransform: serialization
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
    // eTransform: export readable structure
    ////////////////////////////////////////////////////////////////
    void eTransform::writeStructureToTextFile(FileOperator &file, int32_t indentation, bool group_written) const
    {
        int32_t a;
        eNode* child_node;

        char bufor[128];

        /* "eGroup": parent class */

        eGroup::writeStructureToTextFile(file, indentation, true);

        /* "eTransform": additional info */

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

        if (nullptr != ctrl)
        {
            sprintf_s
            (
                bufor, 128,
                " - xform ctrl: [%s]",
                ctrl->getType()->name
            );

            ArFunctions::writeIndentation(file, indentation);
            file << bufor;
            ArFunctions::writeNewLine(file, 0);
        }

        /****************/

        if (!group_written)
        {
            MACRO_KAO2_GROUP_FOREACH_NODE({ child_node->writeStructureToTextFile(file, (indentation + 1), false); })
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

                sprintf_s(bufor, 64, "0 0 1 %f", RAD2DEG_F(gamma));
                exporter.openTag("rotate");
                exporter.writeInsideTag(bufor);
                exporter.closeTag();

                sprintf_s(bufor, 64, "0 1 0 %f", RAD2DEG_F(beta));
                exporter.openTag("rotate");
                exporter.writeInsideTag(bufor);
                exporter.closeTag();

                sprintf_s(bufor, 64, "1 0 0 %f", RAD2DEG_F(alpha));
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
                    if (nullptr != (test_node = (eNode*)nodes.getIthChild(i)))
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
    // eTransform: set `previousTransform` gradually
    ////////////////////////////////////////////////////////////////
    void eTransform::setPreviousTransformGradually(eTransform* last_xform)
    {
        eGroup::setPreviousTransformGradually(this);

        previousTransform = last_xform;
    }


    ////////////////////////////////////////////////////////////////
    // eTransform: update before rendering [[vptr]+0x38]
    // <kao2.0047BCF0>
    ////////////////////////////////////////////////////////////////
    void eTransform::updateBeforeRendering(eDrawContext &draw_context)
    {
        eSRP* previous_parent_srp;
        eSRP test_srp;

        eMatrix4x4* previous_parent_matrix;
        eMatrix4x4 test_matrix;

        eAnimate* animate;

        /********************************/
        /* Get some properties from "eDrawContext" */

        animate = draw_context.getAnimateObject();

        previous_parent_srp = draw_context.getParentSRP();
        previous_parent_matrix = draw_context.getParentMatrix();

        /********************************/
        /* Update current "eSRP" and the current render matrix */

        if (draw_context.isNodeSelectedOrMarked())
        {
            GUI::getMovedSeletedTransform(&test_srp);
        }
        else
        {
            if (GUI::drawFlags::DRAW_FLAG_ANIMS & draw_context.getDrawFlags())
            {
                if ((0 == (flags & 0x00001000)) && (nullptr != ctrl))
                {
                    if (nullptr != animate)
                    {
                        test_srp = ctrl->ctrlGetTransform(defaultTransform, animate);
                    }
                    else
                    {
                        ctrl->ctrlApplyTransform(&test_srp, 0);
                    }
                }
                else
                {
                    test_srp = defaultTransform;
                }
            }
            else if (!jointType)
            {
                test_srp = defaultTransform;
            }
        }

        getTransposedMatrices(test_srp);

        if (nullptr != previous_parent_srp)
        {
            worldTransform = test_srp.applyAnotherSRP(*previous_parent_srp);
        }
        else
        {
            worldTransform = test_srp;
        }

        if (nullptr != previous_parent_matrix)
        {
            test_matrix = (*previous_parent_matrix) * currentMatrix;
        }
        else
        {
            test_matrix = currentMatrix;
        }

        /********************************/
        /* Go to the `eGroup` method, then restore the Draw Context */

        draw_context.setParentSRP(&worldTransform);
        draw_context.setParentMatrix(&test_matrix);

        eGroup::updateBeforeRendering(draw_context);

        draw_context.setParentMatrix(previous_parent_matrix);
        draw_context.setParentSRP(previous_parent_srp);
    }


    ////////////////////////////////////////////////////////////////
    // eTransform: render this node
    ////////////////////////////////////////////////////////////////
    void eTransform::renderNode(eDrawContext &draw_context) const
    {
        bool use_outline = draw_context.isNodeOutlined();
        bool is_selected = draw_context.isNodeSelectedOrMarked();

        eSRP* previous_parent_srp = draw_context.getParentSRP();
        eMatrix4x4* previous_parent_matrix = draw_context.getParentMatrix();

        /********************************/
        /* Draw the Helper Arrow with a transformation that ignores scaling */

        if (GUI::drawFlags::DRAW_FLAG_SPECIAL & draw_context.getDrawFlags())
        {
            if (use_outline)
            {
                glColor3f(0, 1.0f, 0);
            }

            glPushMatrix();

            if (is_selected)
            {
                GUI::multiplyBySelectedObjectTransform(true);
            }
            else
            {
                glMultMatrixf(transposedMatrix[1]);
            }

            draw_context.useMaterial(nullptr, 0);
            GUI::renderSpecialModel((!use_outline), ZOOKIEWIZARD_SPECIALMODEL_ARROW);

            glPopMatrix();

            if (use_outline)
            {
                glColor3f(1.0f, 1.0f, 1.0f);
            }
        }

        /********************************/
        /* Apply Transformation (on top of previous ones) */

        glPushMatrix();

        if (is_selected)
        {
            GUI::multiplyBySelectedObjectTransform(false);
        }
        else
        {
            glMultMatrixf(transposedMatrix[0]);
        }

        /********************************/
        /* Draw children nodes */

        draw_context.setParentSRP(&worldTransform);
        draw_context.setParentMatrix(&currentMatrix);

        eGroup::renderNode(draw_context);

        /********************************/
        /* Restore parent matrix (OpenGL) and the Draw Context */

        glPopMatrix();

        draw_context.setParentMatrix(previous_parent_matrix);
        draw_context.setParentSRP(previous_parent_srp);
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
    // eTransform: preparing just-created node
    ////////////////////////////////////////////////////////////////
    void eTransform::editingNewNodeSetup()
    {
        getTransposedMatrices(defaultTransform);

        eGroup::editingNewNodeSetup();
    }


    ////////////////////////////////////////////////////////////////
    // eTransform: custom TXT parser methods
    ////////////////////////////////////////////////////////////////

    int32_t eTransform::parsingSetProperty(char* result_msg, const TxtParsingNodeProp &property)
    {
        int32_t test;
        float dummy_floats[4];
        eString prop_name;

        if (1 != (test = eGroup::parsingSetProperty(result_msg, property)))
        {
            return test;
        }

        prop_name = property.getName();

        if (prop_name.compareExact("pos", true))
        {
            if (!property.checkType(TXT_PARSING_NODE_PROPTYPE_FLOAT3))
            {
                TxtParsingNode_ErrorPropType(result_msg, "pos", TXT_PARSING_NODE_PROPTYPE_FLOAT3);
                return 2;
            }

            property.getValue(dummy_floats);

            defaultTransform.pos.x = dummy_floats[0];
            defaultTransform.pos.y = dummy_floats[1];
            defaultTransform.pos.z = dummy_floats[2];

            return 0;
        }
        else if (prop_name.compareExact("rot", true))
        {
            if (property.checkType(TXT_PARSING_NODE_PROPTYPE_FLOAT3))
            {
                property.getValue(dummy_floats);

                dummy_floats[0] = DEG2RAD_F(dummy_floats[0]);
                dummy_floats[1] = DEG2RAD_F(dummy_floats[1]);
                dummy_floats[2] = DEG2RAD_F(dummy_floats[2]);

                defaultTransform.rot.fromEulerAngles(true, dummy_floats[0], dummy_floats[1], dummy_floats[2]);
            }
            else if (property.checkType(TXT_PARSING_NODE_PROPTYPE_FLOAT4))
            {
                property.getValue(dummy_floats);

                defaultTransform.rot.x = dummy_floats[0];
                defaultTransform.rot.y = dummy_floats[1];
                defaultTransform.rot.z = dummy_floats[2];
                defaultTransform.rot.w = dummy_floats[3];

                defaultTransform.rot.normalize();
            }
            else
            {
                TxtParsingNode_ErrorPropType(result_msg, "rot", TXT_PARSING_NODE_PROPTYPE_FLOAT4);
                return 2;
            }

            return 0;
        }
        else if (prop_name.compareExact("scl", true))
        {
            if (property.checkType(TXT_PARSING_NODE_PROPTYPE_INTEGER))
            {
                property.getValue(&test);
                defaultTransform.scale = (float)test;
            }
            else if (property.checkType(TXT_PARSING_NODE_PROPTYPE_FLOAT1))
            {
                property.getValue(&(defaultTransform.scale));
            }
            else
            {
                TxtParsingNode_ErrorPropType(result_msg, "scl", TXT_PARSING_NODE_PROPTYPE_FLOAT1);
                return 2;
            }

            return 0;
        }

        return 1;
    }

    int32_t eTransform::parsingCustomMessage(char* result_msg, const eString &message, int32_t params_count, const TxtParsingNodeProp* params)
    {
        int32_t test[4];
        float dummy_floats[5];
        eSRP dummy_srp;

        if (1 != (test[0] = eGroup::parsingCustomMessage(result_msg, message, params_count, params)))
        {
            return test[0];
        }

        if (message.compareExact("setPos", true))
        {
            if (1 != params_count)
            {
                TxtParsingNode_ErrorArgCount(result_msg, "setPos", 1);
                return 2;
            }

            /********************************/

            if (!params[0].checkType(TXT_PARSING_NODE_PROPTYPE_FLOAT3))
            {
                TxtParsingNode_ErrorArgType(result_msg, "setPos", 0, TXT_PARSING_NODE_PROPTYPE_FLOAT3);
                return 2;
            }

            params[0].getValue(dummy_floats);

            defaultTransform.pos.x = dummy_floats[0];
            defaultTransform.pos.y = dummy_floats[1];
            defaultTransform.pos.z = dummy_floats[2];

            /********************************/

            getTransposedMatrices(defaultTransform);
            return 0;
        }
        else if (message.compareExact("setRot", true))
        {
            if (1 != params_count)
            {
                TxtParsingNode_ErrorArgCount(result_msg, "setRot", 1);
                return 2;
            }

            /********************************/

            if (params[0].checkType(TXT_PARSING_NODE_PROPTYPE_FLOAT3))
            {
                params[0].getValue(dummy_floats);

                dummy_floats[0] = DEG2RAD_F(dummy_floats[0]);
                dummy_floats[1] = DEG2RAD_F(dummy_floats[1]);
                dummy_floats[2] = DEG2RAD_F(dummy_floats[2]);

                defaultTransform.rot.fromEulerAngles(true, dummy_floats[0], dummy_floats[1], dummy_floats[2]);
            }

            else if (params[0].checkType(TXT_PARSING_NODE_PROPTYPE_FLOAT4))
            {
                params[0].getValue(dummy_floats);

                defaultTransform.rot.x = dummy_floats[0];
                defaultTransform.rot.y = dummy_floats[1];
                defaultTransform.rot.z = dummy_floats[2];
                defaultTransform.rot.w = dummy_floats[3];

                defaultTransform.rot.normalize();
            }
            else
            {
                TxtParsingNode_ErrorArgType(result_msg, "setRot", 0, TXT_PARSING_NODE_PROPTYPE_FLOAT4);
                return 2;
            }

            /********************************/

            getTransposedMatrices(defaultTransform);
            return 0;
        }
        else if (message.compareExact("setScl", true))
        {
            if (1 != params_count)
            {
                TxtParsingNode_ErrorArgCount(result_msg, "setScl", 1);
                return 2;
            }

            /********************************/

            if (params[0].checkType(TXT_PARSING_NODE_PROPTYPE_INTEGER))
            {
                params[0].getValue(&(test[0]));
                defaultTransform.scale = (float)test[0];
            }
            else if (params[0].checkType(TXT_PARSING_NODE_PROPTYPE_FLOAT1))
            {
                params[0].getValue(&(defaultTransform.scale));
            }
            else
            {
                TxtParsingNode_ErrorArgType(result_msg, "setScl", 0, TXT_PARSING_NODE_PROPTYPE_FLOAT1);
                return 2;
            }

            /********************************/

            getTransposedMatrices(defaultTransform);
            return 0;
        }
        else if (message.compareExact("ctrlClearKeyframes", true))
        {
            if (1 != params_count)
            {
                TxtParsingNode_ErrorArgCount(result_msg, "ctrlClearKeyframes", 1);
                return 2;
            }

            /********************************/

            if (!params[0].checkType(TXT_PARSING_NODE_PROPTYPE_INTEGER))
            {
                TxtParsingNode_ErrorArgType(result_msg, "ctrlClearKeyframes", 0, TXT_PARSING_NODE_PROPTYPE_INTEGER);
                return 2;
            }

            params[0].getValue(&(test[0]));

            /********************************/

            ctrlClearKeyframes(test[0]);
            return 0;
        }
        else if (message.compareExact("ctrlSetStaticScale", true))
        {
            if (1 != params_count)
            {
                TxtParsingNode_ErrorArgCount(result_msg, "ctrlSetStaticScale", 1);
                return 2;
            }

            /********************************/

            if (params[0].checkType(TXT_PARSING_NODE_PROPTYPE_INTEGER))
            {
                params[0].getValue(&(test[0]));
                dummy_srp.scale = (float)test[0];
            }
            else if (params[0].checkType(TXT_PARSING_NODE_PROPTYPE_FLOAT1))
            {
                params[0].getValue(&(dummy_srp.scale));
            }
            else
            {
                TxtParsingNode_ErrorArgType(result_msg, "ctrlSetStaticScale", 0, TXT_PARSING_NODE_PROPTYPE_FLOAT1);
                return 2;
            }

            /********************************/

            ctrlSetStaticScale(dummy_srp.scale);
            return 0;
        }
        else if (message.compareExact("ctrlSetStaticRotation", true))
        {
            if (1 != params_count)
            {
                TxtParsingNode_ErrorArgCount(result_msg, "ctrlSetStaticRotation", 1);
                return 2;
            }

            /********************************/

            if (params[0].checkType(TXT_PARSING_NODE_PROPTYPE_FLOAT3))
            {
                params[0].getValue(dummy_floats);

                dummy_floats[0] = DEG2RAD_F(dummy_floats[0]);
                dummy_floats[1] = DEG2RAD_F(dummy_floats[1]);
                dummy_floats[2] = DEG2RAD_F(dummy_floats[2]);

                dummy_srp.rot.fromEulerAngles(true, dummy_floats[0], dummy_floats[1], dummy_floats[2]);
            }
            else if (params[0].checkType(TXT_PARSING_NODE_PROPTYPE_FLOAT4))
            {
                params[0].getValue(dummy_floats);

                dummy_srp.rot.x = dummy_floats[0];
                dummy_srp.rot.y = dummy_floats[1];
                dummy_srp.rot.z = dummy_floats[2];
                dummy_srp.rot.w = dummy_floats[3];

                dummy_srp.rot.normalize();
            }
            else
            {
                TxtParsingNode_ErrorArgType(result_msg, "ctrlSetStaticRotation", 0, TXT_PARSING_NODE_PROPTYPE_FLOAT4);
                return 2;
            }


            /********************************/

            ctrlSetStaticRotation(dummy_srp.rot);
            return 0;
        }
        else if (message.compareExact("ctrlSetStaticPosition", true))
        {
            if (1 != params_count)
            {
                TxtParsingNode_ErrorArgCount(result_msg, "ctrlSetStaticPosition", 1);
                return 2;
            }

            /********************************/

            if (!params[0].checkType(TXT_PARSING_NODE_PROPTYPE_FLOAT3))
            {
                TxtParsingNode_ErrorArgType(result_msg, "ctrlSetStaticPosition", 0, TXT_PARSING_NODE_PROPTYPE_FLOAT3);
                return 2;
            }

            params[0].getValue(dummy_floats);

            dummy_srp.pos.x = dummy_floats[0];
            dummy_srp.pos.y = dummy_floats[1];
            dummy_srp.pos.z = dummy_floats[2];

            /********************************/

            ctrlSetStaticPosition(dummy_srp.pos);
            return 0;
        }
        else if (message.compareExact("ctrlSetLoopType", true))
        {
            if (3 != params_count)
            {
                TxtParsingNode_ErrorArgCount(result_msg, "ctrlSetLoopType", 3);
                return 2;
            }

            /********************************/

            if (!params[0].checkType(TXT_PARSING_NODE_PROPTYPE_INTEGER))
            {
                TxtParsingNode_ErrorArgType(result_msg, "ctrlSetLoopType", 1, TXT_PARSING_NODE_PROPTYPE_INTEGER);
                return 2;
            }

            /********************************/

            if (!params[1].checkType(TXT_PARSING_NODE_PROPTYPE_INTEGER))
            {
                TxtParsingNode_ErrorArgType(result_msg, "ctrlSetLoopType", 2, TXT_PARSING_NODE_PROPTYPE_INTEGER);
                return 2;
            }

            /********************************/

            if (!params[2].checkType(TXT_PARSING_NODE_PROPTYPE_INTEGER))
            {
                TxtParsingNode_ErrorArgType(result_msg, "ctrlSetLoopType", 3, TXT_PARSING_NODE_PROPTYPE_INTEGER);
                return 2;
            }

            params[0].getValue(&(test[0]));
            params[1].getValue(&(test[1]));
            params[2].getValue(&(test[2]));

            /********************************/

            ctrlSetLoopType(test[0], test[1], test[2]);
            return 0;
        }
        else if (message.compareExact("ctrlAddKeyframe", true))
        {
            if (6 != params_count)
            {
                TxtParsingNode_ErrorArgCount(result_msg, "ctrlAddKeyframe", 6);
                return 2;
            }

            /********************************/

            if (!params[0].checkType(TXT_PARSING_NODE_PROPTYPE_INTEGER))
            {
                TxtParsingNode_ErrorArgType(result_msg, "ctrlAddKeyframe", 1, TXT_PARSING_NODE_PROPTYPE_INTEGER);
                return 2;
            }

            params[0].getValue(&(test[3]));

            /********************************/

            if (params[1].checkType(TXT_PARSING_NODE_PROPTYPE_INTEGER))
            {
                params[1].getValue(&(test[0]));
                dummy_floats[4] = (float)test[0];
            }
            else if (params[1].checkType(TXT_PARSING_NODE_PROPTYPE_FLOAT1))
            {
                params[1].getValue(&(dummy_floats[4]));
            }
            else
            {
                TxtParsingNode_ErrorArgType(result_msg, "ctrlAddKeyframe", 2, TXT_PARSING_NODE_PROPTYPE_FLOAT1);
                return 2;
            }

            /********************************/

            if (!params[2].checkType(TXT_PARSING_NODE_PROPTYPE_FLOAT3))
            {
                TxtParsingNode_ErrorArgType(result_msg, "ctrlAddKeyframe", 3, TXT_PARSING_NODE_PROPTYPE_FLOAT3);
                return 2;
            }

            params[2].getValue(dummy_floats);
            dummy_srp.pos.x = dummy_floats[0];
            dummy_srp.pos.y = dummy_floats[1];
            dummy_srp.pos.z = dummy_floats[2];

            /********************************/

            if (params[3].checkType(TXT_PARSING_NODE_PROPTYPE_FLOAT3))
            {
                params[3].getValue(dummy_floats);

                dummy_floats[0] = DEG2RAD_F(dummy_floats[0]);
                dummy_floats[1] = DEG2RAD_F(dummy_floats[1]);
                dummy_floats[2] = DEG2RAD_F(dummy_floats[2]);

                dummy_srp.rot.fromEulerAngles(true, dummy_floats[0], dummy_floats[1], dummy_floats[2]);
            }
            else if (params[3].checkType(TXT_PARSING_NODE_PROPTYPE_FLOAT4))
            {
                params[3].getValue(dummy_floats);

                dummy_srp.rot.x = dummy_floats[0];
                dummy_srp.rot.y = dummy_floats[1];
                dummy_srp.rot.z = dummy_floats[2];
                dummy_srp.rot.w = dummy_floats[3];

                dummy_srp.rot.normalize();
            }
            else
            {
                TxtParsingNode_ErrorArgType(result_msg, "ctrlAddKeyframe", 4, TXT_PARSING_NODE_PROPTYPE_FLOAT4);
                return 2;
            }

            /********************************/

            if (params[4].checkType(TXT_PARSING_NODE_PROPTYPE_INTEGER))
            {
                params[4].getValue(&(test[0]));
                dummy_srp.scale = (float)test[0];
            }
            else if (params[4].checkType(TXT_PARSING_NODE_PROPTYPE_FLOAT1))
            {
                params[4].getValue(&(dummy_srp.scale));
            }
            else
            {
                TxtParsingNode_ErrorArgType(result_msg, "ctrlAddKeyframe", 5, TXT_PARSING_NODE_PROPTYPE_FLOAT1);
                return 2;
            }

            /********************************/

            if (!params[5].checkType(TXT_PARSING_NODE_PROPTYPE_INTEGER))
            {
                TxtParsingNode_ErrorArgType(result_msg, "ctrlAddKeyframe", 6, TXT_PARSING_NODE_PROPTYPE_INTEGER);
                return 2;
            }

            params[5].getValue(&(test[0]));

            /********************************/

            ctrlAddKeyframe(test[3], dummy_floats[4], dummy_srp, test[0]);
            return 0;
        }

        return 1;
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

        getTransposedMatrices(defaultTransform);
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
            else if (false == ctrl->getType()->checkHierarchy(&E_MULTICTRL_ESRP_TYPEINFO))
            {
                multi_ctrl = new eMultiCtrl<eSRP>;

                multi_ctrl->multiCtrl_SetSize(1 + anim_id);
                multi_ctrl->multiCtrl_SetTrack(anim_id, ctrl);

                ctrl->decRef();
                ctrl = multi_ctrl;
                ctrl->incRef();
            }
            else
            {
                ((eMultiCtrl<eSRP>*)ctrl)->multiCtrl_SetSize(1 + anim_id);
            }

            ctrl->ctrlAddKeyframe(anim_id, new_time, new_data, param);
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
    // eTransform: set current matrix and create a matrix with no scaling
    ////////////////////////////////////////////////////////////////
    void eTransform::getTransposedMatrices(eSRP some_srp)
    {
        currentMatrix = some_srp.getMatrix();
        currentMatrix.transpose(transposedMatrix[0]);

        some_srp.scale = 1.0f;
        some_srp.getMatrix().transpose(transposedMatrix[1]);
    }

}
