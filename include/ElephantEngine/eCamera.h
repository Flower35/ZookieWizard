#ifndef H_KAO2AR_CAMERA
#define H_KAO2AR_CAMERA

#include <ElephantEngine/eObserver.h>
#include <ElephantEngine/eLeafCtrl.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eCamera interface
    // <kao2.005D4A20> (vptr)
    ////////////////////////////////////////////////////////////////

    class eCamera : public eObserver
    {
        /*** Properties ***/

        protected:

            /*[0x01CC]*/ bool followCurrentActor;
            /*[0x01D0]*/ eTransform* camTarget;
            /*[0x01D4]*/ eLeafCtrl<float>* unknown_01D4;
            /*[0x01D8-0x01E4]*/ float unknown_01D8[4];

            eLeafCtrl<float>* unknown_01E0;
            float unknown_01DC;

        /*** Methods ***/

        public:

            eCamera();
            ~eCamera();

        private:

            void createFromOtherObject(const eCamera &other);

        public:

            eCamera(const eCamera &other);
            eCamera& operator = (const eCamera &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
            void serialize(Archive &ar) override;

            /* << eNode >> */

            void findAndDereference(eNode* target) override;

            bool removeEmptyAndUnreferencedGroups() override;
            void assertNodeLinksSameArchive() override;

            void renderNode(eDrawContext &draw_context) const override;

            int32_t parsingSetProperty(char* result_msg, const TxtParsingNodeProp &property) override;
            int32_t parsingCustomMessage(char* result_msg, const eString &message, int32_t params_count, const TxtParsingNodeProp* params) override;

            /* << eCamera >> */

            eTransform* getCameraTarget() const;
            void setCameraTarget(eTransform* new_target);

            void setLookingAtFollowCamera(bool value);
    };


    ////////////////////////////////////////////////////////////////
    // eCamera TypeInfo
    // <kao2.0050EC20> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_CAMERA_ID = 0x0CA4E7A1;

    extern TypeInfo E_CAMERA_TYPEINFO;

}

#endif
