#ifndef H_KAO2AR_ZONE
#define H_KAO2AR_ZONE

#include <ElephantEngine/eNode.h>

#include <ElephantEngine/eActionTable.h>

namespace ZookieWizard
{
    class eALZoneSensor;

    ////////////////////////////////////////////////////////////////
    // eZone interface
    // <kao2.005D17E8> (vptr)
    ////////////////////////////////////////////////////////////////

    class eZone : public eNode
    {
        /*** Properties ***/

        protected:

            /*[0x3C-0x4C]*/ eActionTable enterActions;
            /*[0x50-0x60]*/ eActionTable leaveActions;

            /*[0x70-0x78]*/ ePoint3 boxBoundMin;
            /*[0x7C-0x84]*/ ePoint3 boxBoundMax;

        /*** Methods ***/

        public:

            eZone();
            ~eZone();

        private:

            void createFromOtherObject(const eZone &other);

        public:

            eZone(const eZone &other);
            eZone& operator = (const eZone &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
            void serialize(Archive &ar) override;

            void dumpTreeAsJsonValue(JsonValue& output, bool dumpChildNodes) const override;

            /* << eNode >> */

            void destroyNode() override;
            void findAndDereference(eNode* target) override;

            void assertNodeLinksSameArchive() override;

            bool createCollisionEntry() override;

            ePoint3 editingGetCenterPoint() const override;
            void editingRebuildCollision() override;
            void editingApplyNewTransform(eSRP &new_transform, int32_t marked_id) override;
            void editingNewNodeSetup() override;

            int32_t parsingSetProperty(char* result_msg, const TxtParsingNodeProp &property) override;
            int32_t parsingCustomMessage(char* result_msg, const eString &message, int32_t params_count, const TxtParsingNodeProp* params) override;

            /* << eZone >> */

            void setBoundaryBox(ePoint3 &new_min, ePoint3 &new_max);

            void zoneClearActions(bool enter_or_leave);
            void zoneAddAction(bool enter_or_leave, eActionBase &new_action);
    };


    ////////////////////////////////////////////////////////////////
    // eZone TypeInfo
    // <kao2.0049DEC0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_ZONE_ID = 0xFE01;

    extern TypeInfo E_ZONE_TYPEINFO;

}

#endif
