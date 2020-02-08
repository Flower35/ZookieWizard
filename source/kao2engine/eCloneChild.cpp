#include <kao2engine/eCloneChild.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eCloneChild interface
    // <kao2.005A50C0> (constructor)
    // <kao2.005A5150> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_CLONECHILD_TYPEINFO
    (
        E_CLONECHILD_ID,
        "eCloneChild",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eCloneChild;
        }
    );

    TypeInfo* eCloneChild::getType() const
    {
        return &E_CLONECHILD_TYPEINFO;
    }

    eCloneChild::eCloneChild()
    : Gadget()
    {}

    eCloneChild::~eCloneChild() {}

}
