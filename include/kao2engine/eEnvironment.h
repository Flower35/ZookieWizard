#ifndef H_KAO2AR_ENVIRONMENT
#define H_KAO2AR_ENVIRONMENT

#include <kao2engine/eGroup.h>

namespace ZookieWizard
{
    class eFogEnv;
    class eLight;

    ////////////////////////////////////////////////////////////////
    // eEnvironment interface
    // <kao2.005D0C48> (vptr)
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

        private:

            void createFromOtherObject(const eEnvironment &other);

        public:

            eEnvironment(const eEnvironment &other);
            eEnvironment& operator = (const eEnvironment &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
            void serialize(Archive &ar) override;

            /* << eNode >> */

            void findAndDereference(eNode* target) override;

            void renderNode(eDrawContext &draw_context) const override;

            int32_t parsingSetProperty(char* result_msg, const TxtParsingNodeProp &property) override;
            int32_t parsingCustomMessage(char* result_msg, const eString &message, int32_t params_count, const TxtParsingNodeProp* params) override;

            /* << eEnvironment >> */

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
    // <kao2.0047E590> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_ENVIRONMENT_ID = 0x3F800001;

    extern TypeInfo E_ENVIRONMENT_TYPEINFO;

}

#endif
