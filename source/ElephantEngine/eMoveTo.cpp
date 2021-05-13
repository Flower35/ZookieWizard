#include <ElephantEngine/eMoveTo.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eMoveTo interface
    // <kao2.0051F8D0> (constructor)
    // <kao2.0051F950> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_MOVETO_TYPEINFO
    (
        E_MOVETO_ID,
        "eMoveTo",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eMoveTo;
        }
    );

    TypeInfo* eMoveTo::getType() const
    {
        return &E_MOVETO_TYPEINFO;
    }

    eMoveTo::eMoveTo()
    : Gadget()
    {}

    eMoveTo::~eMoveTo()
    {}


    ////////////////////////////////////////////////////////////////
    // eMoveTo: cloning the object
    ////////////////////////////////////////////////////////////////

    void eMoveTo::createFromOtherObject(const eMoveTo &other)
    {}

    eMoveTo::eMoveTo(const eMoveTo &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eMoveTo& eMoveTo::operator = (const eMoveTo &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eMoveTo::cloneFromMe() const
    {
        return new eMoveTo(*this);
    }

}
