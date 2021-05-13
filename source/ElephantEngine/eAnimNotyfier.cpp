#include <ElephantEngine/eAnimNotyfier.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eAnimNotyfier interface
    // <kao2.00444AD0> (constructor)
    // <kao2.00444B60> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_ANIMNOTYFIER_TYPEINFO
    (
        E_ANIMNOTYFIER_ID,
        "eAnimNotyfier",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eAnimNotyfier;
        }
    );

    const TypeInfo* eAnimNotyfier::getType() const
    {
        return &E_ANIMNOTYFIER_TYPEINFO;
    }

    eAnimNotyfier::eAnimNotyfier()
    : Gadget()
    {}

    eAnimNotyfier::~eAnimNotyfier()
    {}


    ////////////////////////////////////////////////////////////////
    // eAnimNotyfier: cloning the object
    ////////////////////////////////////////////////////////////////

    void eAnimNotyfier::createFromOtherObject(const eAnimNotyfier &other)
    {}

    eAnimNotyfier::eAnimNotyfier(const eAnimNotyfier &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eAnimNotyfier& eAnimNotyfier::operator = (const eAnimNotyfier &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eAnimNotyfier::cloneFromMe() const
    {
        return new eAnimNotyfier(*this);
    }

}
