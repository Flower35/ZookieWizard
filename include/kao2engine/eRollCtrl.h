#ifndef H_KAO2AR_ROLLCTRL
#define H_KAO2AR_ROLLCTRL

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eRollCtrl interface
    // <kao2.005CF910> (vptr)
    ////////////////////////////////////////////////////////////////

    class eRollCtrl : public Gadget
    {
        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x38]*/

        /*** Methods ***/

        public:

            eRollCtrl();
            ~eRollCtrl();

        private:

            void createFromOtherObject(const eRollCtrl &other);

        public:

            eRollCtrl(const eRollCtrl &other);
            eRollCtrl& operator = (const eRollCtrl &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eRollCtrl TypeInfo
    // <kao2.0044B890> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_ROLLCTRL_ID = 0xF001A031;

    extern TypeInfo E_ROLLCTRL_TYPEINFO;

}

#endif
