#include <ElephantEngine/ePowerUp.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // ePowerUp interface
    // <kao2.00507BA0> (constructor)
    // <kao2.00507C20> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_POWERUP_TYPEINFO
    (
        E_POWERUP_ID,
        "ePowerUp",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new ePowerUp;
        }
    );

    TypeInfo* ePowerUp::getType() const
    {
        return &E_POWERUP_TYPEINFO;
    }

    ePowerUp::ePowerUp()
    : Gadget()
    {}

    ePowerUp::~ePowerUp()
    {}


    ////////////////////////////////////////////////////////////////
    // ePowerUp: cloning the object
    ////////////////////////////////////////////////////////////////

    void ePowerUp::createFromOtherObject(const ePowerUp &other)
    {}

    ePowerUp::ePowerUp(const ePowerUp &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    ePowerUp& ePowerUp::operator = (const ePowerUp &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* ePowerUp::cloneFromMe() const
    {
        return new ePowerUp(*this);
    }


    ////////////////////////////////////////////////////////////////
    // ePowerUp: get default name (scripting shenanigans)
    ////////////////////////////////////////////////////////////////
    eString ePowerUp::getDefaultGadgetName() const
    {
        return "powerUp";
    }

}
