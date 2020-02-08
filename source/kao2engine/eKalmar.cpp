#include <kao2engine/eKalmar.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eKalmar interface
    // <kao2.00527DD1> (constructor)
    // <kao2.00527E40> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_KALMAR_TYPEINFO
    (
        E_KALMAR_ID,
        "eKalmar",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eKalmar;
        }
    );

    TypeInfo* eKalmar::getType() const
    {
        return &E_KALMAR_TYPEINFO;
    }

    eKalmar::eKalmar()
    : Gadget()
    {}

    eKalmar::~eKalmar() {}

}
