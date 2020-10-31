#ifndef H_KAO2AR_BITMAP
#define H_KAO2AR_BITMAP

#include <kao2engine/eRefCounter.h>

namespace ZookieWizard
{
    ////////////////////////////////////////////////////////////////
    // eBitmap helper definitions
    ////////////////////////////////////////////////////////////////

    namespace ArFunctions
    {
        bool isValidImageWidth(int32_t test);
    }

    enum bitmapType
    {
        RGBA8 = 0x00,
        RGB8 = 0x01,
        PAL8_RGBA8 = 0x02,
        PAL8_RGBX8 = 0x03,
        RGBX8 = 0x04,
        PAL8_RGBA8_IDTEX8 = 0x05,
        PAL8_RGBX8_IDTEX8 = 0x06,
        RGBA8_SWIZZLED = 0x2C,
        RGBX8_SWIZZLED = 0x63
    };


    ////////////////////////////////////////////////////////////////
    // eBitmap interface
    // <kao2.005D0718> (vptr)
    ////////////////////////////////////////////////////////////////

    class eBitmap : public eRefCounter
    {
        /*** Properties ***/

        protected:

            /*[0x08]*/ int32_t virtualWidth;
            /*[0x0C]*/ int32_t virtualHeight;
            /*[0x10]*/ int32_t width;
            /*[0x14]*/ int32_t height;
            /*[0x18]*/ GLuint texture_name_id;
            /*[0x1C]*/ uint8_t* pixels;
            /*[0x20]*/ uint32_t* palette;
            /*[0x24]*/ int32_t type;
            /*[0x28]*/ eString path;

            bool isLoadedFromExternalFile;

        /*** Methods ***/

        public:

            eBitmap();
            ~eBitmap();

        private:

            void createFromOtherObject(const eBitmap &other);

        public:

            eBitmap(const eBitmap &other);
            eBitmap& operator = (const eBitmap &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
            void serialize(Archive &ar) override;

            void writeNodeToXmlFile(ColladaExporter &exporter) const override;

            /* << eBitmap >> */

            int32_t checkSimilarityToAnotherBitmap(const eBitmap &other) const;

            void generateTexture();

            void loadRaw(const uint8_t* other_pixels, const uint32_t* other_palette, int32_t new_width, int32_t new_height);
            bool loadFromFile(eString directory, bool silent_if_not_exists);
            void exportImageFile(eString directory) const;

            void setTransparencyColor(uint32_t color);
            bool isTransparent() const;
            void changeAlphaChannel(float factor);

            float getAspectRatio() const;

            GLuint getTextureId() const;

            eString getPath() const;
            void setPath(eString new_path);

            bool getLoadedFromExternalFileFlag() const;
            void setLoadedFromExternalFileFlag(bool new_flag);

        private:

            /* << eBitmap >> */

            bool isUsingPalette() const;
            int getBytesPerPixel() const;
            int getBytesPerPixelOutput(bool bmp_ext) const;
            const char* getTypeName() const;

            void deleteTexture();
    };


    ////////////////////////////////////////////////////////////////
    // eBitmap TypeInfo
    // <kao2.00472B40> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_BITMAP_ID = 0x1001;

    extern TypeInfo E_BITMAP_TYPEINFO;

}

#endif
