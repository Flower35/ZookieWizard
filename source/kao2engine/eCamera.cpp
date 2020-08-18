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
        /*[0x01CC]*/ lookingAtCurrentFollowCamera = true;

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
        ar.readOrWrite(&lookingAtCurrentFollowCamera, 0x01);

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
        lookingAtCurrentFollowCamera = value;
    }

}
