#ifndef H_KAO2AR_SKYMANAGER
#define H_KAO2AR_SKYMANAGER

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSkyManager interface
    // <kao2.005D7160> (vptr)
    ////////////////////////////////////////////////////////////////

    class eSkyManager : public Gadget
    {

        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*[0x14]*/
            /*[0x18]*/

        /*** Methods ***/

        public:

            eSkyManager();
            ~eSkyManager();

            TypeInfo* getType() override;
    };


    ////////////////////////////////////////////////////////////////
    // eSkyManager TypeInfo
    // <kao2.00565450> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_SKYMANAGER_ID = 0xEE223344;

    extern TypeInfo E_SKYMANAGER_TYPEINFO;

}

#endif
