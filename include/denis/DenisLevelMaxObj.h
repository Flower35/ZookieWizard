#ifndef H_DENIS_LEVEL_MAXOBJ
#define H_DENIS_LEVEL_MAXOBJ

#include <denis/Denis.h>

namespace ZookieWizard
{
    struct DenisLevelWObj;

    ////////////////////////////////////////////////////////////////
    // Kao the Kangaroo: World Object proxy ("max Object")
    ////////////////////////////////////////////////////////////////

    struct DenisLevelMaxObj
    {
        /*** Properties ***/

            uint8_t name[32];
            int32_t index;

            DenisVertex position;
            float scale;
            DenisEulerRotation rotation;

            int16_t dummy_A;
            int32_t flags;
            int32_t damage;
            int32_t dummy_B;
            float dummy_C;
            float dummy_D;

            DenisColor* vertexColors;

        /*** Methods ***/

            DenisLevelMaxObj();
            ~DenisLevelMaxObj();

            void serialize(DenisFileOperator &file, DenisLevelWObj* wobj, int32_t wobj_count);
    };

}

#endif
