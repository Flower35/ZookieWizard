#ifndef H_KAO2AR_WHALEMANAGER
#define H_KAO2AR_WHALEMANAGER

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eWhaleManager interface
    // <kao2.005D3FE0> (vptr)
    ////////////////////////////////////////////////////////////////

    class eWhaleManager : public Gadget
    {

        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x90]*/

        /*** Methods ***/

        public:

            eWhaleManager();
            ~eWhaleManager();

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eWhaleManager TypeInfo
    // <kao2.004FACE0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_WHALEMANAGER_ID = 0x0002DF22;

    extern TypeInfo E_WHALEMANAGER_TYPEINFO;

}

#endif
