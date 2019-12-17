#include <kao2engine/eOMB.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eOMB interface
    // <kao2.005684E4> (constructor)
    // <kao2.00568F60> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_OMB_TYPEINFO
    (
        E_OMB_ID,
        "eOMB",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eOMB;
        }
    );

    TypeInfo* eOMB::getType()
    {
        return &E_OMB_TYPEINFO;
    }

    eOMB::eOMB()
    : Gadget()
    {}

    eOMB::~eOMB() {}

}
