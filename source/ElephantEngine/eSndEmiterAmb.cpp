#include <ElephantEngine/eSndEmiterAmb.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSndEmiterAmb interface
    // <kao2.0056C4FC> (constructor)
    // <kao2.0043A170> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_SNDEMITERAMB_TYPEINFO
    (
        E_SNDEMITERAMB_ID,
        "eSndEmiterAmb",
        &E_SNDEMITER_TYPEINFO,
        []() -> eObject*
        {
            return new eSndEmiterAmb;
        }
    );

    const TypeInfo* eSndEmiterAmb::getType() const
    {
        return &E_SNDEMITERAMB_TYPEINFO;
    }

    eSndEmiterAmb::eSndEmiterAmb()
    : eSndEmiter()
    {}

    eSndEmiterAmb::~eSndEmiterAmb()
    {}


    ////////////////////////////////////////////////////////////////
    // eSndEmiterAmb: cloning the object
    ////////////////////////////////////////////////////////////////

    void eSndEmiterAmb::createFromOtherObject(const eSndEmiterAmb &other)
    {
        unknown_08 = other.unknown_08;
    }

    eSndEmiterAmb::eSndEmiterAmb(const eSndEmiterAmb &other)
    : eSndEmiter(other)
    {
        createFromOtherObject(other);
    }

    eSndEmiterAmb& eSndEmiterAmb::operator = (const eSndEmiterAmb &other)
    {
        if ((&other) != this)
        {
            eSndEmiter::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eSndEmiterAmb::cloneFromMe() const
    {
        return new eSndEmiterAmb(*this);
    }

}
