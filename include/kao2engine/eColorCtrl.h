#ifndef H_KAO2AR_COLORCTRL
#define H_KAO2AR_COLORCTRL

#include <kao2engine/eRefCounter.h>

#include <kao2engine/eLinearCtrl.h>
#include <kao2engine/e3fCtrl.h>

namespace ZookieWizard
{
    ////////////////////////////////////////////////////////////////
    // eColorCtrl interface
    ////////////////////////////////////////////////////////////////

    class eColorCtrl : public eRefCounter
    {

        /*** Properties ***/

        protected:
            
            /*[0x08-0x4C]*/ eLinearCtrl unknown_08;
            /*[0x50-0x78]*/ e3fCtrl unknown_50;
            /*(...)*/
            /*[0x7C]*/ int32_t unknown_7C;
            /*[0x80]*/ int32_t unknown_80;
            /*[0x84]*/ int32_t unknown_84;
            /*[0x88]*/ int32_t unknown_88;
            /*[0x8C]*/ int32_t unknown_8C;
            /*[0x90]*/ uint8_t unknown_90;

        /*** Methods ***/

        public:

            eColorCtrl();
            ~eColorCtrl();

            void serialize(Archive &ar) override;
            TypeInfo* getType() override;
    };


    ////////////////////////////////////////////////////////////////
    // eColorCtrl TypeInfo
    // <kao2.0055CE40> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_COLORCTRL_ID = 0x0F0F123C;

    extern TypeInfo E_COLORCTRL_TYPEINFO;

}

#endif
