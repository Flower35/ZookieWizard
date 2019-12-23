#include <denis/DenisLevelTrack.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // Moving Track: sub-structures
    ////////////////////////////////////////////////////////////////

    DenisLevelTrack_A::DenisLevelTrack_A()
    {
        std::memset(dummy, 0x00, 0x3C);
    }

    void DenisLevelTrack_A::serialize(DenisFileOperator &file)
    {
        file.readOrWrite(dummy, 0x3C);
    }
    
    DenisLevelTrack_B::DenisLevelTrack_B()
    {
        std::memset(dummy, 0x00, 0x58);
    }

    void DenisLevelTrack_B::serialize(DenisFileOperator &file)
    {
        file.readOrWrite(dummy, 0x58);
    }

    DenisLevelTrack_C::DenisLevelTrack_C()
    {
        std::memset(dummy, 0x00, 0x10);
    }

    void DenisLevelTrack_C::serialize(DenisFileOperator &file)
    {
        file.readOrWrite(dummy, 0x10);
    }

    DenisLevelTrack_D::DenisLevelTrack_D()
    {
        std::memset(dummy, 0x00, 0x08);
    }

    void DenisLevelTrack_D::serialize(DenisFileOperator &file)
    {
        file.readOrWrite(dummy, 0x08);
    }

    DenisLevelTrack_E::DenisLevelTrack_E()
    {
        std::memset(dummy, 0x00, 0x10);
    }

    void DenisLevelTrack_E::serialize(DenisFileOperator &file)
    {
        file.readOrWrite(dummy, 0x10);
    }

    DenisLevelTrack_F::DenisLevelTrack_F()
    {
        std::memset(dummy, 0x00, 0x10);
    }

    void DenisLevelTrack_F::serialize(DenisFileOperator &file)
    {
        file.readOrWrite(dummy, 0x10);
    }

    ////////////////////////////////////////////////////////////////
    // Moving Track: constructor
    ////////////////////////////////////////////////////////////////

    DenisLevelTrack::DenisLevelTrack()
    {
        dummy_00 = 0;
        dummy_04 = 0;
        dummy_08 = 0;
        dummy_0C = 0;

        groupA_Count = 0;
        groupA = nullptr;

        groupB_Count = 0;
        groupB = nullptr;

        groupC_Count = 0;
        groupC = nullptr;

        groupD_Count = 0;
        groupD = nullptr;

        groupE_Count = 0;
        groupE = nullptr;

        groupF_Count = 0;
        groupF = nullptr;
    }


    ////////////////////////////////////////////////////////////////
    // Moving Track: destructor
    ////////////////////////////////////////////////////////////////

    DenisLevelTrack::~DenisLevelTrack()
    {
        if (nullptr != groupA)
        {
            delete[](groupA);
        }

        if (nullptr != groupB)
        {
            delete[](groupB);
        }

        if (nullptr != groupC)
        {
            delete[](groupC);
        }

        if (nullptr != groupD)
        {
            delete[](groupD);
        }

        if (nullptr != groupE)
        {
            delete[](groupE);
        }

        if (nullptr != groupF)
        {
            delete[](groupF);
        }
    }


    ////////////////////////////////////////////////////////////////
    // Moving Track: serialization
    ////////////////////////////////////////////////////////////////

    void DenisLevelTrack::serialize(DenisFileOperator &file)
    {
        int32_t i;

        /* unknown values */

        file.readOrWrite(&dummy_00, 0x04);
        file.readOrWrite(&dummy_04, 0x04);
        file.readOrWrite(&dummy_08, 0x04);
        file.readOrWrite(&dummy_0C, 0x04);

        /* unknown group (1 of 6) */

        file.readOrWrite(&groupA_Count, 0x04);

        if (file.isInReadMode())
        {
            if (nullptr != groupA)
            {
                delete[](groupA);
                groupA = nullptr;
            }

            if (groupA_Count > 0)
            {
                groupA = new DenisLevelTrack_A [groupA_Count];
            }
        }

        for (i = 0; i < groupA_Count; i++)
        {
            groupA[i].serialize(file);
        }

        /* unknown group (2 of 6) */

        file.readOrWrite(&groupB_Count, 0x04);

        if (file.isInReadMode())
        {
            if (nullptr != groupB)
            {
                delete[](groupB);
                groupB = nullptr;
            }

            if (groupB_Count > 0)
            {
                groupB = new DenisLevelTrack_B [groupB_Count];
            }
        }

        for (i = 0; i < groupB_Count; i++)
        {
            groupB[i].serialize(file);
        }

        /* unknown group (3 of 6) */

        file.readOrWrite(&groupC_Count, 0x04);

        if (file.isInReadMode())
        {
            if (nullptr != groupC)
            {
                delete[](groupC);
                groupC = nullptr;
            }

            if (groupC_Count > 0)
            {
                groupC = new DenisLevelTrack_C [groupC_Count];
            }
        }

        for (i = 0; i < groupC_Count; i++)
        {
            groupC[i].serialize(file);
        }

        /* unknown group (4 of 6) */

        file.readOrWrite(&groupD_Count, 0x04);

        if (file.isInReadMode())
        {
            if (nullptr != groupD)
            {
                delete[](groupD);
                groupD = nullptr;
            }

            if (groupD_Count > 0)
            {
                groupD = new DenisLevelTrack_D [groupD_Count];
            }
        }

        for (i = 0; i < groupD_Count; i++)
        {
            groupD[i].serialize(file);
        }

        /* unknown group (5 of 6) */

        file.readOrWrite(&groupE_Count, 0x04);

        if (file.isInReadMode())
        {
            if (nullptr != groupE)
            {
                delete[](groupE);
                groupE = nullptr;
            }

            if (groupE_Count > 0)
            {
                groupE = new DenisLevelTrack_E [groupE_Count];
            }
        }

        for (i = 0; i < groupE_Count; i++)
        {
            groupE[i].serialize(file);
        }

        /* unknown group (6 of 6) */

        file.readOrWrite(&groupF_Count, 0x04);

        if (file.isInReadMode())
        {
            if (nullptr != groupF)
            {
                delete[](groupF);
                groupF = nullptr;
            }

            if (groupF_Count > 0)
            {
                groupF = new DenisLevelTrack_F [groupF_Count];
            }
        }

        for (i = 0; i < groupF_Count; i++)
        {
            groupF[i].serialize(file);
        }
    }

}
