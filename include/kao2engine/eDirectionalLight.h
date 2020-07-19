#ifndef H_KAO2AR_DIRECTIONALLIGHT
#define H_KAO2AR_DIRECTIONALLIGHT

#include <kao2engine/eLight.h>

namespace ZookieWizard
{
    class eTransform;

    ////////////////////////////////////////////////////////////////
    // eDirectionalLight interface
    ////////////////////////////////////////////////////////////////

    class eDirectionalLight : public eLight
    {

        /*** Properties ***/

        protected:

            /*[0x6C-0x74]*/ ePoint3 position;
            /*[0x78]*/ eTransform* target;

        /*** Methods ***/

        public:

            eDirectionalLight();
            ~eDirectionalLight();

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;

            bool renderObject(int32_t draw_flags, eAnimate* anim, eSRP &parent_srp, eMatrix4x4 &parent_matrix, int32_t marked_id) override;
            ePoint3 editingGetCenterPoint() const override;
            void editingApplyNewTransform(eSRP &new_transform, int32_t marked_id) override;

            ePoint3 getPosition() const;
            void setPosition(ePoint3 &new_position);

            eTransform* getLightTarget() const;
            void setLightTarget(eTransform* new_target);
    };


    ////////////////////////////////////////////////////////////////
    // eDirectionalLight TypeInfo
    // <kao2.0047FC90> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_DIRECTIONALLIGHT_ID = 0x03454501;

    extern TypeInfo E_DIRECTIONALLIGHT_TYPEINFO;

}

#endif
