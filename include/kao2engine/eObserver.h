#ifndef H_KAO2AR_OBSERVER
#define H_KAO2AR_OBSERVER

#include <kao2engine/eTransform.h>

namespace ZookieWizard
{
    class ePathCamCtrl;

    ////////////////////////////////////////////////////////////////
    // eObserver interface
    ////////////////////////////////////////////////////////////////

    class eObserver : public eTransform
    {

        /*** Properties ***/

        protected:

            /*[0x014C]*/ ePathCamCtrl* pathCtrl;
            /*[0x0150]*/ uint8_t unknown_0150;
            /*[0x0151]*/ uint8_t unknown_0151;
            /*[0x0154-0x0160]*/ float unknown_0154[4];
            /*[0x0164]*/ float fov;
            /*[0x0168]*/ float nearPlane;
            /*[0x016C]*/ float farPlane;
            /*[0x0170-0x0190]*/ float look[3][3];
            /*[0x194]*/ float unknown_0194;
            /*[0x198]*/ float unknown_0198;

        /*** Methods ***/

        public:

            eObserver();
            ~eObserver();

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;

            void editingNewNodeSetup() override;

            int32_t parsingSetProperty(char* result_msg, const TxtParsingNodeProp &property) override;
            int32_t parsingCustomMessage(char* result_msg, const eString &message, int32_t params_count, const TxtParsingNodeProp* params) override;

            float getFieldOfView() const;
            float getNearPlane() const;
            float getFarPlane() const;

            void setFieldOfView(float new_fov);
            void setNearPlane(float new_value);
            void setFarPlane(float new_value);

            ePathCamCtrl* getPathCamCtrl() const;
            void setPathCamCtrl(ePathCamCtrl* new_pathctrl);
    };


    ////////////////////////////////////////////////////////////////
    // eObserver TypeInfo
    // <kao2.004822A0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_OBSERVER_ID = 0x5000;

    extern TypeInfo E_OBSERVER_TYPEINFO;

}

#endif
