#ifndef H_KAO2AR_COLLISIONSPHERE
#define H_KAO2AR_COLLISIONSPHERE

#include <kao2engine/eCollisionPrimitive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eCollisionSphere interface
    // <kao2.005D8170> (vptr)
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

        private:

            void createFromOtherObject(const eCollisionSphere &other);

        public:

            eCollisionSphere(const eCollisionSphere &other);
            eCollisionSphere& operator = (const eCollisionSphere &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eCollisionSphere TypeInfo
    // <kao2.00598E20> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_COLLISIONSPHERE_ID = 0x0002FC01;

    extern TypeInfo E_COLLISIONSPHERE_TYPEINFO;

}

#endif
