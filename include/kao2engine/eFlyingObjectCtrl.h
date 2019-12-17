#ifndef H_KAO2AR_FLYINGOBJECTCTRL
#define H_KAO2AR_FLYINGOBJECTCTRL

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eFlyingObjectCtrl interface
    // <kao2.005D4120> (vptr)
    ////////////////////////////////////////////////////////////////

    class eFlyingObjectCtrl : public Gadget
    {

        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x80]*/

        /*** Methods ***/

        public:

            eFlyingObjectCtrl();
            ~eFlyingObjectCtrl();

            TypeInfo* getType() override;
    };


    ////////////////////////////////////////////////////////////////
    // eFlyingObjectCtrl TypeInfo
    // <kao2.004FE020> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_FLYINGOBJECTCTRL_ID = 0x0002F0F1;

    extern TypeInfo E_FLYINGOBJECTCTRL_TYPEINFO;

}

#endif
