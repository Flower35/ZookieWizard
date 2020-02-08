#include <kao2engine/eTextWriterEx.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eTextWriterEx interface
    // <kao2.0045A1B0> (constructor)
    // <kao2.0045A240> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_TEXTWRITEREX_TYPEINFO
    (
        E_TEXTWRITEREX_ID,
        "eTextWriterEx",
        &E_TEXTWRITER_TYPEINFO,
        []() -> eObject*
        {
            return new eTextWriterEx;
        }
    );

    TypeInfo* eTextWriterEx::getType() const
    {
        return &E_TEXTWRITEREX_TYPEINFO;
    }

    eTextWriterEx::eTextWriterEx()
    : eTextWriter()
    {}

    eTextWriterEx::~eTextWriterEx() {}

}
