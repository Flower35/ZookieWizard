#ifndef H_KAO2AR_PATHCAMCTRL
#define H_KAO2AR_PATHCAMCTRL

#include <kao2engine/eCameraCtrl.h>

namespace ZookieWizard
{
    class eCamera;
    class eBezierSplineNode;

    ////////////////////////////////////////////////////////////////
    // ePathCamCtrl interface
    ////////////////////////////////////////////////////////////////

    class ePathCamCtrl : public eCameraCtrl
    {

        /*** Properties ***/

        protected:

            /*[0x08]*/ eCamera* cam;
            /*[0x0C]*/ eBezierSplineNode* bezier;
            /*[0x10-0x18]*/ float pos[3];
            /*[0x1C]*/ float unknown_1C;
            /*[0x20-0x23]*/ uint8_t unknown_20[4];
            /*[0x24]*/ float unknown_24;
            /*[0x28]*/ float unknown_28;
            /*[0x38]*/ float unknown_38;

        /*** Methods ***/

        public:

            ePathCamCtrl();
            ~ePathCamCtrl();

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // ePathCamCtrl TypeInfo
    // <kao2.0052B0F0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_PATHCAMCTRL_ID = 0x12455671;

    extern TypeInfo E_PATHCAMCTRL_TYPEINFO;

}

#endif
