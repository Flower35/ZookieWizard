#ifndef H_KAO2AR_ADDPOWERUP
#define H_KAO2AR_ADDPOWERUP

#include <ElephantEngine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eAddPowerUp interface
    // <kao2.005D87E0> (vptr)
    ////////////////////////////////////////////////////////////////

    class eAddPowerUp : public Gadget
    {
        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x20]*/

        /*** Methods ***/

        public:

            eAddPowerUp();
            ~eAddPowerUp();

        private:

            void createFromOtherObject(const eAddPowerUp &other);

        public:

            eAddPowerUp(const eAddPowerUp &other);
            eAddPowerUp& operator = (const eAddPowerUp &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eAddPowerUp TypeInfo
    // <kao2.005A48E0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_ADDPOWERUP_ID = 0x3E1CA1FD;

    extern TypeInfo E_ADDPOWERUP_TYPEINFO;

}

#endif
