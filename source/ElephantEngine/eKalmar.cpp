#include <ElephantEngine/eKalmar.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eKalmar interface
    // <kao2.00527DD1> (constructor)
    // <kao2.00527E40> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_KALMAR_TYPEINFO
    (
        E_KALMAR_ID,
        "eKalmar",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eKalmar;
        }
    );

    TypeInfo* eKalmar::getType() const
    {
        return &E_KALMAR_TYPEINFO;
    }

    eKalmar::eKalmar()
    : Gadget()
    {}

    eKalmar::~eKalmar()
    {}


    ////////////////////////////////////////////////////////////////
    // eKalmar: cloning the object
    ////////////////////////////////////////////////////////////////

    void eKalmar::createFromOtherObject(const eKalmar &other)
    {}

    eKalmar::eKalmar(const eKalmar &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eKalmar& eKalmar::operator = (const eKalmar &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eKalmar::cloneFromMe() const
    {
        return new eKalmar(*this);
    }

}
