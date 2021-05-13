#include <ElephantEngine/StringProperty.h>
#include <ElephantBase/Archive.h>

#include <ElephantBase/Collection.h>
#include <ElephantBase/ArTemplates.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // StringProperty interface
    // <kao2.00592E50> (constructor)
    // <kao2.00592F40> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_STRINGPROPERTY_TYPEINFO
    (
        E_STRINGPROPERTY_ID,
        "StringProperty",
        &E_REFCOUNTER_TYPEINFO,
        []() -> eObject*
        {
            return new StringProperty;
        }
    );

    const TypeInfo* StringProperty::getType() const
    {
        return &E_STRINGPROPERTY_TYPEINFO;
    }

    StringProperty::StringProperty()
    : eRefCounter()
    {
        checked = 0;
        state = false;
    }

    StringProperty::~StringProperty() {}


    ////////////////////////////////////////////////////////////////
    // StringProperty serialization
    // <kao2.005930F0>
    ////////////////////////////////////////////////////////////////
    void StringProperty::serialize(Archive &ar)
    {
        /* [0x08] property name */
        ar.serializeString(prop);

        /* [0x0C] property value */
        ar.serializeString(value);
    }


    ////////////////////////////////////////////////////////////////
    // Explicit templates
    // <kao2.005976E0>: Outer serialization
    // <kao2.00595E30>: Group template
    ////////////////////////////////////////////////////////////////

    void ArFunctions::serialize_StringProperty(Archive &ar, eRefCounter** o, const TypeInfo* t)
    {
        serializeKnownObject<StringProperty>(ar, o, t);
    }


    ////////////////////////////////////////////////////////////////
    // StringProperty: get textual representation
    ////////////////////////////////////////////////////////////////
    eString StringProperty::getStringRepresentation() const
    {
        eString result;

        result += prop;
        result += " = \"";
        result += value;
        result += "\"";

        return result;
    }

}
