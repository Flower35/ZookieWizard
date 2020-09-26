#ifndef H_KAO2AR_ELECTRICITY
#define H_KAO2AR_ELECTRICITY

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eElectricity interface
    // <kao2.005D72F0> (vptr)
    ////////////////////////////////////////////////////////////////

    class eElectricity : public Gadget
    {
        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x8C]*/

        /*** Methods ***/

        public:

            eElectricity();
            ~eElectricity();

        private:

            void createFromOtherObject(const eElectricity &other);

        public:

            eElectricity(const eElectricity &other);
            eElectricity& operator = (const eElectricity &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eElectricity TypeInfo
    // <kao2.005682B0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_ELECTRICITY_ID = 0x3B3E6942;

    extern TypeInfo E_ELECTRICITY_TYPEINFO;

}

#endif
