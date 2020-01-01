#include <denis/DenisLevelMap.h>

#include <denis/DenisLevelTexture.h>
#include <denis/DenisLevelSample.h>
#include <denis/DenisLevelWObj.h>
#include <denis/DenisLevelObject.h>
#include <denis/DenisLevelMaxObj.h>
#include <denis/DenisLevelZone.h>
#include <denis/DenisLevelBillboard.h>
#include <denis/DenisLevelBonus.h>

#include <kao2engine/eMaterial.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // Level Map: constructor
    ////////////////////////////////////////////////////////////////

    DenisLevelMap::DenisLevelMap()
    {
        DenisLevelMap("level.01");
    }

    DenisLevelMap::DenisLevelMap(eString new_name)
    {
        int32_t i;

        levelName = new_name;

        texturesCount = 0;
        texturesMaxLength = 0;
        textures = nullptr;

        ambientSamplesCount = 0;
        ambientSamplesMaxLength = 0;
        ambientSamples = nullptr;

        worldObjectsCount = 0;
        worldObjectsMaxLength = 0;
        worldObjects = nullptr;

        for (i = 0; i < DENIS_LEVEL_OBJECT_TYPES; i++)
        {
            objectsCount[DENIS_LEVEL_OBJECT_ID[i]] = 0;
            objectsMaxLength[DENIS_LEVEL_OBJECT_ID[i]] = 0;
            objects[DENIS_LEVEL_OBJECT_ID[i]] = nullptr;
        }

        proxiesCount = 0;
        proxiesMaxLength = 0;
        proxies = nullptr;

        eventZonesCount = 0;
        eventZonesMaxLength = 0;
        eventZones = nullptr;

        billboardsCount = 0;
        billboardsMaxLength = 0;
        billboards = nullptr;

        bonusesCount = 0;
        bonusesMaxLength = 0;
        bonuses = nullptr;

        materialsList = nullptr;

        for (i = 0; i < 3; i++)
        {
            kaoPos[i] = 0;
            kaoRot[i] = 0;
        }
    }
    

    ////////////////////////////////////////////////////////////////
    // Level Map: destructor
    ////////////////////////////////////////////////////////////////

    DenisLevelMap::~DenisLevelMap()
    {
        destroy();
    }

    void DenisLevelMap::destroy()
    {
        int32_t i;

        if (nullptr != textures)
        {
            delete[](textures);
            textures = nullptr;
        }
        texturesCount = 0;
        texturesMaxLength = 0;

        if (nullptr != ambientSamples)
        {
            delete[](ambientSamples);
            ambientSamples = nullptr;
        }
        ambientSamplesCount = 0;
        ambientSamplesMaxLength = 0;

        if (nullptr != worldObjects)
        {
            delete[](worldObjects);
            worldObjects = nullptr;
        }
        worldObjectsCount = 0;
        worldObjectsMaxLength = 0;

        for (i = 0; i < DENIS_LEVEL_OBJECT_TYPES; i++)
        {
            if (nullptr != objects[DENIS_LEVEL_OBJECT_ID[i]])
            {
                delete[](objects[DENIS_LEVEL_OBJECT_ID[i]]);
                objects[DENIS_LEVEL_OBJECT_ID[i]] = nullptr;
            }

            objectsCount[DENIS_LEVEL_OBJECT_ID[i]] = 0;
            objectsMaxLength[DENIS_LEVEL_OBJECT_ID[i]] = 0;
        }

        if (nullptr != proxies)
        {
            delete[](proxies);
            proxies = nullptr;
        }
        proxiesCount = 0;
        proxiesMaxLength = 0;

        if (nullptr != eventZones)
        {
            delete[](eventZones);
            eventZones = nullptr;
        }
        eventZonesCount = 0;
        eventZonesMaxLength = 0;

        if (nullptr != billboards)
        {
            delete[](billboards);
            billboards = nullptr;
        }
        billboardsCount = 0;
        billboardsMaxLength = 0;

        if (nullptr != bonuses)
        {
            delete[](bonuses);
            bonuses = nullptr;
        }
        bonusesCount = 0;
        bonusesMaxLength = 0;

        deleteMaterialsList();
    }


    ////////////////////////////////////////////////////////////////
    // Level Map: create materials lists
    ////////////////////////////////////////////////////////////////

    void DenisLevelMap::createMaterialsList(DenisFileOperator &file)
    {
        int32_t i, j;

        deleteMaterialsList();

        materialsList = new eMaterial* [4 * texturesCount];

        for (i = 0; i < texturesCount; i++)
        {
            for (j = 0; j < 4; j++)
            {
                materialsList[4 * i + j] = nullptr;
            }

            textures[i].convertToKao2(file, &(materialsList[4 * i]));
        }
    }


    ////////////////////////////////////////////////////////////////
    // Level Map: delete materials list
    ////////////////////////////////////////////////////////////////

    void DenisLevelMap::deleteMaterialsList()
    {
        int32_t i;

        if (nullptr != materialsList)
        {
            for (i = 0; i < (4 * texturesCount); i++)
            {
                if (nullptr != materialsList[i])
                {
                    materialsList[i]->decRef();
                }
            }

            delete[](materialsList);
            materialsList = nullptr;
        }
    }


    ////////////////////////////////////////////////////////////////
    // Level Map: serialization
    ////////////////////////////////////////////////////////////////

    void DenisLevelMap::openAndSerialize(DenisFileOperator &file)
    {
        int32_t i, j;

        eString test_str = "world/";
        test_str += levelName;
        test_str += "/map-win.bin";

        if (!file.open(test_str))
        {
            throw ErrorMessage
            (
                "Could not open file: \n" \
                "\"%s\"",
                file.fileName.getText()
            );
        }

        /********************************/
        /* Main Map magic */

        i = *(int32_t*)"T8LM";

        file.readOrWrite(&i, 0x04);

        if (file.isInReadMode())
        {
            if (*(int32_t*)"T8LM" != i)
            {
                throw ErrorMessage
                (
                    "\"%s\": invalid main map magic.",
                    file.fileName.getText()
                );
            }
        }

        /********************************/
        /* File version */

        i = 70;
        
        file.readOrWrite(&i, 0x04);

        if (file.isInReadMode())
        {
            if (70 != i)
            {
                throw ErrorMessage
                (
                    "\"%s\": wrong file version.\n" \
                    "(got %i, expected %i)",
                    file.fileName.getText(),
                    i, 70
                );
            }
        }

        /********************************/
        /* Texture names */
        
        i = *(int32_t*)"TEXN";

        file.readOrWrite(&i, 0x04);

        if (file.isInReadMode())
        {
            if (*(int32_t*)"TEXN" != i)
            {
                throw ErrorMessage
                (
                    "\"%s\": invalid texture names magic.",
                    file.fileName.getText()
                );
            }
        }

        if (file.isInReadMode())
        {
            if (nullptr != textures)
            {
                delete[](textures);
                texturesMaxLength = 0;
                texturesCount = 0;
            }

            file.readOrWrite(&texturesMaxLength, 0x04);

            textures = new DenisLevelTexture [texturesMaxLength];

            for (i = 0; i < texturesMaxLength; i++)
            {
                textures[i].serialize(file);

                texturesCount = (i + 1);
            }
        }
        else
        {
            file.readOrWrite(&texturesCount, 0x04);

            for (i = 0; i < texturesCount; i++)
            {
                textures[i].serialize(file);
            }
        }

        /********************************/
        /* Ambient samples */
        
        i = *(int32_t*)"smpl";

        file.readOrWrite(&i, 0x04);

        if (file.isInReadMode())
        {
            if (*(int32_t*)"smpl" != i)
            {
                throw ErrorMessage
                (
                    "\"%s\": invalid samples magic.",
                    file.fileName.getText()
                );
            }
        }

        if (file.isInReadMode())
        {
            if (nullptr != ambientSamples)
            {
                delete[](ambientSamples);
                ambientSamplesMaxLength = 0;
                ambientSamplesCount = 0;
            }

            file.readOrWrite(&ambientSamplesMaxLength, 0x04);

            ambientSamples = new DenisLevelSample [ambientSamplesMaxLength];

            for (i = 0; i < ambientSamplesMaxLength; i++)
            {
                ambientSamples[i].serialize(file);

                ambientSamplesCount = (i + 1);
            }
        }
        else
        {
            file.readOrWrite(&ambientSamplesCount, 0x04);

            for (i = 0; i < ambientSamplesCount; i++)
            {
                ambientSamples[i].serialize(file);
            }
        }

        /********************************/
        /* World Objects magic */
        
        i = *(int32_t*)"WOBJ";

        file.readOrWrite(&i, 0x04);

        if (file.isInReadMode())
        {
            if (*(int32_t*)"WOBJ" != i)
            {
                throw ErrorMessage
                (
                    "\"%s\": invalid WOBJ magic.",
                    file.fileName.getText()
                );
            }
        }

        /********************************/
        /* Objects serialization */

        if (file.isInReadMode())
        {
            if (nullptr != worldObjects)
            {
                delete[](worldObjects);
                worldObjectsMaxLength = 0;
                worldObjectsCount = 0;
            }

            for (i = 0; i < DENIS_LEVEL_OBJECT_TYPES; i++)
            {
                if (nullptr != objects[DENIS_LEVEL_OBJECT_ID[i]])
                {
                    delete[](objects[DENIS_LEVEL_OBJECT_ID[i]]);
                    objectsMaxLength[DENIS_LEVEL_OBJECT_ID[i]] = 0;
                    objectsCount[DENIS_LEVEL_OBJECT_ID[i]] = 0;
                }
            }

            if (nullptr != proxies)
            {
                delete[](proxies);
                proxiesMaxLength = 0;
                proxiesCount = 0;
            }

            /* Read number of each objects group [5 numbers] */

            file.readOrWrite(&worldObjectsMaxLength, 0x04);

            for (i = 0; i < DENIS_LEVEL_OBJECT_TYPES; i++)
            {
                file.readOrWrite(&(objectsMaxLength[DENIS_LEVEL_OBJECT_ID[i]]), 0x04);
            }
            
            file.readOrWrite(&proxiesMaxLength, 0x04);

            /* Allocate size and load objects */

            worldObjects = new DenisLevelWObj [worldObjectsMaxLength];

            for (i = 0; i < worldObjectsMaxLength; i++)
            {
                worldObjects[i].serialize(file);

                worldObjectsCount = (i + 1);
            }

            for (i = 0; i < DENIS_LEVEL_OBJECT_TYPES; i++)
            {
                objects[DENIS_LEVEL_OBJECT_ID[i]] = new DenisLevelObject [objectsMaxLength[DENIS_LEVEL_OBJECT_ID[i]]];

                for (j = 0; j < objectsMaxLength[DENIS_LEVEL_OBJECT_ID[i]]; j++)
                {
                    objects[DENIS_LEVEL_OBJECT_ID[i]][j].serialize(file, DENIS_LEVEL_OBJECT_ID[i]);

                    objectsCount[DENIS_LEVEL_OBJECT_ID[i]] = (j + 1);
                }
            }
            
            proxies = new DenisLevelMaxObj [proxiesMaxLength];

            for (i = 0; i < proxiesMaxLength; i++)
            {
                proxies[i].serialize(file, worldObjects, worldObjectsCount);

                proxiesCount = (i + 1);
            }
        }
        else
        {
            /* Write number of each objects group [5 numbers] */

            file.readOrWrite(&worldObjectsCount, 0x04);

            for (i = 0; i < DENIS_LEVEL_OBJECT_TYPES; i++)
            {
                file.readOrWrite(&(objectsCount[DENIS_LEVEL_OBJECT_ID[i]]), 0x04);
            }
            
            file.readOrWrite(&proxiesCount, 0x04);

            /* Save objects */

            for (i = 0; i < worldObjectsCount; i++)
            {
                worldObjects[i].serialize(file);
            }

            for (i = 0; i < DENIS_LEVEL_OBJECT_TYPES; i++)
            {
                for (j = 0; j < objectsCount[DENIS_LEVEL_OBJECT_ID[i]]; j++)
                {
                    objects[DENIS_LEVEL_OBJECT_ID[i]][j].serialize(file, DENIS_LEVEL_OBJECT_ID[i]);
                }
            }

            for (i = 0; i < proxiesCount; i++)
            {
                proxies[i].serialize(file, worldObjects, worldObjectsCount);
            }
        }

        /********************************/
        /* Moving lights */
        
        i = *(int32_t*)"LGHT";

        file.readOrWrite(&i, 0x04);

        if (file.isInReadMode())
        {
            if (*(int32_t*)"LGHT" != i)
            {
                throw ErrorMessage
                (
                    "\"%s\": invalid wlight magic.",
                    file.fileName.getText()
                );
            }
        }

        i = 0;

        for (j = 0; j < 4; j++)
        {
            file.readOrWrite(&i, 0x04);

            if (file.isInReadMode())
            {
                if (0 != i)
                {
                    throw ErrorMessage
                    (
                        "\"%s\": non-empty lights section is not supported.",
                        file.fileName.getText()
                    );
                }
            }
        }

        /********************************/
        /* Event zones */
        
        i = *(int32_t*)"EVNZ";

        file.readOrWrite(&i, 0x04);

        if (file.isInReadMode())
        {
            if (*(int32_t*)"EVNZ" != i)
            {
                throw ErrorMessage
                (
                    "\"%s\": invalid event zones magic.",
                    file.fileName.getText()
                );
            }
        }

        if (file.isInReadMode())
        {
            if (nullptr != eventZones)
            {
                delete[](eventZones);
                eventZonesMaxLength = 0;
                eventZonesCount = 0;
            }

            file.readOrWrite(&eventZonesMaxLength, 0x04);

            eventZones = new DenisLevelZone [eventZonesMaxLength];

            for (i = 0; i < eventZonesMaxLength; i++)
            {
                eventZones[i].serialize(file);

                eventZonesCount = (i + 1);
            }
        }
        else
        {
            file.readOrWrite(&eventZonesCount, 0x04);

            for (i = 0; i < eventZonesCount; i++)
            {
                eventZones[i].serialize(file);
            }
        }

        /********************************/
        /* Billboards */
        
        i = *(int32_t*)"bb2d";

        file.readOrWrite(&i, 0x04);

        if (file.isInReadMode())
        {
            if (*(int32_t*)"bb2d" != i)
            {
                throw ErrorMessage
                (
                    "\"%s\": invalid billboards magic.",
                    file.fileName.getText()
                );
            }
        }

        if (file.isInReadMode())
        {
            if (nullptr != billboards)
            {
                delete[](billboards);
                billboardsMaxLength = 0;
                billboardsCount = 0;
            }

            file.readOrWrite(&billboardsMaxLength, 0x04);

            billboards = new DenisLevelBillboard [billboardsMaxLength];

            for (i = 0; i < billboardsMaxLength; i++)
            {
                billboards[i].serialize(file);

                billboardsCount = (i + 1);
            }
        }
        else
        {
            file.readOrWrite(&billboardsCount, 0x04);

            for (i = 0; i < billboardsCount; i++)
            {
                billboards[i].serialize(file);
            }
        }
        
        /********************************/
        /* Bonuses */
        
        i = *(int32_t*)"bns!";

        file.readOrWrite(&i, 0x04);

        if (file.isInReadMode())
        {
            if (*(int32_t*)"bns!" != i)
            {
                throw ErrorMessage
                (
                    "\"%s\": invalid bonuses magic.",
                    file.fileName.getText()
                );
            }
        }

        if (file.isInReadMode())
        {
            if (nullptr != bonuses)
            {
                delete[](bonuses);
                bonusesMaxLength = 0;
                bonusesCount = 0;
            }

            file.readOrWrite(&bonusesMaxLength, 0x04);

            bonuses = new DenisLevelBonus [bonusesMaxLength];

            for (i = 0; i < bonusesMaxLength; i++)
            {
                bonuses[i].serialize(file);

                bonusesCount = (i + 1);
            }
        }
        else
        {
            file.readOrWrite(&bonusesCount, 0x04);

            for (i = 0; i < bonusesCount; i++)
            {
                bonuses[i].serialize(file);
            }
        }

        /********************************/
        /* Finish magic */

        i = *(int32_t*)"FINI";

        file.readOrWrite(&i, 0x04);

        if (file.isInReadMode())
        {
            if (*(int32_t*)"FINI" != i)
            {
                throw ErrorMessage
                (
                    "\"%s\": invalid finish magic.",
                    file.fileName.getText()
                );
            }
        }

        file.close();

        /********************************/
        /* Denis starting position */

        test_str = "world/";
        test_str += levelName;
        test_str += "/savegame.bin";

        if (!file.open(test_str))
        {
            throw ErrorMessage
            (
                "Could not open file: \n" \
                "\"%s\"",
                file.fileName.getText()
            );
        }

        file.readOrWrite(&(kaoPos[0]), 0x04);
        file.readOrWrite(&(kaoPos[1]), 0x04);
        file.readOrWrite(&(kaoPos[2]), 0x04);
        file.readOrWrite(&(kaoRot[0]), 0x02);
        file.readOrWrite(&(kaoRot[1]), 0x02);
        file.readOrWrite(&(kaoRot[2]), 0x02);

        file.close();

        /********************************/
        /* Denis Map reading complete! :) */
    }


    ////////////////////////////////////////////////////////////////
    // Level Map: get level name
    ////////////////////////////////////////////////////////////////

    eString DenisLevelMap::getName()
    {
        int32_t i;
        char* test_text;
        int32_t test_length;

        /* Create new instance, not a copy! */
        eString result = levelName.getText();

        test_text = result.getText();
        test_length = result.getLength();

        for (i = 0; i < test_length; i++)
        {
            switch (test_text[i])
            {
                case '.':
                {
                    test_text[i] = '_';

                    break;
                }
            }
        }

        return result;
    }

}
