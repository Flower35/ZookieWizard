#include <kao2engine/eMaterial.h>
#include <kao2ar/Archive.h>

#include <kao2engine/eTexture.h>
#include <kao2engine/eMaterialState.h>

#include <utilities/ColladaExporter.h>

namespace ZookieWizard
{
    MaterialType materialTypes[16] =
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
        /*[0x22]*/ unknown_22 = 0;

        /*[0x14]*/ materialFlags = 0x00;
        /*[0x28]*/ transpLayer = 0;
        /*[0x2C]*/ unknown_2C = 0.5f;

        if (nullptr != x)
        {
            textures.appendChild(x);
        }
    }

    eMaterial::~eMaterial()
    {
        state->decRef();
    }


    ////////////////////////////////////////////////////////////////
    // eMaterial serialization
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
            ar.readOrWrite(&unknown_22, 0x02);
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
                        unknown_22 = 0x40;

                        test &= 0x00FFFFFF;
                        collisionType = materialTypes[test].id;

                        break;
                    }

                    case 0x02000000:
                    {
                        unknown_22 = 0x10;
                    }

                    default:
                    {
                        test &= 0x00FFFFFF;
                        collisionType = materialTypes[test].id;

                    }
                }
            }
            else
            {
                throw ErrorMessage
                (
                    "eMaterial::serialize():" \
                    "ar.version smaller than 108 not supported for saving..."
                );
            }
        }

        /* Material name */
        ar.serializeString(name);

        /* [0x28] unknown */
        ar.readOrWrite(&transpLayer, 0x04);

        /* [0x2C] unknown */
        ar.readOrWrite(&unknown_2C, 0x04);
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
    // eMaterial: get i-th texture (used with eTriMesh)
    ////////////////////////////////////////////////////////////////
    eTexture* eMaterial::getIthTexture(int32_t i) const
    {
        return (eTexture*)textures.getIthChild(i);
    }


    ////////////////////////////////////////////////////////////////
    // eMaterial: append texture
    ////////////////////////////////////////////////////////////////
    void eMaterial::appendTexture(eTexture* new_texture)
    {
        textures.appendChild(new_texture);
    }


    ////////////////////////////////////////////////////////////////
    // eMaterial: get name
    ////////////////////////////////////////////////////////////////
    eString eMaterial::getStringRepresentation() const
    {
        return name;
    }


    ////////////////////////////////////////////////////////////////
    // eMaterial: set name
    ////////////////////////////////////////////////////////////////
    void eMaterial::setName(eString new_name)
    {
        name = new_name;
    }


    ////////////////////////////////////////////////////////////////
    // eMaterial: find if name contains "invisible" (used with eTriMesh)
    ////////////////////////////////////////////////////////////////
    bool eMaterial::hasInvisibleInName() const
    {
        return std::strstr(name.getText(), "invisible");
    }


    ////////////////////////////////////////////////////////////////
    // eMaterial: apply or erase flag bits
    ////////////////////////////////////////////////////////////////

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

    void eMaterial::setMaterialState(eMaterialState* new_mtl_state)
    {
        if (state == new_mtl_state)
        {
            return;
        }

        if (nullptr != state)
        {
            state->decRef();
        }

        state = new_mtl_state;

        if (nullptr != state)
        {
            state->incRef();
        }
    }

    eMaterialState* eMaterial::getMaterialState() const
    {
        return state;
    }


    ////////////////////////////////////////////////////////////////
    // eMaterial: get or set collision type
    ////////////////////////////////////////////////////////////////

    void eMaterial::setCollisionType(int32_t new_type)
    {
        collisionType = new_type;
    }

    int32_t eMaterial::getCollisionType() const
    {
        return collisionType;
    }

}
