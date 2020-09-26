#include <kao2ar/AxisList.h>
#include <kao2ar/Archive.h>

#include <kao2engine/eALBox.h>

#include <kao2engine/eScene.h>
#include <kao2engine/eCollisionMgr.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // AxisList: Constructor and Descructor
    // <kao2.004BAC80> (costructor)
    // <kao2.004BACA0> (destructor)
    ////////////////////////////////////////////////////////////////
    AxisList::AxisList()
    {
        clearNewAxisList();
    }

    AxisList::~AxisList()
    {
        if (nullptr != next)
        {
            next->previous = previous;
        }

        if (nullptr != previous)
        {
            previous->next = next;
        }
    }


    ////////////////////////////////////////////////////////////////
    // AxisList: cloning the object
    ////////////////////////////////////////////////////////////////

    void AxisList::createFromOtherObject(const AxisList &other)
    {
        throw ErrorMessage
        (
            "CRITICAL ERROR while cloning the \"AxisList\" object:\n" \
            "cloning << axis lists >> without context is not supported!!!"
        );
    }

    AxisList::AxisList(const AxisList &other)
    {
        clearNewAxisList();

        createFromOtherObject(other);
    }

    AxisList& AxisList::operator = (const AxisList &other)
    {
        if ((&other) != this)
        {
            createFromOtherObject(other);
        }

        return (*this);
    }


    ////////////////////////////////////////////////////////////////
    // AxisList: serialization
    // <kao2.004BAEF0>
    ////////////////////////////////////////////////////////////////
    void AxisList::serialize(Archive &ar)
    {
        /* [0x08] Point in space on Axis */
        ar.readOrWrite(&coordLimit, 0x04);

        /* (ar.version() >= 0x81) */

        /* [0x0C] "eALBox" ID in "eCollisionMgr" collection of boxes */
        ar.readOrWrite(&alboxEntryId, 0x02);

        /* [0x0E] Column ID (0 for MIN boundary, 1 for MAX boundary) */
        ar.readOrWrite(&columnId, 0x01);

        /* [0x0F] Row ID (0 for X, 1 for Y, 2 for Z) */
        ar.readOrWrite(&rowId, 0x01);

        /* [0x04] [0x00] next list and previous list pointers */
        if (ar.isInReadMode())
        {
            ar.readOrWrite(&tempNextId, 0x04);
            ar.readOrWrite(&tempPreviousId, 0x04);
        }
        else
        {
            if (nullptr != next)
            {
                next->serializePointer(ar);
            }
            else
            {
                ar.readOrWrite(&tempNextId, 0x04);
            }

            if (nullptr != previous)
            {
                previous->serializePointer(ar);
            }
            else
            {
                ar.readOrWrite(&tempPreviousId, 0x04);
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // AxisList
    // <kao2.004BAE40> (pointer serialization)
    ////////////////////////////////////////////////////////////////
    void AxisList::serializePointer(Archive &ar) const
    {
        int32_t a;

        if ((-1) != alboxEntryId)
        {
            a = alboxEntryId + 0x02;

            if (0x00 == columnId)
            {
                a = (-a);
            }
        }
        else
        {
            a = columnId ? (-1) : 1;
        }

        ar.readOrWrite(&a, 0x04);
    }


    ////////////////////////////////////////////////////////////////
    //
    // <kao2.004BAFD0>
    ////////////////////////////////////////////////////////////////
    void AxisList::setPointersFromCollisionManager_A(eALBox** group, AxisList* arg2, AxisList* arg3)
    {
        AxisList* a;

        a = getPointerFromCollisionManager_B(group, arg2, arg3, tempNextId);

        next = a;

        if (a == arg2)
        {
            arg2->previous = this;
        }

        a = getPointerFromCollisionManager_B(group, arg2, arg3, tempPreviousId);

        previous = a;

        if (a == arg3)
        {
            arg3->next = this;
        }
    }


    ////////////////////////////////////////////////////////////////
    //
    // <kao2.004BAE90> ("getPointers")
    ////////////////////////////////////////////////////////////////
    AxisList* AxisList::getPointerFromCollisionManager_B(eALBox** group, AxisList* arg2, AxisList* arg3, int32_t arg4) const
    {
        int32_t a;
        eALBox* box;

        if (arg4 < 0)
        {
            if ((-1) == arg4)
            {
                return arg2;
            }

            a = arg4 + 0x02;

            box = group[(-a)];

            return box->getAxisList(rowId, 0);
        }
        else if (arg4 > 0)
        {
            if (1 == arg4)
            {
                return arg3;
            }

            a = arg4 - 0x02;

            box = group[a];

            return box->getAxisList(rowId, 1);
        }
        else
        {
            throw ErrorMessage
            (
                "AxisList::function_004BAE90():\n" \
                "other list ID initialized incorrectly! (cannot be zero)"
            );
        }
    }


    ////////////////////////////////////////////////////////////////
    //
    // <kao2.004BCF30>
    ////////////////////////////////////////////////////////////////
    void AxisList::function_004BCF30(AxisList arg1[2]) const
    {
        AxisList* test_list = this->previous;

        while ((arg1[0].coordLimit) >= (test_list->coordLimit))
        {
            test_list->function_004BADA0(&(arg1[0]));

            test_list = test_list->previous;
        }

        test_list->next->previous = &(arg1[0]);
        arg1[0].next = test_list->next;

        arg1[0].previous = test_list;
        test_list->next = &(arg1[0]);

        while ((arg1[1].coordLimit) >= (test_list->coordLimit))
        {
            test_list->function_004BADA0(&(arg1[1]));

            test_list = test_list->previous;
        }

        test_list->next->previous = &(arg1[1]);
        arg1[1].next = test_list->next;

        arg1[1].previous = test_list;
        test_list->next = &(arg1[1]);
    }


    ////////////////////////////////////////////////////////////////
    //
    // <kao2.004BADA0>
    ////////////////////////////////////////////////////////////////
    void AxisList::function_004BADA0(AxisList* arg1) const
    {
        int32_t a;
        int32_t array_size = 0;

        eScene* test_scene = ArFunctions::getCurrentScene();
        eCollisionMgr* test_manager = test_scene->getCollisionManager();
        eALBox** test_boxes = nullptr;
        eALBox* test_box_A = nullptr;
        eALBox* test_box_B = nullptr;

        array_size = test_manager->get_ALBoxes_array_size();
        test_boxes = test_manager->get_ALBoxes_array();

        /* First block */

        a = alboxEntryId;

        if (a < 0)
        {
            a = array_size - alboxEntryId;
        }

        a = a % array_size;

        test_box_A = test_boxes[a];

        /* Second block */

        a = arg1->alboxEntryId;

        if (a < 0)
        {
            a = array_size - alboxEntryId;
        }

        a = a % array_size;

        test_box_B = test_boxes[a];

        /* Checking */

        if ((arg1->alboxEntryId) < alboxEntryId)
        {
            test_box_A->function_004A9F40(test_box_B, rowId);
        }
        else if ((arg1->alboxEntryId) > alboxEntryId)
        {
            test_box_B->function_004A9F40(test_box_A, rowId);
        }
    }


    ////////////////////////////////////////////////////////////////
    // AxisList: clear this object
    ////////////////////////////////////////////////////////////////
    void AxisList::clearNewAxisList()
    {
        /*[0x00]*/ previous = nullptr;
        /*[0x04]*/ next = nullptr;
        /*[0x08]*/ coordLimit = 0;
        /*[0x0C]*/ alboxEntryId = (-1);
        /*[0x0E]*/ columnId = 0;
        /*[0x0F]*/ rowId = 0;

        tempPreviousId = 0;
        tempNextId = 0;
    }


    ////////////////////////////////////////////////////////////////
    // Generate AxisList pointers
    // <kao2.005A589E>
    // Arg4 = <kao2.004BCDC0>
    ////////////////////////////////////////////////////////////////
    void ArFunctions::generate_AxisList_pointers(AxisList** pointer, int32_t arg2, int32_t arg3)
    {
        int32_t i;
        int32_t j = 0;

        AxisList* testA;
        AxisList* testB;

        for (i = 0; i < arg3; i++)
        {
            testA = new AxisList;
            pointer[j + 0] = testA;

            testB = new AxisList;
            pointer[j + 1] = testB;

            testA->alboxEntryId = (-1);
            *(uint32_t*)&(testA->coordLimit) = 0xD8635FA9;
            testA->columnId = 0x01;

            testB->alboxEntryId = (-1);
            *(uint32_t*)&(testB->coordLimit) = 0x58635FA9;
            testB->columnId = 0x00;

            testA->previous = testB;
            testA->next = nullptr;

            testB->previous = nullptr;
            testB->next = testA;

            /* Pointer to next group */
            j += (arg2 / 0x04);
        }
    }


    ////////////////////////////////////////////////////////////////
    // Destroy AxisList pointers
    // <kao2.005A57AA>
    // Arg4 = <kao2.004BCEA0>
    ////////////////////////////////////////////////////////////////
    void ArFunctions::destroy_AxisList_pointers(AxisList** pointer, int32_t arg2, int32_t arg3)
    {
        if (nullptr == pointer)
        {
            return;
        }

        int32_t i;
        int32_t j = (arg2 / 0x04) * (arg3 - 1);

        AxisList* testA;
        AxisList* testB;

        for (i = 0; i < arg3; i++)
        {
            testA = pointer[j + 0];
            testB = pointer[j + 1];

            if (nullptr != testA)
            {
                delete(testA);
            }

            if (nullptr != testB)
            {
                delete(testB);
            }

            /* Pointer to previous group */
            j -= (arg2 / 0x04);
        }
    }

}

