#include <ElephantEngine/eAddPowerUp.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eAddPowerUp interface
    // <kao2.005A4942> (constructor)
    // <kao2.005A49D0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_ADDPOWERUP_TYPEINFO
    (
        E_ADDPOWERUP_ID,
        "eAddPowerUp",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eAddPowerUp;
        }
    );

    const TypeInfo* eAddPowerUp::getType() const
    {
        return &E_ADDPOWERUP_TYPEINFO;
    }

    eAddPowerUp::eAddPowerUp()
    : Gadget()
    {}

    eAddPowerUp::~eAddPowerUp()
    {}


    ////////////////////////////////////////////////////////////////
    // eAddPowerUp: cloning the object
    ////////////////////////////////////////////////////////////////

    void eAddPowerUp::createFromOtherObject(const eAddPowerUp &other)
    {}

    eAddPowerUp::eAddPowerUp(const eAddPowerUp &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eAddPowerUp& eAddPowerUp::operator = (const eAddPowerUp &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eAddPowerUp::cloneFromMe() const
    {
        return new eAddPowerUp(*this);
    }

}
