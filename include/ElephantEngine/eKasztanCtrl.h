#ifndef H_KAO2AR_KASZTANCTRL
#define H_KAO2AR_KASZTANCTRL

#include <ElephantEngine/eEmptyCtrl.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eKasztanCtrl interface
    // <kao2.005CE398> (vptr)
    ////////////////////////////////////////////////////////////////

    class eKasztanCtrl : public eEmptyCtrl
    {
        /*** Properties ***/

        protected:

            /*[0x5C]*/ int32_t unknown_5C;
            /*[0x60]*/

        /*** Methods ***/

        public:

            eKasztanCtrl();
            ~eKasztanCtrl();

        private:

            void createFromOtherObject(const eKasztanCtrl &other);

        public:

            eKasztanCtrl(const eKasztanCtrl &other);
            eKasztanCtrl& operator = (const eKasztanCtrl &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
            void serialize(Archive &ar) override;
    };


    ////////////////////////////////////////////////////////////////
    // eKasztanCtrl TypeInfo
    // <kao2.004281F0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_KASZTANCTRL_ID = 0xF0A10029;

    extern TypeInfo E_KASZTANCTRL_TYPEINFO;

}

#endif
