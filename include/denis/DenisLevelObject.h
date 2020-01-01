#ifndef H_DENIS_LEVEL_OBJECT
#define H_DENIS_LEVEL_OBJECT

#include <denis/Denis.h>

#include <denis/DenisDisplayCommands.h>

namespace ZookieWizard
{
    struct DenisLevelTrack;
    
    class eGroup;
    class eMaterial;

    ////////////////////////////////////////////////////////////////
    // Kao the Kangaroo: Static/Pushable/Moving object structure
    ////////////////////////////////////////////////////////////////

    struct DenisLevelObject
    {
        /*** Properties ***/

            int32_t flags;
            int32_t dummy_04;
            int32_t vertexCount;
            int32_t faces1sidedCount;
            int32_t faces2sidedCount;
            char name[32];
            int32_t dummy_34;
            int32_t dummy_38;
            int32_t dummy_3C;

            DenisBoundBox boundBox;

            DenisGeoVertex* vertices;
            DenisGeoFace* faces;

            int32_t tracksCount;
            DenisLevelTrack* tracks;

            int32_t unknownWordsCount;
            int16_t* unknownWords;

            DenisDisplayCommands displayCommands;

        /*** Methods ***/

            DenisLevelObject();
            ~DenisLevelObject();

            void serialize(DenisFileOperator &file, int32_t current_type);

            void convertToKao2
            (
                int32_t object_type,
                int32_t object_id,
                eGroup* parent_group,
                int32_t materials_count,
                eMaterial** materials_list
            );
    };

}

#endif
