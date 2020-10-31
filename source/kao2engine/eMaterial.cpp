#include <kao2engine/eMaterial.h>
#include <kao2ar/Archive.h>

#include <kao2engine/eTexture.h>
#include <kao2engine/eMaterialState.h>

#include <utilities/ColladaExporter.h>

namespace ZookieWizard
{
    MaterialType theMaterialTypes[KAO2_MATERIAL_TYPES_COUNT] =
    {
        {0x00000000, "NORMAL"},
        {0x00000001, "ICE"},
        {0x00000002, "CLIMB"},
        {0x00000003, "EARWALK"},
        {0x40000004, "SWAMP"},
        {0x40000005, "SWAMP_WALL"},
        {0x20000006, "HURT_GROUND"},
        {0x20000007, "HURT_OBJECT"},
        {0x40000008, "SWAMP_RAMP"},
        {0x30000009, "KILL_WATER"},
        {0x1000000A, "GIRAFFE_WATER"},
        {0x0000000B, "ICE_JUMP"},
        {0x4000000C, "SWAMP_SLOW"},
        {0x2000000D, "HURT_LAVA"},
        {0x2000000E, "KILL_OBJECT"},
        {0x80000000, "DESTROYABLE"}
    };

    MaterialSound theMaterialSounds[KAO2_MATERIAL_SOUNDS_COUNT] =
    {
        {0x0000, "GRASS"},
        {0x1000, "WOOD"},
        {0x2000, "METAL"},
        {0x4000, "STONE"},
        {0x8000, "SNOW"},
        {0x0001, "SAND"}
    };

    const char* theMaterialFlags[KAO2_MATERIAL_FLAGS_COUNT] =
    {
        "2-SIDED", "BLEND", "ADDITIVE", "ALPHA_TEST"
    };


    ////////////////////////////////////////////////////////////////
    // eMaterial interface
    // <kao2.0047C7F0> (constructor)
    // <kao2.0047CA20> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_MATERIAL_TYPEINFO
    (
        E_MATERIAL_ID,
        "eMaterial",
        &E_REFCOUNTER_TYPEINFO,
        []() -> eObject*
        {
            return new eMaterial(nullptr);
        }
    );

    TypeInfo* eMaterial::getType() const
    {
        return &E_MATERIAL_TYPEINFO;
    }

    eMaterial::eMaterial(eTexture* x)
    : eRefCounter()
    {
        /*[0x18]*/ state = nullptr;

        /*[0x1C]*/ collisionType = 0;
        /*[0x20]*/ unknown_20 = 0;
        /*[0x22]*/ soundType = 0;

        /*[0x14]*/ materialFlags = 0x00;
        /*[0x28]*/ transpLayer = 0;
        /*[0x2C]*/ alphaTestRef = 0.5f;

        if (nullptr != x)
        {
            textures.appendChild(x);
        }

        GUI::materialsManager_InsertMaterial(this);
    }

    eMaterial::~eMaterial()
    {
        GUI::materialsManager_DeleteMaterial(this);

        state->decRef();
    }


    ////////////////////////////////////////////////////////////////
    // eMaterial: cloning the object
    ////////////////////////////////////////////////////////////////

    void eMaterial::createFromOtherObject(const eMaterial &other)
    {
        textures = other.textures;

        materialFlags = other.materialFlags;

        if (nullptr != other.state)
        {
            state = new eMaterialState(*(other.state));
        }
        else
        {
            state = nullptr;
        }

        collisionType = other.collisionType;

        unknown_20 = other.unknown_20;

        soundType = other.soundType;

        name = other.name;
        GUI::materialsManager_UpdateMaterialName(this);

        transpLayer = other.transpLayer;

        alphaTestRef = other.alphaTestRef;
    }

    eMaterial::eMaterial(const eMaterial &other)
    : eRefCounter(other)
    {
        GUI::materialsManager_InsertMaterial(this);

        /****************/

        createFromOtherObject(other);
    }

