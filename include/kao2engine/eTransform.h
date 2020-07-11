#ifndef H_KAO2AR_TRANSFORM
#define H_KAO2AR_TRANSFORM

#include <kao2engine/eGroup.h>
#include <kao2engine/eCtrl.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eTransform interface
    ////////////////////////////////////////////////////////////////

    class eTransform : public eGroup
    {

        /*** Properties ***/

        protected:

            /*[0x48-0x84]*/ eSRP defaultTransform[2];
            /*[0xA8]*/ eCtrl<eSRP>* ctrl;

            eSRP modifiedTransform[2];
            eMatrix4x4 currentMatrix;
            float transposedMatrix[16];
            bool jointType;

        /*** Methods ***/

        public:

            eTransform();
            ~eTransform();

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;

            void writeStructureToTextFile(FileOperator &file, int32_t indentation) const override;
            void writeNodeToXmlFile(ColladaExporter &exporter) const override;

            bool renderObject(int32_t draw_flags, eAnimate* anim, eSRP &parent_srp, eMatrix4x4 &parent_matrix, int32_t marked_id) override;
            void updateSRP(bool update, eAnimate* anim, eSRP &parent_srp) override;

            ePoint3 editingGetCenterPoint() const override;
            void editingRebuildCollision() override;
            void editingApplyNewTransform(eSRP &new_transform, int32_t marked_id) override;

            void ctrlExpandAnimTracks(int32_t new_size) override;
            void ctrlRemoveAnimTrack(int32_t deleted_id) override;

            eSRP getXForm(bool modified, bool animated) const;
            void setXForm(eSRP &new_xform);

            void setTypeToJoint(bool is_joint);
            bool isJointNode() const;

            void ctrlSetStaticScale(float new_value);
            void ctrlSetStaticRotation(eQuat new_value);
            void ctrlSetStaticPosition(ePoint3 new_value);

            void ctrlClearKeyframes(int anim_id);
            void ctrlAddKeyframe(int anim_id, float new_time, eSRP new_data, int param);

        protected:

            void deserializationCorrection();
    };


    ////////////////////////////////////////////////////////////////
    // eTransform TypeInfo
    // <kao2.0047C5B0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_TRANSFORM_ID = 0x8112;

    extern TypeInfo E_TRANSFORM_TYPEINFO;

}

#endif
