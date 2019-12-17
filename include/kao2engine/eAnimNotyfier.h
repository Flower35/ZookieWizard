#ifndef H_KAO2AR_ANIMNOTYFIER
#define H_KAO2AR_ANIMNOTYFIER

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eAnimNotyfier interface
    // <kao2.005CF5F0> (vptr)
    ////////////////////////////////////////////////////////////////

    class eAnimNotyfier : public Gadget
    {

        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*[0x14]*/
            /*[0x18]*/

        /*** Methods ***/

        public:

            eAnimNotyfier();
            ~eAnimNotyfier();

            TypeInfo* getType() override;
    };


    ////////////////////////////////////////////////////////////////
    // eAnimNotyfier TypeInfo
    // <kao2.00444E60> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_ANIMNOTYFIER_ID = 0x3B272876;

    extern TypeInfo E_ANIMNOTYFIER_TYPEINFO;

}

#endif
