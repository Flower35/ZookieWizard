#ifndef H_KAO2AR_POWERUP
#define H_KAO2AR_POWERUP

#include <ElephantEngine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // ePowerUp interface
    // <kao2.005D4758> (vptr)
    ////////////////////////////////////////////////////////////////

    class ePowerUp : public Gadget
    {
        /*** Properties ***/

        protected:

            /*[0x10]*/ // int32_t type;
            /*[0x14]*/ // ePowerUpManager* manager;

        /*** Methods ***/

        public:

            ePowerUp();
            ~ePowerUp();

        private:

            void createFromOtherObject(const ePowerUp &other);

        public:

            ePowerUp(const ePowerUp &other);
            ePowerUp& operator = (const ePowerUp &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;

            /* << Gadget >> */

            eString getDefaultGadgetName() const override;
    };


    ////////////////////////////////////////////////////////////////
    // ePowerUp TypeInfo
    // <kao2.00507AE0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_POWERUP_ID = 0x0002F550;

    extern TypeInfo E_POWERUP_TYPEINFO;

}

#endif
