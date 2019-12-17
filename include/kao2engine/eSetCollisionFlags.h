#ifndef H_KAO2AR_SETCOLLISIONFLAGS
#define H_KAO2AR_SETCOLLISIONFLAGS

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSetCollisionFlags interface
    // <kao2.005D82D8> (vptr)
    ////////////////////////////////////////////////////////////////

    class eSetCollisionFlags : public Gadget
    {

        /*** Properties ***/

        protected:

            /*[0x10]*/

        /*** Methods ***/

        public:

            eSetCollisionFlags();
            ~eSetCollisionFlags();

            TypeInfo* getType() override;
    };


    ////////////////////////////////////////////////////////////////
    // eSetCollisionFlags TypeInfo
    // <kao2.0059A2D0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_SETCOLLISIONFLAGS_ID = 0x0002FCC2;

    extern TypeInfo E_SETCOLLISIONFLAGS_TYPEINFO;

}

#endif
