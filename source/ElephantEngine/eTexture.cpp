#include <ElephantEngine/eTexture.h>
#include <ElephantBase/Archive.h>

#include <ElephantEngine/eTexTransform.h>
#include <ElephantEngine/eBitmap.h>

#include <utilities/ColladaExporter.h>

namespace ZookieWizard
{
    const char* theTextureFlags[KAO2_TEXTURE_FLAGS_COUNT] =
    {
        "WRAP_S: Clamp to Edge\n / Repeat",
        "WRAP_T: Clamp to Edge\n / Repeat",
        "MAG_FILTER: Linear\n / Nearest"
    };


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

    const TypeInfo* eTexture::getType() const
    {
        return &E_TEXTURE_TYPEINFO;
    }

    eTexture::eTexture(eBitmap* x)
    : eRefCounter()
    {
        /*[0x08]*/ textureFlags = 0x00000004;
        /*[0x0C]*/ form = nullptr;

        /*[0x10]*/ bmp = x;
        if (nullptr != bmp)
        {
            bmp->incRef();
        }

        /*[0x14]*/ unknown_14 = 0;

        GUI::materialsManager_InsertTexture(this);
    }

    eTexture::~eTexture()
    {
        GUI::materialsManager_DeleteTexture(this);

        bmp->decRef();
        form->decRef();
    }


    ////////////////////////////////////////////////////////////////
    // eTexture: cloning the object
    ////////////////////////////////////////////////////////////////

    void eTexture::createFromOtherObject(const eTexture &other)
    {
        textureFlags = other.textureFlags;

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

        GUI::materialsManager_UpdateTextureName(this);

        unknown_14 = other.unknown_14;
    }

    eTexture::eTexture(const eTexture &other)
    : eRefCounter(other)
    {
        GUI::materialsManager_InsertTexture(this);

        /****************/

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
        ar.readOrWrite(&textureFlags, 0x04);

        /* Texture tranformation */
        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&form, &E_TEXTRANSFORM_TYPEINFO);

        if (ar.isInReadMode())
        {
            GUI::materialsManager_UpdateTextureName(this);
        }

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
    // eTexture: dump object tree as a JSON value
    ////////////////////////////////////////////////////////////////
    void eTexture::dumpTreeAsJsonValue(JsonValue& output, bool dumpChildNodes) const
    {
        output.setType(JSON_VALUETYPE_OBJECT);
        JsonObject * jsonObjectRef = (JsonObject *) output.getValue();

        /* "eTexture": transform */

        if (nullptr != form)
        {
            JsonValue dummy_value;
            dummy_value.setType(JSON_VALUETYPE_TRUE);

            jsonObjectRef->appendKeyValue("animated", dummy_value);
        }

        /* "eTexture": bitmap path */

        if (nullptr != bmp)
        {
            jsonObjectRef->appendKeyValue("path", bmp->getPath());
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
    // eTexture: optimize data by removing "eBitmap" duplicates
    ////////////////////////////////////////////////////////////////
    void eTexture::optimizeTextureByComparingBitmaps(eTexture &other)
    {
        bool loaded_flag_test;
        int32_t result;

        if (((&other) != this) && (nullptr != bmp) && (nullptr != other.bmp))
        {
            result = bmp->checkSimilarityToAnotherBitmap(*(other.bmp));

            if (result > 0)
            {
                loaded_flag_test = (bmp->getLoadedFromExternalFileFlag() || other.bmp->getLoadedFromExternalFileFlag());

                if (2 == result)
                {
                    setBitmap(other.bmp);
                    bmp->setLoadedFromExternalFileFlag(loaded_flag_test);
                }
                else if (1 == result)
                {
                    other.setBitmap(bmp);
                    other.bmp->setLoadedFromExternalFileFlag(loaded_flag_test);
                }
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eTexture: compare two textures
    ////////////////////////////////////////////////////////////////
    bool eTexture::checkSimilarityToAnotherTexture(const eTexture &other) const
    {
        if ((&other) != this)
        {
            if (textureFlags != other.textureFlags)
            {
                return false;
            }

            if (form != other.form)
            {
                return false;
            }

            if (bmp != other.bmp)
            {
                return false;
            }

            /* Property [eTexture + 0x14] is probably not used */
        }

        return true;
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
    // eTexture: apply or erase flag bits
    ////////////////////////////////////////////////////////////////

    uint32_t eTexture::getTextureFlags() const
    {
        return textureFlags;
    }

    void eTexture::setTextureFlags(uint32_t bits_to_apply)
    {
        textureFlags |= bits_to_apply;
    }

    void eTexture::unsetTextureFlags(uint32_t bits_to_erase)
    {
        textureFlags &= (~bits_to_erase);
    }


    ////////////////////////////////////////////////////////////////
    // eTexture: get or set the bitmap pointer
    ////////////////////////////////////////////////////////////////

    eBitmap* eTexture::getBitmap() const
    {
        return bmp;
    }

    void eTexture::setBitmap(eBitmap* new_bitmap)
    {
        if (bmp != new_bitmap)
        {
            bmp->decRef();

            bmp = new_bitmap;

            if (nullptr != bmp)
            {
                bmp->incRef();
            }
        }
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
    // eTexture: get or set the texture transform
    ////////////////////////////////////////////////////////////////

    eTexTransform* eTexture::getTextureTransform() const
    {
        return form;
    }

    void eTexture::setTextureTransform(eTexTransform* new_form)
    {
        if (form != new_form)
        {
            form->decRef();

            form = new_form;

            if (nullptr != form)
            {
                form->incRef();
            }
        }
    }

}
