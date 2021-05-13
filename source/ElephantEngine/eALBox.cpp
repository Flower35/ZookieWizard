#include <ElephantEngine/eALBox.h>
#include <ElephantBase/Archive.h>

#include <ElephantEngine/eScene.h>

#include <ElephantEngine/eObserver.h>
#include <ElephantEngine/Actor.h>
#include <ElephantEngine/eGroundTest.h>
#include <ElephantEngine/eNPCMap.h>
#include <ElephantEngine/eRain.h>

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

    TypeInfo* eALBox::getType() const
    {
        return &E_ALBOX_TYPEINFO;
    }

    eALBox::eALBox()
    : eRefCounter()
    {
        clearNewALBox();
    }

    eALBox::~eALBox()
    {
        eScene* test_scene;
        eCollisionMgr* test_manager;

        if (nullptr != myScene)
        {
            function_004A9870();
        }

        if (unknown_8C >= 0x02)
        {
            test_scene = ArFunctions::getCurrentScene();
            test_manager = test_scene->getCollisionManager();

            test_manager->save_ALBox(collisionEntryId, nullptr);
        }

        if (nullptr != series)
        {
            delete[](series);
        }
    }


    ////////////////////////////////////////////////////////////////
    // eALBox: cloning the object
    ////////////////////////////////////////////////////////////////

    void eALBox::createFromOtherObject(const eALBox &other)
    {
        throw ErrorMessage
        (
            "CRITICAL ERROR while cloning the \"eALBox\" object:\n" \
            "cloning << axis list boxes >> without context is not supported!!!"
        );
    }

    eALBox::eALBox(const eALBox &other)
    : eRefCounter(other)
    {
        clearNewALBox();

        createFromOtherObject(other);
    }

    eALBox& eALBox::operator = (const eALBox &other)
    {
        if ((&other) != this)
        {
            eRefCounter::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eALBox::cloneFromMe() const
    {
        return new eALBox(*this);
    }


    ////////////////////////////////////////////////////////////////
    // eALBox: serialization
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

        /* [0x08] Link to a local "eScene" (that contains "eCollisionMgr") */
        ar.serialize((eObject**)&myScene, &E_SCENE_TYPEINFO);

        /* [0x0C] "eBoxZone" or "eTriMesh" link */
        ar.serialize((eObject**)&parentNode, &E_NODE_TYPEINFO);

        /* ASSERTIONS */

        if (!ar.assertLastSerializedNode(parentNode))
        {
            throw ErrorMessage
            (
                "eALBox::serialize():\n" \
                "incorrect Node linked to this AxisListBox!"
            );
        }

        if (!ar.compareWithMyRoot(myScene))
        {
            throw ErrorMessage
            (
                "eALBox::serialize():\n" \
                "scene link is not set!\n" \
                "([%s] \"%s\")",
                parentNode->getType()->name,
                parentNode->getDebugName().getText()
            );
        }

        /* set [0x8C] (unknown) */

        if (isParentNodeInteractive())
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

        /* [0x7C] entry ID from "eCollisionMgr" boxes collection */
        ar.readOrWrite(&collisionEntryId, 0x04);

        /* [0x10] [0x30] [0x50] :: <kao2.004BDE00> :: (2x) <kao2.004BAEF0> */
        for (i = 0; i < 3; i++)
        {
            axis_list[i][0].serialize(ar);
            axis_list[i][1].serialize(ar);
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
            if (nullptr != myScene)
            {
                test_manager = myScene->getCollisionManager();

                test_manager->save_ALBox(collisionEntryId, this);
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eALBox: get ID that represents position within "eCollisionMgr"
    ////////////////////////////////////////////////////////////////
    int32_t eALBox::getCollisionId() const
    {
        return collisionEntryId;
    }


    //////////////////////////////////////////////////////
    // eALBox: return a pointer to one of the AxisLists
    ////////////////////////////////////////////////////////////////
    AxisList* eALBox::getAxisList(int32_t row, int32_t column) const
    {
        if (nullptr == this)
        {
            throw ErrorMessage
            (
                "eALBox::getAxisList():\r\n" \
                "non-existing collision entry found!"
            );
        }

        if ((row >= 0) && (row < 3) && (column >= 0) && (column < 2))
        {
            return (AxisList*)&(axis_list[row][column]);
        }

        return nullptr;
    }


    ////////////////////////////////////////////////////////////////
    // eALBox: get Series pointer (required for Collision Manager)
    ////////////////////////////////////////////////////////////////
    uint8_t* eALBox::getSeriesPointer() const
    {
        return series;
    }


    ////////////////////////////////////////////////////////////////
    // eALBox: create axis list entry
    // <kao2.004AABC0>
    ////////////////////////////////////////////////////////////////
    void eALBox::createAxisListEntry(eNode* parent, float* boxBound)
    {
        int32_t i;

        if (nullptr != parent)
        {
            parent->setAxisListBox(this);
        }

        parentNode = parent;
        myScene = nullptr;

        if (unknown_8C < 2)
        {
            /* set [0x8C] (unknown) */

            if (isParentNodeInteractive())
            {
                unknown_8C = 0x01;
            }
            else
            {
                unknown_8C = 0x00;
            }
        }

        /* Update coords sub-structures */

        for (i = 0; i < 3; i++)
        {
            axis_list[i][0].coordLimit = boxBound[0 + i];
            axis_list[i][0].rowId = i;
            axis_list[i][0].columnId = 0x00;

            axis_list[i][1].coordLimit = boxBound[3 + i];
            axis_list[i][1].rowId = i;
            axis_list[i][1].columnId = 0x01;
        }

        if (0x02 != unknown_8C)
        {
            function_004A9CC0();
        }
        else
        {
            function_004A99C0();
        }
    }


    ////////////////////////////////////////////////////////////////
    // eALBox: ???
    // <kao2.004A9F40>
    ////////////////////////////////////////////////////////////////
    void eALBox::function_004A9F40(eALBox* other, uint8_t row_id)
    {
        int32_t otherCollisionId, id;
        uint8_t a, b, c;

        otherCollisionId = other->getCollisionId();
        c = otherCollisionId & 0x01;
        id = otherCollisionId / 2;

        a = (series[id] >> c) & 0x55;
        b = (0x01 << (2 * row_id + 0x02)) ^ a;

        series[id] &= (0xAA << c);
        series[id] |= (b << c);

        b &= 0x54;
        if (0x54 == b)
        {
            function_004AA560(other);
            other->function_004AA560(this);
        }

        a &= 0x54;
        if ((0x54 == a) && (b != a))
        {
            function_004AA750(other);
            other->function_004AA750(this);

            function_004A9FF0(other->parentNode, 0x00);
        }
    }


    ////////////////////////////////////////////////////////////////
    // eALBox: check if parent node is "interactive"
    // <kao2.004AAB60>
    ////////////////////////////////////////////////////////////////
    bool eALBox::isParentNodeInteractive() const
    {
        TypeInfo* info;

        if (nullptr != parentNode)
        {
            info = parentNode->getType();

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
    // eALBox: ???
    // <kao2.004A9830>
    ////////////////////////////////////////////////////////////////
    uint8_t eALBox::function_004A9830(eALBox* other) const
    {
        uint8_t result = 0x00;
        uint8_t* test_series;
        int32_t otherCollisionId = other->getCollisionId();

        if (otherCollisionId > collisionEntryId)
        {
            test_series = other->getSeriesPointer();

            result = test_series[collisionEntryId / 2];

            result = (result >> (collisionEntryId & 0x01)) & 0x55;
        }
        else
        {
            result = series[otherCollisionId / 2];

            result = (result >> (otherCollisionId & 0x01)) & 0x55;
        }

        return result;
    }


    ////////////////////////////////////////////////////////////////
    // eALBox: ???
    // <kao2.004A9870>
    ////////////////////////////////////////////////////////////////
    void eALBox::function_004A9870()
    {
        int32_t i;
        int32_t num_boxes;
        eALBox** boxes;
        eCollisionMgr* test_manager;

        /* [0x08] scene link */
        if (nullptr != myScene)
        {
            test_manager = myScene->getCollisionManager();

            num_boxes = test_manager->get_ALBoxes_array_size();
            boxes = test_manager->get_ALBoxes_array();

            for (i = 0; i < num_boxes; i++)
            {
                if ((nullptr != boxes[i]) && (this != boxes[i]))
                {
                    if (0x54 == (0x54 & function_004A9830(boxes[i])))
                    {
                        function_004AA750(boxes[i]);

                        if (nullptr != boxes[i])
                        {
                            boxes[i]->function_004AA750(this);
                        }
                    }
                }
            }

            test_manager = myScene->getCollisionManager();
            test_manager->function_004994E0(collisionEntryId);
        }
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

        collisionEntryId = test_manager->function_004993D0(test);

        /* [0x70] Generate series */

        if (nullptr != series)
        {
            delete[](series);
            series = nullptr;

            seriesCount = 0;
            seriesMaxLength = 0;
        }

        seriesMaxLength = (collisionEntryId + 1) / 2;

        series = new uint8_t [seriesMaxLength];

        for (i = 0; i < seriesMaxLength; i++)
        {
            series[i] = 0x00;

            seriesCount = (i+1);
        }

        /* Copy eALBox reference to Collision Manager */

        test_scene = ArFunctions::getCurrentScene();
        test_manager = test_scene->getCollisionManager();

        test_manager->save_ALBox(collisionEntryId, this);
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
            axis_list[i][1].alboxEntryId = collisionEntryId;
            axis_list[i][0].alboxEntryId = collisionEntryId;
        }

        /* (...) */

        test_manager = myScene->getCollisionManager();

        test_manager->function_00499390(axis_list);
    }


    ////////////////////////////////////////////////////////////////
    // eALBox: update global scene's collision manager
    // <kao2.004A9CC0>
    ////////////////////////////////////////////////////////////////
    void eALBox::function_004A9CC0()
    {
        if (nullptr == myScene)
        {
            myScene = ArFunctions::getCurrentScene();

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
    // <kao2.004A9FF0>
    ////////////////////////////////////////////////////////////////
    void eALBox::function_004A9FF0(eNode* arg1, int8_t arg2) const
    {
        eALBox* other = arg1->getAxisListBox();
        int32_t otherCollisionId = other->getCollisionId();

        if (nullptr == other)
        {
            /* (--dsp--) <kao2.004AA020> */
        }

        if (0x00 != (arg2 ^ function_004AA4F0(other)))
        {
            if ((-1) != arg2)
            {
                if (collisionEntryId > otherCollisionId)
                {
                    if (0x00 != arg2)
                    {
                        series[arg2 / 2] |= (0x01 << (otherCollisionId & 0x01));

                        /* eRefMsg("touch") */
                    }
                    else
                    {
                        series[arg2 / 2] &= (0xFE << (otherCollisionId & 0x01));

                        /* eRefMsg("untouch") */
                    }
                }
                else
                {
                    /* (--dsp--) <kao2.004AA4A8> */
                }
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eALBox: ???
    // <kao2.004AA4F0>
    ////////////////////////////////////////////////////////////////
    uint8_t eALBox::function_004AA4F0(eALBox* other) const
    {
        uint8_t a = 0x00;
        uint8_t* test_series;
        int32_t otherCollisionId = other->getCollisionId();

        if (collisionEntryId > otherCollisionId)
        {
            a = series[otherCollisionId / 2];

            a = (a >> (otherCollisionId & 0x01)) & 0x01;
        }
        else
        {
            test_series = other->getSeriesPointer();

            a = test_series[collisionEntryId / 2];

            a = (a >> (collisionEntryId & 0x01)) & 0x01;
        }

        return a;
    }


    ////////////////////////////////////////////////////////////////
    // eALBox: ???
    // <kao2.004AA540>
    ////////////////////////////////////////////////////////////////
    bool eALBox::function_004AA540(eALBox* other) const
    {
        if (0 == unknown_8C)
        {
            return false;
        }

        return (unknown_8C != (other->unknown_8C));
    }


    ////////////////////////////////////////////////////////////////
    // [[vptr]+0x24] eALBox: ???
    // <kao2.004AA560>
    ////////////////////////////////////////////////////////////////
    void eALBox::function_004AA560(eALBox* other)
    {
        int32_t i;

        if (function_004AA540(other))
        {
            for (i = 1; i < unknown_80.getSize(); i++)
            {
                if ((other->parentNode) == unknown_80.getIthChild(i))
                {
                    /* (--dsp--) "begin overlap" */

                    return;
                }
            }

            unknown_80.appendChild(other->parentNode);
        }
    }


    ////////////////////////////////////////////////////////////////
    // [[vptr]+0x28] eALBox: ???
    // <kao2.004AA750>
    ////////////////////////////////////////////////////////////////
    void eALBox::function_004AA750(eALBox* other)
    {
        int32_t i;

        if (function_004AA540(other))
        {
            for (i = 0; i < unknown_80.getSize(); i++)
            {
                if ((other->parentNode) == unknown_80.getIthChild(i))
                {
                    unknown_80.deleteIthChild(i);

                    return;
                }
            }

            /* (--dsp--) "collider not found" */
        }
    }


    ////////////////////////////////////////////////////////////////
    // eALBox: clear this object
    ////////////////////////////////////////////////////////////////
    void eALBox::clearNewALBox()
    {
        /*[0x08]*/ myScene = nullptr;
        /*[0x0C]*/ parentNode = nullptr;

        /* [0x10] Automatic constructors */

        /*[0x70]*/ seriesCount = 0;
        /*[0x74]*/ seriesMaxLength = 0;
        /*[0x78]*/ series = nullptr;

        /*[0x8C]*/ unknown_8C = 0;

        /*[0x7C]*/ collisionEntryId = (-1);
    }

}
