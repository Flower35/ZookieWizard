#include <denis/DenisLevelTexture.h>

#include <kao2engine/eMaterial.h>
#include <kao2engine/eTexture.h>
#include <kao2engine/eBitmap.h>

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

    void DenisLevelTexture::convertToKao2(DenisFileOperator &file, eMaterial** materials_list) const
    {
        int32_t i;

        uint8_t test_flags[4] =
        {
            0x00, // normal
            0x0E, // + "transparent" + "alpha test"
            0x01, // + "2-sided"
            0x0F // + "2-sided" + "transparent" + "alpha test"
        };

        eMaterial* test_material = nullptr;
        eTexture* test_texture = nullptr;
        eBitmap* test_bitmap = nullptr;

        eString bitmap_path[3];

        bool add_transparency = isTransparent;

        /********************************/
        /* Create bitmap and texture */

        test_bitmap = new eBitmap();
        test_bitmap->incRef();

        bitmap_path[0] = "world/textures/8BIT/";
        bitmap_path[0] += name;
        bitmap_path[1] = bitmap_path[0] + ".tga";
        bitmap_path[2] = bitmap_path[0] + ".bmp";

        if (file.checkIfExists(bitmap_path[0]))
        {
            /* "*.tga" texture found */

            add_transparency = false;

            bitmap_path[0] = bitmap_path[1];
        }
        else
        {
            /* otherwie load "*.bmp" texture */

            bitmap_path[0] = bitmap_path[2];
        }

        test_bitmap->setPath(bitmap_path[0]);

        try
        {
            test_bitmap->loadFromFile(file.workingDirectory);

            if (add_transparency)
            {
                /* Add alpha channel */

                test_bitmap->setTransparencyColor(0x00000000);

                /* Change extension to "*.tga" */

                test_bitmap->setPath(bitmap_path[1]);
            }

            test_bitmap->generateTexture();
        }
        catch (ErrorMessage &e)
        {
            e.display();
        }

        test_texture = new eTexture(test_bitmap);
        test_texture->incRef();

        test_bitmap->decRef();

        /********************************/
        /* Create four types of materials */

        for (i = 0; i < 4; i++)
        {
            test_material = new eMaterial(test_texture);

            test_material->setName(name);
            test_material->setMaterialFlags(test_flags[i]);

            materials_list[i] = test_material;
            test_material->incRef();
        }

        test_texture->decRef();
    }

}
