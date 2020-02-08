#include <kao2engine/eBitmap.h>
#include <kao2ar/Archive.h>

#include <kao2engine/Log.h>

#include <utilities/ColladaExporter.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eBitmap interface
    // <kao2.004700E0> (constructor)
    // <kao2.004703E0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_BITMAP_TYPEINFO
    (
        E_BITMAP_ID,
        "eBitmap",
        &E_REFCOUNTER_TYPEINFO,
        []() -> eObject*
        {
            return new eBitmap;
        }
    );

    TypeInfo* eBitmap::getType() const
    {
        return &E_BITMAP_TYPEINFO;
    }

    eBitmap::eBitmap()
    : eRefCounter()
    {
        /* Only "kao_tw" supports external bitmaps */
        isLoadedFromExternalFile = false;

        /*[0x08]*/ virtualWidth = 0;
        /*[0x0C]*/ virtualHeight = 0;
        /*[0x10]*/ width = 0;
        /*[0x14]*/ height = 0;
        /*[0x18]*/ texture_name_id = 0;
        /*[0x1C]*/ pixels = nullptr;
        /*[0x20]*/ palette = nullptr;
        /*[0x24]*/ type = (-1);
    }

    eBitmap::~eBitmap()
    {
        deleteTexture();

        if (nullptr != pixels)
        {
            delete[](pixels);
        }

        if (nullptr != palette)
        {
            delete[](palette);
        }
    }


    ////////////////////////////////////////////////////////////////
    // eBitmap: load image from file
    ////////////////////////////////////////////////////////////////
    void eBitmap::loadFromFile(eString directory)
    {
        FileOperator file;
        eString result;
        char* full_path;

        int32_t a, b, i, x, y;

        int32_t offset;
        int32_t bpp;
        int32_t new_width;
        int32_t new_height;

        /* Get path and open file */

        result += directory;
        result += path;

        theLog.print(eString(" @ LOADING BITMAP: \"") + result + "\"\n");

        full_path = result.getText();

        if (!file.open(full_path, (FILE_OPERATOR_MODE_READ | FILE_OPERATOR_MODE_BINARY)))
        {
            throw ErrorMessage
            (
                "Bitmap::loadFromFile():\n" \
                "Could not open file: \"%s\"",
                full_path
            );
        }

        /* Check file format (only BMP and TGA are supported by game engine) */

        if (result.hasExtension("bmp"))
        {
            /* [0x00] Bitmap header */
            file.read(&a, 0x02);

            if (*(int16_t*)"BM" != (0x0000FFFF & a))
            {
                return;
            }

            /* [0x02] Dummy (file size) */
            file.read(&a, 0x04);

            /* [0x06] Dummy */
            file.read(&a, 0x04);

            /* [0x0A] Pixels offset */
            file.read(&offset, 0x04);

            /* [0x0E] Dummy (BITMAPINFOHEADER size) */
            file.read(&a, 0x04);

            /* [0x12] "biWidth" */
            file.read(&new_width, 0x04);

            /* [0x16] "biHeight" */
            file.read(&new_height, 0x04);

            /* [0x1A] "biPlanes" */
            file.read(&a, 0x02);

            /* [0x1C] "bBitCount" */
            file.read(&bpp, 0x02);

            bpp &= 0x0000FFFF;

            /* Check BPP and read pixels */

            switch (bpp)
            {
                case 8:
                {
                    file.setPointer(offset - 0x0400);

                    if (nullptr == palette)
                    {
                        palette = new uint32_t [256];
                    }

                    for (i = 0; i < 256; i++)
                    {
                        file.read(&a, 0x04);

                        /* shift RGBX -> BGRX */

                        palette[i] = ((a & 0xFF00FF00) | ((a >> 16) & 0x000000FF) | ((a << 16) & 0x00FF0000));
                    }

                    /* Skip break here! */
                }

                case 24:
                {
                    file.setPointer(offset);

                    if (nullptr != pixels)
                    {
                        delete[](pixels);
                        pixels = nullptr;
                    }

                    b = (bpp / 8);

                    pixels = new uint8_t [new_width * new_height * b];

                    for (y = (new_height - 1); y >= 0; y--)
                    {
                        for (x = 0; x < new_width; x++)
                        {
                            file.read(&a, b);

                            /* When there are 3 bytes per pixel, read in reverser order */

                            for (i = 0; i < b; i++)
                            {
                                pixels[(y * new_width * b) + (x * b) + (b - i - 1)] = ((a >> (8 * i)) & 0x000000FF);
                            }
                        }
                    }

                    break;
                }

                default:
                {
                    return;
                }
            }

            /* Set width, height and type */

            width = virtualWidth = new_width;
            height = virtualHeight = new_height;

            switch (bpp)
            {
                case 8:
                {
                    type = bitmapType::PAL8_RGBX8;
                    break;
                }

                case 24:
                {
                    type = bitmapType::RGB8;
                    break;
                }
            }

        }
        else if (result.hasExtension("tga"))
        {
            /* [0x00] "ID length" */
            file.read(&a, 0x01);

            if (0 != (0x000000FF & a))
            {
                return;
            }

            /* [0x01] "Color Map Type" */
            file.read(&a, 0x01);

            if (0 != (0x000000FF & a))
            {
                return;
            }

            /* [0x02] "Image Type" */
            /* 2 = "Uncompressed, True-color type" */
            file.read(&a, 0x01);

            if (2 != (0x000000FF & a))
            {
                return;
            }

            /* [0x03-0x07] "Color Map Specification" */
            for (i = 0; i < 5; i++)
            {
                file.read(&a, 0x01);

                if (0 != (0x000000FF & a))
                {
                    return;
                }
            }

            /* [0x08] "X-origin of Image" */
            file.read(&a, 0x02);

            if (0 != (0x0000FFFF & a))
            {
                return;
            }

            /* [0x0A] "Y-origin of Image" */
            file.read(&a, 0x02);

            if (0 != (0x0000FFFF & a))
            {
                return;
            }

            /* [0x0C] "Image Width" */
            file.read(&new_width, 0x02);

            new_width &= 0x0000FFFF;

            /* [0x0E] "Image Height" */
            file.read(&new_height, 0x02);

            new_height &= 0x0000FFFF;

            /* [0x10] "Pixel Depth" */
            file.read(&bpp, 0x01);

            bpp &= 0x000000FF;

            if (32 != bpp)
            {
                return;
            }

            /* [0x11] "Image Descriptor" */
            file.read(&a, 0x01);

            if (8 != (0x000000FF & a))
            {
                return;
            }

            /* [0x12] "Image data" */

            if (nullptr != pixels)
            {
                delete[](pixels);
                pixels = nullptr;
            }

            pixels = new uint8_t [new_width * new_height * 4];

            for (y = (new_height - 1); y >= 0; y--)
            {
                for (x = 0; x < new_width; x++)
                {
                    file.read(&a, 4);

                    /* RGBA -> BGRA format */

                    pixels[(y * new_width * 4) + (x * 4) + 0] = ((a >> 16) & 0x000000FF);
                    pixels[(y * new_width * 4) + (x * 4) + 1] = ((a >> 8) & 0x000000FF);
                    pixels[(y * new_width * 4) + (x * 4) + 2] = ((a >> 0) & 0x000000FF);
                    pixels[(y * new_width * 4) + (x * 4) + 3] = ((a >> 24) & 0x000000FF);
                }
            }

            /* Set width, height and type */

            width = virtualWidth = new_width;
            height = virtualHeight = new_height;

            type = bitmapType::RGBA8;
        }
        else
        {
            throw ErrorMessage
            (
                "eBitmap::loadFromFile():\n"
                "unsupported file extension! [%s]",
                path.getText()
            );
        }
    }


    ////////////////////////////////////////////////////////////////
    // eBitmap: export image to file
    ////////////////////////////////////////////////////////////////
    void eBitmap::exportImageFile(eString directory) const
    {
        FileOperator file;
        eString result;
        char* full_path;

        int32_t a, b, x, y, output_size;
        bool bmp_ext = true;
        uint8_t* output_pixels = nullptr;

        char header[0x36];

        /* Get path and open file */

        result += directory;
        result += path;

        theLog.print(eString(" @ EXPORTING BITMAP: \"") + result + "\"\n");

        full_path = result.getText();

        file.setDir(full_path);
        file.createDir();

        if (!file.open(full_path, (FILE_OPERATOR_MODE_BINARY)))
        {
            throw ErrorMessage
            (
                "Bitmap::exportImageFile():\n" \
                "Could not open file: \"%s\"",
                full_path
            );
        }

        /* Check file format and set headers */
        std::memset(header, 0x00, 0x36);

        if (result.hasExtension("bmp"))
        {
            bmp_ext = true;

            a = getBytesPerPixel() * width * height;
            b = isUsingPalette();

            header[0x00] = 'B';
            header[0x01] = 'M';
            *(int32_t*)&(header[0x02]) = (b ? 0x0400 : 0) + 0x36 + a;
            header[0x0A] = 0x36;
            header[0x0B] = b ? 0x04 : 0x00;
            header[0x0E] = 0x28;
            *(int32_t*)&(header[0x12]) = width;
            *(int32_t*)&(header[0x16]) = height;
            header[0x1A] = 0x01;
            header[0x1C] = b ? 0x08 : 0x18;
            *(int32_t*)&(header[0x22]) = a;
        }
        else if (result.hasExtension("tga"))
        {
            bmp_ext = false;

            header[0x02] = 0x02;
            *(int16_t*)&(header[0x0C]) = width;
            *(int16_t*)&(header[0x0E]) = height;
            header[0x10] = 0x08 * getBytesPerPixelOutput(bmp_ext);
            header[0x11] = 0x08;
        }
        else
        {
            throw ErrorMessage
            (
                "eBitmap::exportImageFile():\n"
                "unsupported file extension! [%s]",
                path.getText()
            );
        }

        /* Prepare output block */
        output_size = width * height * getBytesPerPixelOutput(bmp_ext);
        output_pixels = new uint8_t [output_size];

        /********************************/
        /* Check "eBitmap" configurations */
        /* (vertical flip) */

        if ((!bmp_ext) && (bitmapType::PAL8_RGBA8 == type))
        {
            /* TGA, 8-bit -> 32-bit */

            for (y = 0; y < height; y++)
            {
                for (x = 0; x < width; x++)
                {
                    b = palette[pixels[y * width + x]];

                    b = ((b & 0xFF00FF00) | ((b >> 16) & 0x000000FF) | ((b << 16) & 0x00FF0000));

                    a = (4 * width * height) - (4 * (y+1) * width) + (4 * x);

                    *(int32_t*)&(output_pixels[a]) = b;
                }
            }
        }
        else if (bmp_ext && (bitmapType::PAL8_RGBA8 == type))
        {
            /* BMP, 8-bit (256 colors) */

            for (y = 0; y < height; y++)
            {
                std::memcpy
                (
                    output_pixels + width*y,
                    pixels + width*height - width*(y+1),
                    width
                );
            }
        }
        else if ((!bmp_ext) && (bitmapType::RGBA8 == type))
        {
            /* TGA, 32-bit (Truecolor) */

            for (y = 0; y < height; y++)
            {
                for (x = 0; x < width; x++)
                {
                    b = *(int32_t*)&(pixels[(4 * y * width) + (4 * x)]);

                    b = ((b & 0xFF00FF00) | ((b >> 16) & 0x000000FF) | ((b << 16) & 0x00FF0000));

                    a = (4 * width * height) - (4 * (y+1) * width) + (4 * x);

                    *(int32_t*)&(output_pixels[a]) = b;
                }
            }
        }
        else if (bmp_ext && (bitmapType::RGB8 == type))
        {
            /* BMP, 24-bit */

            for (y = 0; y < height; y++)
            {
                for (x = 0; x < width; x++)
                {
                    b = (3 * y * width) + (3 * x);

                    a = (3 * width * height) - (3 * (y+1) * width) + (3 * x);

                    output_pixels[a + 0] = pixels[b + 2];
                    output_pixels[a + 1] = pixels[b + 1];
                    output_pixels[a + 2] = pixels[b + 0];
                }
            }
        }
        else if (bmp_ext && (bitmapType::RGBA8 == type))
        {
            /* BMP, 32-bit -> 24-bit */

            for (y = 0; y < height; y++)
            {
                for (x = 0; x < width; x++)
                {
                    b = (4 * y * width) + (4 * x);

                    a = (3 * width * height) - (3 * (y+1) * width) + (3 * x);

                    output_pixels[a + 0] = pixels[b + 2];
                    output_pixels[a + 1] = pixels[b + 1];
                    output_pixels[a + 2] = pixels[b + 0];
                }
            }
        }
        else
        {
            if (nullptr != output_pixels)
            {
                delete[](output_pixels);
                output_pixels = nullptr;
            }

            throw ErrorMessage
            (
                "eBitmap::exportImageFile():\n"
                "unsupported output configuation! [%s] [%s]",
                (bmp_ext ? "bmp" : "tga"),
                getTypeName()
            );
        }

        /* Save header */
        file.write(header, (bmp_ext ? 0x36 : 0x12));

        /* Save palette [BGRA -> RGBA] */
        if (bmp_ext && isUsingPalette())
        {
            for (a = 0; a < 256; a++)
            {
                b = palette[a];
                b = ((b & 0xFF00FF00) | ((b >> 16) & 0x000000FF) | ((b << 16) & 0x00FF0000));
                file.write(&b, 0x04);
            }
        }

        /* Save output colors */
        file.write(output_pixels, output_size);

        if (nullptr != output_pixels)
        {
            delete[](output_pixels);
        }
    }


    ////////////////////////////////////////////////////////////////
    // eBitmap: generate OpenGL texture
    ////////////////////////////////////////////////////////////////
    void eBitmap::generateTexture()
    {
        int32_t a, b;
        int32_t total_size;
        int32_t bytes_per_pixel;
        uint8_t* temp_pixels = nullptr;
        bool using_pal = false;
        GLint internal_format = 0;
        GLenum px_data_format = 0;

        if (0 == texture_name_id)
        {
            /* Generate 32-bit image, if palette is used */

            if (using_pal = isUsingPalette())
            {
                switch (type)
                {
                    case bitmapType::PAL8_RGBA8:
                    {
                        bytes_per_pixel = 4;
                        break;
                    }

                    case bitmapType::PAL8_RGBX8:
                    {
                        bytes_per_pixel = 3;
                        break;
                    }

                    default:
                    {
                        bytes_per_pixel = 1;
                    }
                }

                total_size = width * height;

                temp_pixels = new uint8_t[total_size * bytes_per_pixel];

                if ((nullptr != palette) && (nullptr != pixels) && (nullptr != temp_pixels))
                {
                    for (a = 0; a < total_size; a++)
                    {
                        for (b = 0; b < bytes_per_pixel; b++)
                        {
                            temp_pixels[bytes_per_pixel * a + b] = ((palette[pixels[a]] >> (8 * b)) & 0x000000FF);
                        }
                    }
                }
            }

            /* Check color format */

            switch (type)
            {
                case bitmapType::RGBA8:
                case bitmapType::PAL8_RGBA8:
                case bitmapType::RGBX8:
                {
                    internal_format = GL_RGBA8;
                    px_data_format = GL_RGBA;

                    break;
                }

                case bitmapType::RGB8:
                case bitmapType::PAL8_RGBX8:
                {
                    internal_format = GL_RGB8;
                    px_data_format = GL_RGB;

                    break;
                }
            }

            /* Generate and bind one texture */

            glGenTextures(1, &texture_name_id);

            glBindTexture(GL_TEXTURE_2D, texture_name_id);

            glTexImage2D
            (
                GL_TEXTURE_2D, // target
                0, // level of detail
                internal_format, // number of color components
                virtualWidth, // width
                virtualHeight, // height
                0, // border (must be 0)
                px_data_format, // pixel data format
                GL_UNSIGNED_BYTE, // data type
                (using_pal ? temp_pixels : pixels) // pixels
            );

            /* Default params (so that texture isn't white!) */

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

            glBindTexture(GL_TEXTURE_2D, 0);
        }

        if (nullptr != temp_pixels)
        {
            delete[](temp_pixels);
        }
    }


    ////////////////////////////////////////////////////////////////
    // eBitmap: delete texture
    // <kao2.00470F10>
    ////////////////////////////////////////////////////////////////
    void eBitmap::deleteTexture()
    {
        if (0 != texture_name_id)
        {
            glDeleteTextures(1, &texture_name_id);

            texture_name_id = 0;
        }
    }


    ////////////////////////////////////////////////////////////////
    // eBitmap: get bytes per pixel
    // <kao2.00470AA0>
    ////////////////////////////////////////////////////////////////
    int eBitmap::getBytesPerPixel() const
    {
        switch (type)
        {
            case bitmapType::RGBA8:
            case bitmapType::RGBX8:
            case bitmapType::RGBA8_SWIZZLED:
            case bitmapType::RGBX8_SWIZZLED:
            {
                return 0x04;
            }

            case bitmapType::RGB8:
            {
                return 0x03;
            }

            case bitmapType::PAL8_RGBA8:
            case bitmapType::PAL8_RGBX8:
            case bitmapType::PAL8_RGBA8_IDTEX8:
            case bitmapType::PAL8_RGBX8_IDTEX8:
            {
                return 0x01;
            }

            default:
            {
                return 0x00;
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eBitmap: cakculate bytes per pixel when exporting
    ////////////////////////////////////////////////////////////////
    int eBitmap::getBytesPerPixelOutput(bool bmp_ext) const
    {
        switch (type)
        {
            case bitmapType::RGBA8:
            {
                return (bmp_ext ? 0x03 : 0x04);
            }

            case bitmapType::PAL8_RGBA8:
            {
                return (bmp_ext ? 0x01: 0x04);
            }

            case bitmapType::RGB8:
            case bitmapType::RGBX8:
            {
                return 0x03;
            }

            default:
            {
                return 0x01;
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eBitmap: show object type
    ////////////////////////////////////////////////////////////////
    const char* eBitmap::getTypeName() const
    {
        switch (type)
        {
            case bitmapType::RGBA8:
            {
                return "RGBA8";
            }

            case bitmapType::RGB8:
            {
                return "RGB8";
            }

            case bitmapType::PAL8_RGBA8:
            {
                return "PAL8_RGBA8";
            }

            case bitmapType::PAL8_RGBX8:
            {
                return "PAL8_RGBX8";
            }

            case bitmapType::RGBX8:
            {
                return "RGBX8";
            }

            default:
            {
                return "<???>";
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eBitmap: check if color palette needs to be allocated
    // <kao2.00470F40>
    ////////////////////////////////////////////////////////////////
    bool eBitmap::isUsingPalette() const
    {
        switch (type)
        {
            case bitmapType::PAL8_RGBA8:
            case bitmapType::PAL8_RGBX8:
            case bitmapType::PAL8_RGBA8_IDTEX8:
            case bitmapType::PAL8_RGBX8_IDTEX8:
            {
                return true;
            }

            default:
            {
                return false;
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eBitmap serialization
    // <kao2.00470B50>
    ////////////////////////////////////////////////////////////////
    void eBitmap::serialize(Archive &ar)
    {
        int32_t a = 0;

        int32_t total_length;
        bool using_pal;

        if (ar.isInReadMode())
        {
            deleteTexture();
        }

        /* Bitmap dimensions */

        if (ar.isInWriteMode() && isLoadedFromExternalFile)
        {
            ar.readOrWrite(&a, 0x04);
            ar.readOrWrite(&a, 0x04);
        }
        else
        {
            ar.readOrWrite(&virtualWidth, 0x04);
            ar.readOrWrite(&virtualHeight, 0x04);
        }

        if (ar.getVersion() < 0x6B)
        {
            width = virtualWidth;
            height = virtualHeight;
        }
        else
        {
            if (ar.isInWriteMode() && isLoadedFromExternalFile)
            {
                ar.readOrWrite(&a, 0x04);
                ar.readOrWrite(&a, 0x04);
            }
            else
            {
                ar.readOrWrite(&width, 0x04);
                ar.readOrWrite(&height, 0x04);
            }
        }

        /* Bitmap type, image size in bytes */

        ar.readOrWrite(&type, 0x04);

        total_length = getBytesPerPixel() * width * height;

        using_pal = isUsingPalette();

        if (ar.isInReadMode())
        {
            /* Allocate memory for pixels */

            if (nullptr != pixels)
            {
                delete[](pixels);
                pixels = nullptr;
            }

            if (total_length > 0)
            {
                pixels = new uint8_t [total_length];
            }

            if (using_pal)
            {
                if (nullptr == palette)
                {
                    palette = new uint32_t [256];
                }
            }
            else
            {
                if (nullptr != palette)
                {
                    delete[](palette);
                    palette = nullptr;
                }
            }
        }

        /* Read image contents */

        if ((total_length > 0) && (!isLoadedFromExternalFile))
        {
            ar.readOrWrite(pixels, total_length);
        }

        if (using_pal)
        {
            ar.readOrWrite(palette, 0x0400);
        }


        /* Filename ("*.bmp" or "*.tga") */

        ar.serializeString(path);

        /* Load texture from file, Bind texture */

        if (ar.isInReadMode())
        {
            if (total_length <= 0)
            {
                try
                {
                    loadFromFile(ar.getMediaDir());

                    isLoadedFromExternalFile = true;
                }
                catch (ErrorMessage &e)
                {
                    e.display();
                }
            }

            generateTexture();
        }

        /* Abstract "eBitmapEvaluator" pointer */

        a = 0x01;
        ar.readOrWrite(&a, 0x04);
        if (0x01 != a)
        {
            throw ErrorMessage
            (
                "eBitmap::serialize()\n" \
                "non-empty eBitmapEvaulator pointer!"
            );
        }
    }


    ////////////////////////////////////////////////////////////////
    // eBitmap: COLLADA exporting
    ////////////////////////////////////////////////////////////////
    void eBitmap::writeNodeToXmlFile(ColladaExporter &exporter) const
    {
        int32_t i;
        char bufor[64];

        if (exporter.objectRefAlreadyExists(COLLADA_EXPORTER_OBJ_IMAGE, this))
        {
            /* Bitmap was already exported */
            return;
        }

        exporter.openTag("image");

        i = exporter.getObjectRefId(COLLADA_EXPORTER_OBJ_IMAGE, this, true);
        sprintf_s(bufor, 64, "Bitmap%d", i);
        exporter.insertTagAttrib("id", bufor);

        exporter.openTag("init_from");
        exporter.openTag("ref");
        exporter.writeInsideTag(path);

        exporter.closeTag(); // "ref"
        exporter.closeTag(); // "init_from"
        exporter.closeTag(); // "image"

        /* Actually export the image to hard drive */
        exportImageFile(exporter.getWorkingDirectory());
    }


    ////////////////////////////////////////////////////////////////
    // eBitmap: set and get filename path
    ////////////////////////////////////////////////////////////////

    void eBitmap::setPath(eString new_path)
    {
        path = new_path;
    }

    eString eBitmap::getPath() const
    {
        return path;
    }


    ////////////////////////////////////////////////////////////////
    // eBitmap: get texture name (used with eTexture)
    ////////////////////////////////////////////////////////////////
    GLuint eBitmap::getTextureName() const
    {
        return texture_name_id;
    }


    ////////////////////////////////////////////////////////////////
    // eBitmap: set transparency color
    ////////////////////////////////////////////////////////////////
    void eBitmap::setTransparencyColor(uint32_t color)
    {
        int32_t i;

        if (bitmapType::PAL8_RGBX8 == type)
        {
            type = bitmapType::PAL8_RGBA8;

            /* shift RGBX -> BGRX */
            color = ((color & 0x0000FF00) | ((color >> 16) & 0x000000FF) | ((color << 16) & 0x00FF0000));

            for (i = 0; i < 256; i++)
            {
                if ((0x00FFFFFF & palette[i]) == (0x00FFFFFF & color))
                {
                    /* Set alpha to 0 */
                    palette[i] = palette[i] & 0x00FFFFFF;
                }
                else
                {
                    /* Set alpha to 255 */
                    palette[i] = palette[i] | 0xFF000000;
                }
            }
        }
    }

}
