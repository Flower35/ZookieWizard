#ifndef H_KAO2AR_ZONE
#define H_KAO2AR_ZONE

#include <kao2engine/eNode.h>

#include <kao2engine/eActionTable.h>

namespace ZookieWizard
{
    class eALZoneSensor;

    ////////////////////////////////////////////////////////////////
    // eZone interface
    ////////////////////////////////////////////////////////////////

    class eZone : public eNode
    {

        /*** Properties ***/

        protected:

            /*[0x3C-0x4C]*/ eActionTable enterActions;
            /*[0x50-0x60]*/ eActionTable leaveActions;

            /*[0x64]*/
            /*[0x68]*/
            /*[0x6C]*/

            /*[0x70-0x78]*/ ePoint3 boxBoundMin;
            /*[0x7C-0x84]*/ ePoint3 boxBoundMax;

        /*** Methods ***/

        public:

            eZone();
            ~eZone();

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;

            void writeStructureToTextFile(FileOperator &file, int32_t indentation) const override;

            ePoint3 editingGetCenterPoint() const override;
            void editingRebuildCollision() override;
            void editingApplyNewTransform(eSRP &new_transform, int32_t marked_id) override;
            void editingNewNodeSetup() override;

            int32_t parsingSetProperty(char* result_msg, const TxtParsingNodeProp &property) override;
            int32_t parsingCustomMessage(char* result_msg, const eString &message, int32_t params_count, const TxtParsingNodeProp* params) override;

            void setBoundaryBox(ePoint3 &new_min, ePoint3 &new_max);

            void createCollisionEntry();

            void destroyNode() override;
            void findAndDereference(eNode* target) override;

            void zoneClearActions(bool enter_or_leave);
            void zoneAddAction(bool enter_or_leave, eActionBase &new_action);
    };


    ////////////////////////////////////////////////////////////////
    // eZone TypeInfo
    // <kao2.0049DEF0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_ZONE_ID = 0xFE01;

    extern TypeInfo E_ZONE_TYPEINFO;

}

#endif
