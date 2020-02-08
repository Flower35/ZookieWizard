#ifndef H_KAO2AR_PHYSICS
#define H_KAO2AR_PHYSICS

#include <kao2engine/eBasePhysics.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // ePhysics interface
    // <kao2.005D30D8> (vptr)
    ////////////////////////////////////////////////////////////////

    class ePhysics : public eBasePhysics
    {

        /*** Properties ***/

        protected:

            /*(...)*/

        /*** Methods ***/

        public:

            ePhysics();
            ~ePhysics();

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // ePhysics TypeInfo
    // <kao2.004DE0F0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_PHYSICS_ID = 0x0002DF01;

    extern TypeInfo E_PHYSICS_TYPEINFO;

}

#endif
