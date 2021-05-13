#ifndef H_KAO2AR_XREFPROXY
#define H_KAO2AR_XREFPROXY

#include <ElephantEngine/eNode.h>

namespace ZookieWizard
{
    class eXRefTarget;

    ////////////////////////////////////////////////////////////////
    // eXRefProxy interface
    // <kao2.005D1F50> (vptr)
    ////////////////////////////////////////////////////////////////

    class eXRefProxy : public eNode
    {
        /*** Properties ***/

        protected:

            /*[0x3C]*/ eXRefTarget* target;

        /*** Methods ***/

        public:

            eXRefProxy(eXRefTarget* x);
            ~eXRefProxy();

        private:

            void createFromOtherObject(const eXRefProxy &other);

        public:

            eXRefProxy(const eXRefProxy &other);
            eXRefProxy& operator = (const eXRefProxy &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
            void serialize(Archive &ar) override;

            /* << eNode >> */

            void updateDrawPassFlags(uint32_t* parent_flags) override;
            void renderNode(eDrawContext &draw_context) const override;

            /* << eXRefProxy >> */

            eXRefTarget* getXRefTarget() const;
    };


    ////////////////////////////////////////////////////////////////
    // eXRefProxy TypeInfo
    // <kao2.004AD710> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_XREFPROXY_ID = 0x87EF0002;

    extern TypeInfo E_XREFPROXY_TYPEINFO;

}

#endif
