#include <kao2engine/eFloatObject.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eFloatObject interface
    // <kao2.00431B70> (constructor)
    // <kao2.00431C00> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_FLOATOBJECT_TYPEINFO
    (
        E_FLOATOBJECT_ID,
        "eFloatObject",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eFloatObject;
        }
    );

    TypeInfo* eFloatObject::getType() const
    {
        return &E_FLOATOBJECT_TYPEINFO;
    }

    eFloatObject::eFloatObject()
    : Gadget()
    {}

    eFloatObject::~eFloatObject()
    {}


    ////////////////////////////////////////////////////////////////
    // eFloatObject: cloning the object
    ////////////////////////////////////////////////////////////////

    void eFloatObject::createFromOtherObject(const eFloatObject &other)
    {}

    eFloatObject::eFloatObject(const eFloatObject &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eFloatObject& eFloatObject::operator = (const eFloatObject &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eFloatObject::cloneFromMe() const
    {
        return new eFloatObject(*this);
    }

}
