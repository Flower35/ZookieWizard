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
            float transposedMatrix[16];
            bool jointType;

        /*** Methods ***/

        public:

            eTransform();
            ~eTransform();

            void serialize(Archive &ar) override;
            TypeInfo* getType() override;

            void writeNodeToXmlFile(ColladaExporter &exporter) override;

            void renderObject(eAnimate* anim, int32_t draw_flags, eSRP &parent_srp) override;
            void updateSRP(eAnimate* anim, eSRP &parent_srp) override;

            void setXForm(eSRP new_xform);
            eSRP getXForm();

            void setTypeToJoint(bool is_joint);
            bool isJointNode();
    };


    ////////////////////////////////////////////////////////////////
    // eTransform TypeInfo
    // <kao2.0047C5B0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_TRANSFORM_ID = 0x8112;

    extern TypeInfo E_TRANSFORM_TYPEINFO;

}

#endif
