#ifndef H_KAO2AR_SNOWBOARDPHYSICS
#define H_KAO2AR_SNOWBOARDPHYSICS

#include <kao2engine/eBasePhysics.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSnowboardPhysics interface
    // <kao2.005D3390> (vptr)
    ////////////////////////////////////////////////////////////////

    class eSnowboardPhysics : public eBasePhysics
    {

        /*** Properties ***/

        protected:

            /*(...)*/
            /*[0x07EC]*/

        /*** Methods ***/

        public:

            eSnowboardPhysics();
            ~eSnowboardPhysics();

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eSnowboardPhysics TypeInfo
    // <kao2.004E3340> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_SNOWBOARDPHYSICS_ID = 0x3B950C40;

    extern TypeInfo E_SNOWBOARDPHYSICS_TYPEINFO;

}

#endif
