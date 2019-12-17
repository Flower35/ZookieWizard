#include <kao2engine/eWalkWPF.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eWalkWPF interface
    // <kao2.00425784> (constructor)
    // <kao2.00425800> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_WALKWPF_TYPEINFO
    (
        E_WALKWPF_ID,
        "eWalkWPF",
        &E_WALK_TYPEINFO,
        []() -> eObject*
        {
            return new eWalkWPF;
        }
    );

    TypeInfo* eWalkWPF::getType()
    {
        return &E_WALKWPF_TYPEINFO;
    }

    eWalkWPF::eWalkWPF()
    : eWalk()
    {}

    eWalkWPF::~eWalkWPF() {}

}
