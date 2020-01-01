#ifndef DENIS_LEVEL_BONUS
#define DENIS_LEVEL_BONUS

#include <denis/Denis.h>

namespace ZookieWizard
{
    class eGroup;

    ////////////////////////////////////////////////////////////////
    // Kao the Kangaroo: Bonus structure
    ////////////////////////////////////////////////////////////////

    struct DenisLevelBonus
    {
        /*** Properties ***/

            DenisVertex position;
            int32_t difficulty;
            int32_t type;

        /*** Methods ***/

            DenisLevelBonus();
            ~DenisLevelBonus();

            void serialize(DenisFileOperator &file);

            void convertToKao2(int32_t bonus_id, eGroup* parent_group);
    };

}

#endif
