#include <kao2engine/eOmniLight.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eOmniLight interface
    // <kao2.0047F130> (constructor)
    // <kao2.0047F220> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_OMNILIGHT_TYPEINFO
    (
        E_OMNILIGHT_ID,
        "eOmniLight",
        &E_LIGHT_TYPEINFO,
        []() -> eObject*
        {
            return new eOmniLight;
        }
    );

    TypeInfo* eOmniLight::getType() const
    {
        return &E_OMNILIGHT_TYPEINFO;
    }

    eOmniLight::eOmniLight()
    : eLight()
    {
        /*[0x78]*/ attenuationConstant = 1.0f;
        /*[0x7C]*/ attenuationLinear = 0;
        /*[0x80]*/ attenuationQuadratic = 0;
    }

    eOmniLight::~eOmniLight() {}


    ////////////////////////////////////////////////////////////////
    // eOmniLight serialization
    // <kao2.0047F510>
    ////////////////////////////////////////////////////////////////
    void eOmniLight::serialize(Archive &ar)
    {
        eLight::serialize(ar);

        position.serialize(ar);

        ar.readOrWrite(&attenuationConstant, 0x04);
        ar.readOrWrite(&attenuationLinear, 0x04);
        ar.readOrWrite(&attenuationQuadratic, 0x04);
    }


    ////////////////////////////////////////////////////////////////
    // eOmniLight: render light (source position)
    ////////////////////////////////////////////////////////////////
    bool eOmniLight::renderObject(int32_t draw_flags, eAnimate* anim, eSRP &parent_srp, eMatrix4x4 &parent_matrix, int32_t marked_id)
    {
        bool is_selected_or_marked;
        bool use_outline;

        if (GUI::drawFlags::DRAW_FLAG_SPECIAL & draw_flags)
        {
            if (false == eNode::renderObject(draw_flags, anim, parent_srp, parent_matrix, marked_id))
            {
                return false;
            }

            is_selected_or_marked = (((-2) == marked_id) || ((-1) == marked_id));
            use_outline = ((GUI::drawFlags::DRAW_FLAG_OUTLINE & draw_flags) && (((-2) == marked_id) || ((-3) == marked_id)));

            /****************/

            glPushMatrix();

            if (is_selected_or_marked)
            {
                /* This object is selected (-1) or marked (-2) and can be moved around */
                GUI::multiplyBySelectedObjectTransform();
            }

            glTranslatef(position.x, position.y, position.z);

            /****************/

            if (use_outline)
            {
                glColor3f(0, 1.0f, 0);
            }
            else
            {
                glColor3f(diffuse[0], diffuse[1], diffuse[2]);
            }

            GUI::renderSpecialModel((!use_outline), ZOOKIEWIZARD_SPECIALMODEL_LIGHT);

            glColor3f(1.0f, 1.0f, 1.0f);

            glPopMatrix();
        }

        return true;
    }


    ////////////////////////////////////////////////////////////////
    // eOmniLight: (editor option) find object in 3D space
    ////////////////////////////////////////////////////////////////
    ePoint3 eOmniLight::editingGetCenterPoint() const
    {
        return position;
    }


    ////////////////////////////////////////////////////////////////
    // eOmniLight: (editor option) apply new transformation
    ////////////////////////////////////////////////////////////////
    void eOmniLight::editingApplyNewTransform(eSRP &new_transform, int32_t marked_id)
    {
        position = (new_transform.getMatrix() * ePoint4(position.x, position.y, position.z, 1.0f));
    }


    ////////////////////////////////////////////////////////////////
    // eOmniLight: get or set position
    ////////////////////////////////////////////////////////////////

    ePoint3 eOmniLight::getPosition() const
    {
        return position;
    }

    void eOmniLight::setPosition(ePoint3 &new_position)
    {
        position = new_position;
    }

}
