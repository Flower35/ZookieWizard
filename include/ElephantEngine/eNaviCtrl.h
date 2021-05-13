#ifndef H_KAO2AR_NAVICTRL
#define H_KAO2AR_NAVICTRL

#include <ElephantEngine/Gadget.h>

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

        private:

            void createFromOtherObject(const eNaviCtrl &other);

        public:

            eNaviCtrl(const eNaviCtrl &other);
            eNaviCtrl& operator = (const eNaviCtrl &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;

            /* << Gadget >> */

            eString getDefaultGadgetName() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eNaviCtrl TypeInfo
    // <kao2.00428770> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_NAVICTRL_ID = 0xFE010020;

    extern TypeInfo E_NAVICTRL_TYPEINFO;

}

#endif
