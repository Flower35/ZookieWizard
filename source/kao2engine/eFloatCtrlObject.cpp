#include <kao2engine/eFloatCtrlObject.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eFloatCtrlObject interface
    // <kao2.0043BE20> (constructor)
    // <kao2.0043BEC0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_FLOATCTRLOBJECT_TYPEINFO
    (
        E_FLOATCTRLOBJECT_ID,
        "eFloatCtrlObject",
        &E_FLOATOBJECT_TYPEINFO,
        []() -> eObject*
        {
            return new eFloatCtrlObject;
        }
    );

    TypeInfo* eFloatCtrlObject::getType() const
    {
        return &E_FLOATCTRLOBJECT_TYPEINFO;
    }

    eFloatCtrlObject::eFloatCtrlObject()
    : eFloatObject()
    {}

    eFloatCtrlObject::~eFloatCtrlObject()
    {}


    ////////////////////////////////////////////////////////////////
    // eFloatCtrlObject: cloning the object
    ////////////////////////////////////////////////////////////////

    void eFloatCtrlObject::createFromOtherObject(const eFloatCtrlObject &other)
    {}

    eFloatCtrlObject::eFloatCtrlObject(const eFloatCtrlObject &other)
    : eFloatObject(other)
    {
        createFromOtherObject(other);
    }

    eFloatCtrlObject& eFloatCtrlObject::operator = (const eFloatCtrlObject &other)
    {
        if ((&other) != this)
        {
            eFloatObject::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eFloatCtrlObject::cloneFromMe() const
    {
        return new eFloatCtrlObject(*this);
    }

}
