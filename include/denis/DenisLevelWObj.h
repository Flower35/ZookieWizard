#ifndef H_DENIS_LEVEL_WOBJ
#define H_DENIS_LEVEL_WOBJ

#include <denis/Denis.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // Kao the Kangaroo: World Object Reference
    ////////////////////////////////////////////////////////////////

    struct DenisLevelWObj
    {
        /*** Properties ***/

            uint8_t name[32];
            int32_t vertexCount;

            /* (...) */

        /*** Methods ***/

            DenisLevelWObj();
            ~DenisLevelWObj();

            void serialize(DenisFileOperator &file);
    };

}

#endif
