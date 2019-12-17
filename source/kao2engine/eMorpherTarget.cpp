#include <kao2engine/eMorpherTarget.h>
#include <kao2ar/Archive.h>

#include <kao2engine/e3fXArray.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eMorpherTarget interface
    // <kao2.0049EF79> (constructor)
    // <kao2.0049F020> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_MORPHERTARGET_TYPEINFO
    (
        E_MORPHERTARGET_ID,
        "eMorpherTarget",
        &E_REFCOUNTER_TYPEINFO,
        []() -> eObject*
        {
            return new eMorpherTarget;
        }
    );

    TypeInfo* eMorpherTarget::getType()
    {
        return &E_MORPHERTARGET_TYPEINFO;
    }

    eMorpherTarget::eMorpherTarget()
    : eRefCounter()
    {
        /*[0x08]*/ unknown_08 = nullptr;
        /*[0x0C]*/ unknown_0C = nullptr;
    }

    eMorpherTarget::~eMorpherTarget()
    {
        /*[0x0C]*/ unknown_0C->decRef();
        /*[0x08]*/ unknown_08->decRef();
    }


    ////////////////////////////////////////////////////////////////
    // eMorpherTarget serialization
    // <kao2.0049ECC0>
    ////////////////////////////////////////////////////////////////
    void eMorpherTarget::serialize(Archive &ar)
    {
        /* [0x08] unknown */
        ArFunctions::serialize_e3fXArray(ar, &unknown_08);

        /* [0x0C] unknown */
        ArFunctions::serialize_e3fXArray(ar, &unknown_0C);
    }

}
