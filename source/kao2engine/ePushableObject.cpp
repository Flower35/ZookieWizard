#include <kao2engine/ePushableObject.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // ePushableObject interface
    // <kao2.004EB470> (constructor)
    // <kao2.004EB4F0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_PUSHABLEOBJECT_TYPEINFO
    (
        E_PUSHABLEOBJECT_ID,
        "ePushableObject",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new ePushableObject;
        }
    );

    TypeInfo* ePushableObject::getType() const
    {
        return &E_PUSHABLEOBJECT_TYPEINFO;
    }

    ePushableObject::ePushableObject()
    : Gadget()
    {}

    ePushableObject::~ePushableObject()
    {}


    ////////////////////////////////////////////////////////////////
    // ePushableObject: cloning the object
    ////////////////////////////////////////////////////////////////

    void ePushableObject::createFromOtherObject(const ePushableObject &other)
    {}

    ePushableObject::ePushableObject(const ePushableObject &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    ePushableObject& ePushableObject::operator = (const ePushableObject &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* ePushableObject::cloneFromMe() const
    {
        return new ePushableObject(*this);
    }


    ////////////////////////////////////////////////////////////////
    // ePushableObject: get default name (scripting shenanigans)
    ////////////////////////////////////////////////////////////////
    eString ePushableObject::getDefaultGadgetName() const
    {
        return "pushObj";
    }

}
