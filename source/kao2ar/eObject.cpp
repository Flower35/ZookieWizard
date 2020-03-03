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

    TypeInfo* eObject::getType() const
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
        TypeInfo* info = getType();

        sprintf_s(bufor, 64, "( 0x%08X - %s )", info->id, info->name);

        return bufor;
    }


    ////////////////////////////////////////////////////////////////
    // eObject: export readable structure
    ////////////////////////////////////////////////////////////////
    void eObject::writeStructureToTextFile(FileOperator &file, int32_t indentation) const
    {
        char bufor[64];
        TypeInfo* info = getType();

        sprintf_s(bufor, 64, "[%08X] %s", info->id, info->name);

        ArFunctions::writeNewLine(file, indentation);
        file << bufor;
        ArFunctions::writeNewLine(file, 0);
    }


    ////////////////////////////////////////////////////////////////
    // eObject: COLLADA exporting
    ////////////////////////////////////////////////////////////////
    void eObject::writeNodeToXmlFile(ColladaExporter &exporter) const
    {}


    ////////////////////////////////////////////////////////////////
    // eObject: 3D rendering
    // (cannot be "const" because "ePivot" changes animation)
    ////////////////////////////////////////////////////////////////
    bool eObject::renderObject(int32_t draw_flags, eAnimate* anim, eSRP &parent_srp, int32_t marked_id)
    {
        return true;
    }

}
