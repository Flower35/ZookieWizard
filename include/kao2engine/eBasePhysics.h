#ifndef H_KAO2AR_BASEPHYSICS
#define H_KAO2AR_BASEPHYSICS

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eBasePhysics interface
    // <kao2.005D3068> (vptr)
    ////////////////////////////////////////////////////////////////

    class eBasePhysics : public Gadget
    {

        /*** Properties ***/

        protected:

            /*[0x0010]*/
            /*(...)*/
            /*[0x0750]*/

        /*** Methods ***/

        public:

            eBasePhysics();
            ~eBasePhysics();

            TypeInfo* getType() const override;

            eString getDefaultGadgetName() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eBasePhysics TypeInfo
    // <kao2.004DC900> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_BASEPHYSICS_ID = 0x0002DF00;

    extern TypeInfo E_BASEPHYSICS_TYPEINFO;

}

#endif
