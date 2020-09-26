#ifndef H_KAO2AR_TRACEGADGET
#define H_KAO2AR_TRACEGADGET

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eTraceGadget interface
    // <kao2.005D49D0> (vptr)
    ////////////////////////////////////////////////////////////////

    class eTraceGadget : public Gadget
    {
        /*** Properties ***/

        protected:

            /*[0x0010]*/
            /*(...)*/
            /*[0x0110]*/

        /*** Methods ***/

        public:

            eTraceGadget();
            ~eTraceGadget();

        private:

            void createFromOtherObject(const eTraceGadget &other);

        public:

            eTraceGadget(const eTraceGadget &other);
            eTraceGadget& operator = (const eTraceGadget &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eTraceGadget TypeInfo
    // <kao2.0050D800> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_TRACEGADGET_ID = 0x3BD8476A;

    extern TypeInfo E_TRACEGADGET_TYPEINFO;

}

#endif
