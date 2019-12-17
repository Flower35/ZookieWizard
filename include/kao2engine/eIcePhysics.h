#ifndef H_KAO2AR_ICEPHYSICS
#define H_KAO2AR_ICEPHYSICS

#include <kao2engine/ePhysics.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eIcePhysics interface
    // <kao2.005D31E8> (vptr)
    ////////////////////////////////////////////////////////////////

    class eIcePhysics : public ePhysics
    {

        /*** Properties ***/

        protected:

            /*(...)*/
            /*[0x07F8]*/

        /*** Methods ***/

        public:

            eIcePhysics();
            ~eIcePhysics();

            TypeInfo* getType() override;
    };


    ////////////////////////////////////////////////////////////////
    // eIcePhysics TypeInfo
    // <kao2.004DF600> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_ICEPHYSICS_ID = 0x0002DF04;

    extern TypeInfo E_ICEPHYSICS_TYPEINFO;

}

#endif
