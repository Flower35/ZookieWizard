#ifndef H_KAO2AR_GROUPMSGFORWARD
#define H_KAO2AR_GROUPMSGFORWARD

#include <ElephantEngine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eGroupMsgForward interface
    // <kao2.005D59A8> (vptr)
    ////////////////////////////////////////////////////////////////

    class eGroupMsgForward : public Gadget
    {
        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*[0x14]*/
            /*[0x18]*/
            /*[0x1C]*/

        /*** Methods ***/

        public:

            eGroupMsgForward();
            ~eGroupMsgForward();

        private:

            void createFromOtherObject(const eGroupMsgForward &other);

        public:

            eGroupMsgForward(const eGroupMsgForward &other);
            eGroupMsgForward& operator = (const eGroupMsgForward &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eGroupMsgForward TypeInfo
    // <kao2.00528250> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_GROUPMSGFORWARD_ID = 0x3F1A9215;

    extern TypeInfo E_GROUPMSGFORWARD_TYPEINFO;

}

#endif
