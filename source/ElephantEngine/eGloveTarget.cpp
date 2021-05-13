#include <ElephantEngine/eGloveTarget.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eGloveTarget interface
    // <kao2.005045A0> (constructor)
    // <kao2.00504610> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_GLOVETARGET_TYPEINFO
    (
        E_GLOVETARGET_ID,
        "eGloveTarget",
        &E_EGGTARGET_TYPEINFO,
        []() -> eObject*
        {
            return new eGloveTarget;
        }
    );

    const TypeInfo* eGloveTarget::getType() const
    {
        return &E_GLOVETARGET_TYPEINFO;
    }

    eGloveTarget::eGloveTarget()
    : eEggTarget()
    {}

    eGloveTarget::~eGloveTarget()
    {}


    ////////////////////////////////////////////////////////////////
    // eGloveTarget: cloning the object
    ////////////////////////////////////////////////////////////////

    void eGloveTarget::createFromOtherObject(const eGloveTarget &other)
    {}

    eGloveTarget::eGloveTarget(const eGloveTarget &other)
    : eEggTarget(other)
    {
        createFromOtherObject(other);
    }

    eGloveTarget& eGloveTarget::operator = (const eGloveTarget &other)
    {
        if ((&other) != this)
        {
            eEggTarget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eGloveTarget::cloneFromMe() const
    {
        return new eGloveTarget(*this);
    }

}
