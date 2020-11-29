#ifndef H_KAO2AR_GROUP
#define H_KAO2AR_GROUP

#include <kao2engine/eNode.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eGroup macros
    ////////////////////////////////////////////////////////////////

    #define MACRO_KAO2_GROUP_FOREACH_NODE(code_block) \
        for (a = 0; a < nodes.getSize(); a++) \
        { \
            if (nullptr != (child_node = (eNode*)nodes.getIthChild(a))) \
            { \
                code_block \
            } \
        }


    ////////////////////////////////////////////////////////////////
    // eGroup interface
    // <kao2.005D0F88> (vptr)
    ////////////////////////////////////////////////////////////////

    class eGroup : public eNode
    {
        /*** Properties ***/

        protected:

            /*[0x3C-0x44]*/ Collection<ArFunctions::serialize_eRefCounter> nodes;

        /*** Methods ***/

        public:

            eGroup(eString s, eNode* x);
            eGroup();
            ~eGroup();

        private:

            void createFromOtherObject(const eGroup &other);

        public:

            eGroup(const eGroup &other);
            eGroup& operator = (const eGroup &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
            void serialize(Archive &ar) override;

            void writeStructureToTextFile(FileOperator &file, int32_t indentation, bool group_written) const override;
            void writeNodeToXmlFile(ColladaExporter &exporter) const override;

            /* << eNode >> */

            void destroyNode() override;
            void findAndDereference(eNode* target) override;
            eNode* findNode(eString &searched_name) const override;

            void setPreviousTransformGradually(eTransform* last_xform) override;
            void updateDrawPassFlags(uint32_t* parent_flags) override;
            bool removeEmptyAndUnreferencedGroups() override;
            void assertNodeLinksSameArchive() override;

            void updateBeforeRendering(eDrawContext &draw_context) override;
            void renderNode(eDrawContext &draw_context) const override;

            void editingRebuildCollision() override;
            void editingClearCollision(bool create_empty_pointer) override;
            void editingApplyNewTransform(eSRP &new_transform, int32_t marked_id) override;

            int32_t parsingCustomMessage(char* result_msg, const eString &message, int32_t params_count, const TxtParsingNodeProp* params) override;

            void collectNodesOfSomeType(const TypeInfo* type, Collection<ArFunctions::serialize_eRefCounter> &collection) override;

            void exportScripts(const eString &media_dir) const override;

            void reloadXRef(const eString &media_dir, int32_t engine_version) override;
            void exportXRef(const eString &media_dir, int32_t engine_version) const override;

            void ctrlExpandAnimTracks(int32_t new_size) override;
            void ctrlRemoveAnimTrack(int32_t deleted_id) override;

            /* << eGroup >> */

            int32_t getNodesCount() const;
            int32_t findChildId(eNode* o) const;
            eNode* getIthChild(int32_t i) const;

            void appendChild(eNode* o);
            void deleteIthChild(int32_t i);
            void findAndDeleteChild(eNode* o);
            void findAndDetachChild(eNode* o);

            void swapForward(int32_t i);
            void swapBackward(int32_t i);

            void deleteNodesWithMultiRefs(bool can_be_invalid, eGroup* root_node);
    };


    ////////////////////////////////////////////////////////////////
    // eGroup TypeInfo
    // <kao2.00483D80> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_GROUP_ID = 0x8111;

    extern TypeInfo E_GROUP_TYPEINFO;

}

#endif
