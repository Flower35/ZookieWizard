#include <ElephantEngine/eEggTarget.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eEggTarget interface
    // <kao2.00502740> (constructor)
    // <kao2.005027F0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_EGGTARGET_TYPEINFO
    (
        E_EGGTARGET_ID,
        "eEggTarget",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eEggTarget;
        }
    );

    const TypeInfo* eEggTarget::getType() const
    {
        return &E_EGGTARGET_TYPEINFO;
    }

    eEggTarget::eEggTarget()
    : Gadget()
    {}

    eEggTarget::~eEggTarget()
    {}


    ////////////////////////////////////////////////////////////////
    // eEggTarget: cloning the object
    ////////////////////////////////////////////////////////////////

    void eEggTarget::createFromOtherObject(const eEggTarget &other)
    {}

    eEggTarget::eEggTarget(const eEggTarget &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eEggTarget& eEggTarget::operator = (const eEggTarget &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eEggTarget::cloneFromMe() const
    {
        return new eEggTarget(*this);
    }

}
