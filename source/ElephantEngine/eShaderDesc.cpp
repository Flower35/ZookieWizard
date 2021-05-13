#include <ElephantEngine/eShaderDesc.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eShaderDesc interface
    ////////////////////////////////////////////////////////////////

    eShaderDesc::eShaderDesc(eString _name, int32_t _params)
    : eRefCounter()
    {
        name   = _name;
        params = _params;
    }

    eShaderDesc::~eShaderDesc()
    {}


    ////////////////////////////////////////////////////////////////
    // eShaderDesc: cloning the object
    ////////////////////////////////////////////////////////////////

    void eShaderDesc::createFromOtherObject(const eShaderDesc &other)
    {
        name   = other.name;
        params = other.params;
    }

    eShaderDesc::eShaderDesc(const eShaderDesc &other)
    : eRefCounter(other)
    {
        createFromOtherObject(other);
    }

    eShaderDesc& eShaderDesc::operator = (const eShaderDesc &other)
    {
        if ((&other) != this)
        {
            eRefCounter::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eShaderDesc::cloneFromMe() const
    {
        return new eShaderDesc(*this);
    }


    ////////////////////////////////////////////////////////////////
    // eShaderDesc: get shader name
    ////////////////////////////////////////////////////////////////
    eString eShaderDesc::getStringRepresentation() const
    {
        return name;
    }


    ////////////////////////////////////////////////////////////////
    // eShaderDesc: get the number or parameters
    ////////////////////////////////////////////////////////////////
    int32_t eShaderDesc::getParamsCount() const
    {
        return params;
    }

}
