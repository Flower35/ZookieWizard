#include <kao2engine/eTexture.h>
#include <kao2ar/Archive.h>

#include <kao2engine/eTexTransform.h>
#include <kao2engine/eBitmap.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eTexture interface
    // <kao2.00472F80> (constructor)
    // <kao2.004731C0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_TEXTURE_TYPEINFO
    (
        E_TEXTURE_ID,
        "eTexture",
        &E_REFCOUNTER_TYPEINFO,
        []() -> eObject*
        {
            return new eTexture(nullptr);
        }
    );

    TypeInfo* eTexture::getType()
    {
        return &E_TEXTURE_TYPEINFO;
    }

    eTexture::eTexture(eBitmap* x)
    : eRefCounter()
    {
        /*[0x08]*/ params = 0x00000004;
        /*[0x0C]*/ form = nullptr;
        
        /*[0x10]*/ bmp = x;
        if (nullptr != bmp)
        {
            bmp->incRef();
        }

        /*[0x14]*/ unknown_14 = 0;
    }

    eTexture::~eTexture()
    {
        bmp->decRef();
        form->decRef();
    }


    ////////////////////////////////////////////////////////////////
    // eTexture serialization
    // <kao2.004732A0>
    ////////////////////////////////////////////////////////////////
    void eTexture::serialize(Archive &ar)
    {
        /* Bitmap */
        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&bmp, &E_BITMAP_TYPEINFO);

        /* `glTexParameteri` flags */
        ar.readOrWrite(&params, 0x04);

        /* Texture tranformation */
        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&form, &E_TEXTRANSFORM_TYPEINFO);

        /* [0x14] unknown */
        if (ar.getVersion() >= 0x6D)
        {
            ar.readOrWrite(&unknown_14, 0x04);
        }
        else
        {
            unknown_14 = 0;
        }
    }


    ////////////////////////////////////////////////////////////////
    // eTexture: get texture name (used with eTriMesh)
    ////////////////////////////////////////////////////////////////
    GLuint eTexture::getTextureName()
    {
        if (nullptr != bmp)
        {
            return bmp->getTextureName();
        }

        return 0;
    }

}
