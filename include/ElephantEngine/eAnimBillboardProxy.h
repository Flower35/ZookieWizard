#ifndef H_KAO2AR_ANIMBILLBOARDPROXY
#define H_KAO2AR_ANIMBILLBOARDPROXY

#include <ElephantEngine/eNode.h>

namespace ZookieWizard
{
    class eAnimBillboardTarget;

    ////////////////////////////////////////////////////////////////
    // eAnimBillboardProxy interface
    // <kao_tw.0069A0D4> (vptr)
    ////////////////////////////////////////////////////////////////

    class eAnimBillboardProxy : public eNode
    {
        /*** Properties ***/

        protected:

            /*[(kao3)0x40]*/ eAnimBillboardTarget* target;

        /*** Methods ***/

        public:

            eAnimBillboardProxy();
            ~eAnimBillboardProxy();

        private:

            void createFromOtherObject(const eAnimBillboardProxy &other);

        public:

            eAnimBillboardProxy(const eAnimBillboardProxy &other);
            eAnimBillboardProxy& operator = (const eAnimBillboardProxy &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
            void serialize(Archive &ar) override;
    };


    ////////////////////////////////////////////////////////////////
    // eAnimBillboardProxy TypeInfo
    // <kao_tw.004779F0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_ANIMBILLBOARDPROXY_ID = 0xA31B1BD1;

    extern TypeInfo E_ANIMBILLBOARDPROXY_TYPEINFO;

}

#endif
