#ifndef H_KAO2AR_JUMPPHYSICS
#define H_KAO2AR_JUMPPHYSICS

#include <kao2engine/ePhysics.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eJumpPhysics interface
    // <kao2.005D3BA0> (vptr)
    ////////////////////////////////////////////////////////////////

    class eJumpPhysics : public ePhysics
    {

        /*** Properties ***/

        protected:

            /*(...)*/
            /*[0x0880]*/

        /*** Methods ***/

        public:

            eJumpPhysics();
            ~eJumpPhysics();

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eJumpPhysics TypeInfo
    // <kao2.004EF2C0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_JUMPPHYSICS_ID = 0x0002DF03;

    extern TypeInfo E_JUMPPHYSICS_TYPEINFO;

}

#endif
