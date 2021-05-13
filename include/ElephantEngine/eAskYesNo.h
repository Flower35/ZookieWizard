#ifndef H_KAO2AR_ASKYESNO
#define H_KAO2AR_ASKYESNO

#include <ElephantEngine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eAskYesNo interface
    // <kao2.005D0238> (vptr)
    ////////////////////////////////////////////////////////////////

    class eAskYesNo : public Gadget
    {
        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x60]*/

        /*** Methods ***/

        public:

            eAskYesNo();
            ~eAskYesNo();

        private:

            void createFromOtherObject(const eAskYesNo &other);

        public:

            eAskYesNo(const eAskYesNo &other);
            eAskYesNo& operator = (const eAskYesNo &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eAskYesNo TypeInfo
    // <kao2.00460440> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_ASKYESNO_ID = 0x38339AA6;

    extern TypeInfo E_ASKYESNO_TYPEINFO;

}

#endif
