#ifndef H_KAO2AR_3FCTRL
#define H_KAO2AR_3FCTRL

#include <kao2ar/eObject.h>

namespace ZookieWizard
{
    ////////////////////////////////////////////////////////////////
    // Unknown structures
    ////////////////////////////////////////////////////////////////

    struct e3fCtrlBaseA
    {
        /*** Properties ***/

            /*[0x00]*/ float unknown_00;
            /*[0x04-0x0C]*/ ePoint3 unknown_04;

        /*** Methods ***/

            void serialize(Archive &ar);
    };

    struct e3fCtrlBaseB
    {
        /*** Properties ***/

            /*[0x00]*/ float unknown_00;
            /*[0x04]*/ float unknown_04;
            /*[0x08]*/ float unknown_08;
            /*[0x0C]*/ float unknown_0C;
            /*[0x10]*/ float unknown_10;
            /*[0x14]*/ float unknown_14;
            /*[0x18]*/ float unknown_18;
            /*[0x1C]*/ float unknown_1C;

        /*** Methods ***/
            
            void serialize(Archive &ar);
    };


    ////////////////////////////////////////////////////////////////
    // e3fCtrl interface
    ////////////////////////////////////////////////////////////////

    class e3fCtrl : public eObject
    {

        /*** Properties ***/

        protected:

            /*[0x04]*/ int32_t groupA_Count;
            /*[0x08]*/ int32_t groupA_MaxLength;
            /*[0x0C]*/ e3fCtrlBaseA* groupA;

            /*[0x10]*/ int32_t groupB_Count;
            /*[0x14]*/ int32_t groupB_MaxLength;
            /*[0x18]*/ e3fCtrlBaseB* groupB;

            /*[0x1C]*/ uint8_t unknown_1C;
            /*[0x20]*/ int32_t unknown_20;

            /*[0x24]*/ ePoint4* series;
            /*[0x28]*/ int32_t seriesLength;

        /*** Methods ***/

        public:

            e3fCtrl();
            ~e3fCtrl();

            void serialize(Archive &ar) override;
            TypeInfo* getType() override;
    };


    ////////////////////////////////////////////////////////////////
    // e3fCtrl TypeInfo
    // <kao2.00559B00> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_3FCTRL_ID = 0xFFEAAA02;

    extern TypeInfo E_3FCTRL_TYPEINFO;

}

#endif
