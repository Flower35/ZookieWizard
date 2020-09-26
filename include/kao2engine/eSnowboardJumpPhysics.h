#ifndef H_KAO2AR_SNOWBOARDJUMPPHYSICS
#define H_KAO2AR_SNOWBOARDJUMPPHYSICS

#include <kao2engine/eJumpPhysics.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSnowboardJumpPhysics interface
    // <kao2.005D3410> (vptr)
    ////////////////////////////////////////////////////////////////

    class eSnowboardJumpPhysics : public eJumpPhysics
    {
        /*** Properties ***/

        protected:

            /*[0x0884]*/
            /*(...)*/
            /*[0x0898]*/

        /*** Methods ***/

        public:

            eSnowboardJumpPhysics();
            ~eSnowboardJumpPhysics();

        private:

            void createFromOtherObject(const eSnowboardJumpPhysics &other);

        public:

            eSnowboardJumpPhysics(const eSnowboardJumpPhysics &other);
            eSnowboardJumpPhysics& operator = (const eSnowboardJumpPhysics &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eSnowboardJumpPhysics TypeInfo
    // <kao2.004E5970> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_SNOWBOARDJUMPPHYSICS_ID = 0x3B950C42;

    extern TypeInfo E_SNOWBOARDJUMPPHYSICS_TYPEINFO;

}

#endif
