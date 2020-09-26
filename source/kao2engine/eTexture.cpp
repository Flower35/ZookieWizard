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
    // eTexture: cloning the object
    ////////////////////////////////////////////////////////////////

    void eTexture::createFromOtherObject(const eTexture &other)
    {
        params = other.params;

        form = other.form;
        if (nullptr != form)
        {
            form->incRef();
        }

        bmp = other.bmp;
        if (nullptr != bmp)
        {
            bmp->incRef();
        }

        unknown_14 = other.unknown_14;
    }

    eTexture::eTexture(const eTexture &other)
    : eRefCounter(other)
    {
        createFromOtherObject(other);
    }

    eTexture& eTexture::operator = (const eTexture &other)
    {
        if ((&other) != this)
        {
            eRefCounter::operator = (other);

            /****************/

            form->decRef();
            bmp->decRef();

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eTexture::cloneFromMe() const
    {
        return new eTexture(*this);
    }


    ////////////////////////////////////////////////////////////////
    // eTexture: serialization
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


    ////////////////////////////////////////////////////////////////
    // eTexture: get texture name index
    ////////////////////////////////////////////////////////////////
    GLuint eTexture::getTextureId() const
    {
        if (nullptr != bmp)
        {
            return bmp->getTextureId();
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
    // eTexture: update OpenGL TEXTURE matrix, if "eTexTransform" exists
    ////////////////////////////////////////////////////////////////
    void eTexture::updateTextureMatrix(eAnimate* anim) const
    {
        if ((nullptr != form) && (nullptr != anim))
        {
            form->updateTextureMatrix(anim);
        }
        else
        {
            glMatrixMode(GL_TEXTURE);

            glLoadIdentity();

            glMatrixMode(GL_MODELVIEW);
        }
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

}
