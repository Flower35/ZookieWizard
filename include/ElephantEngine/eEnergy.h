#ifndef H_KAO2AR_ENERGY
#define H_KAO2AR_ENERGY

#include <ElephantEngine/ePowerBar.h>

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

        private:

            void createFromOtherObject(const eEnergy &other);

        public:

            eEnergy(const eEnergy &other);
            eEnergy& operator = (const eEnergy &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eEnergy TypeInfo
    // <kao2.0050AEC0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_ENERGY_ID = 0x2DC45EDF;

    extern TypeInfo E_ENERGY_TYPEINFO;

}

#endif
