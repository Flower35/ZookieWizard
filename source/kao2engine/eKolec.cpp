#include <kao2engine/eKolec.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eKolec interface
    // <kao2.00451450> (constructor)
    // <kao2.004514C0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_KOLEC_TYPEINFO
    (
        E_KOLEC_ID,
        "eKolec",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eKolec;
        }
    );

    TypeInfo* eKolec::getType() const
    {
        return &E_KOLEC_TYPEINFO;
    }

    eKolec::eKolec()
    : Gadget()
    {}

    eKolec::~eKolec()
    {}


    ////////////////////////////////////////////////////////////////
    // eKolec: cloning the object
    ////////////////////////////////////////////////////////////////

    void eKolec::createFromOtherObject(const eKolec &other)
    {}

    eKolec::eKolec(const eKolec &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eKolec& eKolec::operator = (const eKolec &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eKolec::cloneFromMe() const
    {
        return new eKolec(*this);
    }

}
