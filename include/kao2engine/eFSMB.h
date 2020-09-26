#ifndef H_KAO2AR_FSMB
#define H_KAO2AR_FSMB

#include <kao2engine/eFSOp.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eFSMB interface
    // <kao2.005D6D38> (vptr)
    ////////////////////////////////////////////////////////////////

    class eFSMB : public eFSOp
    {
        /*** Properties ***/

        protected:

            /*(...)*/
            /*[0x40]*/

        /*** Methods ***/

        public:

            eFSMB();
            ~eFSMB();

        private:

            void createFromOtherObject(const eFSMB &other);

        public:

            eFSMB(const eFSMB &other);
            eFSMB& operator = (const eFSMB &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eFSMB TypeInfo
    // <kao2.0055FB20> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_FSMB_ID = 0xFF777791;

    extern TypeInfo E_FSMB_TYPEINFO;


    ////////////////////////////////////////////////////////////////
    // Static Gadget
    ////////////////////////////////////////////////////////////////

    extern eFSMB theFSMB;

}

#endif
