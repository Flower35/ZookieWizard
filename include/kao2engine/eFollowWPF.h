#ifndef H_KAO2AR_FOLLOWWPF
#define H_KAO2AR_FOLLOWWPF

#include <kao2engine/ePathCtrl.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eFollowWPF interface
    // <kao2.005CE8E0> (vptr)
    ////////////////////////////////////////////////////////////////

    class eFollowWPF : public ePathCtrl
    {

        /*** Properties ***/

        protected:

            /*[0x50]*/ eObject* unknown_50;
            
            /*[0x54]*/ float unknown_54;
            /*[0x58]*/ float unknown_58;
            /*[0x5C]*/ float unknown_5C;

            /*[0x60]*/ float unknown_60;
            /*[0x64]*/ float unknown_64;

            /*[0x68]*/ uint8_t unknown_68;

        /*** Methods ***/

        public:

            eFollowWPF();
            ~eFollowWPF();

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eFollowWPF TypeInfo
    // <kao2.004301A0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_FOLLOWWPF_ID = 0xF0C1A029;

    extern TypeInfo E_FOLLOWWPF_TYPEINFO;

}

#endif
