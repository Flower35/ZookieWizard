#ifndef H_KAO2AR_GROUP
#define H_KAO2AR_GROUP

#include <kao2engine/eNode.h>

#include <kao2ar/Collection.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eGroup interface
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

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;

            void writeStructureToTextFile(FileOperator &file, int32_t indentation) const override;
            void writeNodeToXmlFile(ColladaExporter &exporter) const override;

            bool renderObject(int32_t draw_flags, eAnimate* anim, eSRP &parent_srp, int32_t marked_id) override;

            void editingRebuildCollision() override;
            void editingClearCollision() override;
            void editingApplyNewTransform(eSRP &new_transform, int32_t marked_id) override;

            void destroyNode() override;
            void findAndDereference(eNode* target) override;
            bool deleteXRefTargets() override;

            int32_t getNodesCount() const;
            eNode* getIthChild(int32_t i) const;
            void appendChild(eNode* o);
            void deleteIthChild(int32_t i);
            void findAndDeleteChild(eNode* o);
            void findAndDetachChild(eNode* o);

            void deleteNodesWithMultiRefs(bool canBeInvalid);
    };


    ////////////////////////////////////////////////////////////////
    // eGroup TypeInfo
    // <kao2.00483DB0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_GROUP_ID = 0x8111;

    extern TypeInfo E_GROUP_TYPEINFO;

}

#endif
