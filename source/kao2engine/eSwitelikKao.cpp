#include <kao2engine/eSwitelikKao.h>
#include <kao2ar/Archive.h>

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

    TypeInfo* eSwitelikKao::getType() const
    {
        return &E_SWITELIKKAO_TYPEINFO;
    }

    eSwitelikKao::eSwitelikKao()
    : Gadget()
    {}

    eSwitelikKao::~eSwitelikKao() {}

}
