#include <ElephantEngine/eShaderData.h>
#include <ElephantBase/Archive.h>

#include <ElephantEngine/eShaderDesc.h>
#include <ElephantBase/StaticPool.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eShaderParam: constructor and destructor
    ////////////////////////////////////////////////////////////////

    eShaderParam::eShaderParam()
    {
        paramType = 0;

        boolParam     = false;
        intParam      = 0;
        floatParam[0] = 0;
        floatParam[1] = 0;
        floatParam[2] = 0;
        floatParam[3] = 0;
    }

    eShaderParam::~eShaderParam()
    {}


    ////////////////////////////////////////////////////////////////
    // eShaderParam: copying the object
    ////////////////////////////////////////////////////////////////

    void eShaderParam::createFromOtherObject(const eShaderParam &other)
    {
        paramName = other.paramName;
        paramType = other.paramType;

        boolParam     = other.boolParam;
        intParam      = other.intParam;
        floatParam[0] = other.floatParam[0];
        floatParam[1] = other.floatParam[1];
        floatParam[2] = other.floatParam[2];
        floatParam[3] = other.floatParam[3];
    }

    eShaderParam::eShaderParam(const eShaderParam &other)
    {
        createFromOtherObject(other);
    }

    eShaderParam& eShaderParam::operator = (const eShaderParam &other)
    {
        if ((&other) != this)
        {
            createFromOtherObject(other);
        }

        return (eShaderParam&)(*this);
    }


    ////////////////////////////////////////////////////////////////
    // eShaderParam: serialization
    ////////////////////////////////////////////////////////////////
    void eShaderParam::serialize(Archive &ar)
    {
        void* data_ptr;
        int32_t data_size;

        ar.serializeString(paramName);
        ar.readOrWrite(&paramType, 0x04);

        switch (paramType)
        {
            case 0:  // "bool"
            {
                data_ptr  = &boolParam;
                data_size = 0x01;
                break;
            }

            case 1:  // "int"
            {
                data_ptr  = &intParam;
                data_size = 0x04;
                break;
            }

            case 2:  // "float"
            {
                data_ptr  = &(floatParam[0]);
                data_size = 0x04;
                break;
            }

            case 3:  // "float4"
            case 4:  // "color4f"
            {
                data_ptr  = floatParam;
                data_size = 0x10;
                break;
            }

            default:
            {
                throw ErrorMessage
                (
                    "eShaderData::serialize():\n" \
                    "Unknown ShaderParamType: '%s' - [%i].",
                    paramName.getText(),
                    paramType
                );
            }
        }

        ar.readOrWrite(data_ptr, data_size);
    }


    ////////////////////////////////////////////////////////////////
    // eShaderData interface
    // <SaddleClub.005AD830> (constructor)
    // <SaddleClub.005AD890> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_SHADERDATA_TYPEINFO
    (
        E_SHADERDATA_ID,
        "eShaderData",
        &E_REFCOUNTER_TYPEINFO,
        []() -> eObject*
        {
            return new eShaderData();
        }
    );

    const TypeInfo* eShaderData::getType() const
    {
        return &E_SHADERDATA_TYPEINFO;
    }

    eShaderData::eShaderData()
    : eRefCounter()
    {
        /*[0x08]*/ shaderDescription = nullptr;
        /*[0x0C]*/ shaderParameters = nullptr;
    }

    eShaderData::~eShaderData()
    {
        if (nullptr != shaderParameters)
        {
            delete[](shaderParameters);
        }

        shaderDescription->decRef();
    }


    ////////////////////////////////////////////////////////////////
    // eShaderData: cloning the object
    ////////////////////////////////////////////////////////////////

    void eShaderData::createFromOtherObject(const eShaderData &other)
    {
        int32_t a, b = 0;

        if (nullptr != other.shaderDescription)
        {
            shaderDescription = other.shaderDescription;
            shaderDescription->incRef();

            b = shaderDescription->getParamsCount();
        }
        else
        {
            shaderDescription = nullptr;
        }

        if (0 != b)
        {
            shaderParameters = new eShaderParam [b];

            if (nullptr != other.shaderParameters)
            {
                for (a = 0; a < b; a++)
                {
                    shaderParameters[a] = other.shaderParameters[a];
                }
            }
        }
        else
        {
            shaderParameters = nullptr;
        }
    }

    eShaderData::eShaderData(const eShaderData &other)
    : eRefCounter(other)
    {
        createFromOtherObject(other);
    }

    eShaderData& eShaderData::operator = (const eShaderData &other)
    {
        if ((&other) != this)
        {
            eRefCounter::operator = (other);

            /****************/

            shaderDescription->decRef();

            if (nullptr != shaderParameters)
            {
                delete[](shaderParameters);
            }

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eShaderData::cloneFromMe() const
    {
        return new eShaderData(*this);
    }


    ////////////////////////////////////////////////////////////////
    // eShaderData: serialization
    // <SaddleClub.005ADA60>
    ////////////////////////////////////////////////////////////////
    void eShaderData::serialize(Archive &ar)
    {
        int32_t a, current_params, shader_params;
        eString dummy_name;
        eShaderParam dummy_param;

        if (ar.isInReadMode())
        {
            ar.serializeString(dummy_name);
            ar.readOrWrite(&current_params, 0x04);

            shaderDescription->decRef();
            shaderDescription = theElephantStaticPool.getShaderDescription(dummy_name);
            shaderDescription->incRef();

            if (nullptr != shaderParameters)
            {
                delete[](shaderParameters);
                shaderParameters = nullptr;
            }

            if (0 != (shader_params = shaderDescription->getParamsCount()))
            {
                shaderParameters = new eShaderParam [shader_params];
            }

            for (a = 0; a < current_params; a++)
            {
                dummy_param.serialize(ar);

                if (a < shader_params)
                {
                    shaderParameters[a] = dummy_param;
                }
            }
        }
        else
        {
            if (nullptr == shaderDescription)
            {
                shaderDescription = theElephantStaticPool.getShaderDescription(dummy_name);
                shaderDescription->incRef();
            }

            dummy_name = shaderDescription->getStringRepresentation();
            shader_params = shaderDescription->getParamsCount();

            ar.serializeString(dummy_name);
            ar.readOrWrite(&shader_params, 0x04);

            for (a = 0; a < shader_params; a++)
            {
                shaderParameters[a].serialize(ar);
            }
        }
    }

}
