#ifndef H_KAO2AR_TIMER
#define H_KAO2AR_TIMER

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // Timer interface
    // <kao2.005D84C0> (vptr)
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

        private:

            void createFromOtherObject(const Timer &other);

        public:

            Timer(const Timer &other);
            Timer& operator = (const Timer &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
            void serialize(Archive &ar) override;

            /* << Gadget >> */

            eString getDefaultGadgetName() const override;
    };


    ////////////////////////////////////////////////////////////////
    // Timer TypeInfo
    // <kao2.0059CB50> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_TIMER_ID = 0x00020006;

    extern TypeInfo E_TIMER_TYPEINFO;

}

#endif
