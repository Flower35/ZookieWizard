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
            TypeInfo* getType() override;

            void writeStructureToTextFile(FileOperator &file, int32_t indentation) override;
            void writeNodeToXmlFile(ColladaExporter &exporter) override;

            void renderObject(eAnimate* anim, int32_t draw_flags, eSRP &parent_srp) override;

            int32_t getNodesCount();
            eNode* getIthChild(int32_t i);
            void appendChild(eNode* o);
            void deleteIthChild(int32_t i);
            void findAndDeleteChild(eNode* o);
    };


    ////////////////////////////////////////////////////////////////
    // eGroup TypeInfo
    // <kao2.00483DB0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_GROUP_ID = 0x8111;

    extern TypeInfo E_GROUP_TYPEINFO;

}

#endif
