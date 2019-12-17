#include <kao2engine/eFloatTriple.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eFloatTriple interface
    // <kao2.0058AD52> (constructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_FLOATTRIPLE_TYPEINFO
    (
        E_FLOATTRIPLE_ID,
        "eFloatTriple",
        &E_REFCOUNTER_TYPEINFO,
        []() -> eObject*
        {
            return new eFloatTriple;
        }
    );

    TypeInfo* eFloatTriple::getType()
    {
        return &E_FLOATTRIPLE_TYPEINFO;
    }

    eFloatTriple::eFloatTriple()
    : eRefCounter()
    {
        /*[0x08]*/ values[0] = 0;
        /*[0x0C]*/ values[1] = 0;
        /*[0x10]*/ values[2] = 0;
    }


    ////////////////////////////////////////////////////////////////
    // eFloatTriple serialization
    // <kao2.00442310>
    ////////////////////////////////////////////////////////////////
    void eFloatTriple::serialize(Archive &ar)
    {
        ar.readOrWrite(&(values[0]), 0x04);
        ar.readOrWrite(&(values[1]), 0x04);
        ar.readOrWrite(&(values[2]), 0x04);
    }


    ////////////////////////////////////////////////////////////////
    // eFloatTriple: get textual representation
    ////////////////////////////////////////////////////////////////
    eString eFloatTriple::getStringRepresentation()
    {
        char bufor[96];

        sprintf_s(bufor, 96, "%.1f, %.1f, %.1f", values[0], values[1], values[2]);

        return eString(bufor);
    }

}
