#include <ElephantEngine/eButterfly.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eButterfly interface
    // <kao2.00435A80> (constructor)
    // <kao2.00435B10> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_BUTTERFLY_TYPEINFO
    (
        E_BUTTERFLY_ID,
        "eButterfly",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eButterfly;
        }
    );

    TypeInfo* eButterfly::getType() const
    {
        return &E_BUTTERFLY_TYPEINFO;
    }

    eButterfly::eButterfly()
    : Gadget()
    {}

    eButterfly::~eButterfly()
    {}


    ////////////////////////////////////////////////////////////////
    // eButterfly: cloning the object
    ////////////////////////////////////////////////////////////////

    void eButterfly::createFromOtherObject(const eButterfly &other)
    {}

    eButterfly::eButterfly(const eButterfly &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eButterfly& eButterfly::operator = (const eButterfly &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eButterfly::cloneFromMe() const
    {
        return new eButterfly(*this);
    }

}
