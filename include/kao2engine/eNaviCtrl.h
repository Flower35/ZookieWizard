#ifndef H_KAO2AR_NAVICTRL
#define H_KAO2AR_NAVICTRL

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eNaviCtrl interface
    // <kao2.005CE468> (vptr)
    ////////////////////////////////////////////////////////////////

    class eNaviCtrl : public Gadget
    {

        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*[0x14]*/
            /*[0x18]*/

        /*** Methods ***/

        public:

            eNaviCtrl();
            ~eNaviCtrl();

            TypeInfo* getType() const override;

            eString getDefaultGadgetName() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eNaviCtrl TypeInfo
    // <kao2.004287A0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_NAVICTRL_ID = 0xFE010020;

    extern TypeInfo E_NAVICTRL_TYPEINFO;

}

#endif
