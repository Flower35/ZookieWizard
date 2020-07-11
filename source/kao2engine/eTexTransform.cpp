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
        xScale = nullptr;
        yScale = nullptr;
        uOffset = nullptr;
        vOffset = nullptr;
    }

    eTexTransform::~eTexTransform()
    {
        xScale->decRef();
        yScale->decRef();
        uOffset->decRef();
        vOffset->decRef();
    }


    ////////////////////////////////////////////////////////////////
    // eTexTransform serialization
    // <kao2.00472C80>
    ////////////////////////////////////////////////////////////////
    void eTexTransform::serialize(Archive &ar)
    {
        /* Texture's X-scale controller */
        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&xScale, &E_LEAFCTRL_FLOAT_TYPEINFO);

        /* Texture's Y-scale controller */
        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&yScale, &E_LEAFCTRL_FLOAT_TYPEINFO);

        /* Texture's U-offset controller */
        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&uOffset, &E_LEAFCTRL_FLOAT_TYPEINFO);

        /* Texture's V-offset controller */
        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&vOffset, &E_LEAFCTRL_FLOAT_TYPEINFO);
    }

}
