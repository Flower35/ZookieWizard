#include <kao2engine/eObjectChain.h>
#include <kao2ar/Archive.h>

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

    TypeInfo* eObjectChain::getType()
    {
        return &E_OBJECTCHAIN_TYPEINFO;
    }

    eObjectChain::eObjectChain()
    : Gadget()
    {}

    eObjectChain::~eObjectChain() {}

}
