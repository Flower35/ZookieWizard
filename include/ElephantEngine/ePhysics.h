#ifndef H_KAO2AR_PHYSICS
#define H_KAO2AR_PHYSICS

#include <ElephantEngine/eBasePhysics.h>

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

        private:

            void createFromOtherObject(const ePhysics &other);

        public:

            ePhysics(const ePhysics &other);
            ePhysics& operator = (const ePhysics &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // ePhysics TypeInfo
    // <kao2.004DE0C0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_PHYSICS_ID = 0x0002DF01;

    extern TypeInfo E_PHYSICS_TYPEINFO;

}

#endif
