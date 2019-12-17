#ifndef H_KAO2AR_TIMER
#define H_KAO2AR_TIMER

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // Timer interface
    ////////////////////////////////////////////////////////////////

    class Timer : public Gadget
    {

        /*** Properties ***/

        protected:

            /*[0x10]*/ uint8_t unknown_10;
            /*[0x14]*/ int32_t unknown_14;

        /*** Methods ***/

        public:

            Timer();
            ~Timer();

            void serialize(Archive &ar) override;
            TypeInfo* getType() override;

            eString getDefaultGadgetName() override;
    };


    ////////////////////////////////////////////////////////////////
    // Timer TypeInfo
    // <kao2.0059CB80> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_TIMER_ID = 0x00020006;

    extern TypeInfo E_TIMER_TYPEINFO;

}

#endif
