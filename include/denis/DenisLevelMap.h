#ifndef H_DENIS_LEVEL_MAP
#define H_DENIS_LEVEL_MAP

#include <denis/Denis.h>

namespace ZookieWizard
{
    struct DenisLevelTexture;
    struct DenisLevelSample;
    struct DenisLevelWObj;
    struct DenisLevelObject;
    struct DenisLevelMaxObj;
    struct DenisLevelZone;
    struct DenisLevelBillboard;
    struct DenisLevelBonus;

    class eScene;
    class eMaterial;

    ////////////////////////////////////////////////////////////////
    // Kao the Kangaroo: Level Map interface
    ////////////////////////////////////////////////////////////////

    class DenisLevelMap
    {
        /*** Properties ***/

       protected:

            eString levelName;

            int32_t texturesCount;
            int32_t texturesMaxLength;
            DenisLevelTexture* textures;

            int32_t ambientSamplesCount;
            int32_t ambientSamplesMaxLength;
            DenisLevelSample* ambientSamples;

            int32_t worldObjectsCount;
            int32_t worldObjectsMaxLength;
            DenisLevelWObj* worldObjects;

            int32_t objectsCount[DENIS_LEVEL_OBJECT_TYPES];
            int32_t objectsMaxLength[DENIS_LEVEL_OBJECT_TYPES];
            DenisLevelObject* objects[DENIS_LEVEL_OBJECT_TYPES];

            int32_t proxiesCount;
            int32_t proxiesMaxLength;
            DenisLevelMaxObj* proxies;

            int32_t eventZonesCount;
            int32_t eventZonesMaxLength;
            DenisLevelZone* eventZones;

            int32_t billboardsCount;
            int32_t billboardsMaxLength;
            DenisLevelBillboard* billboards;

            int32_t bonusesCount;
            int32_t bonusesMaxLength;
            DenisLevelBonus* bonuses;

            /* External things */

            eMaterial** materialsList;

            float kaoPos[3];
            uint16_t kaoRot[3];

        /*** Methods ***/

        public:

            DenisLevelMap();
            DenisLevelMap(eString new_name);
            ~DenisLevelMap();

            void serialize(DenisFileOperator &file);
            void destroy();

            eString getName();

            void createMaterialsList(DenisFileOperator &file);
            void deleteMaterialsList();
            eScene* convertToKao2(DenisFileOperator &file);
    };

}

#endif
