#ifndef H_KAO2AR_COLLISIONCYLINDER
#define H_KAO2AR_COLLISIONCYLINDER

#include <kao2engine/eCollisionPrimitive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eCollisionCylinder interface
    // <kao2.005D81D0> (vptr)
    ////////////////////////////////////////////////////////////////

    class eCollisionCylinder : public eCollisionPrimitive
    {

        /*** Properties ***/

        protected:

            /*[0x38]*/
            /*[0x3C]*/

        /*** Methods ***/

        public:

            eCollisionCylinder();
            ~eCollisionCylinder();

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eCollisionCylinder TypeInfo
    // <kao2.00599270> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_COLLISIONCYLINDER_ID = 0x0002FC02;

    extern TypeInfo E_COLLISIONCYLINDER_TYPEINFO;

}

#endif
