#include <denis/DenisLevelBonus.h>

#include <ElephantEngine/eProxy.h>

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


    ////////////////////////////////////////////////////////////////
    // Level Bonus: convert from Kao1 to Kao2
    ////////////////////////////////////////////////////////////////

    void DenisLevelBonus::convertToKao2(int32_t bonus_id, eGroup* parent_group) const
    {
        char bufor[16];
        eString test_str;

        eProxy* test_proxy;
        eSRP srp;

        if (0x00 == type)
        {
            /********************************/
            /* Create proxy */

            test_proxy = new eProxy();
            test_proxy->incRef();

            test_proxy->setCategory(2);

            test_proxy->setTargetName("powerup\\medal\\medal.def");

            sprintf_s(bufor, 16, "PowerUp%02d", bonus_id);
            test_proxy->setName(bufor);

            /********************************/
            /* Apply bonus position */
            /* Left-haned to Right-handed system conversion */

            srp.pos.x = position.x;
            srp.pos.y = position.z;
            srp.pos.z = position.y;

            test_proxy->setXForm(srp);

            /********************************/
            /* Append this object */

            if (nullptr != parent_group)
            {
                parent_group->appendChild(test_proxy);
            }

            test_proxy->decRef();
        }
    }

}
