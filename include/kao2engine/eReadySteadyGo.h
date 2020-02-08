#ifndef H_KAO2AR_READYSTEADYGO
#define H_KAO2AR_READYSTEADYGO

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eReadySteadyGo interface
    // <kao2.005D00A8> (vptr)
    ////////////////////////////////////////////////////////////////

    class eReadySteadyGo : public Gadget
    {

        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x54]*/

        /*** Methods ***/

        public:

            eReadySteadyGo();
            ~eReadySteadyGo();

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eReadySteadyGo TypeInfo
    // <kao2.0045BE40> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_READYSTEADYGO_ID = 0x3B97B235;

    extern TypeInfo E_READYSTEADYGO_TYPEINFO;

}

#endif
