#ifndef H_KAO2AR_ARCHIVE
#define H_KAO2AR_ARCHIVE

#include <ElephantBase/kao2ar.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // KAO2 OBJECT REFERENCES
    ////////////////////////////////////////////////////////////////

    struct TypeInfo;

    class eObject;
    class eRefCounter;
    class eNode;
    class eGroup;
    class eScene;


    ////////////////////////////////////////////////////////////////
    // KAO2 HELPER FUNCTIONS
    ////////////////////////////////////////////////////////////////

    namespace ArFunctions
    {
        eString getFullArchivePath(const eString &filename, const eString &media_dir, int32_t ar_version, int32_t flags);
    }


    ////////////////////////////////////////////////////////////////
    // KAO2 ARCHIVE CLASS
    ////////////////////////////////////////////////////////////////

    #define AR_MODE_READ (1 << 0)
    #define AR_MODE_WRITE (1 << 1)
    #define AR_MODE_DEBUG (1 << 2)
    #define AR_MODE_IS_PROXY (1 << 3)
    #define AR_MODE_SKIP_PROXIES (1 << 4)
    #define AR_MODE_ABSOLUTE_PATH (1 << 5)
    #define AR_MODE_PARTICLES_PATH (1 << 6)
    #define AR_MODE_XREF_PATH (1 << 7)

    #define AR_MAX_ITEMS   65536
    #define AR_MAX_TEMPSTR   192

    #define AR_ITEM_TYPE_OBJECT 0x00
    #define AR_ITEM_TYPE_STRING 0x01
    #define AR_ITEM_TYPE_OTHER  0x02

    #define NODES_LISTBOX_SET_MARKED_CHILD   (-1)
    #define NODES_LISTBOX_UPDATE_CURRENT     (-2)
    #define NODES_LISTBOX_PARENT             (-3)
    #define NODES_LISTBOX_ROOT               (-4)
    #define NODES_LISTBOX_MOVE_UP            (-5)
    #define NODES_LISTBOX_MOVE_DOWN          (-6)
    #define NODES_LISTBOX_MOVE_OUT           (-7)
    #define NODES_LISTBOX_MOVE_IN            (-8)
    #define NODES_LISTBOX_CENTER_CAMERA      (-9)
    #define NODES_LISTBOX_DELETE_CURRENT    (-10)
    #define NODES_LISTBOX_DELETE_CHILDREN   (-11)
    #define NODES_LISTBOX_DELETE_SELECTED   (-12)
    #define NODES_LISTBOX_COLLISION_REBUILD (-13)
    #define NODES_LISTBOX_COLLISION_CLEAR   (-14)
    #define NODES_EDITING_SET_FLAG          (-15)
    #define NODES_EDITING_UNSET_FLAG        (-16)
    #define NODES_EDITING_CHANGE_NAME       (-17)
    #define NODES_EDITING_CHANGE_TYPE       (-18)
    #define NODES_EDITING_INSERT            (-19)
    #define NODES_EDITING_RESET_TRANSFORM   (-20)
    #define NODES_EDITING_APPLY_TRANSFORM   (-21)
    #define NODES_EDITING_CLONE_CURRENT     (-22)
    #define NODES_EDITING_CLONE_SELECTED    (-23)
    #define NODES_EDITING_CLONE_PASTING     (-24)
    #define NODES_EDITING_MATERIAL_CLONE    (-25)
    #define NODES_EDITING_MATERIAL_DELETE   (-26)
    #define NODES_EDITING_MATERIAL_CHANGE   (-27)
    #define NODES_EDITING_MATERIAL_OPTIMIZE (-28)
    #define NODES_EDITING_GROUPS_DPFLAGS    (-29)
    #define NODES_EDITING_GROUPS_UNREF      (-30)

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

            eNode* lastSerializedNode;

            eString baseFileName;
            eString mediaDirectory;

        /*** Methods ***/

        public:

            Archive();
            Archive(eString new_media_dir);
            ~Archive();

        private:

            Archive(const Archive &other);
            Archive& operator = (const Archive &other);

        public:

            bool isNotEmpty() const;

            bool open(eString path, int32_t mode, int32_t version_override);
            void close(bool hide);

            /* << State determining >> */

            bool isInReadMode() const;
            bool isInWriteMode() const;
            bool isInDebugMode() const;

            /* << Serialization (reading from archives, writing to archives) >> */

            int32_t getVersion() const;

            bool addItem(void* item, int type);
            void* getItem(int id, int type) const;
            int findItem(void* item) const;
            bool addTempStr(eStringBase<char>* str);

            void readOrWrite(void* pointer, int size);
            void assertObjectType(const TypeInfo* expected_type, const TypeInfo* current_type) const;
            void serialize(eObject** o, const TypeInfo* t);
            void serializeString(eString &s);
            void replaceStringDuringSerialization(eString &oldStr, eString newStr);

            bool compareWithMyRoot(const eRefCounter* object) const;
            eNode* getLastSerializedNode() const;
            void setLastSerializedNode(eNode* node);
            bool assertLastSerializedNode(const eNode* node) const;

            void checkTypeInfo(const TypeInfo** t);

            /* << Other functions >> */

            eString getBaseFileName() const;

            eString getMediaDir() const;
            void setMediaDir(eString new_media_dir);

            void changeGlobalScene() const;
            void renderScene(uint32_t draw_flags) const;
            void changeSelectedObject(int32_t child_id, void* param);

            void copySceneFromMe(eScene** target) const;
            void setMyParentScene(eScene* pointer);

            void exportScripts() const;
            void exportProxies(int32_t version_override) const;
            void reloadProxies(int32_t version_override) const;
            void writeTreeToJsonFile(const char* output_path) const;
            void writeTreeToXmlFile(eString filename) const;
            void writeSelectedObjectToObjFile(eString filename) const;
            void appendToSelectedObjectFromObjFile(eString filename);
            int32_t appendNodesFromTxtFile(const char* filename);
            int32_t changeNodesWithTxtFile(const char* filename);

        private:

            void deleteTempStrPtrs();

            void destroyParent();
    };

}

#endif
