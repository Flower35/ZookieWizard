#include <ElephantEngine/eBubbleFlakes.h>
#include <ElephantBase/Archive.h>

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

    eBubbleFlakes::~eBubbleFlakes()
    {}


    ////////////////////////////////////////////////////////////////
    // eBubbleFlakes: cloning the object
    ////////////////////////////////////////////////////////////////

    void eBubbleFlakes::createFromOtherObject(const eBubbleFlakes &other)
    {}

    eBubbleFlakes::eBubbleFlakes(const eBubbleFlakes &other)
    : eForrestFlakes(other)
    {
        createFromOtherObject(other);
    }

    eBubbleFlakes& eBubbleFlakes::operator = (const eBubbleFlakes &other)
    {
        if ((&other) != this)
        {
            eForrestFlakes::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eBubbleFlakes::cloneFromMe() const
    {
        return new eBubbleFlakes(*this);
    }

}
