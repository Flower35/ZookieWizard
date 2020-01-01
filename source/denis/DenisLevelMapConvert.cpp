#include <denis/DenisLevelMap.h>

#include <denis/DenisLevelTexture.h>
#include <denis/DenisLevelSample.h>
#include <denis/DenisLevelWObj.h>
#include <denis/DenisLevelObject.h>
#include <denis/DenisLevelMaxObj.h>
#include <denis/DenisLevelZone.h>
#include <denis/DenisLevelBillboard.h>
#include <denis/DenisLevelBonus.h>

#include <kao2engine/eScene.h>
#include <kao2engine/eMaterial.h>
#include <kao2engine/eEnvironment.h>
#include <kao2engine/eProxy.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // Level Map: convert from Kao1 to Kao2
    ////////////////////////////////////////////////////////////////

    eScene* DenisLevelMap::convertToKao2(DenisFileOperator &file)
    {
        int32_t i, j;
        eString test_str;
        eString current_name;

        std::time_t current_time;
        std::tm time_info;
        char time_bufor[32];
        
        eScene* result_scene = nullptr;
        eEnvironment* global_env = nullptr;
        eCollisionMgr* test_collision = nullptr;
        eProxy* test_proxy = nullptr;

        eSRP test_srp;

        /********************************/
        /* Get current time and date */

        std::time(&current_time);
        localtime_s(&time_info, &current_time);

        std::strftime(time_bufor, 32, "%c", &time_info);

        /********************************/
        /* Load and prepare textures */

        createMaterialsList(file);

        /********************************/
        /* Load and prepare WOBJ references */

        for (i = 0; i < worldObjectsCount; i++)
        {
            worldObjects[i].loadMesh(file);
        }

        /********************************/
        /* Create new scene and new environment */

        result_scene = new eScene();
        result_scene->setFlags(0x70071000);

        global_env = new eEnvironment("global_env");
        global_env->setFlags(0x70000000);

        test_collision = result_scene->getCollisionManager();

        /********************************/
        /* Set scene name and creation details */

        current_name = getName();

        test_str = "$root of ";
        test_str += current_name;

        result_scene->setName(test_str);

        test_str = "converted with ZookieWizard at ";
        test_str += time_bufor;
        test_str += "\r\n";

        result_scene->setCompileStrings(test_str, current_name);

        result_scene->setBackgroundColor(GUI::backgroundColor);

        /********************************/
        /* Will be useful after figuring out how "eALBox" works */

        ArFunctions::setCurrentScene(result_scene);

        /********************************/
        /* Add environment (and update its parent) */

        result_scene->appendChild(global_env);

        /********************************/
        /* Add one collision entry (REQUIRED BY KAO2 ENGINE) */

        test_collision->insertNewItem_seriesA(0);

        /********************************/
        /* Convert static meshes */

        for (i = 0; i < objectsCount[DENIS_LEVEL_OBJECT_TYPE_STATIC]; i++)
        {
            objects[DENIS_LEVEL_OBJECT_TYPE_STATIC][i].convertToKao2
            (
                DENIS_LEVEL_OBJECT_TYPE_STATIC,
                i,
                global_env,
                texturesCount,
                materialsList
            );
        }

        /********************************/
        /* Delete unused textures */

        deleteMaterialsList();

        /********************************/
        /* Convert geo proxies */

        for (i = 0; i < proxiesCount; i++)
        {
            j = proxies[i].index;

            if ((j >= 0) && (j < worldObjectsCount))
            {
                proxies[i].convertToKao2
                (
                    i,
                    global_env,
                    worldObjects[j]
                );
            }
        }

        /********************************/
        /* Add power-ups */

        for (i = 0; i < bonusesCount; i++)
        {
            bonuses[i].convertToKao2(i, global_env);
        }

        /********************************/
        /* Add Kao's starting place */

        test_srp.pos.x = kaoPos[0];
        test_srp.pos.y = kaoPos[2];
        test_srp.pos.z = kaoPos[1] + 100.0f;

        test_srp.rot.fromEulerAngles
        (
            true,
            ((-kaoRot[2]) & 0x0000FFFF) / float(0x8000) * float(M_PI),
            ((-kaoRot[0]) & 0x0000FFFF) / float(0x8000) * float(M_PI),
            ((-kaoRot[1]) & 0x0000FFFF) / float(0x8000) * float(M_PI)
        );

        test_proxy = new eProxy();
        test_proxy->setName("kao01");
        test_proxy->setTargetName("");
        test_proxy->setCategory(1);
        test_proxy->setXForm(test_srp);

        global_env->appendChild(test_proxy);

        /********************************/
        /* Finish! */

        return result_scene;
    }

}
