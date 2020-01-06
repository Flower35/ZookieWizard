#ifndef H_KAO2AR_XREFPROXY
#define H_KAO2AR_XREFPROXY

#include <kao2engine/eNode.h>

namespace ZookieWizard
{
    class eXRefTarget;

    ////////////////////////////////////////////////////////////////
    // eXRefProxy interface
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

            void serialize(Archive &ar) override;
            TypeInfo* getType() override;

            void renderObject(eAnimate* anim, int32_t draw_flags, eSRP &parent_srp) override;

            eXRefTarget* getXRefTarget();
    };


    ////////////////////////////////////////////////////////////////
    // eXRefProxy TypeInfo
    // <kao2.004AD740> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_XREFPROXY_ID = 0x87EF0002;

    extern TypeInfo E_XREFPROXY_TYPEINFO;

}

#endif
