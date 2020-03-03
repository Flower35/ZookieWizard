#include <kao2engine/eBoxZone.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eBoxZone interface
    // <kao2.0049DF30> (constructor)
    // <kao2.0049E010> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_BOXZONE_TYPEINFO
    (
        E_BOXZONE_ID,
        "eBoxZone",
        &E_ZONE_TYPEINFO,
        []() -> eObject*
        {
            return new eBoxZone;
        }
    );

    TypeInfo* eBoxZone::getType() const
    {
        return &E_BOXZONE_TYPEINFO;
    }

    eBoxZone::eBoxZone()
    : eZone()
    {}

    eBoxZone::~eBoxZone() {}


    ////////////////////////////////////////////////////////////////
    // eBoxZone serialization
    // <kao2.0049E290>
    ////////////////////////////////////////////////////////////////
    void eBoxZone::serialize(Archive &ar)
    {
        eZone::serialize(ar);

        boxBoundMin.serialize(ar);
        boxBoundMax.serialize(ar);
    }


    ////////////////////////////////////////////////////////////////
    // eBoxZone: (editor option) find object in 3D space
    ////////////////////////////////////////////////////////////////
    ePoint3 eBoxZone::editingGetCenterPoint() const
    {
        return (boxBoundMax - boxBoundMin) * 0.5f;
    }


    ////////////////////////////////////////////////////////////////
    // eBoxZone: (editor option) apply new transformation
    ////////////////////////////////////////////////////////////////
    void eBoxZone::editingApplyNewTransform(eSRP &new_transform, int32_t marked_id)
    {
        ePoint4 test_point;
        eMatrix4x4 matrix = new_transform.getMatrix();

        test_point = {boxBoundMin.x, boxBoundMin.y, boxBoundMin.z, 1.0f};
        test_point = matrix * test_point;
        boxBoundMin = {test_point.x, test_point.y, test_point.z};

        test_point = {boxBoundMax.x, boxBoundMax.y, boxBoundMax.z, 1.0f};
        test_point = matrix * test_point;
        boxBoundMax = {test_point.x, test_point.y, test_point.z};
    }


    ////////////////////////////////////////////////////////////////
    // eBoxZone: render
    ////////////////////////////////////////////////////////////////
    bool eBoxZone::renderObject(int32_t draw_flags, eAnimate* anim, eSRP &parent_srp, int32_t marked_id)
    {
        bool is_selected_or_marked;

        /* Inactive color (red) */
        float color[3] = {1.0f, 0, 0};

        if (GUI::drawFlags::DRAW_FLAG_BOXZONES & draw_flags)
        {
            if (false == eNode::renderObject(draw_flags, anim, parent_srp, marked_id))
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

            if ((GUI::drawFlags::DRAW_FLAG_OUTLINE & draw_flags) && (((-2) == marked_id) || ((-3) == marked_id)))
            {
                /* Active color */
                GUI::colorOfMarkedObject(color[0], color[1], color[2]);
            }

            GUI::renderBoundingBox
            (
                2.0f,
                color[0], color[1], color[2],
                boxBoundMin.x, boxBoundMin.y, boxBoundMin.z,
                boxBoundMax.x, boxBoundMax.y, boxBoundMax.z
            );

            if (is_selected_or_marked)
            {
                glPopMatrix();
            }
        }

        return true;
    }

}
