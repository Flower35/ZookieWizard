#include <kao2engine/eCamera.h>
#include <kao2ar/Archive.h>
#include <kao2ar/eDrawContext.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eCamera interface
    // <kao2.0050E1A0> (constructor)
    // <kao2.0050E450> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_CAMERA_TYPEINFO
    (
        E_CAMERA_ID,
        "eCamera",
        &E_OBSERVER_TYPEINFO,
        []() -> eObject*
        {
            return new eCamera;
        }
    );

    TypeInfo* eCamera::getType() const
    {
        return &E_CAMERA_TYPEINFO;
    }

    eCamera::eCamera()
    : eObserver()
    {
        /*[0x01CC]*/ followCurrentActor = true;

        /*[0x01D0]*/ camTarget = nullptr;

        /*[0x01D8-0x01E4]*/
        unknown_01D8[0] = 80.0f;
        unknown_01D8[1] = 600.0f;
        unknown_01D8[2] = 0;
        unknown_01D8[3] = 200.0f;

        unknown_additional_01 = nullptr;

        unknown_additional_02[0] = 1.0f;
        unknown_additional_02[1] = 1.0f;
    }

    eCamera::~eCamera()
    {
        unknown_additional_01->decRef();

        camTarget->decRef();
    }


    ////////////////////////////////////////////////////////////////
    // eCamera serialization
    // <kao2.0050EA80>
    ////////////////////////////////////////////////////////////////
    void eCamera::serialize(Archive &ar)
    {
        int32_t i;

        eObserver::serialize(ar);

        /* Camera target point */
        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&camTarget, &E_TRANSFORM_TYPEINFO);

        /* Empty object link */
        i = 0x01;
        ar.readOrWrite(&i, 0x04);
        if (0x01 != i)
        {
            throw ErrorMessage
            (
                "eCamera::serialize():\n" \
                "non-empty object is not supported!"
            );
        }

        /* [0x01DC] unknown (note: different order) */
        ar.readOrWrite(&(unknown_01D8[1]), 0x04);
        ar.readOrWrite(&(unknown_01D8[3]), 0x04);
        ar.readOrWrite(&(unknown_01D8[0]), 0x04);
        ar.readOrWrite(&(unknown_01D8[2]), 0x04);

        /* [0x01CC] Shold the camera look at the Actor with `eFollowCameraCtrl.makeCurrent()` */
        ar.readOrWrite(&followCurrentActor, 0x01);

        /* "Asterix & Obelix XXL 2: Mission Wifix" */
        if (ar.getVersion() >= 0x91)
        {
            throw ErrorMessage
            (
                "eCamera::serialize():\n" \
                "archve versions 145-147 ARE NOT SUPPORTED!"
            );

            ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&unknown_additional_01, &E_LEAFCTRL_FLOAT_TYPEINFO);

            for (i = 0; i < 2; i++)
            {
                ar.readOrWrite(&(unknown_additional_02[i]), 0x04);
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eCamera: render this node
    ////////////////////////////////////////////////////////////////
    void eCamera::renderNode(eDrawContext &draw_context) const
    {
        if (GUI::drawFlags::DRAW_FLAG_SPECIAL & draw_context.getDrawFlags())
        {
            /********************************/
            /* Apply Transformation */

            glPushMatrix();

            bool use_outline = draw_context.isNodeOutlined();

            if (draw_context.isNodeSelectedOrMarked())
            {
                GUI::multiplyBySelectedObjectTransform(true);
            }
            else
            {
                glMultMatrixf(transposedMatrix[1]);
            }

            /********************************/
            /* Draw helper camera */

            if (use_outline)
            {
                glColor3f(0, 1.0f, 0);
            }

            draw_context.useMaterial(nullptr, 0);
            GUI::renderSpecialModel((!use_outline), ZOOKIEWIZARD_SPECIALMODEL_CAMERA);

            if (use_outline)
            {
                glColor3f(1.0f, 1.0f, 1.0f);
            }

            /********************************/
            /* Restore parent matrix (OpenGL) */

            glPopMatrix();
        }
    }


    ////////////////////////////////////////////////////////////////
    // eCamera: find reference to some node when deleting it
    ////////////////////////////////////////////////////////////////
    void eCamera::findAndDereference(eNode* target)
    {
        eNode* targets_parent;

        if (nullptr != camTarget)
        {
            targets_parent = camTarget->getParentNode();

            if (nullptr != targets_parent)
            {
                if ((targets_parent == target)
                  || (nullptr == targets_parent->getParentNode()))
                {
                    /* Is the target's parent invalid? (no longer has a valid parent) */

                    camTarget->setParentNode(nullptr);
                }
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eCamera: custom TXT parser methods
    ////////////////////////////////////////////////////////////////

    int32_t eCamera::parsingSetProperty(char* result_msg, const TxtParsingNodeProp &property)
    {
        int32_t test;
        float dummy_float;
        eString prop_name;
        eTransform* dummy_target;

        if (1 != (test = eObserver::parsingSetProperty(result_msg, property)))
        {
            return test;
        }

        prop_name = property.getName();

        if (prop_name.compareExact("followCurrentActor", true))
        {
            if (property.checkType(TXT_PARSING_NODE_PROPTYPE_INTEGER))
            {
                property.getValue(&test);
                followCurrentActor = (0 != test);
            }
            else if (property.checkType(TXT_PARSING_NODE_PROPTYPE_FLOAT1))
            {
                property.getValue(&dummy_float);
                followCurrentActor = (0 != dummy_float);
            }
            else
            {
                TxtParsingNode_ErrorPropType(result_msg, "followCurrentActor", TXT_PARSING_NODE_PROPTYPE_FLOAT1);
                return 2;
            }

            return 0;
        }
        else if (prop_name.compareExact("target", true))
        {
            if (!property.checkType(TXT_PARSING_NODE_PROPTYPE_NODEREF))
            {
                TxtParsingNode_ErrorPropType(result_msg, "target", TXT_PARSING_NODE_PROPTYPE_NODEREF);
                return 2;
            }

            property.getValue(&dummy_target);

            if (nullptr == dummy_target)
            {
                sprintf_s(result_msg, LARGE_BUFFER_SIZE, "Noderef for \"target\" property is not set!");
                return 2;
            }

            if (!(dummy_target->getType()->checkHierarchy(&E_TRANSFORM_TYPEINFO)))
            {
                sprintf_s(result_msg, LARGE_BUFFER_SIZE, "Expected the noderef of \"target\" property to be a \"eTransform\" or its child!");
                return 2;
            }

            setCameraTarget(dummy_target);
            return 0;
        }

        return 1;
    }

    int32_t eCamera::parsingCustomMessage(char* result_msg, const eString &message, int32_t params_count, const TxtParsingNodeProp* params)
    {
        int32_t test;
        float dummy_float;
        eTransform* dummy_target;

        if (1 != (test = eObserver::parsingCustomMessage(result_msg, message, params_count, params)))
        {
            return test;
        }

        if (message.compareExact("followCurrentActor", true))
        {
            if (1 != params_count)
            {
                TxtParsingNode_ErrorArgCount(result_msg, "followCurrentActor", 1);
                return 2;
            }

            /********************************/

            if (params[0].checkType(TXT_PARSING_NODE_PROPTYPE_INTEGER))
            {
                params[0].getValue(&test);
                followCurrentActor = (0 != test);
            }
            else if (params[0].checkType(TXT_PARSING_NODE_PROPTYPE_FLOAT1))
            {
                params[0].getValue(&dummy_float);
                followCurrentActor = (0 != dummy_float);
            }
            else
            {
                TxtParsingNode_ErrorArgType(result_msg, "followCurrentActor", 0, TXT_PARSING_NODE_PROPTYPE_FLOAT1);
                return 2;
            }

            return 0;
        }
        else if (message.compareExact("setTarget", true))
        {
            if (0 == params_count)
            {
                setCameraTarget(nullptr);
                return 0;
            }
            else if (1 != params_count)
            {
                TxtParsingNode_ErrorArgCount(result_msg, "setTarget", 1);
                return 2;
            }

            /********************************/

            if (!params[0].checkType(TXT_PARSING_NODE_PROPTYPE_NODEREF))
            {
                TxtParsingNode_ErrorArgType(result_msg, "setTarget", 0, TXT_PARSING_NODE_PROPTYPE_NODEREF);
                return 2;
            }

            /********************************/

            params[0].getValue(&dummy_target);

            if (nullptr == dummy_target)
            {
                sprintf_s(result_msg, LARGE_BUFFER_SIZE, "\"setTarget\" message: noderef is not set!");
                return 2;
            }

            if (!(dummy_target->getType()->checkHierarchy(&E_TRANSFORM_TYPEINFO)))
            {
                sprintf_s(result_msg, LARGE_BUFFER_SIZE, "\"setTarget\" message: expected the noderef to be a \"eTransform\" or its child!");
                return 2;
            }

            /********************************/

            setCameraTarget(dummy_target);
            return 0;
        }

        return 1;
    }


    ////////////////////////////////////////////////////////////////
    // eCamera: get or set the target point
    ////////////////////////////////////////////////////////////////

    eTransform* eCamera::getCameraTarget() const
    {
        return camTarget;
    }

    void eCamera::setCameraTarget(eTransform* new_target)
    {
        if (camTarget != new_target)
        {
            if (nullptr != camTarget)
            {
                camTarget->decRef();
            }

            camTarget = new_target;

            if (nullptr != camTarget)
            {
                camTarget->incRef();
            }
        }
    }

    void eCamera::setLookingAtFollowCamera(bool value)
    {
        followCurrentActor = value;
    }

}
