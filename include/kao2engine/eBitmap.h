#ifndef H_KAO2AR_BITMAP
#define H_KAO2AR_BITMAP

#include <kao2engine/eRefCounter.h>

namespace ZookieWizard
{
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

        private:

            bool isUsingPalette();
            int getBytesPerPixel();

            void deleteTexture();

        public:

            eBitmap();
            ~eBitmap();

            void serialize(Archive &ar) override;
            TypeInfo* getType() override;

            void generateTexture();

            void setPath(eString new_path);
            void loadFromFile(Archive &ar);

            GLuint getTextureName();
    };


    ////////////////////////////////////////////////////////////////
    // eBitmap TypeInfo
    // <kao2.00472B70> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_BITMAP_ID = 0x1001;

    extern TypeInfo E_BITMAP_TYPEINFO;

}

#endif
