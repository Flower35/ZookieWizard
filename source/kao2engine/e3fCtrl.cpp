#include <kao2engine/e3fCtrl.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // e3fCtrl interface
    // <kao2.0055DA50> (constructor)
    // <kao2.0055DB00> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_3FCTRL_TYPEINFO
    (
        E_3FCTRL_ID,
        "e3fCtrl",
        &E_OBJECT_TYPEINFO,
        []() -> eObject*
        {
            return new e3fCtrl;
        }
    );

    TypeInfo* e3fCtrl::getType()
    {
        return &E_3FCTRL_TYPEINFO;
    }

    e3fCtrl::e3fCtrl()
    : eObject()
    {
        /*[0x04]*/ groupA_Count = 0;
        /*[0x08]*/ groupA_MaxLength = 0;
        /*[0x0C]*/ groupA = nullptr;
        /*[0x10]*/ groupB_Count = 0;
        /*[0x14]*/ groupB_MaxLength = 0;
        /*[0x18]*/ groupB = nullptr;

        /*[0x20]*/ unknown_20 = 0;

        /*[0x24]*/ series = nullptr;
        /*[0x28]*/ seriesLength = 0;
    }

    e3fCtrl::~e3fCtrl()
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
    // <kao2.0055E240> (first group serialization)
    // <kao2.0055E280> (second group serialization)
    ////////////////////////////////////////////////////////////////

    void e3fCtrlBaseA::serialize(Archive &ar)
    {
        ar.readOrWrite(&unknown_00, 0x04);

        unknown_04.serialize(ar);
    }

    void e3fCtrlBaseB::serialize(Archive &ar)
    {
        ar.readOrWrite(&unknown_00, 0x04);
        ar.readOrWrite(&unknown_04, 0x04);
        ar.readOrWrite(&unknown_08, 0x04);
        ar.readOrWrite(&unknown_0C, 0x04);

        ar.readOrWrite(&unknown_10, 0x04);
        ar.readOrWrite(&unknown_14, 0x04);
        ar.readOrWrite(&unknown_18, 0x04);
        ar.readOrWrite(&unknown_1C, 0x04);
    }


    ////////////////////////////////////////////////////////////////
    // e3fCtrl serialization
    // <kao2.0055E080>
    ////////////////////////////////////////////////////////////////
    void e3fCtrl::serialize(Archive &ar)
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

            groupA = new e3fCtrlBaseA [groupA_MaxLength];

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

            groupB = new e3fCtrlBaseB [groupB_MaxLength];

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

        ar.readOrWrite(&unknown_20, 0x04);
        ar.readOrWrite(&unknown_1C, 0x01);

        /* [0x24] unknown series */

        ar.readOrWrite(&seriesLength, 0x04);

        if (ar.isInReadMode())
        {
            if (nullptr != series)
            {
                delete[](series);

                series = nullptr;
            }

            series = new ePoint4 [seriesLength];
        }

        ar.readOrWrite(series, (0x10 * seriesLength));
    }

}
