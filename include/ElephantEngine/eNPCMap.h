#ifndef H_KAO2AR_NPCMAP
#define H_KAO2AR_NPCMAP

#include <ElephantEngine/eGroup.h>

#include <ElephantEngine/eGroupManager.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eNPCMap interface
    // <kao2.005CE078> (vptr)
    ////////////////////////////////////////////////////////////////

    class eNPCMap : public eGroup
    {
        /*** Properties ***/

        protected:

            /*[0x48]*/ uint8_t unknown_48;
            /*[0x4C]*/ int32_t unknown_4C;
            /*[0x50]*/ int32_t unknown_50;
            /*[0x54]*/ float unknown_54;
            /*[0x58]*/ float unknown_58;
            /*[0x5C]*/ float unknown_5C;
            /*[0x60]*/ int32_t* unknown_60;
            /*[0x64-0x6C]*/ ePoint3 boxBoundMin;
            /*[0x70-0x78]*/ ePoint3 boxBoundMax;
            /*[0x7C-0x98]*/ eGroupManager unknown_7C;

            /*[0x9C]*/ int32_t groupA_Count;
            /*[0xA0]*/ int32_t groupA_MaxLength;
            /*[0xA4]*/ int32_t* groupA;

            /*[0xA8]*/ int32_t navisCount;
            /*[0xAC-0xB4]*/ ePoint3 unknown_AC;

            /*(...)*/

            /*[0xBC]*/
            /*[0xC0]*/
            /*[0xC4]*/

        /*** Methods ***/

        public:

            eNPCMap();
            ~eNPCMap();

        private:

            void createFromOtherObject(const eNPCMap &other);

        public:

            eNPCMap(const eNPCMap &other);
            eNPCMap& operator = (const eNPCMap &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
            void serialize(Archive &ar) override;

            /* << eNode >> */

            void renderNode(eDrawContext &draw_context) const override;

            int32_t parsingSetProperty(char* result_msg, const TxtParsingNodeProp &property) override;
            int32_t parsingCustomMessage(char* result_msg, const eString &message, int32_t params_count, const TxtParsingNodeProp* params) override;

            /* << eNPCMap >> */

            void customMapSetup(ePoint3 &box_min, ePoint3 &box_max, int32_t navis_in_group);
			void customStartPointSetup(ePoint3& start_pos);
    };


    ////////////////////////////////////////////////////////////////
    // eNPCMap TypeInfo
    // <kao2.00422630> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_NPCMAP_ID = 0xA10000FF;

    extern TypeInfo E_NPCMAP_TYPEINFO;

}

#endif
