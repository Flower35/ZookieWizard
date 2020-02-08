#include <kao2engine/eDzwig.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eDzwig interface
    // <kao2.0044DD10> (constructor)
    // <kao2.0044DDC0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_DZWIG_TYPEINFO
    (
        E_DZWIG_ID,
        "eDzwig",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eDzwig;
        }
    );

    TypeInfo* eDzwig::getType() const
    {
        return &E_DZWIG_TYPEINFO;
    }

    eDzwig::eDzwig()
    : Gadget()
    {}

    eDzwig::~eDzwig() {}

}
