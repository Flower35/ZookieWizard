#ifndef H_KAO2AR_SNOWBOARDRAMPPHYSICS
#define H_KAO2AR_SNOWBOARDRAMPPHYSICS

#include <ElephantEngine/eSnowboardPhysics.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSnowboardRampPhysics interface
    // <kao2.005D3508> (vptr)
    ////////////////////////////////////////////////////////////////

    class eSnowboardRampPhysics : public eSnowboardPhysics
    {
        /*** Properties ***/

        protected:

            /*[0x07F0]*/
            /*(...)*/
            /*[0x0810]*/

        /*** Methods ***/

        public:

            eSnowboardRampPhysics();
            ~eSnowboardRampPhysics();

        private:

            void createFromOtherObject(const eSnowboardRampPhysics &other);

        public:

            eSnowboardRampPhysics(const eSnowboardRampPhysics &other);
            eSnowboardRampPhysics& operator = (const eSnowboardRampPhysics &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eSnowboardRampPhysics TypeInfo
    // <kao2.004E73D0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_SNOWBOARDRAMPPHYSICS_ID = 0x3B950C51;

    extern TypeInfo E_SNOWBOARDRAMPPHYSICS_TYPEINFO;

}

#endif
