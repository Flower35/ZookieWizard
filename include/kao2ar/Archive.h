#ifndef H_KAO2AR_ARCHIVE
#define H_KAO2AR_ARCHIVE

#include <kao2ar/kao2ar.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // KAO2 OBJECT REFERENCES
    ////////////////////////////////////////////////////////////////

    struct TypeInfo;

    class eObject;
    class eRefCounter;
    class eScene;


    ////////////////////////////////////////////////////////////////
    // KAO2 ARCHIVE CLASS
    ////////////////////////////////////////////////////////////////

    #define AR_MODE_READ (1 << 0)
    #define AR_MODE_WRITE (1 << 1)
    #define AR_MODE_EXPORT_SCRIPTS (1 << 2)
    #define AR_MODE_EXPORT_PROXIES (1 << 3)
    #define AR_MODE_DEBUG (1 << 4)
    #define AR_MODE_ABSOLUTE_PATH (1 << 5)
    #define AR_MODE_XREF_PATH (1 << 6)

    #define AR_MAX_ITEMS 65536
    #define AR_MAX_TEMPSTR 128

    #define AR_ITEM_TYPE_OBJECT 0x00
    #define AR_ITEM_TYPE_STRING 0x01
    #define AR_ITEM_TYPE_OTHER 0x02

    class Archive
    {
        /*** Properties ***/

        private:
        
            /*[0x00]*/ int32_t modeFlags;
            /*[0x04]*/ FileOperator myFile;

            /*[0x14]*/ int32_t version;

            /*[0x1C]*/ int32_t tempItemsCount;
            /*[0x20]*/ int32_t tempItemsMaxLength;
            /*[0x24]*/ void** tempItemsList;
            
            /* Custom features */

            uint8_t* tempItemsTypes;

            int32_t tempStrCount;
            eStringBase<char>** tempStrList;

            eRefCounter* parentObject;
            eObject* selectedObject;

            eString mediaDirectory;

            int32_t engineOpenedWith;
            int32_t engineSavedWith;

        /*** Methods ***/
        
        private:

            eString getFullArchivePath(eString filename, int32_t current_engine);

            void deleteTempStrPtrs();

        public:

            Archive();
            Archive(eString new_media_dir);
            ~Archive();
            Archive& operator = (const Archive &newAr);

            bool open(eString filename, int32_t mode, int32_t engine_version);
            void close(bool hide);

            /* State determining */

            bool isInReadMode();
            bool isInWriteMode();
            bool isInExportScriptsMode();
            bool isInExportProxiesMode();
            bool isInDebugMode();

            /* Serialization (reading/writing archives) */

            int32_t getVersion();
            bool checkGameEngine(int32_t opened, int32_t saved);
            int32_t getCurrentEngineVersion();
            void readOrWrite(void* pointer, int size);

            bool addItem(void* item, int type);
            void* getItem(int id, int type);
            int findItem(void* item);
            bool addTempStr(eStringBase<char>* str);

            void serialize(eObject** o, TypeInfo* t);
            void serializeString(eString &s);
            void replaceStringDuringSerialization(eString &oldStr, eString newStr);

            void checkTypeInfo(TypeInfo** t);

            /* Other */

            eString getMediaDir();
            void setMediaDir(eString new_media_dir);

            void renderScene(float time, int32_t draw_flags);

            void copySceneFromMe(eScene** target);
            void setMyParentScene(eScene* pointer);

            void writeStructureToTextFile();
    };

}

#endif
