#ifndef H_KAO2AR_ENVIRONMENT
#define H_KAO2AR_ENVIRONMENT

#include <kao2engine/eGroup.h>

namespace ZookieWizard
{
    class eFogEnv;
    class eLight;

    ////////////////////////////////////////////////////////////////
    // eEnvironment interface
    ////////////////////////////////////////////////////////////////

    class eEnvironment : public eGroup
    {

        /*** Properties ***/

        protected:

            /*[0x48-0x50]*/ Collection<ArFunctions::serialize_eRefCounter> lights;
            /*[0x54-0x60]*/ float unknown_54[4];
            /*[0x64]*/ eFogEnv* fog;

        /*** Methods ***/

        public:

            eEnvironment(eString s);
            ~eEnvironment();

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;

            void renderNode(eDrawContext &draw_context) const override;

            int32_t parsingSetProperty(char* result_msg, const TxtParsingNodeProp &property) override;
            int32_t parsingCustomMessage(char* result_msg, const eString &message, int32_t params_count, const TxtParsingNodeProp* params) override;

            void findAndDereference(eNode* target) override;

            void clearLighs();
            void addLight(eLight* new_light);
            void removeLight(eLight* selected_light);

            void setFogColor(float* values);
            void setFogStart(float value);
            void setFogEnd(float value);
            void setFogMax(float value);
    };


    ////////////////////////////////////////////////////////////////
    // eEnvironment TypeInfo
    // <kao2.0047E5C0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_ENVIRONMENT_ID = 0x3F800001;

    extern TypeInfo E_ENVIRONMENT_TYPEINFO;

}

#endif
