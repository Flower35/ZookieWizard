#ifndef H_KAO2AR_TIMERGADGET
#define H_KAO2AR_TIMERGADGET

#include <kao2engine/eTextWriterFields2.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eTimerGadget interface
    // <kao2.005D5370> (vptr)
    ////////////////////////////////////////////////////////////////

    class eTimerGadget : public eTextWriterFields2
    {
        /*** Properties ***/

        protected:

            /*[0x34]*/
            /*(...)*/
            /*[0x54]*/

        /*** Methods ***/

        public:

            eTimerGadget();
            ~eTimerGadget();

        private:

            void createFromOtherObject(const eTimerGadget &other);

        public:

            eTimerGadget(const eTimerGadget &other);
            eTimerGadget& operator = (const eTimerGadget &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eTimerGadget TypeInfo
    // <kao2.0051E8D0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_TIMERGADGET_ID = 0x3B248DF2;

    extern TypeInfo E_TIMERGADGET_TYPEINFO;

}

#endif
