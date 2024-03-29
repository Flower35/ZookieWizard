#include <ElephantBase/eObject.h>
#include <ElephantBase/Archive.h>

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

    const TypeInfo* eObject::getType() const
    {
        return &E_OBJECT_TYPEINFO;
    }

    eObject::eObject()
    {}

    eObject::~eObject()
    {}


    ////////////////////////////////////////////////////////////////
    // eObject: cloning the object
    ////////////////////////////////////////////////////////////////

    void eObject::createFromOtherObject(const eObject &other)
    {}

    eObject::eObject(const eObject &other)
    {
        createFromOtherObject(other);
    }

    eObject& eObject::operator = (const eObject &other)
    {
        if ((&other) != this)
        {
            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eObject::cloneFromMe() const
    {
        return new eObject(*this);
    }


    ////////////////////////////////////////////////////////////////
    // eObject: serialization
    // <kao2.004050F0>
    ////////////////////////////////////////////////////////////////
    void eObject::serialize(Archive &ar)
    {}


    ////////////////////////////////////////////////////////////////
    // eObject: get simple name (for instructions)
    ////////////////////////////////////////////////////////////////
    eString eObject::getStringRepresentation() const
    {
        return eString();
    }


    ////////////////////////////////////////////////////////////////
    // eObject: get full name (for gadgets and scripts)
    ////////////////////////////////////////////////////////////////
    eString eObject::generateScriptText() const
    {
        return eString();
    }


    ////////////////////////////////////////////////////////////////
    // eObject: get `Log.print()` message
    ////////////////////////////////////////////////////////////////
    eString eObject::getLogPrintMessage() const
    {
        char bufor[64];
        const TypeInfo* info = getType();

        sprintf_s(bufor, 64, "( 0x%08X - %s )", info->id, info->name);

        return bufor;
    }


    ////////////////////////////////////////////////////////////////
    // eObject: dump object tree as a JSON value
    ////////////////////////////////////////////////////////////////
    void eObject::dumpTreeAsJsonValue(JsonValue& output, bool dumpChildNodes) const
    {
        output.setType(JSON_VALUETYPE_OBJECT);
        JsonObject * jsonObjectRef = (JsonObject *) output.getValue();

        const TypeInfo* info = getType();
        jsonObjectRef->appendKeyValue("type", info->name);
    }


    ////////////////////////////////////////////////////////////////
    // eObject: COLLADA exporting
    ////////////////////////////////////////////////////////////////
    void eObject::writeNodeToXmlFile(ColladaExporter &exporter) const
    {}

}
