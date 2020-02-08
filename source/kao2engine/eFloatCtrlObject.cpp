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

    eFloatCtrlObject::~eFloatCtrlObject() {}

}
