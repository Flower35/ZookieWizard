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

            void renderNode(eDrawContext &draw_context) const override;

            ePoint3 editingGetCenterPoint() const override;
            void editingApplyNewTransform(eSRP &new_transform, int32_t marked_id) override;

            int32_t parsingSetProperty(char* result_msg, const TxtParsingNodeProp &property) override;
            int32_t parsingCustomMessage(char* result_msg, const eString &message, int32_t params_count, const TxtParsingNodeProp* params) override;

            /*[vptr]+0x74]*/ void bindLight(int32_t light_id) const override;

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
