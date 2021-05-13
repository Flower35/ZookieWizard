#include <ElephantEngine/eGravitation.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eGravitation interface
    // <kao2.00440940> (constructor)
    // <kao2.004409C0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_GRAVITATION_TYPEINFO
    (
        E_GRAVITATION_ID,
        "eGravitation",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eGravitation;
        }
    );

    TypeInfo* eGravitation::getType() const
    {
        return &E_GRAVITATION_TYPEINFO;
    }

    eGravitation::eGravitation()
    : Gadget()
    {}

    eGravitation::~eGravitation()
    {}


    ////////////////////////////////////////////////////////////////
    // eGravitation: cloning the object
    ////////////////////////////////////////////////////////////////

    void eGravitation::createFromOtherObject(const eGravitation &other)
    {}

    eGravitation::eGravitation(const eGravitation &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eGravitation& eGravitation::operator = (const eGravitation &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eGravitation::cloneFromMe() const
    {
        return new eGravitation(*this);
    }

}
