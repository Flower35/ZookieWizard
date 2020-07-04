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

        static const int MAX_OPEN_ARCHIVES = 2;
        extern int archivesInUse;
        extern Archive myARs[MAX_OPEN_ARCHIVES];

        static const int MAX_OPEN_DENISLEVELS = 1;
        extern int denisLevelsInUse;
        extern DenisLevelMap myDenisLevels[MAX_OPEN_DENISLEVELS];

        extern OPENFILENAME ofn;

        extern int currentGameVersion;
        extern char currentWorkingDirectory[256];
        extern char denisDirectory[256];
        extern char denisLevelName[256];

    /*** Functions ***/

        void openOrSaveAr(int);
        void setGameVersion(int);
        void writeArStructureToTextFile();
        void bulkArchiveConverter();

        void openDenisLevel();
        void convertDenisLevel();

        void generateEmptyScene();

        void exportArToCollada();
        void exportTrimeshToObj();
        void importTrimeshFromObj();
        void importNodesFromTxt();
        void changeNodesWithTxt();
}

#endif
