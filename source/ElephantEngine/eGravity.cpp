#include <ElephantEngine/eGravity.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eGravity interface
    // <kao2.0052FCF0> (constructor)
    // <kao2.0052FD60> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_GRAVITY_TYPEINFO
    (
        E_GRAVITY_ID,
        "eGravity",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eGravity;
        }
    );

    TypeInfo* eGravity::getType() const
    {
        return &E_GRAVITY_TYPEINFO;
    }

    eGravity::eGravity()
    : Gadget()
    {}

    eGravity::~eGravity()
    {}


    ////////////////////////////////////////////////////////////////
    // eGravity: cloning the object
    ////////////////////////////////////////////////////////////////

    void eGravity::createFromOtherObject(const eGravity &other)
    {}

    eGravity::eGravity(const eGravity &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eGravity& eGravity::operator = (const eGravity &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eGravity::cloneFromMe() const
    {
        return new eGravity(*this);
    }

}
