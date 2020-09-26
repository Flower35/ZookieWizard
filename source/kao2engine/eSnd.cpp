#include <kao2engine/eSnd.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSnd interface
    // <kao2.00438BA0> (constructor)
    // <kao2.00438CA0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_SND_TYPEINFO
    (
        E_SND_ID,
        "eSnd",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eSnd;
        }
    );

    TypeInfo* eSnd::getType() const
    {
        return &E_SND_TYPEINFO;
    }

    eSnd::eSnd()
    : Gadget()
    {}

    eSnd::~eSnd()
    {}


    ////////////////////////////////////////////////////////////////
    // eSnd: cloning the object
    ////////////////////////////////////////////////////////////////

    void eSnd::createFromOtherObject(const eSnd &other)
    {}

    eSnd::eSnd(const eSnd &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eSnd& eSnd::operator = (const eSnd &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eSnd::cloneFromMe() const
    {
        return new eSnd(*this);
    }

}
