#include <ElephantEngine/eFlyingTarget.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eFlyingTarget interface
    // <kao2.00500BD0> (constructor)
    // <kao2.00500D60> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_FLYINGTARGET_TYPEINFO
    (
        E_FLYINGTARGET_ID,
        "eFlyingTarget",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eFlyingTarget;
        }
    );

    const TypeInfo* eFlyingTarget::getType() const
    {
        return &E_FLYINGTARGET_TYPEINFO;
    }

    eFlyingTarget::eFlyingTarget()
    : Gadget()
    {}

    eFlyingTarget::~eFlyingTarget()
    {}


    ////////////////////////////////////////////////////////////////
    // eFlyingTarget: cloning the object
    ////////////////////////////////////////////////////////////////

    void eFlyingTarget::createFromOtherObject(const eFlyingTarget &other)
    {}

    eFlyingTarget::eFlyingTarget(const eFlyingTarget &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eFlyingTarget& eFlyingTarget::operator = (const eFlyingTarget &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eFlyingTarget::cloneFromMe() const
    {
        return new eFlyingTarget(*this);
    }

}
