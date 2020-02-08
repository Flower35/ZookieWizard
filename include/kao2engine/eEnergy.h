#ifndef H_KAO2AR_ENERGY
#define H_KAO2AR_ENERGY

#include <kao2engine/ePowerBar.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eEnergy interface
    // <kao2.005D4800> (vptr)
    ////////////////////////////////////////////////////////////////

    class eEnergy : public ePowerBar
    {

        /*** Properties ***/

        protected:

            /*[0x54]*/
            /*[0x58]*/
            /*[0x5C]*/

        /*** Methods ***/

        public:

            eEnergy();
            ~eEnergy();

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eEnergy TypeInfo
    // <kao2.0050AEF0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_ENERGY_ID = 0x2DC45EDF;

    extern TypeInfo E_ENERGY_TYPEINFO;

}

#endif
