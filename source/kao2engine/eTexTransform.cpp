#include <kao2engine/eTexTransform.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eTexTransform interface
    // <kao2.00472DE9> (constructor)
    // <kao2.00472E80> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_TEXTRANSFORM_TYPEINFO
    (
        E_TEXTRANSFORM_ID,
        "eTexTransform",
        &E_REFCOUNTER_TYPEINFO,
        []() -> eObject*
        {
            return new eTexTransform;
        }
    );

    TypeInfo* eTexTransform::getType() const
    {
        return &E_TEXTRANSFORM_TYPEINFO;
    }

    eTexTransform::eTexTransform()
    : eRefCounter()
    {
        unknown_08 = nullptr;
        unknown_0C = nullptr;
        unknown_10 = nullptr;
        unknown_14 = nullptr;
    }

    eTexTransform::~eTexTransform()
    {
        unknown_08->decRef();
        unknown_0C->decRef();
        unknown_10->decRef();
        unknown_14->decRef();
    }


    ////////////////////////////////////////////////////////////////
    // eTexTransform serialization
    // <kao2.00472C80>
    ////////////////////////////////////////////////////////////////
    void eTexTransform::serialize(Archive &ar)
    {
        /* unknown */
        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&unknown_08, &E_LEAFCTRL_FLOAT_TYPEINFO);

        /* unknown */
        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&unknown_0C, &E_LEAFCTRL_FLOAT_TYPEINFO);

        /* unknown */
        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&unknown_10, &E_LEAFCTRL_FLOAT_TYPEINFO);

        /* unknown */
        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&unknown_14, &E_LEAFCTRL_FLOAT_TYPEINFO);
    }

}
