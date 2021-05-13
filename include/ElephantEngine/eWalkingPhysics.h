#ifndef H_KAO2AR_WALKINGPHYSICS
#define H_KAO2AR_WALKINGPHYSICS

#include <ElephantEngine/ePhysics.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eWalkingPhysics interface
    // <kao2.005D36B8> (vptr)
    ////////////////////////////////////////////////////////////////

    class eWalkingPhysics : public ePhysics
    {
        /*** Properties ***/

        protected:

            /*(...)*/
            /*[0x07EC]*/

        /*** Methods ***/

        public:

            eWalkingPhysics();
            ~eWalkingPhysics();

        private:

            void createFromOtherObject(const eWalkingPhysics &other);

        public:

            eWalkingPhysics(const eWalkingPhysics &other);
            eWalkingPhysics& operator = (const eWalkingPhysics &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eWalkingPhysics TypeInfo
    // <kao2.004E9080> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_WALKINGPHYSICS_ID = 0x0002DF02;

    extern TypeInfo E_WALKINGPHYSICS_TYPEINFO;

}

#endif
