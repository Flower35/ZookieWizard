#ifndef H_KAO2AR_COLLISIONPRIMITIVE
#define H_KAO2AR_COLLISIONPRIMITIVE

#include <ElephantEngine/eCollision.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eCollisionPrimitive interface
    // <kao2.005D8110>
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

        private:

            void createFromOtherObject(const eCollisionPrimitive &other);

        public:

            eCollisionPrimitive(const eCollisionPrimitive &other);
            eCollisionPrimitive& operator = (const eCollisionPrimitive &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eCollisionPrimitive TypeInfo
    // <kao2.005988D0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_COLLISIONPRIMITIVE_ID = 0x0002FC00;

    extern TypeInfo E_COLLISIONPRIMITIVE_TYPEINFO;

}

#endif
