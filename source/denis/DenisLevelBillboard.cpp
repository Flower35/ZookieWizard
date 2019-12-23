#include <denis/DenisLevelBillboard.h>

#include <denis/DenisLevelWObj.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // Level Billboard: constructor
    ////////////////////////////////////////////////////////////////

    DenisLevelBillboard::DenisLevelBillboard()
    {
        std::memset(name, 0x00, 32);

        difficulty = 0x0F;

        textureID = 0;
    }


    ////////////////////////////////////////////////////////////////
    // Level Billboard: destructor
    ////////////////////////////////////////////////////////////////

    DenisLevelBillboard::~DenisLevelBillboard() {}


    ////////////////////////////////////////////////////////////////
    // Level Billboard: serialization
    ////////////////////////////////////////////////////////////////

    void DenisLevelBillboard::serialize(DenisFileOperator &file)
    {
        int32_t i;

        /* Position */

        position.serialize(file);

        /* Difficulty flag */

        file.readOrWrite(&difficulty, 0x04);

        /* unknown values (looks like 4 [X,Y] pairs) */

        for (i = 0; i < 8; i++)
        {
            file.readOrWrite(&(unknown_A[i]), 0x04);
        }

        for (i = 0; i < 8; i++)
        {
            file.readOrWrite(&(unknown_B[i]), 0x02);
        }

        /* Texture ID */

        file.readOrWrite(&textureID, 0x02);

        /* unknown values */

        for (i = 0; i < 5; i++)
        {
            file.readOrWrite(&(unknown_C[i]), 0x02);
        }

        /* Billboard name */

        file.readOrWrite(name, 0x20);

        /* unknown values */

        for (i = 0; i < 4; i++)
        {
            file.readOrWrite(&(unknown_D[i]), 0x04);
        }
    }

}
