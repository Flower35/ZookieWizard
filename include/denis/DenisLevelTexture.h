#ifndef DENIS_LEVEL_TEXTURE
#define DENIS_LEVEL_TEXTURE

#include <denis/Denis.h>

namespace ZookieWizard
{
    class eMaterial;

    #define DENIS_LEVEL_TEXTURE_TYPE_NORMAL 0x00
    #define DENIS_LEVEL_TEXTURE_TYPE_ANIMATED 0x01
    #define DENIS_LEVEL_TEXTURE_TYPE_PROCTEX 0x02

    ////////////////////////////////////////////////////////////////
    // Kao the Kangaroo: Texture structure
    ////////////////////////////////////////////////////////////////

    struct DenisLevelTexture
    {
        /*** Properties ***/

            char name[8 + 1];
            int16_t width;
            int16_t height;
            bool isTransparent;
            uint8_t type;

        /*** Methods ***/

            DenisLevelTexture();
            ~DenisLevelTexture();

            void loadFromFile();
            void serialize(DenisFileOperator &file);

            eMaterial* convertToKao2(DenisFileOperator &file);
    };

}

#endif
