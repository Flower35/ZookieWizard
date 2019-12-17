#include <kao2engine/eBombaExplodujaca.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eBombaExplodujaca interface
    // <kao2.00451B70> (constructor)
    // <kao2.00451BF0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_BOMBAEXPLODUJACA_TYPEINFO
    (
        E_BOMBAEXPLODUJACA_ID,
        "eBombaExplodujaca",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eBombaExplodujaca;
        }
    );

    TypeInfo* eBombaExplodujaca::getType()
    {
        return &E_BOMBAEXPLODUJACA_TYPEINFO;
    }

    eBombaExplodujaca::eBombaExplodujaca()
    : Gadget()
    {}

    eBombaExplodujaca::~eBombaExplodujaca() {}

}
