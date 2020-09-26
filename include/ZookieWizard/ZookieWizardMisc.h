#ifndef H_ZOOKIEWIZARD_MISC
#define H_ZOOKIEWIZARD_MISC

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // miscellaneous
    ////////////////////////////////////////////////////////////////

    class Archive;
    class DenisLevelMap;

    /*** Variables ***/

        static const int MAX_OPEN_ARCHIVES = 5;
        extern int currentArId;
        extern Archive myARs[MAX_OPEN_ARCHIVES];

        static const int MAX_OPEN_DENISLEVELS = 1;
        extern int currentDenisLevelId;
        extern DenisLevelMap myDenisLevels[MAX_OPEN_DENISLEVELS];

        extern OPENFILENAME ofn;

        extern int currentGameVersion;
        extern char mediaDirectory[LARGE_BUFFER_SIZE];
        extern char denisDirectory[LARGE_BUFFER_SIZE];
        extern char denisLevelName[LARGE_BUFFER_SIZE];

    /*** Functions ***/

        void loadEditorSettings();
        void saveEditorSettings();

        const char* getEditorString(int32_t id, bool silent);

        void setGameVersion(int32_t engine_version);

        bool checkArFilenameExtensions(const char* name, int32_t length);

        void ArMenuOptions_OpenOrSaveAr(int32_t mode);
        void ArMenuOptions_CloseAr();
        void ArMenuOptions_GenerateEmptyScene();
        void ArMenuOptions_ExportScripts();
        void ArMenuOptions_ExportProxies();
        void ArMenuOptions_BulkArchiveConverter();
        void ArMenuOptions_WriteStructureToTextFile();
        void ArMenuOptions_ExportArToCollada();
        void ArMenuOptions_ExportTrimeshToObj();
        void ArMenuOptions_ImportTrimeshFromObj();
        void ArMenuOptions_ChangeNodesWithTxt();

        void DenisMenuOptions_OpenDenisLevel();
        void DenisMenuOptions_ConvertDenisLevel();
}

#endif
