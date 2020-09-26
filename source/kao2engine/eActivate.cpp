#include <kao2engine/eActivate.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eActivate interface
    // <kao2.005A2910> (constructor)
    // <kao2.005A29A0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_ACTIVATE_TYPEINFO
    (
        E_ACTIVATE_ID,
        "eActivate",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eActivate;
        }
    );

    TypeInfo* eActivate::getType() const
    {
        return &E_ACTIVATE_TYPEINFO;
    }

    eActivate::eActivate()
    : Gadget()
    {}

    eActivate::~eActivate()
    {}


    ////////////////////////////////////////////////////////////////
    // eActivate: cloning the object
    ////////////////////////////////////////////////////////////////

    void eActivate::createFromOtherObject(const eActivate &other)
    {}

    eActivate::eActivate(const eActivate &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eActivate& eActivate::operator = (const eActivate &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eActivate::cloneFromMe() const
    {
        return new eActivate(*this);
    }

}
