#include <ElephantEngine/eStrafeTarget.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eStrafeTarget interface
    // <kao2.004E8C40> (constructor)
    // <kao2.004E8CC0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_STRAFETARGET_TYPEINFO
    (
        E_STRAFETARGET_ID,
        "eStrafeTarget",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eStrafeTarget;
        }
    );

    TypeInfo* eStrafeTarget::getType() const
    {
        return &E_STRAFETARGET_TYPEINFO;
    }

    eStrafeTarget::eStrafeTarget()
    : Gadget()
    {}

    eStrafeTarget::~eStrafeTarget()
    {}


    ////////////////////////////////////////////////////////////////
    // eStrafeTarget: cloning the object
    ////////////////////////////////////////////////////////////////

    void eStrafeTarget::createFromOtherObject(const eStrafeTarget &other)
    {}

    eStrafeTarget::eStrafeTarget(const eStrafeTarget &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eStrafeTarget& eStrafeTarget::operator = (const eStrafeTarget &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eStrafeTarget::cloneFromMe() const
    {
        return new eStrafeTarget(*this);
    }

}
