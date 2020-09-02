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
    // eDirectionalLight: custom TXT parser methods
    ////////////////////////////////////////////////////////////////

    int32_t eDirectionalLight::parsingSetProperty(char* result_msg, const TxtParsingNodeProp &property)
    {
        int32_t test;
        float dummy_floats[3];
        eString prop_name;
        eTransform* dummy_target;

        if (1 != (test = eLight::parsingSetProperty(result_msg, property)))
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

            position.x = dummy_floats[0];
            position.y = dummy_floats[1];
            position.z = dummy_floats[2];
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

            setLightTarget(dummy_target);
            return 0;
        }

        return 1;
    }

    int32_t eDirectionalLight::parsingCustomMessage(char* result_msg, const eString &message, int32_t params_count, const TxtParsingNodeProp* params)
    {
        int32_t test;
        float dummy_floats[3];
        eTransform* dummy_target;

        if (1 != (test = eLight::parsingCustomMessage(result_msg, message, params_count, params)))
        {
            return test;
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

            /********************************/

            position.x = dummy_floats[0];
            position.y = dummy_floats[1];
            position.z = dummy_floats[2];
            return 0;
        }
        else if (message.compareExact("setTarget", true))
        {
            if (0 == params_count)
            {
                setLightTarget(nullptr);
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

            setLightTarget(dummy_target);
            return 0;
        }

        return 1;
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
