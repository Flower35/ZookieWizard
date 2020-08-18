#include <kao2engine/eDirectionalLight.h>
#include <kao2ar/Archive.h>
#include <kao2ar/eDrawContext.h>

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
    // eDirectionalLight: render this node (light source position)
    ////////////////////////////////////////////////////////////////
    void eDirectionalLight::renderNode(eDrawContext &draw_context) const
    {
        if (GUI::drawFlags::DRAW_FLAG_SPECIAL & draw_context.getDrawFlags())
        {
            bool is_selected_or_marked = draw_context.isNodeSelectedOrMarked();
            bool use_outline = draw_context.isNodeOutlined();

            /****************/

            glPushMatrix();

            if (is_selected_or_marked)
            {
                GUI::multiplyBySelectedObjectTransform(true);
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

            draw_context.useMaterial(nullptr, 0);
            GUI::renderSpecialModel((!use_outline), ZOOKIEWIZARD_SPECIALMODEL_LIGHT);

            glColor3f(1.0f, 1.0f, 1.0f);

            glPopMatrix();
        }
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
    // eDirectionalLight: binding function
    // [[vptr]+0x74] <kao2.0047F8D0>
    ////////////////////////////////////////////////////////////////
    void eDirectionalLight::bindLight(int32_t light_id) const
    {
        GLenum light_enum = GL_LIGHT0 + light_id;

        float dummy_floats[16];

        useBasicLightParams(light_id);

        if (nullptr != previousTransform)
        {
            glPushMatrix();

            if (false)
            {
                // (--dsp--) (...) `if (nullptr != target)`
            }
            else
            {
                previousTransform->getXForm(true).getMatrix().transpose(dummy_floats);

                glLoadMatrixf(dummy_floats);

                dummy_floats[0] = position.x;
                dummy_floats[1] = position.y;
                dummy_floats[2] = position.z;
                dummy_floats[3] = 0;

                glLightfv(light_enum, GL_POSITION, dummy_floats);
            }

            glPopMatrix();
        }
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
