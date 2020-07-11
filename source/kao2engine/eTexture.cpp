#include <kao2engine/eTexture.h>
#include <kao2ar/Archive.h>

#include <kao2engine/eTexTransform.h>
#include <kao2engine/eBitmap.h>

#include <utilities/ColladaExporter.h>

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

    TypeInfo* eTexture::getType() const
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
    // eTexture: COLLADA exporting
    ////////////////////////////////////////////////////////////////
    void eTexture::writeNodeToXmlFile(ColladaExporter &exporter) const
    {
        int32_t i;
        char bufor[64];

        if (exporter.objectRefAlreadyExists(COLLADA_EXPORTER_OBJ_EFFECT, this))
        {
            /* Texture was already exported */
            return;
        }

        exporter.openTag("effect");

        i = exporter.getObjectRefId(COLLADA_EXPORTER_OBJ_EFFECT, this, true);
        sprintf_s(bufor, 64, "Texture%d", i);
        exporter.insertTagAttrib("id", bufor);

        exporter.openTag("profile_COMMON");

        exporter.openTag("newparam");
        exporter.insertTagAttrib("sid", "texture-sampler");

        exporter.openTag("sampler2D");

        if (nullptr != bmp)
        {
            exporter.openTag("instance_image");

            i = exporter.getObjectRefId(COLLADA_EXPORTER_OBJ_IMAGE, bmp, false);
            sprintf_s(bufor, 64, "#Bitmap%d", i);
            exporter.insertTagAttrib("url", bufor);

            exporter.closeTag(); // "instance_image"
        }

        exporter.closeTag(); // "sampler2D"
        exporter.closeTag(); // "newparam"

        exporter.openTag("technique");
        exporter.insertTagAttrib("sid", "common");

        exporter.openTag("lambert");
        exporter.openTag("diffuse");

        exporter.openTag("texture");
        exporter.insertTagAttrib("texture", "texture-sampler");
        exporter.insertTagAttrib("texcoord", "UVMap");

        exporter.closeTag(); // "texture"
        exporter.closeTag(); // "diffuse"
        exporter.closeTag(); // "lambert"
        exporter.closeTag(); // "technique"

        exporter.closeTag(); // "profile_COMMON"
        exporter.closeTag(); // "effect"
    }


    ////////////////////////////////////////////////////////////////
    // eTexture: get texture name (used with eTriMesh)
    ////////////////////////////////////////////////////////////////
    GLuint eTexture::getTextureName() const
    {
        if (nullptr != bmp)
        {
            return bmp->getTextureName();
        }

        return 0;
    }


    ////////////////////////////////////////////////////////////////
    // eTexture: get bitmap pointer
    ////////////////////////////////////////////////////////////////
    eBitmap* eTexture::getBitmap() const
    {
        return bmp;
    }


    ////////////////////////////////////////////////////////////////
    // eTexture: set texture transform
    ////////////////////////////////////////////////////////////////
    void eTexture::setTextureTransform(eTexTransform* new_form)
    {
        if (form != new_form)
        {
            if (nullptr != form)
            {
                form->decRef();
            }

            form = new_form;

            if (nullptr != form)
            {
                form->incRef();
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eTexture: check path
    ////////////////////////////////////////////////////////////////
    bool eTexture::matchesPath(eString &searched_path) const
    {
        if (nullptr != bmp)
        {
            if (searched_path.comparePath(bmp->getPath()))
            {
                return true;
            }
        }

        return false;
    }

}
