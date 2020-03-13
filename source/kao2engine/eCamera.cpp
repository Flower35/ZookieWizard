#include <kao2engine/eCamera.h>
#include <kao2ar/Archive.h>

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
        /*[0x01CC]*/ unknown_01CC = 0x01;

        /*[0x01D0]*/ camTarget = nullptr;

        /*[0x01D8-0x01E4]*/
        unknown_01D8[0] = 80.0f;
        unknown_01D8[1] = 600.0f;
        unknown_01D8[2] = 0;
        unknown_01D8[3] = 200.0f;
    }

    eCamera::~eCamera()
    {
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

        /* [0x01CC] unknown */
        ar.readOrWrite(&unknown_01CC, 0x01);
    }


    ////////////////////////////////////////////////////////////////
    // eCamera: render
    ////////////////////////////////////////////////////////////////
    bool eCamera::renderObject(int32_t draw_flags, eAnimate* anim, eSRP &parent_srp, int32_t marked_id)
    {
        bool is_selected_or_marked;

        /* Inactive color (white) */
        float color[3] = {1.0f, 1.0f, 1.0f};

        eSRP rendered_srp;
        float test_matrix[16];

        if (GUI::drawFlags::DRAW_FLAG_SPECIAL & draw_flags)
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

            if (false == is_selected_or_marked)
            {
                rendered_srp.getMatrix().transpose(test_matrix);
                glPushMatrix();
                glMultMatrixf(test_matrix);
            }

            glColor3f(color[0], color[1], color[2]);
            GUI::renderSpecialModel(ZOOKIEWIZARD_SPECIALMODEL_CAMERA);
            glColor3f(1.0f, 1.0f, 1.0f);

            glPopMatrix();
        }

        return true;
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

}
