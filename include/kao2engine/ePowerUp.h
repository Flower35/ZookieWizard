#ifndef H_KAO2AR_POWERUP
#define H_KAO2AR_POWERUP

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{
    class ePowerUpManager;

    ////////////////////////////////////////////////////////////////
    // ePowerUp interface
    // <kao2.005D4758> (vptr)
    ////////////////////////////////////////////////////////////////

    class ePowerUp : public Gadget
    {

        /*** Properties ***/

        protected:

            /*[0x10]*/ int32_t type;
            /*[0x14]*/ ePowerUpManager* manager;

        /*** Methods ***/

        public:

            ePowerUp();
            ~ePowerUp();

            TypeInfo* getType() override;

            eString getDefaultGadgetName() override;
    };


    ////////////////////////////////////////////////////////////////
    // ePowerUp TypeInfo
    // <kao2.00507B10> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_POWERUP_ID = 0x0002F550;

    extern TypeInfo E_POWERUP_TYPEINFO;

}

#endif
