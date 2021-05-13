#ifndef H_KAO2AR_GLOBALCTRL
#define H_KAO2AR_GLOBALCTRL

#include <ElephantEngine/eRefCounter.h>

#include <ElephantEngine/eLinearCtrl.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eGlobalCtrl interface
    // <kao2.005D6CC8> (vptr)
    ////////////////////////////////////////////////////////////////

    class eGlobalCtrl : public eRefCounter
    {
        /*** Properties ***/

        protected:

            /*[0x0008]*/ int32_t unknown_0008;
            /*[0x000C-0x0050]*/ eLinearCtrl unknown_000C;
            /*[0x0054-0x0098]*/ eLinearCtrl unknown_0054;
            /*[0x009C-0x00E0]*/ eLinearCtrl unknown_009C;
            /*[0x00E4-0x0128]*/ eLinearCtrl unknown_00E4;
            /*[0x012C]*/ float unknown_012C;
            /*[0x0130]*/ uint8_t unknown_0130;
            /*[0x0134]*/ float unknown_0134;
            /*[0x0138]*/ int32_t unknown_0138;
            /*[0x013C]*/ int32_t unknown_013C;
            /*[0x0140]*/ int32_t unknown_0140;
            /*[0x0144]*/ int32_t unknown_0144;
            /*[0x0148]*/ int32_t unknown_0148;
            /*[0x014C]*/ int32_t unknown_014C;
            /*[0x0150]*/ uint8_t unknown_0150;
            /*[0x0154]*/ float unknown_0154;
            /*[0x0158]*/ float unknown_0158;
            /*[0x015C]*/ float unknown_015C;
            /*[0x0160]*/ float unknown_0160;
            /*(...)*/
            /*[0x0168]*/ uint8_t unknown_0168;

        /*** Methods ***/

        public:

            eGlobalCtrl();
            ~eGlobalCtrl();

        private:

            void createFromOtherObject(const eGlobalCtrl &other);

        public:

            eGlobalCtrl(const eGlobalCtrl &other);
            eGlobalCtrl& operator = (const eGlobalCtrl &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
            void serialize(Archive &ar) override;
    };


    ////////////////////////////////////////////////////////////////
    // eGlobalCtrl TypeInfo
    // <kao2.0055CBA0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_GLOBALCTRL_ID = 0x0F0F120A;

    extern TypeInfo E_GLOBALCTRL_TYPEINFO;

}

#endif
