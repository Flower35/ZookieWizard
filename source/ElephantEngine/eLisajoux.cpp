#include <ElephantEngine/eLisajoux.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eLisajoux interface
    // <kao2.005642B0> (constructor)
    // <kao2.00564430> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_LISAJOUX_TYPEINFO
    (
        E_LISAJOUX_ID,
        "eLisajoux",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eLisajoux;
        }
    );

    const TypeInfo* eLisajoux::getType() const
    {
        return &E_LISAJOUX_TYPEINFO;
    }

    eLisajoux::eLisajoux()
    : Gadget()
    {}

    eLisajoux::~eLisajoux()
    {}


    ////////////////////////////////////////////////////////////////
    // eLisajoux: cloning the object
    ////////////////////////////////////////////////////////////////

    void eLisajoux::createFromOtherObject(const eLisajoux &other)
    {}

    eLisajoux::eLisajoux(const eLisajoux &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eLisajoux& eLisajoux::operator = (const eLisajoux &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eLisajoux::cloneFromMe() const
    {
        return new eLisajoux(*this);
    }

}
