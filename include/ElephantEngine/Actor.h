#ifndef H_KAO2AR_ACTOR
#define H_KAO2AR_ACTOR

#include <ElephantEngine/ePivot.h>

#include <ElephantEngine/Namespace.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // Actor interface
    // <kao2.005D7530> (vptr)
    ////////////////////////////////////////////////////////////////

    class Actor : public ePivot
    {
        /*** Properties ***/

        protected:

            /*[0x0114]*/ Namespace* script;
            /*[0x0118]*/ eString scriptPath;
            /*(kao3)[0x04D0-0x04D8]*/ Collection<ArFunctions::serialize_eRefCounter> unknown_04D0;
            /*(kao3)[0x04DC-0x04E4]*/ Collection<ArFunctions::serialize_eRefCounter> unknown_04DC;

        /*** Methods ***/

        public:

            Actor();
            ~Actor();

        private:

            void createFromOtherObject(const Actor &other);

        public:

            Actor(const Actor &other);
            Actor& operator = (const Actor &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
            void serialize(Archive &ar) override;

            void dumpTreeAsJsonValue(JsonValue& output, bool dumpChildNodes) const override;

            /* << eNode >> */

            void destroyNode() override;
            void findAndDereference(eNode* target) override;

            int32_t parsingSetProperty(char* result_msg, const TxtParsingNodeProp &property) override;
            int32_t parsingCustomMessage(char* result_msg, const eString &message, int32_t params_count, const TxtParsingNodeProp* params) override;

            void exportScripts(const eString &media_dir) const override;
    };


    ////////////////////////////////////////////////////////////////
    // Actor TypeInfo
    // <kao2.00572860> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_ACTOR_ID = 0x07EA0000;

    extern TypeInfo E_ACTOR_TYPEINFO;

}

#endif
