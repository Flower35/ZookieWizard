#ifndef H_KAO2AR_ROTCTRL
#define H_KAO2AR_ROTCTRL

#include <kao2engine/eRefCounter.h>

#include <kao2engine/eLinearCtrl.h>

namespace ZookieWizard
{
    ////////////////////////////////////////////////////////////////
    // eRotCtrl interface
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

            void serialize(Archive &ar) override;
            TypeInfo* getType() override;
    };


    ////////////////////////////////////////////////////////////////
    // eRotCtrl TypeInfo
    // <kao2.0055CD70> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_ROTCTRL_ID = 0x0F0F125B;

    extern TypeInfo E_ROTCTRL_TYPEINFO;

}

#endif
