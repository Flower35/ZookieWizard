#include <kao2engine/eCredits.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eCredits interface
    // <kao2.00461372> (constructor)
    // <kao2.00461420> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_CREDITS_TYPEINFO
    (
        E_CREDITS_ID,
        "eCredits",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eCredits;
        }
    );

    TypeInfo* eCredits::getType() const
    {
        return &E_CREDITS_TYPEINFO;
    }

    eCredits::eCredits()
    : Gadget()
    {}

    eCredits::~eCredits()
    {}


    ////////////////////////////////////////////////////////////////
    // eCredits: cloning the object
    ////////////////////////////////////////////////////////////////

    void eCredits::createFromOtherObject(const eCredits &other)
    {}

    eCredits::eCredits(const eCredits &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eCredits& eCredits::operator = (const eCredits &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eCredits::cloneFromMe() const
    {
        return new eCredits(*this);
    }

}
