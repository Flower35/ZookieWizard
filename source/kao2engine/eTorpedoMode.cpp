#include <kao2engine/eTorpedoMode.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eTorpedoMode interface
    // <kao2.004CD106> (constructor)
    // <kao2.004CD8C0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_TORPEDOMODE_TYPEINFO
    (
        E_TORPEDOMODE_ID,
        "eTorpedoMode",
        &E_FSOP_TYPEINFO,
        []() -> eObject*
        {
            return new eTorpedoMode;
        }
    );

    TypeInfo* eTorpedoMode::getType()
    {
        return &E_TORPEDOMODE_TYPEINFO;
    }

    eTorpedoMode::eTorpedoMode()
    : eFSOp()
    {}

    eTorpedoMode::~eTorpedoMode() {}

}
