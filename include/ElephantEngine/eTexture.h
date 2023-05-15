#ifndef H_KAO2AR_TEXTURE
#define H_KAO2AR_TEXTURE

#include <ElephantEngine/eRefCounter.h>

namespace ZookieWizard
{
    class eTexTransform;
    class eBitmap;
    struct eAnimate;

    ////////////////////////////////////////////////////////////////
    // eTexture helper definitions
    ////////////////////////////////////////////////////////////////

    #define KAO2_TEXTURE_FLAGS_COUNT 3

    extern const char* theTextureFlags[KAO2_TEXTURE_FLAGS_COUNT];


    ////////////////////////////////////////////////////////////////
    // eTexture interface
    // <kao2.005D0760> (vptr)
    ////////////////////////////////////////////////////////////////

    class eTexture : public eRefCounter
    {
        /*** Properties ***/

        protected:

            /*[0x08]*/ uint32_t textureFlags;
            /*[0x0C]*/ eTexTransform* form;
            /*[0x10]*/ eBitmap* bmp;
            /*[0x14]*/ int32_t unknown_14;

        /*** Methods ***/

        public:

            eTexture(eBitmap* x);
            ~eTexture();

        private:

            void createFromOtherObject(const eTexture &other);

        public:

            eTexture(const eTexture &other);
            eTexture& operator = (const eTexture &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
            void serialize(Archive &ar) override;

            void dumpTreeAsJsonValue(JsonValue& output, bool dumpChildNodes) const override;
            void writeNodeToXmlFile(ColladaExporter &exporter) const override;

            /* << eTexture >> */

            void optimizeTextureByComparingBitmaps(eTexture &other);
            bool checkSimilarityToAnotherTexture(const eTexture &other) const;

            bool matchesPath(eString &searched_path) const;

            GLuint getTextureId() const;

            uint32_t getTextureFlags() const;
            void setTextureFlags(uint32_t bits_to_apply);
            void unsetTextureFlags(uint32_t bits_to_erase);

            eBitmap* getBitmap() const;
            void setBitmap (eBitmap* new_bitmap);

            void updateTextureMatrix(eAnimate* anim) const;

            eTexTransform* getTextureTransform() const;
            void setTextureTransform(eTexTransform* new_form);
    };


    ////////////////////////////////////////////////////////////////
    // eTexture TypeInfo
    // <kao2.00473570> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_TEXTURE_ID = 0x1002;

    extern TypeInfo E_TEXTURE_TYPEINFO;

}

#endif
