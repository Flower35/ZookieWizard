#ifndef H_KAO2AR_REALTIMECLOCK
#define H_KAO2AR_REALTIMECLOCK

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eRealTimeClock interface
    // <kao2.005CF698> (vptr)
    ////////////////////////////////////////////////////////////////

    class eRealTimeClock : public Gadget
    {

        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x88]*/

        /*** Methods ***/

        public:

            eRealTimeClock();
            ~eRealTimeClock();

            TypeInfo* getType() override;
    };


    ////////////////////////////////////////////////////////////////
    // eRealTimeClock TypeInfo
    // <kao2.00445C70> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_REALTIMECLOCK_ID = 0x3A2CB899;

    extern TypeInfo E_REALTIMECLOCK_TYPEINFO;

}

#endif
