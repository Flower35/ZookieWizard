#ifndef H_KAO2AR_MATERIAL
#define H_KAO2AR_MATERIAL

#include <ElephantEngine/eRefCounter.h>

#include <ElephantBase/Collection.h>

namespace ZookieWizard
{
    class eTexture;
    class eMaterialState;
    class eShaderData;

    ////////////////////////////////////////////////////////////////
    // eMaterial helper definitions
    ////////////////////////////////////////////////////////////////

    #define KAO2_MATERIAL_TYPES_COUNT 16
    #define KAO2_MATERIAL_SOUNDS_COUNT 6
    #define KAO2_MATERIAL_FLAGS_COUNT 4

    struct MaterialType
    {
        uint32_t id;
        const char* name;
    };

    struct MaterialSound
    {
        uint16_t id;
        const char* name;
    };

    extern MaterialType theMaterialTypes[KAO2_MATERIAL_TYPES_COUNT];
    extern MaterialSound theMaterialSounds[KAO2_MATERIAL_SOUNDS_COUNT];
    extern const char* theMaterialFlags[KAO2_MATERIAL_FLAGS_COUNT];


    ////////////////////////////////////////////////////////////////
    // eMaterial interface
    // <kao2.005D0C1C> (vptr)
    ////////////////////////////////////////////////////////////////

    class eMaterial : public eRefCounter
    {
        /*** Properties ***/

        protected:

            /*[0x08-0x10]*/ Collection<ArFunctions::serialize_eRefCounter> textures;
            /*[0x14]*/ uint16_t materialFlags;
            /*[0x18]*/ eMaterialState* state;
            /*[0x1C]*/ uint32_t collisionType;
            /*[0x20]*/ uint16_t unknown_20;
            /*[0x22]*/ uint16_t soundType;
            /*[0x24]*/ eString name;
            /*[0x28]*/ int32_t transpLayer;
            /*[0x2C]*/ float alphaTestRef;

            /*[0x34]*/ eShaderData* shaderData;

        /*** Methods ***/

        public:

            eMaterial(eTexture* x);
            ~eMaterial();

        private:

            void createFromOtherObject(const eMaterial &other);

        public:

            eMaterial(const eMaterial &other);
            eMaterial& operator = (const eMaterial &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
            void serialize(Archive &ar) override;

            eString getStringRepresentation() const override;
            void writeNodeToXmlFile(ColladaExporter &exporter) const override;

            /* << eMaterial >> */

            void optimizeMaterialByComparingTexturesAndStates(eMaterial &other);
            bool checkSimilarityToAnotherMaterial(const eMaterial &other) const;

            int32_t getTexturesCount() const;
            eTexture* getIthTexture(int32_t i) const;
            void setIthTexture(int32_t i, eTexture* new_texture);
            void appendTexture(eTexture* new_texture);
            void removeTexture(int32_t i);
            void swapTexture(int32_t i, int32_t direction);

            void setName(eString new_name);
            bool hasInvisibleInName() const;

            bool matchesPath(eString &searched_path) const;

            uint16_t getMaterialFlags() const;
            void setMaterialFlags(uint16_t bits_to_apply);
            void unsetMaterialFlags(uint16_t bits_to_erase);

            eMaterialState* getMaterialState() const;
            void setMaterialState(eMaterialState* new_mtl_state);

            uint32_t getCollisionType() const;
            void setCollisionType(uint32_t new_type);

            uint16_t getSoundType() const;
            void setSoundType(uint16_t new_type);

            float getAlphaTestRef() const;
            void setAlphaTestRef(float new_alpha);
    };


    ////////////////////////////////////////////////////////////////
    // eMaterial TypeInfo
    // <kao2.0047D2C0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_MATERIAL_ID = 0x1003;

    extern TypeInfo E_MATERIAL_TYPEINFO;

}

#endif
