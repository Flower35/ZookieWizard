#include <kao2engine/eLinkToObject.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eLinkToObject interface
    // <kao2.0044A580> (constructor)
    // <kao2.0044A610> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_LINKTOOBJECT_TYPEINFO
    (
        E_LINKTOOBJECT_ID,
        "eLinkToObject",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eLinkToObject;
        }
    );

    TypeInfo* eLinkToObject::getType()
    {
        return &E_LINKTOOBJECT_TYPEINFO;
    }

    eLinkToObject::eLinkToObject()
    : Gadget()
    {}

    eLinkToObject::~eLinkToObject() {}

}
