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
    #define AR_MAX_TEMPSTR 192

    #define AR_ITEM_TYPE_OBJECT 0x00
    #define AR_ITEM_TYPE_STRING 0x01
    #define AR_ITEM_TYPE_OTHER 0x02

    #define NODES_LISTBOX_SET_MARKED_CHILD (-1)
    #define NODES_LISTBOX_UPDATE_CURRENT (-2)
    #define NODES_LISTBOX_PARENT (-3)
    #define NODES_LISTBOX_ROOT (-4)
    #define NODES_LISTBOX_MOVE_UP (-5)
    #define NODES_LISTBOX_MOVE_DOWN (-6)
    #define NODES_LISTBOX_MOVE_OUT (-7)
    #define NODES_LISTBOX_MOVE_IN (-8)
    #define NODES_LISTBOX_CENTER_CAMERA (-9)
    #define NODES_LISTBOX_DELETE_CURRENT (-10)
    #define NODES_LISTBOX_DELETE_CHILDREN (-11)
    #define NODES_LISTBOX_DELETE_SELECTED (-12)
    #define NODES_LISTBOX_COLLISION_REBUILD (-13)
    #define NODES_LISTBOX_COLLISION_CLEAR (-14)
    #define NODES_EDITING_SET_FLAG (-15)
    #define NODES_EDITING_UNSET_FLAG (-16)
    #define NODES_EDITING_CHANGE_NAME (-17)
    #define NODES_EDITING_CHANGE_TYPE (-18)
    #define NODES_EDITING_INSERT (-19)
    #define NODES_EDITING_RESET_TRANSFORM (-20)
    #define NODES_EDITING_APPLY_TRANSFORM (-21)

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
            int32_t markedChildId;

            eString mediaDirectory;

            int32_t engineOpenedWith;
            int32_t engineSavedWith;

            bool isLoadedAsProxy;

        /*** Methods ***/

        private:

            eString getFullArchivePath(eString filename, int32_t current_engine) const;

            void deleteTempStrPtrs();

            void changeGlobalScene() const;

            void destroyParent();

        public:

            Archive();
            Archive(eString new_media_dir);
            ~Archive();

            bool open(eString filename, int32_t mode, int32_t engine_version, bool is_proxy, int32_t ver_max_override);
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
            bool compareWithMyRoot(eRefCounter* object) const;

            void checkTypeInfo(TypeInfo** t);

            /* Other */

            eString getMediaDir() const;
            void setMediaDir(eString new_media_dir);

            void renderScene(uint32_t draw_flags) const;
            void changeSelectedObject(int32_t child_id, void* param);

            void copySceneFromMe(eScene** target) const;
            void setMyParentScene(eScene* pointer);

            void writeStructureToTextFile(const char* output_path) const;
            void writeStructureToXmlFile(eString filename) const;
            void writeSelectedObjectToObjFile(eString filename) const;
            void appendToSelectedObjectFromObjFile(eString filename);
            int32_t appendNodesFromTxtFile(const char* filename);
            int32_t changeNodesWithTxtFile(const char* filename);

    };

}

#endif
