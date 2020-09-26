#include <kao2engine/SessionFloat.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // SessionFloat interface
    // <kao2.0059CC81> (constructor)
    // <kao2.0059CD00> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_SESSIONFLOAT_TYPEINFO
    (
        E_SESSIONFLOAT_ID,
        "SessionFloat",
        &E_FLOAT_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new SessionFloat;
        }
    );

    TypeInfo* SessionFloat::getType() const
    {
        return &E_SESSIONFLOAT_TYPEINFO;
    }

    SessionFloat::SessionFloat()
    : Float()
    {}

    SessionFloat::~SessionFloat()
    {}


    ////////////////////////////////////////////////////////////////
    // SessionFloat: cloning the object
    ////////////////////////////////////////////////////////////////

    void SessionFloat::createFromOtherObject(const SessionFloat &other)
    {}

    SessionFloat::SessionFloat(const SessionFloat &other)
    : Float(other)
    {
        createFromOtherObject(other);
    }

    SessionFloat& SessionFloat::operator = (const SessionFloat &other)
    {
        if ((&other) != this)
        {
            Float::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* SessionFloat::cloneFromMe() const
    {
        return new SessionFloat(*this);
    }

}
