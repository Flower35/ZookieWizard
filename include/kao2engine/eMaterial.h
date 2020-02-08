#ifndef H_KAO2AR_MATERIAL
#define H_KAO2AR_MATERIAL

#include <kao2engine/eRefCounter.h>

#include <kao2ar/Collection.h>

namespace ZookieWizard
{
    class eTexture;
    class eMaterialState;

    struct MaterialType
    {
        int32_t id;
        const char* name;
    };

    extern MaterialType materialTypes[16];

    ////////////////////////////////////////////////////////////////
    // eMaterial interface
    ////////////////////////////////////////////////////////////////

    class eMaterial : public eRefCounter
    {

        /*** Properties ***/

        protected:

            /*[0x08-0x10]*/ Collection<ArFunctions::serialize_eRefCounter> textures;
            /*[0x14]*/ uint8_t materialFlags;
            /*[0x18]*/ eMaterialState* state;
            /*[0x1C]*/ int32_t collisionType;
            /*[0x20]*/ int16_t unknown_20;
            /*[0x22]*/ int16_t unknown_22;
            /*[0x24]*/ eString name;
            /*[0x28]*/ int32_t transpLayer;
            /*[0x2C]*/ float unknown_2C;


        /*** Methods ***/

        public:

            eMaterial(eTexture* x);
            ~eMaterial();

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;

            eString getStringRepresentation() const override;
            void setName(eString new_name);

            void writeNodeToXmlFile(ColladaExporter &exporter) const override;

            eTexture* getIthTexture(int32_t i) const;
            void appendTexture(eTexture* new_texture);

            bool hasInvisibleInName() const;

            void setMaterialFlags(uint8_t bits_to_apply);
            void unsetMaterialFlags(uint8_t bits_to_erase);

            eMaterialState* getMaterialState() const;
            void setMaterialState(eMaterialState* new_mtl_state);

            int32_t getCollisionType() const;
            void setCollisionType(int32_t new_type);

    };


    ////////////////////////////////////////////////////////////////
    // eMaterial TypeInfo
    // <kao2.0047D2F0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_MATERIAL_ID = 0x1003;

    extern TypeInfo E_MATERIAL_TYPEINFO;

}

#endif
