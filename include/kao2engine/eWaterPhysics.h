#ifndef H_KAO2AR_WATERPHYSICS
#define H_KAO2AR_WATERPHYSICS

#include <kao2engine/ePhysics.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eWaterPhysics interface
    // <kao2.005D3EF0> (vptr)
    ////////////////////////////////////////////////////////////////

    class eWaterPhysics : public ePhysics
    {

        /*** Properties ***/

        protected:

            /*(...)*/
            /*[0x1218]*/

        /*** Methods ***/

        public:

            eWaterPhysics();
            ~eWaterPhysics();

            TypeInfo* getType() override;
    };


    ////////////////////////////////////////////////////////////////
    // eWaterPhysics TypeInfo
    // <kao2.004F6960> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_WATERPHYSICS_ID = 0x0002DF20;

    extern TypeInfo E_WATERPHYSICS_TYPEINFO;

}

#endif
