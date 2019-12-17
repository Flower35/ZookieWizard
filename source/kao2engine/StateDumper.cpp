#include <kao2engine/StateDumper.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // StateDumper interface
    // <kao2.005AFFB1> (constructor)
    // <kao2.005B0020> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_STATEDUMPER_TYPEINFO
    (
        E_STATEDUMPER_ID,
        "StateDumper",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new StateDumper;
        }
    );

    TypeInfo* StateDumper::getType()
    {
        return &E_STATEDUMPER_TYPEINFO;
    }

    StateDumper::StateDumper()
    : Gadget()
    {}

    StateDumper::~StateDumper() {}

}
