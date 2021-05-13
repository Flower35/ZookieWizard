#include <ElephantEngine/eLight.h>
#include <ElephantBase/Archive.h>

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

        /*[0x1C]*/
        flags |= 0x40000000;
        flags &= (~0x00000400);
    }

    eLight::~eLight()
    {}


    ////////////////////////////////////////////////////////////////
    // eLight: cloning the object
    ////////////////////////////////////////////////////////////////

    void eLight::createFromOtherObject(const eLight &other)
    {
        diffuse[0] = other.diffuse[0];
        diffuse[1] = other.diffuse[1];
        diffuse[2] = other.diffuse[2];
        diffuse[3] = other.diffuse[3];

        ambient[0] = other.ambient[0];
        ambient[1] = other.ambient[1];
        ambient[2] = other.ambient[2];
        ambient[3] = other.ambient[3];

        specular[0] = other.specular[0];
        specular[1] = other.specular[1];
        specular[2] = other.specular[2];
        specular[3] = other.specular[3];
    }

    eLight::eLight(const eLight &other)
    : eNode(other)
    {
        createFromOtherObject(other);
    }

    eLight& eLight::operator = (const eLight &other)
    {
        if ((&other) != this)
        {
            eNode::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eLight::cloneFromMe() const
    {
        return nullptr;
    }


    ////////////////////////////////////////////////////////////////
    // eLight: serialization
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
    // eLight: export readable structure
    ////////////////////////////////////////////////////////////////
    void eLight::writeStructureToTextFile(FileOperator &file, int32_t indentation, bool group_written) const
    {
        char bufor[128];
        const float* color_values[3] = {diffuse, ambient, specular};
        const char* color_names[3] = {"diffuse", "ambient", "specular"};

        /* "eNode": parent class */

        eNode::writeStructureToTextFile(file, indentation, true);

        /* "eLight": additional info */

        for (int32_t a = 0; a < 3; a++)
        {
            sprintf_s
            (
                bufor, 128,
                " - %s color: (%.6f, %.6f, %.6f, %.6f)",
                color_names[a],
                color_values[a][0],
                color_values[a][1],
                color_values[a][2],
                color_values[a][3]
            );

            ArFunctions::writeIndentation(file, indentation);
            file << bufor;
            ArFunctions::writeNewLine(file, 0);
        }
    }


    ////////////////////////////////////////////////////////////////
    // eLight: custom TXT parser methods
    ////////////////////////////////////////////////////////////////

    int32_t eLight::parsingSetProperty(char* result_msg, const TxtParsingNodeProp &property)
    {
        int32_t test;
        float dummy_floats[3];
        eString prop_name;

        if (1 != (test = eNode::parsingSetProperty(result_msg, property)))
        {
            return test;
        }

        prop_name = property.getName();

        if (prop_name.compareExact("diffuseColor", true))
        {
            if (!property.checkType(TXT_PARSING_NODE_PROPTYPE_FLOAT3))
            {
                TxtParsingNode_ErrorPropType(result_msg, "diffuseColor", TXT_PARSING_NODE_PROPTYPE_FLOAT3);
                return 2;
            }

            property.getValue(dummy_floats);

            setDiffuseColor(dummy_floats);
            return 0;
        }
        else if (prop_name.compareExact("ambientColor", true))
        {
            if (!property.checkType(TXT_PARSING_NODE_PROPTYPE_FLOAT3))
            {
                TxtParsingNode_ErrorPropType(result_msg, "ambientColor", TXT_PARSING_NODE_PROPTYPE_FLOAT3);
                return 2;
            }

            property.getValue(dummy_floats);

            setAmbientColor(dummy_floats);
            return 0;
        }
        else if (prop_name.compareExact("specularColor", true))
        {
            if (!property.checkType(TXT_PARSING_NODE_PROPTYPE_FLOAT3))
            {
                TxtParsingNode_ErrorPropType(result_msg, "specularColor", TXT_PARSING_NODE_PROPTYPE_FLOAT3);
                return 2;
            }

            property.getValue(dummy_floats);

            setSpecularColor(dummy_floats);
            return 0;
        }

        return 1;
    }

    int32_t eLight::parsingCustomMessage(char* result_msg, const eString &message, int32_t params_count, const TxtParsingNodeProp* params)
    {
        int32_t test;
        float dummy_floats[3];

        if (1 != (test = eNode::parsingCustomMessage(result_msg, message, params_count, params)))
        {
            return test;
        }

        if (message.compareExact("setDiffuseColor", true))
        {
            if (1 != params_count)
            {
                TxtParsingNode_ErrorArgCount(result_msg, "setDiffuseColor", 1);
                return 2;
            }

            /********************************/

            if (!params[0].checkType(TXT_PARSING_NODE_PROPTYPE_FLOAT3))
            {
                TxtParsingNode_ErrorArgType(result_msg, "setDiffuseColor", 0, TXT_PARSING_NODE_PROPTYPE_FLOAT3);
                return 2;
            }

            params[0].getValue(dummy_floats);

            /********************************/

            setDiffuseColor(dummy_floats);
            return 0;
        }
        else if (message.compareExact("setAmbientColor", true))
        {
            if (1 != params_count)
            {
                TxtParsingNode_ErrorArgCount(result_msg, "setAmbientColor", 1);
                return 2;
            }

            /********************************/

            if (!params[0].checkType(TXT_PARSING_NODE_PROPTYPE_FLOAT3))
            {
                TxtParsingNode_ErrorArgType(result_msg, "setAmbientColor", 0, TXT_PARSING_NODE_PROPTYPE_FLOAT3);
                return 2;
            }

            params[0].getValue(dummy_floats);

            /********************************/

            setAmbientColor(dummy_floats);
            return 0;
        }
        else if (message.compareExact("setSpecularColor", true))
        {
            if (1 != params_count)
            {
                TxtParsingNode_ErrorArgCount(result_msg, "setSpecularColor", 1);
                return 2;
            }

            /********************************/

            if (!params[0].checkType(TXT_PARSING_NODE_PROPTYPE_FLOAT3))
            {
                TxtParsingNode_ErrorArgType(result_msg, "setSpecularColor", 0, TXT_PARSING_NODE_PROPTYPE_FLOAT3);
                return 2;
            }

            params[0].getValue(dummy_floats);

            /********************************/

            setSpecularColor(dummy_floats);
            return 0;
        }

        return 1;
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

}
