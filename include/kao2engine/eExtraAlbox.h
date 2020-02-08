#ifndef H_KAO2AR_EXTRAALBOX
#define H_KAO2AR_EXTRAALBOX

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eExtraAlbox interface
    // <kao2.005D3AC8> (vptr)
    ////////////////////////////////////////////////////////////////

    class eExtraAlbox : public Gadget
    {

        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*[0x14]*/

        /*** Methods ***/

        public:

            eExtraAlbox();
            ~eExtraAlbox();

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eExtraAlbox TypeInfo
    // <kao2.004EEAD0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_EXTRAALBOX_ID = 0x00021343;

    extern TypeInfo E_EXTRAALBOX_TYPEINFO;

}

#endif
