#include <kao2engine/eALBox.h>
#include <kao2ar/Archive.h>

#include <kao2engine/eScene.h>

#include <kao2engine/eObserver.h>
#include <kao2engine/Actor.h>
#include <kao2engine/eGroundTest.h>
#include <kao2engine/eNPCMap.h>
#include <kao2engine/eRain.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eALBox interface
    // <kao2.004A94E0> (constructor)
    // <kao2.004A9740> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_ALBOX_TYPEINFO
    (
        E_ALBOX_ID,
        "eALBox",
        &E_REFCOUNTER_TYPEINFO,
        []() -> eObject*
        {
            return new eALBox;
        }
    );

    TypeInfo* eALBox::getType()
    {
        return &E_ALBOX_TYPEINFO;
    }

    eALBox::eALBox()
    : eRefCounter()
    {
        /*[0x08]*/ unknown_08 = nullptr;
        /*[0x0C]*/ unknown_0C = nullptr;

        /* [0x10] Automatic constructors */

        /*[0x70]*/ seriesCount = 0;
        /*[0x74]*/ seriesMaxLength = 0;
        /*[0x78]*/ series = nullptr;

        /*[0x8C]*/ unknown_8C = 0;

        /*[0x7C]*/ unknown_7C = (-1);
    }

    eALBox::~eALBox()
    {
        eScene* test_scene;
        eCollisionMgr* test_manager;

        if (nullptr != unknown_08)
        {
            function_004A9870();
        }

        if (unknown_8C >= 0x02)
        {
            test_scene = ArFunctions::getCurrentScene();
            test_manager = test_scene->getCollisionManager();

            test_manager->save_ALBox(unknown_7C, nullptr);
        }

        if (nullptr != series)
        {
            delete[](series);
        }

        /* [0x10] Automatic destructors */
    }


    ////////////////////////////////////////////////////////////////
    // eALBox: check link type
    // <kao2.004AAB60>
    ////////////////////////////////////////////////////////////////
    bool eALBox::function_004AAB60()
    {
        TypeInfo* info;

        if (nullptr != unknown_0C)
        {
            info = unknown_0C->getType();

            if (info->checkHierarchy(&E_OBSERVER_TYPEINFO))
            {
                return true;
            }

            if (info->checkHierarchy(&E_ACTOR_TYPEINFO))
            {
                return true;
            }

            if (E_GROUNDTEST_ID == info->id)
            {
                return true;
            }

            if (E_NPCMAP_ID == info->id)
            {
                return true;
            }

            if (E_RAIN_ID == info->id)
            {
                return true;
            }
        }

        return false;
    }


    ////////////////////////////////////////////////////////////////
    // eALBox: update global scene's collision manager
    // <kao2.004A9CC0>
    ////////////////////////////////////////////////////////////////
    void eALBox::function_004A9CC0()
    {
        if (nullptr == unknown_08)
        {
            unknown_08 = ArFunctions::getCurrentScene();

            if (0x02 == unknown_8C)
            {
                //// (--dsp--) <kao2.004A9A90>
            }
            else
            {
                function_004A9C80();
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eALBox: ???
    // <kao2.004A9C80>
    ////////////////////////////////////////////////////////////////
    void eALBox::function_004A9C80()
    {
        int32_t i;

        eCollisionMgr* test_manager;

        /* connecting with Collision Manager */

        function_004A99C0();

        /* updating sub-structures */

        for (i = 0; i < 3; i++)
        {
            test[i][1].unknown_0C = unknown_7C;
            test[i][0].unknown_0C = unknown_7C;
        }

        /* */

        test_manager = unknown_08->getCollisionManager();

        test_manager->function_00499390(test);
    }


    ////////////////////////////////////////////////////////////////
    // eALBox: ???
    // <kao2.004A99C0>
    ////////////////////////////////////////////////////////////////
    void eALBox::function_004A99C0()
    {
        int32_t i;
        int8_t test;

        eScene* test_scene;
        eCollisionMgr* test_manager;

        switch (unknown_8C)
        {
            case 0x02:
            case 0x03:
            {
                test = 0x01;

                break;
            }

            default:
            {
                test = 0x00;
            }
        }

        test_scene = ArFunctions::getCurrentScene();
        test_manager = test_scene->getCollisionManager();

        unknown_7C = test_manager->function_004993D0(test);

        /* [0x70] Generate series */

        if (nullptr != series)
        {
            delete[](series);
            series = nullptr;

            seriesCount = 0;
            seriesMaxLength = 0;
        }
        
        seriesMaxLength = (unknown_7C + 1) / 2;

        series = new uint8_t [seriesMaxLength];

        for (i = 0; i < seriesMaxLength; i++)
        {
            series[i] = 0x00;

            seriesCount = (i+1);
        }

        /* Copy eALBox reference to Collision Manager */

        test_scene = ArFunctions::getCurrentScene();
        test_manager = test_scene->getCollisionManager();

        test_manager->save_ALBox(unknown_7C, this);
    }


    ////////////////////////////////////////////////////////////////
    // 
    // <kao2.004A9870>
    ////////////////////////////////////////////////////////////////
    void eALBox::function_004A9870()
    {
        int32_t i;
        int32_t num_boxes;
        eALBox** boxes;
        eCollisionMgr* test_manager;

        /* [0x08] scene link */
        if (nullptr != unknown_08)
        {
            test_manager = unknown_08->getCollisionManager();

            num_boxes = test_manager->get_ALBoxes_array_size();
            boxes = test_manager->get_ALBoxes_array();

            for (i = 0; i < num_boxes; i++)
            {
                if ((this != boxes[i]) && (nullptr != boxes[i]))
                {
                    //// (--dsp--) to nie jest a¿ tak wa¿ne, jak funkcja poni¿ej...
                }
            }

            test_manager = unknown_08->getCollisionManager();
            test_manager->function_004994E0(unknown_7C);
        }
    }


    ////////////////////////////////////////////////////////////////
    // eALBox serialization
    // <kao2.004AA940>
    ////////////////////////////////////////////////////////////////
    void eALBox::serialize(Archive &ar)
    {
        int32_t i;

        eCollisionMgr* test_manager;

        if (ar.getVersion() < 0x87)
        {
            throw ErrorMessage
            (
                "eALBox::serialize():\n" \
                "ar.version() 135 required!"
            );
        }

        /* [0x08] parent scene link? */
        ar.serialize((eObject**)&unknown_08, &E_SCENE_TYPEINFO);

        /* [0x0C] "eBoxZone" or "eTriMesh" link */
        ar.serialize((eObject**)&unknown_0C, &E_NODE_TYPEINFO);

        /* set [0x8C] (unknown) */

        if (function_004AAB60())
        {
            unknown_8C = 0x01;
        }
        else
        {
            unknown_8C = 0x00;
        }

        /* dummy */
        i = 0;
        ar.readOrWrite(&i, 0x04);

        /* [0x7C] unknown */
        ar.readOrWrite(&unknown_7C, 0x04);

        /* [0x10] [0x30] [0x50] :: <kao2.004BDE00> :: (2x) <kao2.004BAEF0> */
        for (i = 0; i < 3; i++)
        {
            test[i][0].serialize(ar);
            test[i][1].serialize(ar);
        }

        /* [0x70] unknown bytes group */
        
        ar.readOrWrite(&seriesCount, 0x04);
        
        if (ar.isInReadMode())
        {
            seriesMaxLength = seriesCount;

            if (nullptr != series)
            {
                delete[](series);
            }

            series = new uint8_t [seriesMaxLength];
        }

        if (nullptr != series)
        {
            ar.readOrWrite(series, seriesCount);
        }

        /* [0x80] unknown group ("eTriMesh" or "eBoxZone") */
        
        unknown_80.serialize(ar, &E_NODE_TYPEINFO);

        /* Store copy in Scene's Collision Manager! */

        if (ar.isInReadMode())
        {
            if (nullptr != unknown_08)
            {
                test_manager = unknown_08->getCollisionManager();

                test_manager->save_ALBox(unknown_7C, this);
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eALBox: return a pointer to one of the AxisLists
    ////////////////////////////////////////////////////////////////
    AxisList* eALBox::getAxisList(int32_t row, int32_t column)
    {
        if ((row >= 0) && (row < 3) && (column >= 0) && (column < 2))
        {
            return &(test[row][column]);
        }
        
        return nullptr;
    }


    ////////////////////////////////////////////////////////////////
    // eALBox: get Series pointer (required for Collision Manager)
    ////////////////////////////////////////////////////////////////
    uint8_t* eALBox::getSeriesPointer()
    {
        return series;
    }

}
