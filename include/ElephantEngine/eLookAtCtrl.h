#ifndef H_KAO2AR_LOOKATCTRL
#define H_KAO2AR_LOOKATCTRL

#include <ElephantEngine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eLookAtCtrl interface
    // <kao2.005CEE10> (vptr)
    ////////////////////////////////////////////////////////////////

    class eLookAtCtrl : public Gadget
    {
        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x24]*/

        /*** Methods ***/

        public:

            eLookAtCtrl();
            ~eLookAtCtrl();

        private:

            void createFromOtherObject(const eLookAtCtrl &other);

        public:

            eLookAtCtrl(const eLookAtCtrl &other);
            eLookAtCtrl& operator = (const eLookAtCtrl &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eLookAtCtrl TypeInfo
    // <kao2.004D0C50> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_LOOKATCTRL_ID = 0x3C1A9205;

    extern TypeInfo E_LOOKATCTRL_TYPEINFO;

}

#endif
