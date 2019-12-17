#include <kao2engine/eNPCMap.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eNPCMap interface
    // <kao2.0041FF10> (constructor)
    // <kao2.004201E0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_NPCMAP_TYPEINFO
    (
        E_NPCMAP_ID,
        "eNPCMap",
        &E_GROUP_TYPEINFO,
        []() -> eObject*
        {
            return new eNPCMap;
        }
    );

    TypeInfo* eNPCMap::getType()
    {
        return &E_NPCMAP_TYPEINFO;
    }

    eNPCMap::eNPCMap()
    : eGroup()
    {
        /*[0x9C]*/ groupA_Count = 0;
        /*[0xA0]*/ groupA_MaxLength = 0;
        /*[0xA4]*/ groupA = nullptr;

        /*[0x54]*/ unknown_54 = 60.0f;

        /*[0x4C]*/ unknown_4C = 1;
        /*[0x50]*/ unknown_50 = 1;
        /*[0x60]*/ unknown_60 = new int32_t [1];

        /*[0x1C]*/ flags |= 0x10000000;

        /*[0xAC]*/ unknown_AC = 0;
        /*[0xA8]*/ unknown_A8 = 0;
        /*[0xB0]*/ unknown_B0 = 0;

        /*[0x48]*/ unknown_48 = 0x00;
    }

    eNPCMap::~eNPCMap()
    {
        if (nullptr != unknown_60)
        {
            delete[](unknown_60);
        }

        if (nullptr != groupA)
        {
            delete[](groupA);
        }
    }


    ////////////////////////////////////////////////////////////////
    // eNPCMap serialization
    // <kao2.00420DC0>
    ////////////////////////////////////////////////////////////////
    void eNPCMap::serialize(Archive &ar)
    {
        int32_t i;

        eGroup::serialize(ar);

        /* [0x4C] unknown values */

        ar.readOrWrite(&unknown_4C, 0x04);
        ar.readOrWrite(&unknown_50, 0x04);

        /* [0x64] unknown (3 floats) */

        unknown_64.serialize(ar);

        /* [0x70] unknown (3 floats) */

        unknown_70.serialize(ar);

        /* [0x54] unknown values */

        ar.readOrWrite(&unknown_54, 0x04);
        ar.readOrWrite(&unknown_58, 0x04);
        ar.readOrWrite(&unknown_5C, 0x04);

        /* [0x9C] unknown group */

        if (ar.isInReadMode())
        {
            if (nullptr != groupA)
            {
                delete[](groupA);
                groupA = nullptr;

                groupA_Count = 0;
                groupA_MaxLength = 0;
            }

            ar.readOrWrite(&groupA_MaxLength, 0x04);

            if (0 != groupA_MaxLength)
            {
                groupA = new int32_t [groupA_MaxLength];

                for (i = 0; i < groupA_MaxLength; i++)
                {
                    ar.readOrWrite(&(groupA[i]), 0x04);

                    groupA_Count = (i+1);
                }
            }
        }
        else
        {
            ar.readOrWrite(&groupA_Count, 0x04);

            for (i = 0; i < groupA_Count; i++)
            {
                ar.readOrWrite(&(groupA[i]), 0x04);
            }
        }

        /* [0x64] DUPLICATE SERIALIZATION */

        unknown_64.serialize(ar);

        /* [0x70] DUPLICATE SERIALIZATION */

        unknown_70.serialize(ar);

        /* [0x60] unknown series */

        i = unknown_50 * unknown_4C;

        if (ar.isInReadMode())
        {
            if (nullptr != unknown_60)
            {
                delete[](unknown_60);
                unknown_60 = nullptr;
            }

            unknown_60 = new int32_t [i];
        }

        ar.readOrWrite(unknown_60, sizeof(int32_t) * i);

        /* [0x7C] `eGroupManager::serialize()` */

        unknown_7C.serialize(ar);

        /* [0xA8] unknown values */

        ar.readOrWrite(&unknown_A8, 0x04);

        ar.readOrWrite(&unknown_AC, 0x04);
        ar.readOrWrite(&unknown_B0, 0x04);
        ar.readOrWrite(&unknown_B4, 0x04);

        /* [0x48] unknown value */

        ar.readOrWrite(&unknown_48, 0x01);
    }

}
