#include <denis/DenisLevelTexture.h>

#include <kao2engine/eMaterial.h>
#include <kao2engine/eTexture.h>
#include <kao2engine/eBitmap.h>

#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // Level Texture: constructor
    ////////////////////////////////////////////////////////////////

    DenisLevelTexture::DenisLevelTexture()
    {
        std::memset(name, 0x00, (8 + 1));

        width = 0;
        height = 0;

        isTransparent = false;

        type = 0;
    }


    ////////////////////////////////////////////////////////////////
    // Level Texture: destructor
    ////////////////////////////////////////////////////////////////

    DenisLevelTexture::~DenisLevelTexture() {}


    ////////////////////////////////////////////////////////////////
    // Level Texture: serialization
    ////////////////////////////////////////////////////////////////

    void DenisLevelTexture::serialize(DenisFileOperator &file)
    {
        int16_t dummy = 0;

        /* Texture filename */

        file.readOrWrite(name, 0x08);

        /* Width and Height */

        file.readOrWrite(&width, 0x02);
        file.readOrWrite(&height, 0x02);

        /* Transparency */

        file.readOrWrite(&isTransparent, 0x01);

        /* Type (static, animated, ???) */

        file.readOrWrite(&type, 0x01);

        /* Unused (2 bytes) */

        file.readOrWrite(&dummy, 0x02);
    }


    ////////////////////////////////////////////////////////////////
    // Level Texture: convert from Kao1 to Kao2
    ////////////////////////////////////////////////////////////////

    eMaterial* DenisLevelTexture::convertToKao2(DenisFileOperator &file)
    {
        eMaterial* test_material = nullptr;
        eTexture* test_texture = nullptr;
        eBitmap* test_bitmap = nullptr;

        eString bitmap_path;
        Archive test_ar(file.workingDirectory);

        /********************************/
        /* Create bitmap, texture, then material */

        bitmap_path = "world/textures/8BIT/";
        bitmap_path += name;
        bitmap_path += ".bmp";

        test_bitmap = new eBitmap();
        test_bitmap->setPath(bitmap_path);

        try
        {
            test_bitmap->loadFromFile(test_ar);
            test_bitmap->generateTexture();
        }
        catch (ErrorMessage &e)
        {
            /* Penguin Kelvin "*.tga": [width=1] [height=1] [isTransparent=false] [type=0] */

            e.display();
        }

        test_texture = new eTexture(test_bitmap);

        test_material = new eMaterial(test_texture);
        test_material->setName(name);

        /********************************/
        /* (--dsp--) is default collision ICE ??? */

        return test_material;
    }

}
