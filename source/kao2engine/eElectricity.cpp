#include <kao2engine/eElectricity.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eElectricity interface
    // <kao2.00567360> (constructor)
    // <kao2.00567430> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_ELECTRICITY_TYPEINFO
    (
        E_ELECTRICITY_ID,
        "eElectricity",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eElectricity;
        }
    );

    TypeInfo* eElectricity::getType() const
    {
        return &E_ELECTRICITY_TYPEINFO;
    }

    eElectricity::eElectricity()
    : Gadget()
    {}

    eElectricity::~eElectricity()
    {}


    ////////////////////////////////////////////////////////////////
    // eElectricity: cloning the object
    ////////////////////////////////////////////////////////////////

    void eElectricity::createFromOtherObject(const eElectricity &other)
    {}

    eElectricity::eElectricity(const eElectricity &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eElectricity& eElectricity::operator = (const eElectricity &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eElectricity::cloneFromMe() const
    {
        return new eElectricity(*this);
    }

}
