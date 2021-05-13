#ifndef H_KAO2AR_COLLISIONCYLINDER
#define H_KAO2AR_COLLISIONCYLINDER

#include <ElephantEngine/eCollisionPrimitive.h>

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

        private:

            void createFromOtherObject(const eCollisionCylinder &other);

        public:

            eCollisionCylinder(const eCollisionCylinder &other);
            eCollisionCylinder& operator = (const eCollisionCylinder &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eCollisionCylinder TypeInfo
    // <kao2.00599240> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_COLLISIONCYLINDER_ID = 0x0002FC02;

    extern TypeInfo E_COLLISIONCYLINDER_TYPEINFO;

}

#endif
