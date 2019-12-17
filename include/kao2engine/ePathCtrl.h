#ifndef H_KAO2AR_PATHCTRL
#define H_KAO2AR_PATHCTRL

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // ePathCtrl interface
    // <kao2.005CE130> (vptr)
    ////////////////////////////////////////////////////////////////

    class ePathCtrl : public Gadget
    {

        /*** Properties ***/

        protected:

            /*[0x10]*/ eRefCounter* unknown_10;
            /*[0x14]*/ int32_t unknown_14;
            /*[0x18]*/ int32_t unknown_18;
            /*[0x1C]*/ int32_t unknown_1C;
            /*[0x20]*/ eRefCounter* unknown_20;
            /*[0x24]*/ eRefCounter* unknown_24;
            /*[0x28]*/ eObject* unknown_28;
            /*[0x2C]*/ eObject* unknown_2C;
            /*[0x30]*/ int32_t unknown_30;
            /*[0x34]*/ int32_t unknown_34;
            /*[0x38]*/ int32_t unknown_38;
            /*(...)*/
            /*[0x40]*/ uint8_t unknown_40;
            /*(...)*/
            /*[0x4C]*/

        /*** Methods ***/

        public:

            ePathCtrl();
            ~ePathCtrl();

            void serialize(Archive &ar) override;
            TypeInfo* getType() override;

            eString getDefaultGadgetName() override;
    };


    ////////////////////////////////////////////////////////////////
    // ePathCtrl TypeInfo
    // <kao2.00424230> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_PATHCTRL_ID = 0xF0010020;

    extern TypeInfo E_PATHCTRL_TYPEINFO;

}

#endif
