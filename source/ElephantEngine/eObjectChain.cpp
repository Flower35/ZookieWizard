#include <ElephantEngine/eObjectChain.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eObjectChain interface
    // <kao2.00526022> (constructor)
    // <kao2.005260E0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_OBJECTCHAIN_TYPEINFO
    (
        E_OBJECTCHAIN_ID,
        "eObjectChain",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eObjectChain;
        }
    );

    TypeInfo* eObjectChain::getType() const
    {
        return &E_OBJECTCHAIN_TYPEINFO;
    }

    eObjectChain::eObjectChain()
    : Gadget()
    {}

    eObjectChain::~eObjectChain()
    {}


    ////////////////////////////////////////////////////////////////
    // eObjectChain: cloning the object
    ////////////////////////////////////////////////////////////////

    void eObjectChain::createFromOtherObject(const eObjectChain &other)
    {}

    eObjectChain::eObjectChain(const eObjectChain &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eObjectChain& eObjectChain::operator = (const eObjectChain &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eObjectChain::cloneFromMe() const
    {
        return new eObjectChain(*this);
    }

}
