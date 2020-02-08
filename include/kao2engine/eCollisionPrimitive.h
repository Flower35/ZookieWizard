#ifndef H_KAO2AR_COLLISIONPRIMITIVE
#define H_KAO2AR_COLLISIONPRIMITIVE

#include <kao2engine/eCollision.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eCollisionPrimitive interface
    ////////////////////////////////////////////////////////////////

    class eCollisionPrimitive : public eCollision
    {

        /*** Properties ***/

        protected:

            /*[0x18]*/
            /*(...)*/
            /*[0x34]*/

        /*** Methods ***/

        public:

            eCollisionPrimitive();
            ~eCollisionPrimitive();

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eCollisionPrimitive TypeInfo
    // <kao2.00598900> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_COLLISIONPRIMITIVE_ID = 0x0002FC00;

    extern TypeInfo E_COLLISIONPRIMITIVE_TYPEINFO;

}

#endif
