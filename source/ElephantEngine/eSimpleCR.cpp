#include <ElephantEngine/eSimpleCR.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSimpleCR interface
    // <kao2.0051C800> (constructor)
    // <kao2.0051C9F0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_SIMPLECR_TYPEINFO
    (
        E_SIMPLECR_ID,
        "eSimpleCR",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eSimpleCR;
        }
    );

    const TypeInfo* eSimpleCR::getType() const
    {
        return &E_SIMPLECR_TYPEINFO;
    }

    eSimpleCR::eSimpleCR()
    : Gadget()
    {}

    eSimpleCR::~eSimpleCR()
    {}


    ////////////////////////////////////////////////////////////////
    // eSimpleCR: cloning the object
    ////////////////////////////////////////////////////////////////

    void eSimpleCR::createFromOtherObject(const eSimpleCR &other)
    {}

    eSimpleCR::eSimpleCR(const eSimpleCR &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eSimpleCR& eSimpleCR::operator = (const eSimpleCR &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eSimpleCR::cloneFromMe() const
    {
        return new eSimpleCR(*this);
    }

}
