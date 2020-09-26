#include <kao2engine/eWaterTarget.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eWaterTarget interface
    // <kao2.00507950> (constructor)
    // <kao2.005079C0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_WATERTARGET_TYPEINFO
    (
        E_WATERTARGET_ID,
        "eWaterTarget",
        &E_EGGTARGET_TYPEINFO,
        []() -> eObject*
        {
            return new eWaterTarget;
        }
    );

    TypeInfo* eWaterTarget::getType() const
    {
        return &E_WATERTARGET_TYPEINFO;
    }

    eWaterTarget::eWaterTarget()
    : eEggTarget()
    {}

    eWaterTarget::~eWaterTarget()
    {}


    ////////////////////////////////////////////////////////////////
    // eWaterTarget: cloning the object
    ////////////////////////////////////////////////////////////////

    void eWaterTarget::createFromOtherObject(const eWaterTarget &other)
    {}

    eWaterTarget::eWaterTarget(const eWaterTarget &other)
    : eEggTarget(other)
    {
        createFromOtherObject(other);
    }

    eWaterTarget& eWaterTarget::operator = (const eWaterTarget &other)
    {
        if ((&other) != this)
        {
            eEggTarget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eWaterTarget::cloneFromMe() const
    {
        return new eWaterTarget(*this);
    }

}
