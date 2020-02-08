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

    eFloatObject::~eFloatObject() {}

}
