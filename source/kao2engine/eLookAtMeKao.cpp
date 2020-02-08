#include <kao2engine/eLookAtMeKao.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eLookAtMeKao interface
    // <kao2.004DB9A1> (constructor)
    // <kao2.004DBA20> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_LOOKATMEKAO_TYPEINFO
    (
        E_LOOKATMEKAO_ID,
        "eLookAtMeKao",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eLookAtMeKao;
        }
    );

    TypeInfo* eLookAtMeKao::getType() const
    {
        return &E_LOOKATMEKAO_TYPEINFO;
    }

    eLookAtMeKao::eLookAtMeKao()
    : Gadget()
    {}

    eLookAtMeKao::~eLookAtMeKao() {}

}
