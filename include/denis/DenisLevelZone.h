#ifndef H_DENIS_LEVEL_ZONE
#define H_DENIS_LEVEL_ZONE

#include <denis/Denis.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // Kao the Kangaroo: Event Zone structure
    ////////////////////////////////////////////////////////////////

    struct DenisLevelZone
    {
        /*** Properties ***/

            uint8_t name[32];
            DenisBoundBox boundBox;
            int32_t sampleID;
            int32_t type;

        /*** Methods ***/

            DenisLevelZone();
            ~DenisLevelZone();

            void serialize(DenisFileOperator &file);
    };

}

#endif
