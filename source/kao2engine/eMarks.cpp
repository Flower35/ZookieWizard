#include <kao2engine/eMarks.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eMarks interface
    // <kao2.0055AB90> (constructor)
    // <kao2.0055AC20> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_MARKS_TYPEINFO
    (
        E_MARKS_ID,
        "eMarks",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eMarks;
        }
    );

    TypeInfo* eMarks::getType() const
    {
        return &E_MARKS_TYPEINFO;
    }

    eMarks::eMarks()
    : Gadget()
    {}

    eMarks::~eMarks() {}

}
