#include <ElephantEngine/eCollisionMgr.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eCollisionMgr interface
    // <kao2.00499260> (constructor)
    // <kao2.00498680> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_COLLISIONMGR_TYPEINFO
    (
        E_COLLISIONMGR_ID,
        "eCollisionMgr",
        &E_OBJECT_TYPEINFO,
        []() -> eObject*
        {
            return new eCollisionMgr;
        }
    );

    const TypeInfo* eCollisionMgr::getType() const
    {
        return &E_COLLISIONMGR_TYPEINFO;
    }

    eCollisionMgr::eCollisionMgr()
    : eObject()
    {
        clearNewCollisionMgr();
    }

    eCollisionMgr::~eCollisionMgr()
    {
        /* DEBUG: prevents memory leaks */
        lockedFlag = 0x02;

        if (nullptr != seriesB)
        {
            delete[](seriesB);

            seriesB = nullptr;
            seriesB_MaxLength = 0;
            seriesB_Count = 0;
        }

        ArFunctions::destroy_AxisList_pointers(&(unknown_14), 8, 3);

        if (nullptr != availableIndices)
        {
            delete[](availableIndices);

            availableIndices = nullptr;
            availableIndices_MaxLength = 0;
            availableIndices_Count = 0;
        }
    }


    ////////////////////////////////////////////////////////////////
    // eCollisionMgr: cloning the object
    ////////////////////////////////////////////////////////////////

    void eCollisionMgr::createFromOtherObject(const eCollisionMgr &other)
    {
        throw ErrorMessage
        (
            "CRITICAL ERROR while cloning the \"eCollisionMgr\" object:\n" \
            "cloning << collision managers >> without context is not supported!!!"
        );
    }

    eCollisionMgr::eCollisionMgr(const eCollisionMgr &other)
    : eObject(other)
    {
        clearNewCollisionMgr();

        /****************/

        createFromOtherObject(other);
    }

    eCollisionMgr& eCollisionMgr::operator = (const eCollisionMgr &other)
    {
        if ((&other) != this)
        {
            eObject::operator = (other);

            /****************/

            if (nullptr != seriesB)
            {
                delete[](seriesB);
                seriesB = nullptr;
            }

            seriesB_Count = 0;

            /****************/

            ArFunctions::destroy_AxisList_pointers(&(unknown_14), 8, 3);

            unknown_14 = nullptr;

            /****************/

            if (nullptr != availableIndices)
            {
                delete[](availableIndices);
                availableIndices = nullptr;
            }

            availableIndices_Count = 0;

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eCollisionMgr::cloneFromMe() const
    {
        return new eCollisionMgr(*this);
    }


    ////////////////////////////////////////////////////////////////
    // eCollisionMgr: serialization
    // <kao2.004995F0>
    ////////////////////////////////////////////////////////////////
    void eCollisionMgr::serialize(Archive &ar)
    {
        int32_t i;

        /* [0x04] Left-out indices to give out for new AxisListBoxes */

        if (ar.isInReadMode())
        {
            if (nullptr != availableIndices)
            {
                delete[](availableIndices);
                availableIndices = nullptr;

                availableIndices_Count = 0;
            }

            ar.readOrWrite(&availableIndices_MaxLength, 0x04);

            availableIndices = new int32_t [availableIndices_MaxLength];

            for (availableIndices_Count = 0; availableIndices_Count < availableIndices_MaxLength; availableIndices_Count++)
            {
                ar.readOrWrite(&(availableIndices[availableIndices_Count]), 0x04);
            }
        }
        else
        {
            ar.readOrWrite(&availableIndices_Count, 0x04);

            for (i = 0; i < availableIndices_Count; i++)
            {
                ar.readOrWrite(&(availableIndices[i]), 0x04);
            }
        }

        /* [0x10] Largest ALBox ID ever generated in this session */

        ar.readOrWrite(&largestBoxCount, 0x04);

        /* [0x2C] Collection of AxisListBoxes (populate the array with null pointers) */

        if (ar.isInReadMode())
        {
            if (nullptr != seriesB)
            {
                delete[](seriesB);
                seriesB = nullptr;

                seriesB_Count = 0;
            }

            seriesB_MaxLength = largestBoxCount;

            seriesB = new eALBox* [seriesB_MaxLength];

            for (seriesB_Count = 0; seriesB_Count < seriesB_MaxLength; seriesB_Count++)
            {
                seriesB[seriesB_Count] = nullptr;
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eCollisionMgr: prepare ALBox sub-structures
    // <kao2.00499560>
    ////////////////////////////////////////////////////////////////
    void eCollisionMgr::prepare_ALBox_links()
    {
        int32_t i;
        AxisList* link;

        for (i = 0; i < seriesB_Count; i++)
        {
            if (nullptr != seriesB[i])
            {
                link = seriesB[i]->getAxisList(0, 0);
                link->setPointersFromCollisionManager_A(seriesB, unknown_14, unknown_18);

                link = seriesB[i]->getAxisList(0, 1);
                link->setPointersFromCollisionManager_A(seriesB, unknown_14, unknown_18);

                link = seriesB[i]->getAxisList(1, 0);
                link->setPointersFromCollisionManager_A(seriesB, unknown_1C, unknown_20);

                link = seriesB[i]->getAxisList(1, 1);
                link->setPointersFromCollisionManager_A(seriesB, unknown_1C, unknown_20);

                link = seriesB[i]->getAxisList(2, 0);
                link->setPointersFromCollisionManager_A(seriesB, unknown_24, unknown_28);

                link = seriesB[i]->getAxisList(2, 1);
                link->setPointersFromCollisionManager_A(seriesB, unknown_24, unknown_28);
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eCollisionMgr: ???
    // <kao2.004993D0>
    ////////////////////////////////////////////////////////////////
    int32_t eCollisionMgr::function_004993D0(int8_t arg1)
    {
        int32_t i;
        int32_t some_id;

        eALBox* test_box;
        uint8_t* test_series;

        if (0x00 != arg1)
        {
            some_id = seriesB_Count;
        }
        else
        {
            some_id = availableIndices[availableIndices_Count - 1];

            availableIndices_Count--;

            if (0 == availableIndices_Count)
            {
                appendAvailableId(some_id + 1);
            }

            if (some_id > largestBoxCount)
            {
                largestBoxCount = some_id;
            }
        }

        if (some_id > (seriesB_Count - 1))
        {
            insertNewItem_seriesB(nullptr);
        }

        for (i = (some_id + 1); i < seriesB_Count; i++)
        {
            test_box = seriesB[i];

            if (nullptr != test_box)
            {
                test_series = test_box->getSeriesPointer();

                test_series[some_id / 2] &= (0xAA << (some_id & 0x01));
            }
        }

        return some_id;
    }


    ////////////////////////////////////////////////////////////////
    // eCollisionMgr: ???
    // <kao2.00499390>
    ////////////////////////////////////////////////////////////////
    void eCollisionMgr::function_00499390(AxisList arg1[3][2])
    {
        /* [0x14] first pair ([0x18] goes unused) */
        unknown_14->function_004BCF30(arg1[0]);

        /* [0x1C] second pair ([0x20] goes unused) */
        unknown_1C->function_004BCF30(arg1[1]);

        /* [0x24] third pair ([0x28] goes unused) */
        unknown_24->function_004BCF30(arg1[2]);
    }


    ////////////////////////////////////////////////////////////////
    // eCollisionMgr: ???
    // <kao2.004994E0>
    ////////////////////////////////////////////////////////////////
    void eCollisionMgr::function_004994E0(int32_t offset)
    {
        int32_t a;

        /* DEBUG: prevents memory leaks */
        if (0x02 != lockedFlag)
        {
            if ((availableIndices_Count + 1) > availableIndices_MaxLength)
            {
                appendAvailableId(offset);
            }
            else
            {
                availableIndices[availableIndices_Count] = offset;
                availableIndices_Count++;
            }

            save_ALBox(offset, nullptr);

            if (0x01 != lockedFlag)
            {
                for (a = 0; a < seriesB_Count; a++)
                {
                    if (nullptr != seriesB[a])
                    {
                        return;
                    }
                }

                resetCounters();
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eCollisionMgr: store some eALBox pointer
    ////////////////////////////////////////////////////////////////
    void eCollisionMgr::save_ALBox(int32_t offset, eALBox* pointer)
    {
        if (nullptr != seriesB)
        {
            if (offset == seriesB_Count)
            {
                insertNewItem_seriesB(pointer);
            }
            else if ((offset >= 0) && (offset < seriesB_Count))
            {
                seriesB[offset] = pointer;
            }
            else
            {
                throw ErrorMessage
                (
                    "eCollisionMgr::save_ALBox():\n" \
                    "too big offset! (%i)\n" \
                    "(current length = %i, max length = %i)",
                    offset, seriesB_Count, seriesB_MaxLength
                );
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eCollisionMgr: get eALBox array size
    ////////////////////////////////////////////////////////////////
    int32_t eCollisionMgr::get_ALBoxes_array_size() const
    {
        return seriesB_Count;
    }


    ////////////////////////////////////////////////////////////////
    // eCollisionMgr: get array of eALBox pointers
    ////////////////////////////////////////////////////////////////
    eALBox** eCollisionMgr::get_ALBoxes_array() const
    {
        return seriesB;
    }


    ////////////////////////////////////////////////////////////////
    // eCollisionMgr: make space in "availableIndices" array
    ////////////////////////////////////////////////////////////////
    void eCollisionMgr::appendAvailableId(int32_t item)
    {
        int32_t i;
        int32_t* temp;

        if ((availableIndices_Count + 1) > availableIndices_MaxLength)
        {
            temp = new int32_t [availableIndices_MaxLength + 1];

            if (nullptr != availableIndices)
            {
                for (i = 0; i < availableIndices_Count; i++)
                {
                    temp[i] = availableIndices[i];
                }

                delete[](availableIndices);
            }

            availableIndices = temp;

            availableIndices_MaxLength++;
        }

        availableIndices[availableIndices_Count] = item;

        availableIndices_Count++;
    }


    ////////////////////////////////////////////////////////////////
    // eCollisionMgr: make space in "seriesB" array
    ////////////////////////////////////////////////////////////////
    void eCollisionMgr::insertNewItem_seriesB(eALBox* item)
    {
        int32_t i;
        eALBox** temp;

        if ((seriesB_Count + 1) > seriesB_MaxLength)
        {
            temp = new eALBox* [seriesB_MaxLength + 1];

            if (nullptr != seriesB)
            {
                for (i = 0; i < seriesB_Count; i++)
                {
                    temp[i] = seriesB[i];
                }

                delete[](seriesB);
            }

            seriesB = temp;

            seriesB_MaxLength++;
        }

        seriesB[seriesB_Count] = item;

        seriesB_Count++;
    }


    ////////////////////////////////////////////////////////////////
    // eCollisionMgr: reset the data for ID-generator (used in eScene)
    ////////////////////////////////////////////////////////////////
    void eCollisionMgr::resetCounters()
    {
        largestBoxCount = 0;
        seriesB_Count = 0;

        availableIndices_Count = 0;

        if (availableIndices_MaxLength >= 1)
        {
            availableIndices[0] = 0;
            availableIndices_Count = 1;
        }
        else
        {
            appendAvailableId(0);
        }
    }


    ////////////////////////////////////////////////////////////////
    // eCollisionMgr: manipulate locked-flag (used in eScene)
    ////////////////////////////////////////////////////////////////
    void eCollisionMgr::lockDuringSerialize(bool state)
    {
        /* 0: serialization complete */
        /* 1: serialization in proccess, do not modify "seriesB" */
        lockedFlag = (uint8_t)state;
    }


    ////////////////////////////////////////////////////////////////
    // eCollisionMgr: clear this object
    ////////////////////////////////////////////////////////////////
    void eCollisionMgr::clearNewCollisionMgr()
    {
        lockedFlag = 0x00;

        /*[0x04]*/ availableIndices_Count = 1;
        /*[0x08]*/ availableIndices_MaxLength = 1;
        /*[0x0C]*/ availableIndices = new int32_t [1];
        availableIndices[0] = 0;

        /*[0x10]*/ largestBoxCount = 0;

        ArFunctions::generate_AxisList_pointers(&(unknown_14), 8, 3);

        /*[0x2C]*/ seriesB_Count = 0;
        /*[0x30]*/ seriesB_MaxLength = 0;
        /*[0x34]*/ seriesB = nullptr;
    }

}
