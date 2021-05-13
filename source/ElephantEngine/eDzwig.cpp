#include <ElephantEngine/eDzwig.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eDzwig interface
    // <kao2.0044DD10> (constructor)
    // <kao2.0044DDC0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_DZWIG_TYPEINFO
    (
        E_DZWIG_ID,
        "eDzwig",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eDzwig;
        }
    );

    const TypeInfo* eDzwig::getType() const
    {
        return &E_DZWIG_TYPEINFO;
    }

    eDzwig::eDzwig()
    : Gadget()
    {}

    eDzwig::~eDzwig()
    {}


    ////////////////////////////////////////////////////////////////
    // eDzwig: cloning the object
    ////////////////////////////////////////////////////////////////

    void eDzwig::createFromOtherObject(const eDzwig &other)
    {}

    eDzwig::eDzwig(const eDzwig &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eDzwig& eDzwig::operator = (const eDzwig &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eDzwig::cloneFromMe() const
    {
        return new eDzwig(*this);
    }

}
