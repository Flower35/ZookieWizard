#ifndef H_KAO2AR_STATICSND
#define H_KAO2AR_STATICSND

#include <kao2engine/eSnd.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eStaticSnd interface
    // <kao2.005CEFE8> (vptr)
    ////////////////////////////////////////////////////////////////

    class eStaticSnd : public eSnd
    {

        /*** Methods ***/

        public:

            eStaticSnd();
            ~eStaticSnd();

            TypeInfo* getType() override;
    };


    ////////////////////////////////////////////////////////////////
    // eStaticSnd TypeInfo
    // <kao2.00439E50> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_STATICSND_ID = 0x39D5A029;

    extern TypeInfo E_STATICSND_TYPEINFO;

}

#endif
