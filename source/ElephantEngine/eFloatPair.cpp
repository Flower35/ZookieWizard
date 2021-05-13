#include <ElephantEngine/eFloatPair.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eFloatPair interface
    // <kao2.0058AC72> (constructor)
    // <kao2.00528E40> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_FLOATPAIR_TYPEINFO
    (
        E_FLOATPAIR_ID,
        "eFloatPair",
        &E_REFCOUNTER_TYPEINFO,
        []() -> eObject*
        {
            return new eFloatPair;
        }
    );

    const TypeInfo* eFloatPair::getType() const
    {
        return &E_FLOATPAIR_TYPEINFO;
    }

    eFloatPair::eFloatPair()
    : eRefCounter()
    {
        /*[0x08]*/ values[0] = 0;
        /*[0x0C]*/ values[1] = 0;
    }

    eFloatPair::~eFloatPair() {}


    ////////////////////////////////////////////////////////////////
    // eFloatPair serialization
    // <kao2.00528D80>
    ////////////////////////////////////////////////////////////////
    void eFloatPair::serialize(Archive &ar)
    {
        ar.readOrWrite(&(values[0]), 0x04);
        ar.readOrWrite(&(values[1]), 0x04);
    }


    ////////////////////////////////////////////////////////////////
    // eFloatPair: get textual representation
    ////////////////////////////////////////////////////////////////
    eString eFloatPair::getStringRepresentation() const
    {
        char bufor[64];

        sprintf_s(bufor, 64, "%.1f, %.1f", values[0], values[1]);

        return eString(bufor);
    }

}
