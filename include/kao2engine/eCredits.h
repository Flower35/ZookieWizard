#ifndef H_KAO2AR_CREDITS
#define H_KAO2AR_CREDITS

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eCredits interface
    // <kao2.005D02B8> (vptr)
    ////////////////////////////////////////////////////////////////

    class eCredits : public Gadget
    {

        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x50]*/

        /*** Methods ***/

        public:

            eCredits();
            ~eCredits();

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eCredits TypeInfo
    // <kao2.00461340> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_CREDITS_ID = 0x3B601778;

    extern TypeInfo E_CREDITS_TYPEINFO;

}

#endif
