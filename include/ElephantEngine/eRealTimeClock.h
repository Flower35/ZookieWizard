#ifndef H_KAO2AR_REALTIMECLOCK
#define H_KAO2AR_REALTIMECLOCK

#include <ElephantEngine/Gadget.h>

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

        private:

            void createFromOtherObject(const eRealTimeClock &other);

        public:

            eRealTimeClock(const eRealTimeClock &other);
            eRealTimeClock& operator = (const eRealTimeClock &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eRealTimeClock TypeInfo
    // <kao2.00445C40> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_REALTIMECLOCK_ID = 0x3A2CB899;

    extern TypeInfo E_REALTIMECLOCK_TYPEINFO;

}

#endif
