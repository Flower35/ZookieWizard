#ifndef H_KAO2AR_EMPTYCTRL
#define H_KAO2AR_EMPTYCTRL

#include <ElephantEngine/ePathCtrl.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eEmptyCtrl interface
    // <kao2.005CE400> (vptr)
    ////////////////////////////////////////////////////////////////

    class eEmptyCtrl : public ePathCtrl
    {
        /*** Properties ***/

        protected:

            /*[0x50]*/ uint8_t unknown_50;
            /*[0x51]*/ uint8_t unknown_51;
            /*(...)*/
            /*[0x58]*/

        /*** Methods ***/

        public:

            eEmptyCtrl();
            ~eEmptyCtrl();

        private:

            void createFromOtherObject(const eEmptyCtrl &other);

        public:

            eEmptyCtrl(const eEmptyCtrl &other);
            eEmptyCtrl& operator = (const eEmptyCtrl &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
            void serialize(Archive &ar) override;
    };


    ////////////////////////////////////////////////////////////////
    // eEmptyCtrl TypeInfo
    // <kao2.00428040> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_EMPTYCTRL_ID = 0xF0010029;

    extern TypeInfo E_EMPTYCTRL_TYPEINFO;

}

#endif
