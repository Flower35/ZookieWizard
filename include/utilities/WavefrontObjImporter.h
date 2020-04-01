#ifndef H_WAVEFRONTOBJ_IMPORTER
#define H_WAVEFRONTOBJ_IMPORTER

#include <ZookieWizard/ZookieWizard.h>
#include <kao2ar/kao2ar.h>

namespace ZookieWizard
{
    class eGroup;
    class eMaterial;

    ////////////////////////////////////////////////////////////////
    // WAVEFRONT OBJ Importer structures
    ////////////////////////////////////////////////////////////////

    struct WavefrontObjImporterFace
    {
        int32_t material_id;
        int32_t group_id;
        int32_t v_id[3];
        int32_t vt_id[3];
        int32_t vn_id[3];

        WavefrontObjImporterFace();

        bool matchesSetting(const int32_t g_id, const int32_t m_id) const;
    };

    struct WavefrontObjImporterMaterial
    {
        eString name;
        eMaterial* material;

        WavefrontObjImporterMaterial();
        ~WavefrontObjImporterMaterial();
    };


    ////////////////////////////////////////////////////////////////
    // WAVEFRONT OBJ Importer class
    ////////////////////////////////////////////////////////////////

    class WavefrontObjImporter
    {
        /*** Properties ***/

        protected:

            FileOperator myFiles[2];
            eString fileName;
            eString workingDirectory;

            eGroup* parentGroup;

            ePoint3* objVertices;
            int32_t objVerticesCount;
            int32_t objVerticesMaxLength;

            ePoint2* objMapping;
            int32_t objMappingCount;
            int32_t objMappingMaxLength;

            ePoint3* objNormals;
            int32_t objNormalsCount;
            int32_t objNormalsMaxLength;

            WavefrontObjImporterFace* objFaces;
            int32_t objFacesCount;
            int32_t objFacesMaxLength;

            WavefrontObjImporterMaterial* objMaterials;
            int32_t objMaterialsCount;
            int32_t objMaterialsMaxLength;

            eString* objGroups;
            int32_t objGroupsCount;
            int32_t objGroupsMaxLength;

            uint16_t* referencedVertices;

        /*** Methods ***/

        public:

            WavefrontObjImporter();
            ~WavefrontObjImporter();

            bool openObj(eString filename, eGroup* target);
            bool openMtl(eString filename);

            void begin();

        protected:

            void appendVertices(ePoint3* element, int32_t slots);
            void appendMapping(ePoint2* element, int32_t slots);
            void appendNormals(ePoint3* element, int32_t slots);
            void appendFaces(WavefrontObjImporterFace* element, int32_t slots);
            void appendMaterials(WavefrontObjImporterMaterial* element, int32_t slots);
            void appendGroups(eString* element, int32_t slots);

            void readModelData();
            void readMaterialInfo(eString filename);
            void checkForAlreadyExistingMaterials();
            void constructTriMeshes();

            bool groupHasMultipleMaterials(const int32_t g_id) const;
    };

}

#endif
