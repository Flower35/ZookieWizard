#include <kao2engine/eFSMB.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eFSMB interface
    // <kao2.0055F9B0> (constructor)
    // <kao2.0055FA90> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_FSMB_TYPEINFO
    (
        E_FSMB_ID,
        "eFSMB",
        &E_FSOP_TYPEINFO,
        []() -> eObject*
        {
            return new eFSMB;
        }
    );

    TypeInfo* eFSMB::getType() const
    {
        return &E_FSMB_TYPEINFO;
    }

    eFSMB::eFSMB()
    : eFSOp()
    {
        name = "fsmb";
    }

    eFSMB::~eFSMB() {}


    ////////////////////////////////////////////////////////////////
    // Static Gadget
    ////////////////////////////////////////////////////////////////

    eFSMB theFSMB;

}
