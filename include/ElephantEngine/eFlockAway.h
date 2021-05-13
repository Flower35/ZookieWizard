#ifndef H_KAO2AR_FLOCKAWAY
#define H_KAO2AR_FLOCKAWAY

#include <ElephantEngine/eFlock.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eFlockAway interface
    // <kao2.005CEA40> (vptr)
    ////////////////////////////////////////////////////////////////

    class eFlockAway : public eFlock
    {
        /*** Methods ***/

        public:

            eFlockAway();
            ~eFlockAway();

        private:

            void createFromOtherObject(const eFlockAway &other);

        public:

            eFlockAway(const eFlockAway &other);
            eFlockAway& operator = (const eFlockAway &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eFlockAway TypeInfo
    // <kao2.00431AB0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_FLOCKAWAY_ID = 0x3CE70E18;

    extern TypeInfo E_FLOCKAWAY_TYPEINFO;

}

#endif
