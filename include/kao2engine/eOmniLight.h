#ifndef H_KAO2AR_OMNILIGHT
#define H_KAO2AR_OMNILIGHT

#include <kao2engine/eLight.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eOmniLight interface
    ////////////////////////////////////////////////////////////////

    class eOmniLight : public eLight
    {

        /*** Properties ***/

        protected:

            /*[0x6C-0x74]*/ ePoint3 position;
            /*[0x78]*/ float attenuationConstant;
            /*[0x7C]*/ float attenuationLinear;
            /*[0x80]*/ float attenuationQuadratic;

        /*** Methods ***/

        public:

            eOmniLight();
            ~eOmniLight();

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;

            bool renderObject(int32_t draw_flags, eAnimate* anim, eSRP &parent_srp, eMatrix4x4 &parent_matrix, int32_t marked_id) override;
            ePoint3 editingGetCenterPoint() const override;
            void editingApplyNewTransform(eSRP &new_transform, int32_t marked_id) override;

            ePoint3 getPosition() const;
            void setPosition(ePoint3 &new_position);
    };


    ////////////////////////////////////////////////////////////////
    // eOmniLight TypeInfo
    // <kao2.0047F5D0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_OMNILIGHT_ID = 0x03454502;

    extern TypeInfo E_OMNILIGHT_TYPEINFO;

}

#endif
