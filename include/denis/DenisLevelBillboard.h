#ifndef DENIS_LEVEL_BILLBOARD
#define DENIS_LEVEL_BILLBOARD

#include <denis/Denis.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // Kao the Kangaroo: Billboard structure
    ////////////////////////////////////////////////////////////////

    struct DenisLevelBillboard
    {
        /*** Properties ***/

            DenisVertex position;
            int32_t difficulty;

            float unknown_A[8];
            uint16_t unknown_B[8];

            uint16_t textureID;

            uint16_t unknown_C[5];

            uint8_t name[32];

            int32_t unknown_D[4];

        /*** Methods ***/

            DenisLevelBillboard();
            ~DenisLevelBillboard();

            void serialize(DenisFileOperator &file);
    };

}

#endif
