#include <kao2engine/eLinearCtrl.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eLinearCtrl interface
    // <kao2.0055CFA0> (constructor)
    // <kao2.0055D170> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_LINEARCTRL_TYPEINFO
    (
        E_LINEARCTRL_ID,
        "eLinearCtrl",
        &E_OBJECT_TYPEINFO,
        []() -> eObject*
        {
            return new eLinearCtrl;
        }
    );

    TypeInfo* eLinearCtrl::getType() const
    {
        return &E_LINEARCTRL_TYPEINFO;
    }

    eLinearCtrl::eLinearCtrl()
    : eObject()
    {
        /*[0x04]*/ groupA_Count = 0;
        /*[0x08]*/ groupA_MaxLength = 0;
        /*[0x0C]*/ groupA = nullptr;
        /*[0x10]*/ groupB_Count = 0;
        /*[0x14]*/ groupB_MaxLength = 0;
        /*[0x18]*/ groupB = nullptr;

        /*[0x28]*/ unknown_28 = 1.0f;
        /*[0x34]*/ unknown_34 = 1.0f;
        
        /*[0x1C]*/ unknown_1C = 0;
        /*[0x24]*/ unknown_24 = 0;

        /*[0x3C]*/ series = nullptr;
        /*[0x40]*/ seriesLength = 0;

        /*[0x20]*/ unknown_20 = 0x01;

        /*[0x2C]*/ unknown_2C = (-100.0f);
        /*[0x30]*/ unknown_30 = 100.0f;
        /*[0x38]*/ unknown_38 = 10.0f;
    }

    eLinearCtrl::~eLinearCtrl()
    {
        if (nullptr != series)
        {
            delete[](series);
        }

        if (nullptr != groupB)
        {
            delete[](groupB);
        }

        if (nullptr != groupA)
        {
            delete[](groupA);
        }
    }


    ////////////////////////////////////////////////////////////////
    // Unknown structures
    // <kao2.0055E670> (first group serialization)
    // <kao2.0055E810> (second group serialization)
    ////////////////////////////////////////////////////////////////

    void eLinearCtrlBaseA::serialize(Archive &ar)
    {
        ar.readOrWrite(&unknown_00, 0x04);
        ar.readOrWrite(&unknown_04, 0x04);
    }

    void eLinearCtrlBaseB::serialize(Archive &ar)
    {
        ar.readOrWrite(&unknown_00, 0x04);
        ar.readOrWrite(&unknown_04, 0x04);
        ar.readOrWrite(&unknown_08, 0x04);
        ar.readOrWrite(&unknown_0C, 0x04);
        ar.readOrWrite(&unknown_10, 0x04);
        ar.readOrWrite(&unknown_14, 0x04);
        ar.readOrWrite(&unknown_18, 0x04);
    }


    ////////////////////////////////////////////////////////////////
    // eLinearCtrl serialization
    // <kao2.0055D7C0>
    ////////////////////////////////////////////////////////////////
    void eLinearCtrl::serialize(Archive &ar)
    {
        int32_t i;

        /* [0x04] unknown group */

        if (ar.isInReadMode())
        {
            if (nullptr != groupA)
            {
                delete[](groupA);
                groupA = nullptr;

                groupA_Count = 0;
            }

            ar.readOrWrite(&groupA_MaxLength, 0x04);

            groupA = new eLinearCtrlBaseA [groupA_MaxLength];

            for (i = 0; i < groupA_MaxLength; i++)
            {
                groupA[i].serialize(ar);

                groupA_Count = (i+1);
            }
        }
        else
        {
            ar.readOrWrite(&groupA_Count, 0x04);

            for (i = 0; i < groupA_Count; i++)
            {
                groupA[i].serialize(ar);
            }
        }

        /* [0x10] unknown group */

        if (ar.isInReadMode())
        {
            if (nullptr != groupB)
            {
                delete[](groupB);
                groupB = nullptr;

                groupB_Count = 0;
            }

            ar.readOrWrite(&groupB_MaxLength, 0x04);

            groupB = new eLinearCtrlBaseB [groupB_MaxLength];

            for (i = 0; i < groupB_MaxLength; i++)
            {
                groupB[i].serialize(ar);

                groupB_Count = (i+1);
            }
        }
        else
        {
            ar.readOrWrite(&groupB_Count, 0x04);

            for (i = 0; i < groupB_Count; i++)
            {
                groupB[i].serialize(ar);
            }
        }

        /* unknown values */

        ar.readOrWrite(&unknown_1C, 0x04);
        ar.readOrWrite(&unknown_20, 0x01);
        ar.readOrWrite(&unknown_24, 0x04);
        ar.readOrWrite(&unknown_28, 0x04);
        ar.readOrWrite(&unknown_2C, 0x04);
        ar.readOrWrite(&unknown_30, 0x04);
        ar.readOrWrite(&unknown_34, 0x04);
        ar.readOrWrite(&unknown_38, 0x04);

        /* [0x40] unknown series */

        ar.readOrWrite(&seriesLength, 0x04);

        if (ar.isInReadMode())
        {
            if (nullptr != series)
            {
                delete[](series);

                series = nullptr;
            }

            series = new float [seriesLength];
        }

        ar.readOrWrite(series, (0x04 * seriesLength));
    }

}
