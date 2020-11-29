#ifndef H_KAO2AR_NODE
#define H_KAO2AR_NODE

#include <kao2engine/ePrimitive.h>

#include <kao2ar/Collection.h>

namespace ZookieWizard
{
    class eNode;
    class eGroup;

    class eALBox;
    class eTransform;
    template <typename> class eCtrl;

    ////////////////////////////////////////////////////////////////
    // eNode: helper definitions and structures
    ////////////////////////////////////////////////////////////////

    extern const char* theNodeFlagNames[32];

    #define TXT_PARSING_NODE_PROPTYPE_UNKNOWN (-1)
    #define TXT_PARSING_NODE_PROPTYPE_INTEGER  0
    #define TXT_PARSING_NODE_PROPTYPE_FLOAT1   1
    #define TXT_PARSING_NODE_PROPTYPE_FLOAT2   2
    #define TXT_PARSING_NODE_PROPTYPE_FLOAT3   3
    #define TXT_PARSING_NODE_PROPTYPE_FLOAT4   4
    #define TXT_PARSING_NODE_PROPTYPE_STRING   5
    #define TXT_PARSING_NODE_PROPTYPE_NODEREF  6

    class TxtParsingNodeProp
    {
        /*** Properties ***/

        private:

            int32_t type;
            eString name;

            int32_t intValue;
            float floatValues[4];
            eString strValue;
            eNode* nodeValue;

        /*** Methods ***/

        public:

            TxtParsingNodeProp();
            ~TxtParsingNodeProp();

        private:

            void createFromOtherObject(const TxtParsingNodeProp &other);

        public:

            TxtParsingNodeProp(const TxtParsingNodeProp &other);
            TxtParsingNodeProp& operator = (const TxtParsingNodeProp &other);

            eString getName() const;
            void setName(eString new_name);

            bool checkType(int32_t expected_type) const;

            bool getValue(void* result_ptr) const;
            void setValue(int32_t new_type, void* new_value_ptr);
    };

    void TxtParsingNode_ErrorArgCount(char* result, const char* current_msg, int32_t expected);
    void TxtParsingNode_ErrorArgType(char* result, const char* current_msg, int32_t arg_num, int32_t expected_type);
    void TxtParsingNode_ErrorPropType(char* result, const char* current_prop, int32_t expected_type);


    ////////////////////////////////////////////////////////////////
    // eNode interface
    // <kao2.005D08B0> (vptr)
    ////////////////////////////////////////////////////////////////

    class eNode : public ePrimitive
    {
        /*** Properties ***/

        protected:

            /*[0x08]*/ eTransform* previousTransform;
            /*[0x0C]*/ int32_t unknown_0C;
            /*[0x10]*/ eGroup* parent;
            /*[0x14]*/ eString name;
            /*[0x18]*/ eALBox* axisListBox;
            /*[0x1C]*/ uint32_t flags;
            /*[0x20-0x2C]*/ ePoint4 sphBound;
            /*[0x30]*/ uint16_t flagsCollisionResponse;
            /*[0x34]*/ eCtrl<float>* visCtrl;
            /*[0x38]*/ float visRate;
            /*[(kao3)0x34]*/ int32_t visGroup;

        /*** Methods ***/

        public:

            eNode(eString s, eNode* x);
            eNode();
            ~eNode();

        private:

            void createFromOtherObject(const eNode &other);

        public:

            eNode(const eNode &other);
            eNode& operator = (const eNode &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
            void serialize(Archive &ar) override;

            eString getStringRepresentation() const override;
            eString getLogPrintMessage() const override;
            void writeStructureToTextFile(FileOperator &file, int32_t indentation, bool group_written) const override;

            /* << eNode >> */

            eString getDebugName(int32_t trim = 64) const;

            virtual void destroyNode();
            virtual void findAndDereference(eNode* target);
            virtual eNode* findNode(eString &searched_name) const;

            virtual void setPreviousTransformGradually(eTransform* last_xform);
            virtual void updateDrawPassFlags(uint32_t* parent_flags);
            virtual bool removeEmptyAndUnreferencedGroups();
            virtual void assertNodeLinksSameArchive();

            virtual void updateBeforeRendering(eDrawContext &draw_context);
            virtual void renderNode(eDrawContext &draw_context) const;

            virtual bool createCollisionEntry();

            virtual ePoint3 editingGetCenterPoint() const;
            virtual void editingRebuildCollision();
            virtual void editingClearCollision(bool create_empty_pointer);
            virtual void editingApplyNewTransform(eSRP &new_transform, int32_t marked_id);
            virtual void editingNewNodeSetup();

            virtual int32_t parsingSetProperty(char* result_msg, const TxtParsingNodeProp &property);
            virtual int32_t parsingCustomMessage(char* result_msg, const eString &message, int32_t params_count, const TxtParsingNodeProp* params);

            virtual void collectNodesOfSomeType(const TypeInfo* type, Collection<ArFunctions::serialize_eRefCounter> &collection);

            virtual void exportScripts(const eString &media_dir) const;

            virtual void reloadXRef(const eString &media_dir, int32_t engine_version);
            virtual void exportXRef(const eString &media_dir, int32_t engine_version) const;

            virtual void ctrlExpandAnimTracks(int32_t new_size);
            virtual void ctrlRemoveAnimTrack(int32_t deleted_id);

            void setName(eString new_name);
            eString getArchivePath(eNode* final_root = nullptr) const;

            eGroup* getRootNode() const;
            eGroup* getParentNode() const;
            void setParentNode(eGroup* new_parent);

            eTransform* getPreviousTransform() const;
            void setPreviousTransform();

            uint32_t getFlags() const;
            void setFlags(uint32_t bits_to_apply);
            void unsetFlags(uint32_t bits_to_erase);

            eALBox* getAxisListBox() const;
            void setAxisListBox(eALBox* box);

            eCtrl<float>* getVisCtrl() const;
            void setVisCtrl(eCtrl<float>* new_visctrl);
            void visCtrlClear(int32_t anim_id);
            void visCtrlSetStatic(float opacity);
            void visCtrlSetLoopType(int32_t anim_id, int32_t loop_type);
            void visCtrlAddKeyframe(int32_t anim_id, float time, float opacity);
    };


    ////////////////////////////////////////////////////////////////
    // eNode TypeInfo
    // <kao2.0047A460> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_NODE_ID = 0x8000;

    extern TypeInfo E_NODE_TYPEINFO;


    ////////////////////////////////////////////////////////////////
    // Global Nodes counter
    ////////////////////////////////////////////////////////////////

    extern int32_t theNodesCounter;

}

#endif
