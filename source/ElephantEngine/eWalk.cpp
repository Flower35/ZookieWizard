#include <ElephantEngine/eWalk.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eWalk interface
    // <kao2.00425270> (constructor)
    // <kao2.004252F0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_WALK_TYPEINFO
    (
        E_WALK_ID,
        "eWalk",
        &E_PATHCTRL_TYPEINFO,
        []() -> eObject*
        {
            return new eWalk;
        }
    );

    TypeInfo* eWalk::getType() const
    {
        return &E_WALK_TYPEINFO;
    }

    eWalk::eWalk()
    : ePathCtrl()
    {}

    eWalk::~eWalk()
    {}


    ////////////////////////////////////////////////////////////////
    // eWalk: cloning the object
    ////////////////////////////////////////////////////////////////

    void eWalk::createFromOtherObject(const eWalk &other)
    {}

    eWalk::eWalk(const eWalk &other)
    : ePathCtrl(other)
    {
        createFromOtherObject(other);
    }

    eWalk& eWalk::operator = (const eWalk &other)
    {
        if ((&other) != this)
        {
            ePathCtrl::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eWalk::cloneFromMe() const
    {
        return new eWalk(*this);
    }

}
