#ifndef H_KAO2AR_NAMESPACE
#define H_KAO2AR_NAMESPACE

#include <ElephantEngine/State.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // Namespace interface
    // <kao2.005D85D4> (vptr)
    ////////////////////////////////////////////////////////////////

    class Namespace : public State
    {
        /*** Properties ***/

        protected:

            /*[0x78]*/ Namespace* unknown_0078;
            /*[0x7C]*/ eString unknown_007C;
            /*[0x80]*/ bool isPersistent;

            /*[0x88]*/ int32_t unknown_0088;
            /*[0x8C]*/ int32_t unknown_008C;

            /*[0x90]*/ int32_t nodeRefNames_count;
            /*[0x94]*/ int32_t nodeRefNames_maxLength;
            /*[0x98]*/ eString* nodeRefNames;

            bool exportable;

        /*** Methods ***/

        public:

            Namespace();
            ~Namespace();

        private:

            void createFromOtherObject(const Namespace &other);

        public:

            Namespace(const Namespace &other);
            Namespace& operator = (const Namespace &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
            void serialize(Archive &ar) override;

            /* << Namespace >> */

            bool canBeExported() const;

        private:

            /* << Namespace >> */

            void clearNewNamespace();
    };


    ////////////////////////////////////////////////////////////////
    // Namespace TypeInfo
    // <kao2.0059D7F0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_NAMESPACE_ID = 0x07EA0001;

    extern TypeInfo E_NAMESPACE_TYPEINFO;

}

#endif
