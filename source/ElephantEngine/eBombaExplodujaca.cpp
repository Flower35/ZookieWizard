#include <ElephantEngine/eBombaExplodujaca.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eBombaExplodujaca interface
    // <kao2.00451B70> (constructor)
    // <kao2.00451BF0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_BOMBAEXPLODUJACA_TYPEINFO
    (
        E_BOMBAEXPLODUJACA_ID,
        "eBombaExplodujaca",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eBombaExplodujaca;
        }
    );

    TypeInfo* eBombaExplodujaca::getType() const
    {
        return &E_BOMBAEXPLODUJACA_TYPEINFO;
    }

    eBombaExplodujaca::eBombaExplodujaca()
    : Gadget()
    {}

    eBombaExplodujaca::~eBombaExplodujaca()
    {}


    ////////////////////////////////////////////////////////////////
    // eBombaExplodujaca: cloning the object
    ////////////////////////////////////////////////////////////////

    void eBombaExplodujaca::createFromOtherObject(const eBombaExplodujaca &other)
    {}

    eBombaExplodujaca::eBombaExplodujaca(const eBombaExplodujaca &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eBombaExplodujaca& eBombaExplodujaca::operator = (const eBombaExplodujaca &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eBombaExplodujaca::cloneFromMe() const
    {
        return new eBombaExplodujaca(*this);
    }

}
