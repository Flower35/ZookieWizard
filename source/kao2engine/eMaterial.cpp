#include <kao2engine/eMaterial.h>
#include <kao2ar/Archive.h>

#include <kao2engine/eTexture.h>
#include <kao2engine/eMaterialState.h>

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

    TypeInfo* eMaterial::getType()
    {
        return &E_MATERIAL_TYPEINFO;
    }

    eMaterial::eMaterial(eTexture* x)
    : eRefCounter()
    {
        /*[0x18]*/ state = nullptr;

        /*[0x1C]*/ unknown_1C = 0;
        /*[0x20]*/ unknown_20 = 0;
        /*[0x22]*/ unknown_22 = 0;

        /*[0x14]*/ materialFlags = 0x00;
        /*[0x28]*/ transpLayer = 0;
        /*[0x2C]*/ unknown_2C = 0;

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
            ar.readOrWrite(&unknown_1C, 0x04);
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
                        unknown_1C = materialTypes[test].id;

                        break;
                    }

                    case 0x02000000:
                    {
                        unknown_22 = 0x10;
                    }

                    default:
                    {
                        test &= 0x00FFFFFF;
                        unknown_1C = materialTypes[test].id;

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
    // eMaterial: get i-th texture (used with eTriMesh)
    ////////////////////////////////////////////////////////////////
    eTexture* eMaterial::getIthTexture(int32_t i)
    {
        return (eTexture*)textures.getIthChild(i);
    }


    ////////////////////////////////////////////////////////////////
    // eMaterial: get name
    ////////////////////////////////////////////////////////////////
    eString eMaterial::getStringRepresentation()
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
    bool eMaterial::hasInvisibleInName()
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

}
