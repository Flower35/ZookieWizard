#include <ElephantEngine/eLookAtMeKao.h>
#include <ElephantBase/Archive.h>

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

    const TypeInfo* eLookAtMeKao::getType() const
    {
        return &E_LOOKATMEKAO_TYPEINFO;
    }

    eLookAtMeKao::eLookAtMeKao()
    : Gadget()
    {}

    eLookAtMeKao::~eLookAtMeKao()
    {}


    ////////////////////////////////////////////////////////////////
    // eLookAtMeKao: cloning the object
    ////////////////////////////////////////////////////////////////

    void eLookAtMeKao::createFromOtherObject(const eLookAtMeKao &other)
    {}

    eLookAtMeKao::eLookAtMeKao(const eLookAtMeKao &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eLookAtMeKao& eLookAtMeKao::operator = (const eLookAtMeKao &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eLookAtMeKao::cloneFromMe() const
    {
        return new eLookAtMeKao(*this);
    }

}
