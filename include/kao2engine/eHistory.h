#ifndef H_KAO2AR_HISTORY
#define H_KAO2AR_HISTORY

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eHistory interface
    // <kao2.005D2B70> (vptr)
    ////////////////////////////////////////////////////////////////

    class eHistory : public Gadget
    {

        /*** Properties ***/

        protected:

            /*[0x0010]*/
            /*(...)*/
            /*[0x0180]*/

        /*** Methods ***/

        public:

            eHistory();
            ~eHistory();

            TypeInfo* getType() const override;

            eString getDefaultGadgetName() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eHistory TypeInfo
    // <kao2.004D2100> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_HISTORY_ID = 0x0002DFC4;

    extern TypeInfo E_HISTORY_TYPEINFO;

}

#endif
