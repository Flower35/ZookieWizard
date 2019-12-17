#ifndef H_KAO2AR_FSMB
#define H_KAO2AR_FSMB

#include <kao2engine/eFSOp.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eFSMB interface
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

            TypeInfo* getType() override;
    };


    ////////////////////////////////////////////////////////////////
    // eFSMB TypeInfo
    // <kao2.0055FB50> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_FSMB_ID = 0xFF777791;

    extern TypeInfo E_FSMB_TYPEINFO;


    ////////////////////////////////////////////////////////////////
    // Static Gadget
    ////////////////////////////////////////////////////////////////

    extern eFSMB theFSMB;

}

#endif
