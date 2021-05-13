#ifndef H_KAO2AR_FLOCKEX
#define H_KAO2AR_FLOCKEX

#include <ElephantEngine/eFlock.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eFlockEx interface
    // <kao2.005CF7E0> (vptr)
    ////////////////////////////////////////////////////////////////

    class eFlockEx : public eFlock
    {
        /*** Properties ***/

        protected:

            /*[0xC0]*/
            /*(...)*/
            /*[0xD8]*/

        /*** Methods ***/

        public:

            eFlockEx();
            ~eFlockEx();

        private:

            void createFromOtherObject(const eFlockEx &other);

        public:

            eFlockEx(const eFlockEx &other);
            eFlockEx& operator = (const eFlockEx &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eFlockEx TypeInfo
    // <kao2.0044A380> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_FLOCKEX_ID = 0xF001A030;

    extern TypeInfo E_FLOCKEX_TYPEINFO;

}

#endif
