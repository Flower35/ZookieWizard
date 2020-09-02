#ifndef H_KAO2AR_CAMERA
#define H_KAO2AR_CAMERA

#include <kao2engine/eObserver.h>
#include <kao2engine/eLeafCtrl.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eCamera interface
    ////////////////////////////////////////////////////////////////

    class eCamera : public eObserver
    {

        /*** Properties ***/

        protected:

            /*[0x01CC]*/ bool followCurrentActor;
            /*[0x01D0]*/ eTransform* camTarget;
            /*[0x01D8-0x01E4]*/ float unknown_01D8[4];

            eCtrl<float>* unknown_additional_01;
            float unknown_additional_02[2];

        /*** Methods ***/

        public:

            eCamera();
            ~eCamera();

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;

            void renderNode(eDrawContext &draw_context) const override;

            void findAndDereference(eNode* target) override;

            int32_t parsingSetProperty(char* result_msg, const TxtParsingNodeProp &property) override;
            int32_t parsingCustomMessage(char* result_msg, const eString &message, int32_t params_count, const TxtParsingNodeProp* params) override;

            eTransform* getCameraTarget() const;
            void setCameraTarget(eTransform* new_target);

            void setLookingAtFollowCamera(bool value);
    };


    ////////////////////////////////////////////////////////////////
    // eCamera TypeInfo
    // <kao2.0050EC50> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_CAMERA_ID = 0x0CA4E7A1;

    extern TypeInfo E_CAMERA_TYPEINFO;

}

#endif
