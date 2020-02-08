#include <kao2engine/eFloat.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eFloat interface
    // <kao2.00465EF3> (constructor)
    // <kao2.00466020> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_FLOAT_TYPEINFO
    (
        E_FLOAT_ID,
        "eFloat",
        &E_REFCOUNTER_TYPEINFO,
        []() -> eObject*
        {
            return new eFloat;
        }
    );

    TypeInfo* eFloat::getType() const
    {
        return &E_FLOAT_TYPEINFO;
    }

    eFloat::eFloat()
    : eRefCounter()
    {
        /*[0x08]*/ value = 0;
    }

    eFloat::~eFloat() {}


    ////////////////////////////////////////////////////////////////
    // eFloat serialization
    // <kao2.00465F70>
    ////////////////////////////////////////////////////////////////
    void eFloat::serialize(Archive &ar)
    {
        ar.readOrWrite(&value, 0x04);
    }


    ////////////////////////////////////////////////////////////////
    // eFloat: get textual representation
    ////////////////////////////////////////////////////////////////
    eString eFloat::getStringRepresentation() const
    {
        char bufor[32];

        sprintf_s(bufor, 32, "%.1f", value);

        return eString(bufor);
    }

}
