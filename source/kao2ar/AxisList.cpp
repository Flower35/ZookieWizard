#include <kao2ar/AxisList.h>
#include <kao2ar/Archive.h>

#include <kao2engine/eALBox.h>

#include <kao2engine/eScene.h>
#include <kao2engine/eCollisionMgr.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // AxisList
    // <kao2.004BAC80> (costructor)
    ////////////////////////////////////////////////////////////////
    AxisList::AxisList()
    {
        /*[0x00]*/ previous = nullptr;
        /*[0x04]*/ next = nullptr;
        /*[0x08]*/ unknown_08 = 0;
        /*[0x0C]*/ unknown_0C = (-1);
        /*[0x0E]*/ unknown_0E = 0;
        /*[0x0F]*/ unknown_0F = 0;

        unknown_00_id = 0;
        unknown_04_id = 0;
    }


    ////////////////////////////////////////////////////////////////
    // AxisList
    // <kao2.004BACA0> (destructor)
    ////////////////////////////////////////////////////////////////
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
    // AxisList
    // <kao2.004BAEF0> (serialization)
    ////////////////////////////////////////////////////////////////
    void AxisList::serialize(Archive &ar)
    {
        /* [0x08] unknown */
        ar.readOrWrite(&unknown_08, 0x04);

        /* (ar.version() >= 0x81) */

        /* [0x0C] unknown */
        ar.readOrWrite(&unknown_0C, 0x02);

        /* [0x0E] unknown */
        ar.readOrWrite(&unknown_0E, 0x01);

        /* [0x0F] unknown */
        ar.readOrWrite(&unknown_0F, 0x01);

        /* [0x04] [0x00] unknown pointers */
        if (ar.isInReadMode())
        {
            ar.readOrWrite(&unknown_04_id, 0x04);
            ar.readOrWrite(&unknown_00_id, 0x04);
        }
        else
        {
            if (nullptr != next)
            {
                next->serializePointer(ar);
            }
            else
            {
                ar.readOrWrite(&unknown_04_id, 0x04);
            }

            if (nullptr != previous)
            {
                previous->serializePointer(ar);
            }
            else
            {
                ar.readOrWrite(&unknown_00_id, 0x04);
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // AxisList
    // <kao2.004BAE40> (pointer serialization)
    ////////////////////////////////////////////////////////////////
    void AxisList::serializePointer(Archive &ar)
    {
        int32_t a;

        if ((-1) != unknown_0C)
        {
            a = unknown_0C + 0x02;

            if (false == unknown_0E)
            {
                a = (-a);
            }
        }
        else
        {
            a = unknown_0E ? (-1) : 1;
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

        a = getPointerFromCollisionManager_B(group, arg2, arg3, unknown_04_id);

        next = a;

        if (a == arg2)
        {
            arg2->previous = this;
        }

        a = getPointerFromCollisionManager_B(group, arg2, arg3, unknown_00_id);

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
    AxisList* AxisList::getPointerFromCollisionManager_B(eALBox** group, AxisList* arg2, AxisList* arg3, int32_t arg4)
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

            return box->getAxisList(unknown_0F, 0);
        }
        else
        {
            if (1 == arg4)
            {
                return arg3;
            }

            a = arg4 - 0x02;

            box = group[a];

            return box->getAxisList(unknown_0F, 1);
        }
    }


    ////////////////////////////////////////////////////////////////
    // 
    // <kao2.004BCF30>
    ////////////////////////////////////////////////////////////////
    void AxisList::function_004BCF30(AxisList arg1[2])
    {
        float a;
        float b;

        AxisList* test = this->previous;

        do
        {
            a = *(float*)&(test->unknown_08);
            b = *(float*)&(arg1[0].unknown_08);

            if (a < b)
            {
                function_004BADA0(&(arg1[0]));

                //// (--dsp--) test = test->previous;
            }
        }
        while (0);
        //// (--dsp--) `while (a < b);`

        this->previous = &(arg1[0]);
        arg1[0].next = this;

        arg1[0].previous = test;
        test->next = &(arg1[0]);

        do
        {
            a = *(float*)&(test->unknown_08);
            b = *(float*)&(arg1[1].unknown_08);

            if (a < b)
            {
                function_004BADA0(&(arg1[1]));

                //// (--dsp--) test = test->previous;
            }
        }
        while (0);
        //// (--dsp--) `while (a < b);`

        this->previous = &(arg1[0]);
        arg1[1].next = this;

        arg1[1].previous = test;
        test->next = &(arg1[1]);

    }


    ////////////////////////////////////////////////////////////////
    // 
    // <kao2.004BADA0>
    ////////////////////////////////////////////////////////////////
    void AxisList::function_004BADA0(AxisList* arg1)
    {
        int32_t a;
        int32_t array_size;

        eScene* test_scene = ArFunctions::getCurrentScene();
        eCollisionMgr* test_manager = test_scene->getCollisionManager();
        eALBox** test_boxes;
        eALBox* test_box_A;
        eALBox* test_box_B;

        /* First block */

        a = unknown_0C;

        if (a < 0)
        {
            array_size = test_manager->get_ALBoxes_array_size();

            a = array_size - unknown_0C;
        }

        a = a % array_size;

        test_boxes = test_manager->get_ALBoxes_array();

        test_box_A = test_boxes[a];

        /* Second block */

        a = arg1->unknown_0C;

        if (a < 0)
        {
            array_size = test_manager->get_ALBoxes_array_size();

            a = array_size - unknown_0C;
        }

        a = a % array_size;

        test_boxes = test_manager->get_ALBoxes_array();

        test_box_B = test_boxes[a];

        /* Checking */

        if (arg1->unknown_0C < unknown_0C)
        {
            //// (--dsp--) <kao2.004A9F40>
            // unknown_0F jako arg2
            // test_box_B jako arg1
            // ecx = test_box_A
        }
        else if (arg1->unknown_0C > unknown_0C)
        {
            //// (--dsp--) <kao2.004A9F40>
            // unknown_0F jako arg2
            // test_box_A jako arg1
            // ecx = test_box_B
        }
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

            testA->unknown_0C = (-1);
            *(uint32_t*)&(testA->unknown_08) = 0xD8635FA9;
            testA->unknown_0E = true;

            testB->unknown_0C = (-1);
            *(uint32_t*)&(testB->unknown_08) = 0x58635FA9;
            testB->unknown_0E = false;

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

