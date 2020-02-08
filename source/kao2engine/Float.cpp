#include <kao2engine/Float.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // Float interface
    // <kao2.0059AD51> (constructor)
    // <kao2.0059ADC0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_FLOAT_GADGET_TYPEINFO
    (
        E_FLOAT_GADGET_ID,
        "Float",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new Float;
        }
    );

    TypeInfo* Float::getType() const
    {
        return &E_FLOAT_GADGET_TYPEINFO;
    }

    Float::Float()
    : Gadget()
    {
        value = 0;
    }

    Float::~Float() {}


    ////////////////////////////////////////////////////////////////
    // Float serialization
    // <kao2.0059ACC0>
    ////////////////////////////////////////////////////////////////
    void Float::serialize(Archive &ar)
    {
        Gadget::serialize(ar);

        ar.readOrWrite(&value, 0x04);
    }

}
