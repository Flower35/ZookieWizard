#ifndef H_KAO2AR_SNOWBOARDRAMPPHYSICS
#define H_KAO2AR_SNOWBOARDRAMPPHYSICS

#include <kao2engine/eSnowboardPhysics.h>

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

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eSnowboardRampPhysics TypeInfo
    // <kao2.004E7400> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_SNOWBOARDRAMPPHYSICS_ID = 0x3B950C51;

    extern TypeInfo E_SNOWBOARDRAMPPHYSICS_TYPEINFO;

}

#endif
