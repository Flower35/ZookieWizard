#include <kao2engine/eScene.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eScene interface
    // <kao2.004984D0> (constructor)
    // <kao2.00498860> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_SCENE_TYPEINFO
    (
        E_SCENE_ID,
        "eScene",
        &E_PIVOT_TYPEINFO,
        []() -> eObject*
        {
            return new eScene;
        }
    );

    TypeInfo* eScene::getType()
    {
        return &E_SCENE_TYPEINFO;
    }

    eScene::eScene()
    : ePivot()
    {
        /*[0x0170]*/ color[0] = 0.5f;
        /*[0x0174]*/ color[1] = 0.5f;
        /*[0x0178]*/ color[2] = 0.5f;

        /*[0x017C]*/ ambient[0] = 0.0f;
        /*[0x0180]*/ ambient[1] = 0.0f;
        /*[0x0184]*/ ambient[2] = 0.0f;
        /*[0x0188]*/ ambient[3] = 0.0f;

        /*(kao3)[0x02AC]*/ visSetA_count = 0;
        /*(kao3)[0x02B0]*/ visSetA_maxLength = 0;
        /*(kao3)[0x02B4]*/ visSetA = nullptr;

        /*(kao3)[0x02B8]*/ visSetB_count = 0;
        /*(kao3)[0x02BC]*/ visSetB_maxLength = 0;
        /*(kao3)[0x02C0]*/ visSetB = nullptr;

        ArFunctions::setCurrentScene(this);

        /*[0x14]*/ name = "Scene Root";
    }

    eScene::~eScene()
    {
        function_00498B20();

        if (this != ArFunctions::getCurrentScene())
        {
            ArFunctions::setCurrentScene(this);
        }

        if (nullptr != visSetA)
        {
            delete[](visSetA);
        }

        if (nullptr != visSetB)
        {
            delete[](visSetB);
        }
    }


    ////////////////////////////////////////////////////////////////
    // eScene portal structures
    // <kao_tw.004BF0E0> (first struct, contsructor)
    // <kao_tw.004BF500> (first struct, serialization)
    // <kao_tw.00486C79> (second struct, constructor)
    // <kao_tw.004BFA80> (second struct, serialization)
    ////////////////////////////////////////////////////////////////

    void ScenePortalBaseA::serialize(Archive &ar)
    {
        ar.readOrWrite(&unknown_00, 0x01);
        ar.readOrWrite(&unknown_01, 0x01);
        ar.readOrWrite(&unknown_02, 0x01);

        unknown_04.serialize(ar);
        unknown_10.serialize(ar);

        if (0x02 & unknown_02)
        {
            unknown_1C.serialize(ar);
        }

        ar.serializeString(unknown_28);
    }

    ScenePortalBaseB::ScenePortalBaseB()
    {
        /*[0x00]*/ unknown_00 = 0;

        /*[0x08]*/ groupA_count = 0;
        /*[0x0C]*/ groupA_maxLength = 0;
        /*[0x10]*/ groupA = nullptr;

        /*[0x14]*/ groupB_count = 0;
        /*[0x18]*/ groupB_maxLength = 0;
        /*[0x1C]*/ groupB = nullptr;
    }

    ScenePortalBaseB::~ScenePortalBaseB()
    {
        if (nullptr != groupA)
        {
            delete[](groupA);
        }

        if (nullptr != groupB)
        {
            delete[](groupB);
        }
    }

    void ScenePortalBaseB::serialize(Archive &ar)
    {
        int32_t i;

        /* [0x04] portal name */
        ar.serializeString(name);

        /* [0x08] group (4 floats) */

        if (ar.isInReadMode())
        {
            if (nullptr != groupA)
            {
                delete[](groupA);
                groupA = nullptr;

                groupA_maxLength = 0;
                groupA_count = 0;
            }

            ar.readOrWrite(&groupA_maxLength, 0x04);

            groupA = new ePoint4 [groupA_maxLength];

            for (i = 0; i < groupA_maxLength; i++)
            {
                groupA[i].serialize(ar);

                groupA_count = (i+1);
            }
        }
        else
        {
            ar.readOrWrite(&groupA_count, 0x04);

            for (i = 0; i < groupA_count; i++)
            {
                groupA[i].serialize(ar);
            }
        }

        /* [0x14] group (bytes) */

        if (ar.isInReadMode())
        {
            if (nullptr != groupB)
            {
                delete[](groupB);
                groupB = nullptr;

                groupB_maxLength = 0;
                groupB_count = 0;
            }

            ar.readOrWrite(&groupB_maxLength, 0x04);

            groupB = new uint8_t [groupB_maxLength];

            ar.readOrWrite(groupB, groupB_maxLength);

            groupB_count = groupB_maxLength;
        }
        else
        {
            ar.readOrWrite(&groupB_count, 0x04);

            ar.readOrWrite(groupB, groupB_count);
        }

        /* [0x00] unknown */

        if (ar.getVersion() >= 0x8E)
        {
            ar.readOrWrite(&unknown_00, 0x04);
        }
    }


    ////////////////////////////////////////////////////////////////
    // 
    // <kao2.00498B20>
    ////////////////////////////////////////////////////////////////
    void eScene::function_00498B20()
    {
        int32_t i;

        for (i = 0; i < nodes.getSize(); i++)
        {
            //// (--dsp--) eScene::[[vptr]+0x74](arg1 = nodes.getChild[i]);
        }

        collision.reset();
    }


    ////////////////////////////////////////////////////////////////
    // eScene serialization
    // <kao2.00498FB0>
    ////////////////////////////////////////////////////////////////
    void eScene::serialize(Archive &ar)
    {
        int32_t i;

        /* "ar_compile" string, level name */
        ar.serializeString(compileStrB);

        /* "ar_compile" string, ".COMPILED." */
        ar.serializeString(compileStrA);

        if (ar.isInReadMode())
        {
            function_00498B20();
        }

        /* Collision Manager */
        collision.serialize(ar);

        /* Pivot */
        ePivot::serialize(ar);

        if (ar.isInReadMode())
        {
            collision.prepare_ALBox_links();

            //// (--dsp--) call eScene::[[vptr]+0x44], two times.
        }

        /* [0x0170] Scene background colors */
        ar.readOrWrite(&(color[0]), 0x04);
        ar.readOrWrite(&(color[1]), 0x04);
        ar.readOrWrite(&(color[2]), 0x04);

        /* Unknown group */
        unknown0194.serialize(ar, &E_PIVOT_TYPEINFO);

        /* [0x017C] Ambient intensity */
        if (ar.getVersion() < 0x73)
        {
            ambient[0] = 0;
            ambient[1] = 0;
            ambient[2] = 0;
            ambient[3] = 1.0f;
        }
        else
        {
            ar.readOrWrite(&(ambient[0]), 0x04);
            ar.readOrWrite(&(ambient[1]), 0x04);
            ar.readOrWrite(&(ambient[2]), 0x04);
            ar.readOrWrite(&(ambient[3]), 0x04);
        }

        if (ar.getVersion() >= 0x8C)
        {
            ar.readOrWrite(&visGroups_unknown, 0x01);

            visGroups.serialize(ar, &E_NODE_TYPEINFO);

            i = visGroups.getSize();

            if (i > 512)
            {
                throw ErrorMessage
                (
                    "eScene::serialize():\n" \
                    "Too many visibility nodes/groups - %i. (max 512).",
                    i
                );
            }
        }

        if (ar.getVersion() >= 0x8D)
        {
            /* Portals 1*/

            if (ar.isInReadMode())
            {
                if (nullptr != visSetA)
                {
                    delete[](visSetA);
                    visSetA = nullptr;

                    visSetA_maxLength = 0;
                    visSetA_count = 0;
                }

                ar.readOrWrite(&visSetA_maxLength, 0x04);

                if (visSetA_maxLength > 0)
                {
                    visSetA = new ScenePortalBaseA [visSetA_maxLength];

                    for (i = 0; i < visSetA_maxLength; i++)
                    {
                        visSetA[i].serialize(ar);

                        visSetA_count = (i+1);
                    }
                }
            }
            else
            {
                ar.readOrWrite(&visSetA_count, 0x04);

                for (i = 0; i < visSetA_count; i++)
                {
                    visSetA[i].serialize(ar);
                }
            }

            /* Portals 2 */

            if (ar.isInReadMode())
            {
                if (nullptr != visSetB)
                {
                    delete[](visSetB);
                    visSetB = nullptr;

                    visSetB_maxLength = 0;
                    visSetB_count = 0;
                }

                ar.readOrWrite(&visSetB_maxLength, 0x04);

                if (visSetB_maxLength > 0)
                {
                    visSetB = new ScenePortalBaseB [visSetB_maxLength];

                    for (i = 0; i < visSetB_maxLength; i++)
                    {
                        visSetB[i].serialize(ar);

                        visSetB_count = (i+1);
                    }
                }
            }
            else
            {
                ar.readOrWrite(&visSetB_count, 0x04);

                for (i = 0; i < visSetB_count; i++)
                {
                    visSetB[i].serialize(ar);
                }
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eScene: set background color
    ////////////////////////////////////////////////////////////////
    void eScene::setBackgroundColor(GLfloat new_color[3])
    {
        color[0] = new_color[0];
        color[1] = new_color[1];
        color[2] = new_color[2];
    }


    ////////////////////////////////////////////////////////////////
    // eScene: set compile strings (while creating new level)
    ////////////////////////////////////////////////////////////////
    void eScene::setCompileStrings(eString str_a, eString str_b)
    {
        compileStrA = str_a;
        compileStrB = str_b;
    }


    ////////////////////////////////////////////////////////////////
    // eScene: get collision manager
    ////////////////////////////////////////////////////////////////
    eCollisionMgr* eScene::getCollisionManager()
    {
        return &collision;
    }


    ////////////////////////////////////////////////////////////////
    // Global Scene pointer
    ////////////////////////////////////////////////////////////////

    eScene* theScene;

    void ArFunctions::setCurrentScene(eScene* scene)
    {
        theScene = scene;
    }

    eScene* ArFunctions::getCurrentScene()
    {
        return theScene;
    }

}
