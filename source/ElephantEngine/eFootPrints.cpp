#include <ElephantEngine/eFootPrints.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eFootPrints interface
    // <kao2.00442F30> (constructor)
    // <kao2.004431C0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_FOOTPRINTS_TYPEINFO
    (
        E_FOOTPRINTS_ID,
        "eFootPrints",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eFootPrints;
        }
    );

    const TypeInfo* eFootPrints::getType() const
    {
        return &E_FOOTPRINTS_TYPEINFO;
    }

    eFootPrints::eFootPrints()
    : Gadget()
    {}

    eFootPrints::~eFootPrints()
    {}


    ////////////////////////////////////////////////////////////////
    // eFootPrints: cloning the object
    ////////////////////////////////////////////////////////////////

    void eFootPrints::createFromOtherObject(const eFootPrints &other)
    {}

    eFootPrints::eFootPrints(const eFootPrints &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eFootPrints& eFootPrints::operator = (const eFootPrints &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eFootPrints::cloneFromMe() const
    {
        return new eFootPrints(*this);
    }

}
