#ifndef H_KAO2AR_NECKCTRL
#define H_KAO2AR_NECKCTRL

#include <ElephantEngine/eLookAtCtrl.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eNeckCtrl interface
    // <kao2.005CEDB8> (vptr)
    ////////////////////////////////////////////////////////////////

    class eNeckCtrl : public eLookAtCtrl
    {
        /*** Properties ***/

        protected:

            /*[0x28]*/
            /*(...)*/
            /*[0x80]*/

        /*** Methods ***/

        public:

            eNeckCtrl();
            ~eNeckCtrl();

        private:

            void createFromOtherObject(const eNeckCtrl &other);

        public:

            eNeckCtrl(const eNeckCtrl &other);
            eNeckCtrl& operator = (const eNeckCtrl &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eNeckCtrl TypeInfo
    // <kao2.00438270> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_NECKCTRL_ID = 0x3BB4EFBE;

    extern TypeInfo E_NECKCTRL_TYPEINFO;

}

#endif
