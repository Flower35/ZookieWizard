#include <kao2ar/eObject.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eObject interface
    // <kao2.00462C00> (constructor)
    // <kao2.00462C90> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_OBJECT_TYPEINFO
    (
        E_OBJECT_ID,
        "eObject",
        nullptr,
        []() -> eObject*
        {
            return new eObject;
        }
    );

    TypeInfo* eObject::getType()
    {
        return &E_OBJECT_TYPEINFO;
    }

    eObject::eObject()
    {}

    eObject::~eObject() {}


    ////////////////////////////////////////////////////////////////
    // eObject serialization
    // <kao2.004050F0>
    ////////////////////////////////////////////////////////////////
    void eObject::serialize(Archive &ar) {}


    ////////////////////////////////////////////////////////////////
    // eObject: get simple name (for instructions)
    ////////////////////////////////////////////////////////////////
    eString eObject::getStringRepresentation()
    {
        return eString();
    }


    ////////////////////////////////////////////////////////////////
    // eObject: get full name (for gadgets and scripts)
    ////////////////////////////////////////////////////////////////
    eString eObject::generateScriptText()
    {
        return eString();
    }


    ////////////////////////////////////////////////////////////////
    // eObject: get `Log.print()` message
    ////////////////////////////////////////////////////////////////
    eString eObject::getLogPrintMessage()
    {
        char bufor[64];

        TypeInfo* info = getType();

        sprintf_s(bufor, 64, "( 0x%08X - %s )", info->id, info->name);

        return bufor;
    }


    ////////////////////////////////////////////////////////////////
    // eObject: 3D rendering
    ////////////////////////////////////////////////////////////////
    void eObject::renderObject(float time, int32_t draw_flags)
    {}

}
