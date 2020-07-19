#include <kao2engine/eDirectionalLight.h>
#include <kao2ar/Archive.h>

#include <kao2engine/eTransform.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eDirectionalLight interface
    // <kao2.0047F660> (constructor)
    // <kao2.0047F750> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_DIRECTIONALLIGHT_TYPEINFO
    (
        E_DIRECTIONALLIGHT_ID,
        "eDirectionalLight",
        &E_LIGHT_TYPEINFO,
        []() -> eObject*
        {
            return new eDirectionalLight;
        }
    );

    TypeInfo* eDirectionalLight::getType() const
    {
        return &E_DIRECTIONALLIGHT_TYPEINFO;
    }

    eDirectionalLight::eDirectionalLight()
    : eLight()
    {
        /*[0x6C-0x74]*/
        position.x = 1.0f;

        /*[0x78]*/ target = nullptr;
    }

    eDirectionalLight::~eDirectionalLight()
    {
        target->decRef();
    }


    ////////////////////////////////////////////////////////////////
    // eDirectionalLight serialization
    // <kao2.0047FBC0>
    ////////////////////////////////////////////////////////////////
    void eDirectionalLight::serialize(Archive &ar)
    {
        eLight::serialize(ar);

        position.serialize(ar);

        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&target, &E_TRANSFORM_TYPEINFO);
    }


    ////////////////////////////////////////////////////////////////
    // eDirectionalLight: render light (source position)
    ////////////////////////////////////////////////////////////////
    bool eDirectionalLight::renderObject(int32_t draw_flags, eAnimate* anim, eSRP &parent_srp, eMatrix4x4 &parent_matrix, int32_t marked_id)
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
    // eDirectionalLight: (editor option) find object in 3D space
    ////////////////////////////////////////////////////////////////
    ePoint3 eDirectionalLight::editingGetCenterPoint() const
    {
        return position;
    }


    ////////////////////////////////////////////////////////////////
    // eDirectionalLight: (editor option) apply new transformation
    ////////////////////////////////////////////////////////////////
    void eDirectionalLight::editingApplyNewTransform(eSRP &new_transform, int32_t marked_id)
    {
        position = (new_transform.getMatrix() * ePoint4(position.x, position.y, position.z, 1.0f));
    }


    ////////////////////////////////////////////////////////////////
    // eDirectionalLight: get or set position
    ////////////////////////////////////////////////////////////////

    ePoint3 eDirectionalLight::getPosition() const
    {
        return position;
    }

    void eDirectionalLight::setPosition(ePoint3 &new_position)
    {
        position = new_position;
    }

    ////////////////////////////////////////////////////////////////
    // eDirectionalLight: get or set target point
    ////////////////////////////////////////////////////////////////

    eTransform* eDirectionalLight::getLightTarget() const
    {
        return target;
    }

    void eDirectionalLight::setLightTarget(eTransform* new_target)
    {
        if (nullptr != target)
        {
            target->decRef();
        }

        target = new_target;

        if (nullptr != target)
        {
            target->incRef();
        }
    }

}
