#include <kao2engine/eTextWriterFields2.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eTextWriterFields2 interface
    // <kao2.0051E183> (constructor)
    // <kao2.0051E240> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_TEXTWRITERFIELDS2_TYPEINFO
    (
        E_TEXTWRITERFIELDS2_ID,
        "eTextWriterFields2",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eTextWriterFields2;
        }
    );

    TypeInfo* eTextWriterFields2::getType() const
    {
        return &E_TEXTWRITERFIELDS2_TYPEINFO;
    }

    eTextWriterFields2::eTextWriterFields2()
    : Gadget()
    {}

    eTextWriterFields2::~eTextWriterFields2() {}

}
