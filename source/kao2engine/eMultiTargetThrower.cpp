#include <kao2engine/eMultiTargetThrower.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eMultiTargetThrower interface
    // <kao2.00504780> (constructor)
    // <kao2.00504850> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_MULTITARGETTHROWER_TYPEINFO
    (
        E_MULTITARGETTHROWER_ID,
        "eMultiTargetThrower",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eMultiTargetThrower;
        }
    );

    TypeInfo* eMultiTargetThrower::getType() const
    {
        return &E_MULTITARGETTHROWER_TYPEINFO;
    }

    eMultiTargetThrower::eMultiTargetThrower()
    : Gadget()
    {}

    eMultiTargetThrower::~eMultiTargetThrower()
    {}


    ////////////////////////////////////////////////////////////////
    // eMultiTargetThrower: cloning the object
    ////////////////////////////////////////////////////////////////

    void eMultiTargetThrower::createFromOtherObject(const eMultiTargetThrower &other)
    {}

    eMultiTargetThrower::eMultiTargetThrower(const eMultiTargetThrower &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eMultiTargetThrower& eMultiTargetThrower::operator = (const eMultiTargetThrower &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eMultiTargetThrower::cloneFromMe() const
    {
        return new eMultiTargetThrower(*this);
    }

}
