#ifndef H_KAO2AR_WHALEPHYSICS
#define H_KAO2AR_WHALEPHYSICS

#include <kao2engine/ePhysics.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eWhalePhysics interface
    // <kao2.005D4030> (vptr)
    ////////////////////////////////////////////////////////////////

    class eWhalePhysics : public ePhysics
    {

        /*** Properties ***/

        protected:

            /*(...)*/
            /*[0x1104]*/

        /*** Methods ***/

        public:

            eWhalePhysics();
            ~eWhalePhysics();

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eWhalePhysics TypeInfo
    // <kao2.004FBB00> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_WHALEPHYSICS_ID = 0x0002DF21;

    extern TypeInfo E_WHALEPHYSICS_TYPEINFO;

}

#endif
