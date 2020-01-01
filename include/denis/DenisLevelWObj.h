#ifndef H_DENIS_LEVEL_WOBJ
#define H_DENIS_LEVEL_WOBJ

#include <denis/Denis.h>

#include <denis/DenisAnimmesh.h>

namespace ZookieWizard
{
    class eGroup;

    ////////////////////////////////////////////////////////////////
    // Kao the Kangaroo: World Object Reference
    ////////////////////////////////////////////////////////////////

    struct DenisLevelWObj
    {
        /*** Properties ***/

            char name[32];
            int32_t vertexCount;

            DenisAnimmesh mesh;

        /*** Methods ***/

            DenisLevelWObj();
            ~DenisLevelWObj();

            void serialize(DenisFileOperator &file);

            void loadMesh(DenisFileOperator &file);
    };

}

#endif
