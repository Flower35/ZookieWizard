#include <kao2engine/eEnergy.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eEnergy interface
    // <kao2.0050AF80> (constructor)
    // <kao2.0050B010> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_ENERGY_TYPEINFO
    (
        E_ENERGY_ID,
        "eEnergy",
        &E_POWERBAR_TYPEINFO,
        []() -> eObject*
        {
            return new eEnergy;
        }
    );

    TypeInfo* eEnergy::getType() const
    {
        return &E_ENERGY_TYPEINFO;
    }

    eEnergy::eEnergy()
    : ePowerBar()
    {}

    eEnergy::~eEnergy()
    {}


    ////////////////////////////////////////////////////////////////
    // eEnergy: cloning the object
    ////////////////////////////////////////////////////////////////

    void eEnergy::createFromOtherObject(const eEnergy &other)
    {}

    eEnergy::eEnergy(const eEnergy &other)
    : ePowerBar(other)
    {
        createFromOtherObject(other);
    }

    eEnergy& eEnergy::operator = (const eEnergy &other)
    {
        if ((&other) != this)
        {
            ePowerBar::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eEnergy::cloneFromMe() const
    {
        return new eEnergy(*this);
    }

}
