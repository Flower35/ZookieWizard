#ifndef H_KAO2AR_STRAFECTRL
#define H_KAO2AR_STRAFECTRL

#include <kao2engine/ePathCtrl.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eStrafeCtrl interface
    // <kao2.005CF9C0> (vptr)
    ////////////////////////////////////////////////////////////////

    class eStrafeCtrl : public ePathCtrl
    {
        /*** Properties ***/

        protected:

            /*[0x50]*/
            /*(...)*/
            /*[0x94]*/

        /*** Methods ***/

        public:

            eStrafeCtrl();
            ~eStrafeCtrl();

        private:

            void createFromOtherObject(const eStrafeCtrl &other);

        public:

            eStrafeCtrl(const eStrafeCtrl &other);
            eStrafeCtrl& operator = (const eStrafeCtrl &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eStrafeCtrl TypeInfo
    // <kao2.0044D0B0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_STRAFECTRL_ID = 0x3A8C5FC6;

    extern TypeInfo E_STRAFECTRL_TYPEINFO;

}

#endif
