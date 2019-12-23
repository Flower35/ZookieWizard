#include <denis/DenisLevelBonus.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // Level Bonus: constructor
    ////////////////////////////////////////////////////////////////

    DenisLevelBonus::DenisLevelBonus()
    {
        difficulty = 0x0F;

        type = 0;
    }


    ////////////////////////////////////////////////////////////////
    // Level Bonus: destructor
    ////////////////////////////////////////////////////////////////

    DenisLevelBonus::~DenisLevelBonus() {}


    ////////////////////////////////////////////////////////////////
    // Level Bonus: serialization
    ////////////////////////////////////////////////////////////////

    void DenisLevelBonus::serialize(DenisFileOperator &file)
    {
        /* Bonus position */

        position.serialize(file);

        /* Difficulty flag */

        file.readOrWrite(&difficulty, 0x04);

        /* Bonus type */

        file.readOrWrite(&type, 0x04);
    }

}
