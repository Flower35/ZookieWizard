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

            eString getFullArchivePath(eString filename, int32_t current_engine) const;

            void deleteTempStrPtrs();

            void changeGlobalScene() const;

        public:

            Archive();
            Archive(eString new_media_dir);
            ~Archive();
            Archive& operator = (const Archive &newAr);

            bool open(eString filename, int32_t mode, int32_t engine_version);
            void close(bool hide);

            /* State determining */

            bool isInReadMode() const;
            bool isInWriteMode() const;
            bool isInExportScriptsMode() const;
            bool isInExportProxiesMode() const;
            bool isInDebugMode() const;

            /* Serialization (reading/writing archives) */

            int32_t getVersion() const;
            bool checkGameEngine(int32_t opened, int32_t saved) const;
            int32_t getCurrentEngineVersion() const;
            void readOrWrite(void* pointer, int size);

            bool addItem(void* item, int type);
            void* getItem(int id, int type) const;
            int findItem(void* item) const;
            bool addTempStr(eStringBase<char>* str);

            void serialize(eObject** o, TypeInfo* t);
            void serializeString(eString &s);
            void replaceStringDuringSerialization(eString &oldStr, eString newStr);

            void checkTypeInfo(TypeInfo** t);

            /* Other */

            eString getMediaDir() const;
            void setMediaDir(eString new_media_dir);

            void renderScene(int32_t draw_flags) const;
            void changeSelectedObject(int32_t child_id);

            void copySceneFromMe(eScene** target) const;
            void setMyParentScene(eScene* pointer);

            void writeStructureToTextFile() const;
            void writeStructureToXmlFile(eString filename) const;
            void writeSelectedObjectToObjFile(eString filename) const;
            void appendToSelectedObjectFromObjFile(eString filename);
    };

}

#endif
