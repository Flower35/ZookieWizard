#ifndef H_KAO2AR_KAOKILLER
#define H_KAO2AR_KAOKILLER

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eKaoKiller interface
    // <kao2.005D48A0> (vptr)
    ////////////////////////////////////////////////////////////////

    class eKaoKiller : public Gadget
    {

        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x1C]*/

        /*** Methods ***/

        public:

            eKaoKiller();
            ~eKaoKiller();

            TypeInfo* getType() override;

            eString getDefaultGadgetName() override;
    };


    ////////////////////////////////////////////////////////////////
    // eKaoKiller TypeInfo
    // <kao2.0050BC70> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_KAOKILLER_ID = 0x0002F552;

    extern TypeInfo E_KAOKILLER_TYPEINFO;

}

#endif
