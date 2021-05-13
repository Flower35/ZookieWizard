#ifndef H_KAO2AR_SCREENCOUNTER
#define H_KAO2AR_SCREENCOUNTER

#include <ElephantEngine/eTextWriterFields2.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eScreenCounter interface
    // <kao2.005D53C0> (vptr)
    ////////////////////////////////////////////////////////////////

    class eScreenCounter : public eTextWriterFields2
    {
        /*** Properties ***/

        protected:

            /*[0x34]*/
            /*(...)*/
            /*[0x44]*/

        /*** Methods ***/

        public:

            eScreenCounter();
            ~eScreenCounter();

        private:

            void createFromOtherObject(const eScreenCounter &other);

        public:

            eScreenCounter(const eScreenCounter &other);
            eScreenCounter& operator = (const eScreenCounter &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eScreenCounter TypeInfo
    // <kao2.0051F110> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_SCREENCOUNTER_ID = 0x3B258DF2;

    extern TypeInfo E_SCREENCOUNTER_TYPEINFO;

}

#endif
