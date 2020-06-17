#ifndef H_KAO2AR_CAMERA
#define H_KAO2AR_CAMERA

#include <kao2engine/eObserver.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eCamera interface
    ////////////////////////////////////////////////////////////////

    class eCamera : public eObserver
    {

        /*** Properties ***/

        protected:

            /*[0x01CC]*/ uint8_t unknown_01CC;
            /*[0x01D0]*/ eTransform* camTarget;
            /*[0x01D8-0x01E4]*/ float unknown_01D8[4];

        /*** Methods ***/

        public:

            eCamera();
            ~eCamera();

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;

            bool renderObject(int32_t draw_flags, eAnimate* anim, eSRP &parent_srp, eMatrix4x4 &parent_matrix, int32_t marked_id) override;

            void findAndDereference(eNode* target) override;

            eTransform* getCameraTarget() const;
            void setCameraTarget(eTransform* new_target);
    };


    ////////////////////////////////////////////////////////////////
    // eCamera TypeInfo
    // <kao2.0050EC50> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_CAMERA_ID = 0x0CA4E7A1;

    extern TypeInfo E_CAMERA_TYPEINFO;

}

#endif
