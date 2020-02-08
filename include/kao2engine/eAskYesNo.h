#ifndef H_KAO2AR_ASKYESNO
#define H_KAO2AR_ASKYESNO

#include <kao2engine/Gadget.h>

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

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eAskYesNo TypeInfo
    // <kao2.00460470> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_ASKYESNO_ID = 0x38339AA6;

    extern TypeInfo E_ASKYESNO_TYPEINFO;

}

#endif
