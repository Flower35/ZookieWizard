#include <kao2engine/eVibrate.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eVibrate interface
    // <kao2.004CFBB0> (constructor)
    // <kao2.004CFC40> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_VIBRATE_TYPEINFO
    (
        E_VIBRATE_ID,
        "eVibrate",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eVibrate;
        }
    );

    TypeInfo* eVibrate::getType() const
    {
        return &E_VIBRATE_TYPEINFO;
    }

    eVibrate::eVibrate()
    : Gadget()
    {}

    eVibrate::~eVibrate()
    {}


    ////////////////////////////////////////////////////////////////
    // eVibrate: cloning the object
    ////////////////////////////////////////////////////////////////

    void eVibrate::createFromOtherObject(const eVibrate &other)
    {}

    eVibrate::eVibrate(const eVibrate &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eVibrate& eVibrate::operator = (const eVibrate &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eVibrate::cloneFromMe() const
    {
        return new eVibrate(*this);
    }

}
