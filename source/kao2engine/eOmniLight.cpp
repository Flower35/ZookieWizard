#include <kao2engine/eOmniLight.h>
#include <kao2ar/Archive.h>
#include <kao2ar/eDrawContext.h>

#include <kao2engine/eTransform.h>

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
    // eOmniLight: render this node (light source position)
    ////////////////////////////////////////////////////////////////
    void eOmniLight::renderNode(eDrawContext &draw_context) const
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
    // eOmniLight: binding function
    // [[vptr]+0x74] <kao2.0047F2C0>
    ////////////////////////////////////////////////////////////////
    void eOmniLight::bindLight(int32_t light_id) const
    {
        GLenum light_enum = GL_LIGHT0 + light_id;

        float dummy_floats[16];

        if (nullptr != previousTransform)
        {
            glPushMatrix();

            previousTransform->getXForm(true).getMatrix().transpose(dummy_floats);

            glLoadMatrixf(dummy_floats);

            dummy_floats[0] = position.x;
            dummy_floats[1] = position.y;
            dummy_floats[2] = position.z;
            dummy_floats[3] = 0;

            glLightfv(light_enum, GL_POSITION, dummy_floats);

            glLightf(light_enum, GL_CONSTANT_ATTENUATION, attenuationConstant);
            glLightf(light_enum, GL_LINEAR_ATTENUATION, attenuationLinear);
            glLightf(light_enum, GL_QUADRATIC_ATTENUATION, attenuationQuadratic);

            glPopMatrix();
        }
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
