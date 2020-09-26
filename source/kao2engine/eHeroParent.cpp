#include <kao2engine/eHeroParent.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eHeroParent interface
    // <kao2.00518172> (constructor)
    // <kao2.00518230> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_HEROPARENT_TYPEINFO
    (
        E_HEROPARENT_ID,
        "eHeroParent",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eHeroParent;
        }
    );

    TypeInfo* eHeroParent::getType() const
    {
        return &E_HEROPARENT_TYPEINFO;
    }

    eHeroParent::eHeroParent()
    : Gadget()
    {}

    eHeroParent::~eHeroParent()
    {}


    ////////////////////////////////////////////////////////////////
    // eHeroParent: cloning the object
    ////////////////////////////////////////////////////////////////

    void eHeroParent::createFromOtherObject(const eHeroParent &other)
    {}

    eHeroParent::eHeroParent(const eHeroParent &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eHeroParent& eHeroParent::operator = (const eHeroParent &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eHeroParent::cloneFromMe() const
    {
        return new eHeroParent(*this);
    }

}
