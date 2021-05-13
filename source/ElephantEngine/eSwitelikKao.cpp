#include <ElephantEngine/eSwitelikKao.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSwitelikKao interface
    // <kao2.0044FB20> (constructor)
    // <kao2.0044FBB0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_SWITELIKKAO_TYPEINFO
    (
        E_SWITELIKKAO_ID,
        "eSwitelikKao",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eSwitelikKao;
        }
    );

    const TypeInfo* eSwitelikKao::getType() const
    {
        return &E_SWITELIKKAO_TYPEINFO;
    }

    eSwitelikKao::eSwitelikKao()
    : Gadget()
    {}

    eSwitelikKao::~eSwitelikKao()
    {}


    ////////////////////////////////////////////////////////////////
    // eSwitelikKao: cloning the object
    ////////////////////////////////////////////////////////////////

    void eSwitelikKao::createFromOtherObject(const eSwitelikKao &other)
    {}

    eSwitelikKao::eSwitelikKao(const eSwitelikKao &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eSwitelikKao& eSwitelikKao::operator = (const eSwitelikKao &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eSwitelikKao::cloneFromMe() const
    {
        return new eSwitelikKao(*this);
    }

}
