#include <kao2engine/eBubbleFlakes.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eBubbleFlakes interface
    // <kao2.00565E60> (constructor)
    // <kao2.00565F20> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_BUBBLEFLAKES_TYPEINFO
    (
        E_BUBBLEFLAKES_ID,
        "eBubbleFlakes",
        &E_FORRESTFLAKES_TYPEINFO,
        []() -> eObject*
        {
            return new eBubbleFlakes;
        }
    );

    TypeInfo* eBubbleFlakes::getType() const
    {
        return &E_BUBBLEFLAKES_TYPEINFO;
    }

    eBubbleFlakes::eBubbleFlakes()
    : eForrestFlakes()
    {}

    eBubbleFlakes::~eBubbleFlakes() {}

}
