#ifndef DENIS_DISPLAYCOMMANDS
#define DENIS_DISPLAYCOMMANDS

#include <denis/Denis.h>

namespace ZookieWizard
{
    struct DenisDisplayTexture;

    class eGroup;
    class eMaterial;


    ////////////////////////////////////////////////////////////////
    // Display Commands
    ////////////////////////////////////////////////////////////////

    struct DenisDisplayCommands
    {
        /*** Properties ***/
        
            int32_t bytesCount[2];
            int32_t texturesCount[2];
            int32_t unknownCount[2];

            int32_t texturesCountTotal;
            DenisDisplayTexture* textures;

            int32_t bytesCountTotal;
            uint8_t* stream;
            int32_t streamPointer;

        /*** Methods ***/

            DenisDisplayCommands();
            ~DenisDisplayCommands();

            void serialize(DenisFileOperator &file);
            void read(void* ptr, int size);

            void convertToKao2
            (
                eGroup* parent_group,
                int32_t materials_count,
                eMaterial** materials_list,
                int32_t vertices_count,
                DenisGeoVertex* vertices,
                char* name
            );
    };


    ////////////////////////////////////////////////////////////////
    // Display Vertex
    ////////////////////////////////////////////////////////////////

    struct DenisDisplayVertex
    {
        /*** Properties ***/

            uint16_t index;

            uint16_t u;
            uint16_t v;

        /*** Methods ***/

            DenisDisplayVertex();

            void deserialize(DenisDisplayCommands &cmd);
    };


    ////////////////////////////////////////////////////////////////
    // Display Face
    ////////////////////////////////////////////////////////////////

    struct DenisDisplayFace
    {
        /*** Properties ***/

            uint8_t verticesCount;
            uint8_t dummy;
            DenisDisplayVertex* vertices;

        /*** Methods ***/

            DenisDisplayFace();
            ~DenisDisplayFace();

            void deserialize(DenisDisplayCommands &cmd);
    };


    ////////////////////////////////////////////////////////////////
    // Display Texture
    ////////////////////////////////////////////////////////////////

    struct DenisDisplayTexture
    {
        /*** Properties ***/

            uint16_t index;
            uint16_t facesCount;
            uint8_t transparency;
            DenisDisplayFace* faces;

        /*** Methods ***/

            DenisDisplayTexture();
            ~DenisDisplayTexture();

            void deserialize(DenisDisplayCommands &cmd);
    };

}

#endif
