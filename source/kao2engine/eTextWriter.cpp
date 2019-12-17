#include <kao2engine/eTextWriter.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eTextWriter interface
    // <kao2.0041D690> (constructor)
    // <kao2.0041D790> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_TEXTWRITER_TYPEINFO
    (
        E_TEXTWRITER_ID,
        "eTextWriter",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eTextWriter;
        }
    );

    TypeInfo* eTextWriter::getType()
    {
        return &E_TEXTWRITER_TYPEINFO;
    }

    eTextWriter::eTextWriter()
    : Gadget()
    {}

    eTextWriter::~eTextWriter() {}

}
