#ifndef H_KAO2AR_ROTCTRL
#define H_KAO2AR_ROTCTRL

#include <ElephantEngine/eRefCounter.h>

#include <ElephantEngine/eLinearCtrl.h>

namespace ZookieWizard
{
    ////////////////////////////////////////////////////////////////
    // eRotCtrl interface
    // <kao2.005D6CB0> (vptr)
    ////////////////////////////////////////////////////////////////

    class eRotCtrl : public eRefCounter
    {
        /*** Properties ***/

        protected:

            /*[0x08-0x4C]*/ eLinearCtrl unknown_08;

        /*** Methods ***/

        public:

            eRotCtrl();
            ~eRotCtrl();

        private:

            void createFromOtherObject(const eRotCtrl &other);

        public:

            eRotCtrl(const eRotCtrl &other);
            eRotCtrl& operator = (const eRotCtrl &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
            void serialize(Archive &ar) override;
    };


    ////////////////////////////////////////////////////////////////
    // eRotCtrl TypeInfo
    // <kao2.0055CD40> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_ROTCTRL_ID = 0x0F0F125B;

    extern TypeInfo E_ROTCTRL_TYPEINFO;

}

#endif
