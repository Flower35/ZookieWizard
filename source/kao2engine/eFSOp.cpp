#include <kao2engine/eFSOp.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eFSOp interface
    // <kao2.00559D90> (constructor)
    // <kao2.004CD8B0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_FSOP_TYPEINFO
    (
        E_FSOP_ID,
        "eFSOp",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return nullptr;
        }
    );

    TypeInfo* eFSOp::getType() const
    {
        return &E_FSOP_TYPEINFO;
    }

    eFSOp::eFSOp()
    : Gadget()
    {}

    eFSOp::~eFSOp() {}

}
