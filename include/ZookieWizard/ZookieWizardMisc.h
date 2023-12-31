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

        static const int ARCHIVE_VERSION_MIN = 0x67;
        static const int ARCHIVE_VERSION_MAX = 0xB1;
        extern int currentArchiveVersion;

        extern char mediaDirectory[LARGE_BUFFER_SIZE];
        extern char denisDirectory[LARGE_BUFFER_SIZE];
        extern char denisLevelName[LARGE_BUFFER_SIZE];

    /*** Functions ***/

        void loadEditorSettings();
        void saveEditorSettings();

        const char* getEditorString(int32_t id, bool silent);

        void setMaxArchiveVersion(int32_t ar_version);

        bool checkArFilenameExtensions(const char* name, int32_t length);

        void ArMenuOptions_OpenOrSaveAr(const char* auto_path, int32_t mode);
        void ArMenuOptions_CloseAr(bool automatic);
        void ArMenuOptions_GenerateEmptyScene(bool automatic);
        void ArMenuOptions_ExportScripts();
        void ArMenuOptions_ExportProxies();
        void ArMenuOptions_ReloadProxies();
        void ArMenuOptions_BulkArchiveConverter();
        void ArMenuOptions_WriteTreeToJsonFile();
        void ArMenuOptions_ExportArToCollada();
        void ArMenuOptions_ExportTrimeshToObj();
        void ArMenuOptions_ImportTrimeshFromObj();
        void ArMenuOptions_UpdateVerticesFromObj();
        void ArMenuOptions_AddEnvMapFromObj();
        void ArMenuOptions_ChangeNodesWithTxt();

        void DenisMenuOptions_OpenDenisLevel();
        void DenisMenuOptions_ConvertDenisLevel();
}

#endif
