#ifndef H_KAO2AR_PATHCAMCTRL
#define H_KAO2AR_PATHCAMCTRL

#include <ElephantEngine/eCameraCtrl.h>

namespace ZookieWizard
{
    class eCamera;
    class eBezierSplineNode;

    ////////////////////////////////////////////////////////////////
    // ePathCamCtrl interface
    // <kao2.005D5AB4> (vptr)
    ////////////////////////////////////////////////////////////////

    class ePathCamCtrl : public eCameraCtrl
    {
        /*** Properties ***/

        protected:

            /*[0x08]*/ eCamera* camera;
            /*[0x0C]*/ eBezierSplineNode* bezier;
            /*[0x10-0x18]*/ ePoint3 position;
            /*[0x1C]*/ float unknown_1C;
            /*[0x20-0x23]*/ uint8_t unknown_20[4];
            /*[0x24]*/ int32_t unknown_24;
            /*[0x28]*/ float unknown_28;
            /*[0x38]*/ float unknown_38;

        /*** Methods ***/

        public:

            ePathCamCtrl();
            ~ePathCamCtrl();

        private:

            void createFromOtherObject(const ePathCamCtrl &other);

        public:

            ePathCamCtrl(const ePathCamCtrl &other);
            ePathCamCtrl& operator = (const ePathCamCtrl &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
            void serialize(Archive &ar) override;

            /* << ePathCamCtrl >> */

            eCamera* getCameraLink() const;
            void setCameraLink(eCamera* new_camera);

            eBezierSplineNode* getBezierLink() const;
            void setBezierLink(eBezierSplineNode* new_bezier);

            ePoint3 getPosition() const;
            void setPosition(ePoint3 new_position);
    };


    ////////////////////////////////////////////////////////////////
    // ePathCamCtrl TypeInfo
    // <kao2.0052B0C0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_PATHCAMCTRL_ID = 0x12455671;

    extern TypeInfo E_PATHCAMCTRL_TYPEINFO;

}

#endif
