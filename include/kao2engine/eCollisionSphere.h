#ifndef H_KAO2AR_COLLISIONSPHERE
#define H_KAO2AR_COLLISIONSPHERE

#include <kao2engine/eCollisionPrimitive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eCollisionSphere interface
    ////////////////////////////////////////////////////////////////

    class eCollisionSphere : public eCollisionPrimitive
    {

        /*** Properties ***/

        protected:

            /*[0x38]*/

        /*** Methods ***/

        public:

            eCollisionSphere();
            ~eCollisionSphere();

            TypeInfo* getType() override;
    };


    ////////////////////////////////////////////////////////////////
    // eCollisionSphere TypeInfo
    // <kao2.00598E50> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_COLLISIONSPHERE_ID = 0x0002FC01;

    extern TypeInfo E_COLLISIONSPHERE_TYPEINFO;

}

#endif
