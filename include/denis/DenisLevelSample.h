#ifndef H_DENIS_LEVEL_SAMPLE
#define H_DENIS_LEVEL_SAMPLE

#include <denis/Denis.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // Kao the Kangaroo: Ambient Sample structure
    ////////////////////////////////////////////////////////////////

    struct DenisLevelSample
    {
        /*** Properties ***/

            uint8_t name[8 + 1];

        /*** Methods ***/

            DenisLevelSample();
            ~DenisLevelSample();

            void serialize(DenisFileOperator &file);
    };

}

#endif
