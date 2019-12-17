#ifndef H_KAO2AR_LINEARCTRL
#define H_KAO2AR_LINEARCTRL

#include <kao2ar/eObject.h>

namespace ZookieWizard
{
    ////////////////////////////////////////////////////////////////
    // Unknown structures
    ////////////////////////////////////////////////////////////////

    struct eLinearCtrlBaseA
    {
        /*** Properties ***/

            /*[0x00]*/ float unknown_00;
            /*[0x04]*/ float unknown_04;

        /*** Methods ***/

            void serialize(Archive &ar);
    };

    struct eLinearCtrlBaseB
    {
        /*** Properties ***/

            /*[0x00]*/ float unknown_00;
            /*[0x04]*/ float unknown_04;
            /*[0x08]*/ float unknown_08;
            /*[0x0C]*/ float unknown_0C;
            /*[0x10]*/ float unknown_10;
            /*[0x14]*/ float unknown_14;
            /*[0x18]*/ float unknown_18;

        /*** Methods ***/
            
            void serialize(Archive &ar);
    };


    ////////////////////////////////////////////////////////////////
    // eLinearCtrl interface
    ////////////////////////////////////////////////////////////////

    class eLinearCtrl : public eObject
    {

        /*** Properties ***/

        protected:

            /*[0x04]*/ int32_t groupA_Count;
            /*[0x08]*/ int32_t groupA_MaxLength;
            /*[0x0C]*/ eLinearCtrlBaseA* groupA;

            /*[0x10]*/ int32_t groupB_Count;
            /*[0x14]*/ int32_t groupB_MaxLength;
            /*[0x18]*/ eLinearCtrlBaseB* groupB;

            /*[0x1C]*/ int32_t unknown_1C;
            /*[0x20]*/ uint8_t unknown_20;
            /*[0x24]*/ float unknown_24;
            /*[0x28]*/ float unknown_28;
            /*[0x2C]*/ float unknown_2C;
            /*[0x30]*/ float unknown_30;
            /*[0x34]*/ float unknown_34;
            /*[0x38]*/ float unknown_38;
            
            /*(...)*/
            
            /*[0x3C]*/ float* series;
            /*[0x40]*/ int32_t seriesLength;

        /*** Methods ***/

        public:

            eLinearCtrl();
            ~eLinearCtrl();

            void serialize(Archive &ar) override;
            TypeInfo* getType() override;
    };


    ////////////////////////////////////////////////////////////////
    // eLinearCtrl TypeInfo
    // <kao2.00559A30> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_LINEARCTRL_ID = 0xFFEAAA01;

    extern TypeInfo E_LINEARCTRL_TYPEINFO;

}

#endif