    eMaterial& eMaterial::operator = (const eMaterial &other)
    {
        if ((&other) != this)
        {
            eRefCounter::operator = (other);

            /****************/

            state->decRef();

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eMaterial::cloneFromMe() const
    {
        return new eMaterial(*this);
    }


    ////////////////////////////////////////////////////////////////
    // eMaterial: serialization
    // <kao2.0047CB10>
    ////////////////////////////////////////////////////////////////
    void eMaterial::serialize(Archive &ar)
    {
        int32_t test;

        /* [0x08] Textures collection */
        textures.serialize(ar, &E_TEXTURE_TYPEINFO);

        /* [0x14] unknown */
        ar.readOrWrite(&materialFlags, 0x01);

        /* [0x18] Material state */
        if (ar.getVersion() >= 0x74)
        {
            ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&state, &E_MATERIALSTATE_TYPEINFO);
        }
        else
        {
            if (ar.isInReadMode())
            {
                state->decRef();
            }

            state = new eMaterialState();
            state->serialize(ar);

            if (ar.isInReadMode())
            {
                state->incRef();
            }
        }

        /* Sounds and collision structures */
        if (ar.getVersion() >= 0x6C)
        {
            ar.readOrWrite(&collisionType, 0x04);
            ar.readOrWrite(&unknown_20, 0x02);
            ar.readOrWrite(&soundType, 0x02);
        }
        else
        {
            /* <kao2.004B90BD> */

            if (ar.isInReadMode())
            {
                ar.readOrWrite(&test, 0x04);

                unknown_20 = (test >> 0x10) & 0x0000F000;

                switch (test & 0x0F000000)
                {
                    case 0x01000000:
                    {
                        soundType = 0x40;

                        test &= 0x00FFFFFF;
                        collisionType = theMaterialTypes[test].id;

                        break;
                    }

                    case 0x02000000:
                    {
                        soundType = 0x10;
                    }

                    default:
                    {
                        test &= 0x00FFFFFF;
                        collisionType = theMaterialTypes[test].id;

                    }
                }
            }
            else
            {
                throw ErrorMessage
                (
                    "eMaterial::serialize():" \
                    "ar.version() smaller than 108 not supported for saving..."
                );
            }
        }

        /* Material name */
        ar.serializeString(name);

        if (ar.isInReadMode())
        {
            GUI::materialsManager_UpdateMaterialName(this);
        }

        /* [0x28] unknown */
        ar.readOrWrite(&transpLayer, 0x04);

        /* [0x2C] AlphaTest reference value */
        ar.readOrWrite(&alphaTestRef, 0x04);
    }


    ////////////////////////////////////////////////////////////////
    // eMaterial: COLLADA exporting
    ////////////////////////////////////////////////////////////////
    void eMaterial::writeNodeToXmlFile(ColladaExporter &exporter) const
    {
        int32_t i;
        char bufor[64];
        float color[4];
        eTexture* test_texture;

        if (exporter.objectRefAlreadyExists(COLLADA_EXPORTER_OBJ_MATERIAL, this))
        {
            /* Material was already exported */
            return;
        }

        exporter.openTag("material");

        i = exporter.getObjectRefId(COLLADA_EXPORTER_OBJ_MATERIAL, this, true);
        sprintf_s(bufor, 64, "Material%d", i);
        exporter.insertTagAttrib("id", bufor);
        exporter.insertTagAttrib("name", name);

        test_texture = getIthTexture(0);

        if (nullptr != test_texture)
        {
            exporter.openTag("instance_effect");

            i = exporter.getObjectRefId(COLLADA_EXPORTER_OBJ_EFFECT, test_texture, false);
            sprintf_s(bufor, 64, "#Texture%d", i);
            exporter.insertTagAttrib("url", bufor);

            if (nullptr != state)
            {
                exporter.openTag("setparam");
                exporter.insertTagAttrib("ref", "AMBIENT");

                state->getAmbientColor(color);
                sprintf_s(bufor, 64, "%f %f %f", color[0], color[1], color[2]);

                exporter.openTag("float3");
                exporter.writeInsideTag(bufor);
                exporter.closeTag(); // "float3"
                exporter.closeTag(); // "setparam"

                exporter.openTag("setparam");
                exporter.insertTagAttrib("ref", "DIFFUSE");

                state->getDiffuseColor(color);
                sprintf_s(bufor, 64, "%f %f %f", color[0], color[1], color[2]);

                exporter.openTag("float3");
                exporter.writeInsideTag(bufor);
                exporter.closeTag(); // "float3"
                exporter.closeTag(); // "setparam"

                exporter.openTag("setparam");
                exporter.insertTagAttrib("ref", "SPECULAR");

                state->getSpecularColor(color);
                sprintf_s(bufor, 64, "%f %f %f", color[0], color[1], color[2]);

                exporter.openTag("float3");
                exporter.writeInsideTag(bufor);
                exporter.closeTag(); // "float3"
                exporter.closeTag(); // "setparam"

                exporter.openTag("setparam");
                exporter.insertTagAttrib("ref", "SHININESS");

                color[0] = state->getShininess();
                sprintf_s(bufor, 64, "%f", color[0]);

                exporter.openTag("float");
                exporter.writeInsideTag(bufor);
                exporter.closeTag(); // "float"
                exporter.closeTag(); // "setparam"
            }

            exporter.closeTag(); // "instance_effect"
        }

        exporter.closeTag(); // "material"
    }


    ////////////////////////////////////////////////////////////////
    // eMaterial: optimize data by removing "eTexture" or "eMaterialState" duplicates
    ////////////////////////////////////////////////////////////////
    void eMaterial::optimizeMaterialByComparingTexturesAndStates(eMaterial &other)
    {
        int32_t a, b, textures_count[2];
        eTexture* dummy_texture[2];

        if ((&other) != this)
        {
            textures_count[0] = textures.getSize();
            textures_count[1] = other.textures.getSize();

            for (a = 0; a < textures_count[0]; a++)
            {
                if (nullptr != (dummy_texture[0] = (eTexture*)textures.getIthChild(a)))
                {
                    for (b = 0; b < textures_count[1]; b++)
                    {
                        if (nullptr != (dummy_texture[1] = (eTexture*)other.textures.getIthChild(a)))
                        {
                            if (dummy_texture[0]->checkSimilarityToAnotherTexture(*(dummy_texture[1])))
                            {
                                setIthTexture(a, dummy_texture[1]);
                            }
                        }
                    }
                }
            }

            if ((nullptr != state) && (nullptr != other.state))
            {
                if (state->checkSimilarityToAnotherState(*(other.state)))
                {
                    setMaterialState(other.state);
                }
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eMaterial: compare two materials
    ////////////////////////////////////////////////////////////////
    bool eMaterial::checkSimilarityToAnotherMaterial(const eMaterial &other) const
    {
        int32_t a, textures_count;

        if ((&other) != this)
        {
            if ((textures_count = textures.getSize()) != other.textures.getSize())
            {
                return false;
            }

            for (a = 0; a < textures_count; a++)
            {
                if (textures.getIthChild(a) != other.textures.getIthChild(a))
                {
                    return false;
                }
            }

            if (materialFlags != other.materialFlags)
            {
                return false;
            }

            if (state != other.state)
            {
                return false;
            }

            if (collisionType != other.collisionType)
            {
                return false;
            }

            /* Property [eMaterial + 0x20] is probably not used */

            if (soundType != other.soundType)
            {
                return false;
            }

            /* Name property is not important */

            /* "transpLayer" property is probably not used */

            if (alphaTestRef != other.alphaTestRef)
            {
                return false;
            }
        }

        return true;
    }


    ////////////////////////////////////////////////////////////////
    // eMaterial: get textures count
    ////////////////////////////////////////////////////////////////
    int32_t eMaterial::getTexturesCount() const
    {
        return textures.getSize();
    }


    ////////////////////////////////////////////////////////////////
    // eMaterial: get or set the i-th texture
    ////////////////////////////////////////////////////////////////

    eTexture* eMaterial::getIthTexture(int32_t i) const
    {
        return (eTexture*)textures.getIthChild(i);
    }

    void eMaterial::setIthTexture(int32_t i, eTexture* new_texture)
    {
        /* The Collection does all the necessary checks */
        textures.setIthChild(i, new_texture);
    }


    ////////////////////////////////////////////////////////////////
    // eMaterial: append texture
    ////////////////////////////////////////////////////////////////
    void eMaterial::appendTexture(eTexture* new_texture)
    {
        textures.appendChild(new_texture);
    }


    ////////////////////////////////////////////////////////////////
    // eMaterial: remove i-th texture
    ////////////////////////////////////////////////////////////////
    void eMaterial::removeTexture(int32_t i)
    {
        textures.deleteIthChild(i);
    }


    ////////////////////////////////////////////////////////////////
    // eMaterial: swap some two textures
    ////////////////////////////////////////////////////////////////
    void eMaterial::swapTexture(int32_t i, int32_t direction)
    {
        if (direction > 0)
        {
            textures.swapForward(i);
        }
        else if (direction < 0)
        {
            textures.swapBackward(i);
        }
    }


    ////////////////////////////////////////////////////////////////
    // eMaterial: get or set the Material name
    ////////////////////////////////////////////////////////////////

    eString eMaterial::getStringRepresentation() const
    {
        return name;
    }

    void eMaterial::setName(eString new_name)
    {
        name = new_name;

        GUI::materialsManager_UpdateMaterialName(this);
    }


    ////////////////////////////////////////////////////////////////
    // eMaterial: find if name contains "invisible" (used with eTriMesh)
    ////////////////////////////////////////////////////////////////
    bool eMaterial::hasInvisibleInName() const
    {
        return std::strstr(name.getText(), "invisible");
    }


    ////////////////////////////////////////////////////////////////
    // eMaterial: check filename
    ////////////////////////////////////////////////////////////////
    bool eMaterial::matchesPath(eString &searched_path) const
    {
        int i;
        eTexture* dummy_texture;

        for (i = 0; i < textures.getSize(); i++)
        {
            dummy_texture = (eTexture*)textures.getIthChild(i);

            if (nullptr != dummy_texture)
            {
                if (dummy_texture->matchesPath(searched_path))
                {
                    return true;
                }
            }
        }

        return false;
    }


    ////////////////////////////////////////////////////////////////
    // eMaterial: apply or erase flag bits
    ////////////////////////////////////////////////////////////////

    uint8_t eMaterial::getMaterialFlags() const
    {
        return materialFlags;
    }

    void eMaterial::setMaterialFlags(uint8_t bits_to_apply)
    {
        materialFlags |= bits_to_apply;
    }

    void eMaterial::unsetMaterialFlags(uint8_t bits_to_erase)
    {
        materialFlags &= (~bits_to_erase);
    }


    ////////////////////////////////////////////////////////////////
    // eMaterial: get or set material state
    ////////////////////////////////////////////////////////////////

    eMaterialState* eMaterial::getMaterialState() const
    {
        return state;
    }

    void eMaterial::setMaterialState(eMaterialState* new_mtl_state)
    {
        if (state != new_mtl_state)
        {
            state->decRef();

            state = new_mtl_state;

            if (nullptr != state)
            {
                state->incRef();
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eMaterial: get or set collision type
    ////////////////////////////////////////////////////////////////

    uint32_t eMaterial::getCollisionType() const
    {
        return collisionType;
    }

    void eMaterial::setCollisionType(uint32_t new_type)
    {
        collisionType = new_type;
    }


    ////////////////////////////////////////////////////////////////
    // eMaterial: get or set sound type
    ////////////////////////////////////////////////////////////////

    uint16_t eMaterial::getSoundType() const
    {
        return soundType;
    }

    void eMaterial::setSoundType(uint16_t new_type)
    {
        soundType = new_type;
    }


    ////////////////////////////////////////////////////////////////
    // eMaterial: get or set the AlphaTest reference value
    ////////////////////////////////////////////////////////////////
    float eMaterial::getAlphaTestRef() const
    {
        return alphaTestRef;
    }

    void eMaterial::setAlphaTestRef(float new_alpha)
    {
        alphaTestRef = new_alpha;

        if (alphaTestRef < 0)
        {
            alphaTestRef = 0;
        }
        else if (alphaTestRef > 1)
        {
            alphaTestRef = 1;
        }
    }

}
