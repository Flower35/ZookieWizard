#ifndef H_WAVEFRONTOBJ_EXPORTER
#define H_WAVEFRONTOBJ_EXPORTER

#include <ZookieWizard/ZookieWizard.h>
#include <kao2ar/kao2ar.h>

namespace ZookieWizard
{
    class eObject;
    class eGroup;
    class eTriMesh;
    class eMaterial;

    ////////////////////////////////////////////////////////////////
    // WAVEFRONT OBJ Exporter class
    ////////////////////////////////////////////////////////////////

    class WavefrontObjExporter
    {
        /*** Properties ***/

        protected:

            int totalVertices;
            int totalNormals;
            int totalMappings;

            int materialsCount;
            int materialsMaxLength;
            eMaterial** materials;

            FileOperator myFiles[2];
            eString fileName;
            eString workingDirectory;

            eGroup* meshGroup;
            eTriMesh* meshTrimesh;


        /*** Methods ***/

        public:

            WavefrontObjExporter();
            ~WavefrontObjExporter();

            bool openObj(eString filename, eObject* target);
            bool openMtl();

            void begin();

        protected:

            void writeNewLine(int32_t which_file);

            bool writeMaterialInfo(eTriMesh* current_trimesh, bool file_opened);
            void writeModelData(eTriMesh* current_trimesh, eMatrix4x4 &parent_matrix);

            bool writeMaterialInfoFromGroup(eGroup* current_group, bool file_opened);
            void writeModelDataFromGroup(eGroup* current_group, eMatrix4x4 &parent_matrix);

            void writeFace(int32_t params, int32_t index[3]);
    };

}

#endif
