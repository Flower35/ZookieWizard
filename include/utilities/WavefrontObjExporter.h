#ifndef H_WAVEFRONTOBJ_EXPORTER
#define H_WAVEFRONTOBJ_EXPORTER

#include <ZookieWizard/ZookieWizard.h>
#include <kao2ar/kao2ar.h>

namespace ZookieWizard
{
    class eTriMesh;

    ////////////////////////////////////////////////////////////////
    // WAVEFRONT OBJ Exporter class
    ////////////////////////////////////////////////////////////////

    class WavefrontObjExporter
    {
        /*** Properties ***/

        protected:

            FileOperator myFiles[2];
            eString fileName;
            eString workingDirectory;
            eTriMesh* trimesh;


        /*** Methods ***/

        public:

            WavefrontObjExporter();
            ~WavefrontObjExporter();

            bool openObj(eString filename, eTriMesh* target);
            bool openMtl();

            void begin();

        protected:

            void writeNewLine(int32_t which_file);

            bool writeMaterialInfo();
            void writeModelData(bool uses_mtl);

            void writeFace(int32_t params, int32_t index[3]);
    };

}

#endif
