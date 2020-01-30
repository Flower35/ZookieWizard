#ifndef H_COLLADA_EXPORTER
#define H_COLLADA_EXPORTER

#include <ZookieWizard/ZookieWizard.h>
#include <kao2ar/kao2ar.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // COLLADA Exporter definitions
    ////////////////////////////////////////////////////////////////

    #define COLLADA_EXPORTER_STATE_LIGHTS 1
    #define COLLADA_EXPORTER_STATE_CAMERAS 2
    #define COLLADA_EXPORTER_STATE_IMAGES 3
    #define COLLADA_EXPORTER_STATE_EFFECTS 4
    #define COLLADA_EXPORTER_STATE_MATERIALS 5
    #define COLLADA_EXPORTER_STATE_GEOMETRIES 6
    #define COLLADA_EXPORTER_STATE_CONTROLLERS 7
    #define COLLADA_EXPORTER_STATE_ANIMATIONS 8
    #define COLLADA_EXPORTER_STATE_VISUAL_SCENES 9
    #define COLLADA_EXPORTER_STATE_SCENE 10

    #define COLLADA_EXPORTER_OBJ_SCENE 1
    #define COLLADA_EXPORTER_OBJ_NODE 2
    #define COLLADA_EXPORTER_OBJ_EFFECT 3
    #define COLLADA_EXPORTER_OBJ_IMAGE 4
    #define COLLADA_EXPORTER_OBJ_MATERIAL 5
    #define COLLADA_EXPORTER_OBJ_GEOMETRY 6
    #define COLLADA_EXPORTER_OBJ_ARMATURE 7

    struct ColladaExporterTag
    {
        int32_t state;
        eString name;
    };

    struct ColladaExporterObjRef
    {
        int32_t id;
        int32_t type;
        void* pointer;
    };


    ////////////////////////////////////////////////////////////////
    // COLLADA Exporter class
    ////////////////////////////////////////////////////////////////

    class ColladaExporter
    {
        /*** Properties ***/

        protected:

            FileOperator myFile;
            eString workingDirectory;

            int32_t state;
            int32_t indentation;

            int32_t tagsCount;
            int32_t tagsMaxLength;
            ColladaExporterTag* tags;

            int32_t objRefsCount;
            int32_t objRefsMaxLength;
            ColladaExporterObjRef* objRefs;

        /*** Methods ***/

        public:

            ColladaExporter();
            ~ColladaExporter();

            void openXml(eString filename);
            bool continueExporting();

            void openTag(eString name);
            void insertTagAttrib(eString name, eString value);
            void writeInsideTag(eString text);
            void closeTag();

            int32_t getState();
            int32_t getObjectRefId(int32_t type, void* pointer, bool can_be_created);
            bool objectRefAlreadyExists(int32_t type, void* pointer);

            eString getWorkingDirectory();

        protected:

            void writeNewLine();
            void writeIndentation();

    };

}

#endif
