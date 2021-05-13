#include <ElephantEngine/eFSOp.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eFSOp interface
    // <kao2.00559D90> (constructor)
    // <kao2.004CD8B0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_FSOP_TYPEINFO
    (
        E_FSOP_ID,
        "eFSOp",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return nullptr;
        }
    );

    TypeInfo* eFSOp::getType() const
    {
        return &E_FSOP_TYPEINFO;
    }

    eFSOp::eFSOp()
    : Gadget()
    {}

    eFSOp::~eFSOp()
    {}


    ////////////////////////////////////////////////////////////////
    // eFSOp: cloning the object
    ////////////////////////////////////////////////////////////////

    void eFSOp::createFromOtherObject(const eFSOp &other)
    {}

    eFSOp::eFSOp(const eFSOp &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eFSOp& eFSOp::operator = (const eFSOp &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eFSOp::cloneFromMe() const
    {
        return nullptr;
    }

}
