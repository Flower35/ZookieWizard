#include <kao2engine/StringSection.h>
#include <kao2ar/Archive.h>

#include <kao2ar/ArTemplates.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // StringSection interface
    // <kao2.00593680> (constructor)
    // <kao2.00593500> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_STRINGSECTION_TYPEINFO
    (
        E_STRINGSECTION_ID,
        "StringSection",
        &E_REFCOUNTER_TYPEINFO,
        []() -> eObject*
        {
            return new StringSection;
        }
    );

    TypeInfo* StringSection::getType() const
    {
        return &E_STRINGSECTION_TYPEINFO;
    }

    StringSection::StringSection()
    : eRefCounter()
    {}

    StringSection::~StringSection() {}


    ////////////////////////////////////////////////////////////////
    // StringSection serialization
    // <kao2.00593990>
    ////////////////////////////////////////////////////////////////
    void StringSection::serialize(Archive &ar)
    {
        /* [0x08] Section name */
        ar.serializeString(name);

        /* [0x0C] Properties group serialization */
        props.serialize(ar, &E_STRINGPROPERTY_TYPEINFO);
    }


    ////////////////////////////////////////////////////////////////
    // Explicit templates
    // <kao2.00597820>: Outer serialization
    // <kao2.005962A0>: Group template
    ////////////////////////////////////////////////////////////////

    void ArFunctions::serialize_StringSection(Archive &ar, eRefCounter** o, TypeInfo* t)
    {
        serializeKnownObject<StringSection>(ar, o, t);
    }


    ////////////////////////////////////////////////////////////////
    // StringSection: get textual representation
    ////////////////////////////////////////////////////////////////
    eString StringSection::getStringRepresentation() const
    {
        return name;
    }


    ////////////////////////////////////////////////////////////////
    // StringSection: save section to a text file ;)
    ////////////////////////////////////////////////////////////////
    void StringSection::saveSectionToTextFile(FileOperator &file, int32_t indentation) const
    {
        int32_t i;

        for (i = 0; i < props.getSize(); i++)
        {
            StringProperty* test_prop = (StringProperty*)props.getIthChild(i);

            if (nullptr != test_prop)
            {
                ArFunctions::writeNewLine(file, indentation);

                file << "prop ";
                file << name;
                file << ".";
                file << test_prop->getStringRepresentation();
            }
        }
    }

}
