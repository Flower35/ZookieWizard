#ifndef H_KAO2AR_POSCTRL
#define H_KAO2AR_POSCTRL

#include <kao2engine/eRefCounter.h>

#include <kao2engine/eLinearCtrl.h>

namespace ZookieWizard
{
    ////////////////////////////////////////////////////////////////
    // ePosCtrl interface
    ////////////////////////////////////////////////////////////////

    class ePosCtrl : public eRefCounter
    {

        /*** Properties ***/

        protected:

            /*[0x08-0x4C]*/ eLinearCtrl unknown_08;
            /*[0x50-0x94]*/ eLinearCtrl unknown_50;
            /*[0x98-0xDC]*/ eLinearCtrl unknown_98;
            /*(...)*/
            /*[0xE8]*/

        /*** Methods ***/

        public:

            ePosCtrl();
            ~ePosCtrl();

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // ePosCtrl TypeInfo
    // <kao2.0055CCA0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_POSCTRL_ID = 0x0F0F122D;

    extern TypeInfo E_POSCTRL_TYPEINFO;

}

#endif
