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
            TypeInfo* getType() const override;

            bool renderObject(int32_t draw_flags, eAnimate* anim, eSRP &parent_srp, eMatrix4x4 &parent_matrix, int32_t marked_id) override;

            eXRefTarget* getXRefTarget() const;
    };


    ////////////////////////////////////////////////////////////////
    // eXRefProxy TypeInfo
    // <kao2.004AD740> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_XREFPROXY_ID = 0x87EF0002;

    extern TypeInfo E_XREFPROXY_TYPEINFO;

}

#endif
