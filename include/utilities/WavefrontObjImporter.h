#ifndef H_WAVEFRONTOBJ_IMPORTER
#define H_WAVEFRONTOBJ_IMPORTER

#include <ZookieWizard/ZookieWizard.h>
#include <ElephantBase/kao2ar.h>

namespace ZookieWizard
{
    class eGroup;
    class eMaterial;

    ////////////////////////////////////////////////////////////////
    // WAVEFRONT OBJ Importer structures
    ////////////////////////////////////////////////////////////////

    struct WavefrontObjImporterVertex
    {
        /*** Properties ***/

        public:

            float x;
            float y;
            float z;
            float r;
            float g;
            float b;

        /*** Methods ***/

        public:

            WavefrontObjImporterVertex();

            bool operator == (const WavefrontObjImporterVertex&) const;

            void applyMatrix(eMatrix4x4 &model_matrix);
    };

    struct WavefrontObjImporterFace
    {
        /*** Properties ***/

        public:

            int32_t material_id;
            int32_t group_id;
            int32_t v_id[3];
            int32_t vt_id[3];
            int32_t vn_id[3];

        /*** Methods ***/

        public:

            WavefrontObjImporterFace();

            bool matchesSetting(const int32_t g_id, const int32_t m_id) const;
    };

    struct WavefrontObjImporterMaterial
    {
        /*** Properties ***/

        public:

            eString name;
            eMaterial* material;

        /*** Methods ***/

        public:

            WavefrontObjImporterMaterial();
            ~WavefrontObjImporterMaterial();

            WavefrontObjImporterMaterial& operator = (const WavefrontObjImporterMaterial &other);
    };


    ////////////////////////////////////////////////////////////////
    // WAVEFRONT OBJ Importer class
    ////////////////////////////////////////////////////////////////

    #define WAVEFRONT_OBJ_IMPORTER_DEFAULT_FLAGS 0x07

    class WavefrontObjImporter
    {
        /*** Properties ***/

        protected:

            FileOperator myFiles[2];
            eString fileName;
            eString workingDirectory;

            eGroup* parentGroup;
            eSRP appliedTransform;
            bool appendNameToMeshes;
            bool regroupMeshesWithMaterials;
            bool makeMaterialsTwoSided;

            WavefrontObjImporterVertex* objVertices;
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

            int32_t importedVertices;
            int32_t importedMeshes;

        /*** Methods ***/

        public:

            WavefrontObjImporter();
            ~WavefrontObjImporter();

            void begin(eString obj_fullpath, eGroup* target, int32_t flags, eSRP &srp);

        protected:

            bool openObj(eString filename);
            bool openMtl(eString filename);

            void appendVertices(WavefrontObjImporterVertex* element, int32_t slots);
            void appendMapping(ePoint2* element, int32_t slots);
            void appendNormals(ePoint3* element, int32_t slots);
            void appendFaces(WavefrontObjImporterFace* element, int32_t slots);
            void appendMaterials(WavefrontObjImporterMaterial* element, int32_t slots);
            void appendGroups(eString* element, int32_t slots);

            void readModelData();
            void readMaterialInfo(eString filename);
            void constructTriMeshes();

            bool groupHasMultipleMaterials(const int32_t g_id) const;
    };

}

#endif
