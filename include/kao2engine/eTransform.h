#ifndef H_KAO2AR_TRANSFORM
#define H_KAO2AR_TRANSFORM

#include <kao2engine/eGroup.h>
#include <kao2engine/eCtrl.h>

namespace ZookieWizard
{
    ////////////////////////////////////////////////////////////////
    // eTransform interface
    // <kao2.005D0B60> (vptr)
    ////////////////////////////////////////////////////////////////

    class eTransform : public eGroup
    {
        /*** Properties ***/

        protected:

            /*[0x48-0x64]*/ eSRP defaultTransform;
            /*[0x68-0x84]*/ eSRP worldTransform;
            /*[0xA8]*/ eCtrl<eSRP>* ctrl;

            eMatrix4x4 currentMatrix;
            float transposedMatrix[2][16];
            bool jointType;

        /*** Methods ***/

        public:

            eTransform();
            ~eTransform();

        private:

            void createFromOtherObject(const eTransform &other);

        public:

            eTransform(const eTransform &other);
            eTransform& operator = (const eTransform &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
            void serialize(Archive &ar) override;

            void writeStructureToTextFile(FileOperator &file, int32_t indentation, bool group_written) const override;
            void writeNodeToXmlFile(ColladaExporter &exporter) const override;

            /* << eNode >> */

            void setPreviousTransformGradually(eTransform* last_xform) override;
            void updateBeforeRendering(eDrawContext &draw_context) override;
            void renderNode(eDrawContext &draw_context) const override;

            ePoint3 editingGetCenterPoint() const override;
            void editingRebuildCollision() override;
            void editingApplyNewTransform(eSRP &new_transform, int32_t marked_id) override;
            void editingNewNodeSetup() override;

            int32_t parsingSetProperty(char* result_msg, const TxtParsingNodeProp &property) override;
            int32_t parsingCustomMessage(char* result_msg, const eString &message, int32_t params_count, const TxtParsingNodeProp* params) override;

            void ctrlExpandAnimTracks(int32_t new_size) override;
            void ctrlRemoveAnimTrack(int32_t deleted_id) override;

            /* << eTransform >> */

            eSRP getXForm(bool animated) const;
            void setXForm(eSRP &new_xform);

            void setTypeToJoint(bool is_joint);
            bool isJointNode() const;

            void ctrlSetStaticScale(float new_value);
            void ctrlSetStaticRotation(eQuat new_value);
            void ctrlSetStaticPosition(ePoint3 new_value);

            void ctrlSetLoopType(int32_t anim_id, int32_t loop_type, int32_t param);
            void ctrlClearKeyframes(int32_t anim_id);
            void ctrlAddKeyframe(int32_t anim_id, float new_time, eSRP new_data, int32_t param);

        protected:

            /* << eTransform >> */

            void getTransposedMatrices(eSRP some_srp);

            void deserializationCorrection();
    };


    ////////////////////////////////////////////////////////////////
    // eTransform TypeInfo
    // <kao2.0047C580> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_TRANSFORM_ID = 0x8112;

    extern TypeInfo E_TRANSFORM_TYPEINFO;

}

#endif
