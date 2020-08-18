#include <kao2engine/eLight.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eLight interface
    // <kao2.0047EB00> (constructor)
    // <kao2.0047EC90> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_LIGHT_TYPEINFO
    (
        E_LIGHT_ID,
        "eLight",
        &E_NODE_TYPEINFO,
        []() -> eObject*
        {
            return nullptr;
        }
    );

    TypeInfo* eLight::getType() const
    {
        return &E_LIGHT_TYPEINFO;
    }

    eLight::eLight()
    : eNode()
    {
        /*[0x3C-0x48]*/
        diffuse[0] = 1.0f;
        diffuse[1] = 1.0f;
        diffuse[2] = 1.0f;
        diffuse[3] = 1.0f;

        /*[0x4C-0x58]*/
        ambient[0] = 1.0f;
        ambient[1] = 1.0f;
        ambient[2] = 1.0f;
        ambient[3] = 1.0f;

        /*[0x5C-0x68]*/
        specular[0] = 0;
        specular[1] = 0;
        specular[2] = 0;
        specular[3] = 0;

        flags |= 0x40000000;
    }

    eLight::~eLight() {}


    ////////////////////////////////////////////////////////////////
    // eLight serialization
    // <kao2.0047ECD0>
    ////////////////////////////////////////////////////////////////
    void eLight::serialize(Archive &ar)
    {
        eNode::serialize(ar);

        /* "diffuse" params */
        ar.readOrWrite(&(diffuse[0]), 0x04);
        ar.readOrWrite(&(diffuse[1]), 0x04);
        ar.readOrWrite(&(diffuse[2]), 0x04);
        ar.readOrWrite(&(diffuse[3]), 0x04);

        /* "ambient" params */
        ar.readOrWrite(&(ambient[0]), 0x04);
        ar.readOrWrite(&(ambient[1]), 0x04);
        ar.readOrWrite(&(ambient[2]), 0x04);
        ar.readOrWrite(&(ambient[3]), 0x04);

        /* "specular" params */
        ar.readOrWrite(&(specular[0]), 0x04);
        ar.readOrWrite(&(specular[1]), 0x04);
        ar.readOrWrite(&(specular[2]), 0x04);
        ar.readOrWrite(&(specular[3]), 0x04);

        if (ar.getVersion() < 0x79)
        {
            flags &= 0xCFFFFFFF;
            flags |= 0x40000000;
        }
    }


    ////////////////////////////////////////////////////////////////
    // eLight: set light source parameters
    // <kao2.0047EDB0>
    ////////////////////////////////////////////////////////////////
    void eLight::useBasicLightParams(int32_t light_id) const
    {
        GLenum light_enum = GL_LIGHT0 + light_id;

        glLightfv(light_enum, GL_DIFFUSE, diffuse);
        glLightfv(light_enum, GL_AMBIENT, ambient);
        glLightfv(light_enum, GL_SPECULAR, specular);
    }


    ////////////////////////////////////////////////////////////////
    // eLight: color getters and setters
    ////////////////////////////////////////////////////////////////

    void eLight::getDiffuseColor(float* values) const
    {
        values[0] = diffuse[0];
        values[1] = diffuse[1];
        values[2] = diffuse[2];
    }

    void eLight::getAmbientColor(float* values) const
    {
        values[0] = ambient[0];
        values[1] = ambient[1];
        values[2] = ambient[2];
    }

    void eLight::getSpecularColor(float* values) const
    {
        values[0] = specular[0];
        values[1] = specular[1];
        values[2] = specular[2];
    }

    void eLight::setDiffuseColor(float* values)
    {
        diffuse[0] = values[0];
        diffuse[1] = values[1];
        diffuse[2] = values[2];
        diffuse[3] = 1.0f;
    }

    void eLight::setAmbientColor(float* values)
    {
        ambient[0] = values[0];
        ambient[1] = values[1];
        ambient[2] = values[2];
        ambient[3] = 1.0f;
    }

    void eLight::setSpecularColor(float* values)
    {
        specular[0] = values[0];
        specular[1] = values[1];
        specular[2] = values[2];
        specular[3] = 1.0f;
    }

}
