#ifndef H_KAO2AR_COLLISIONCTRL
#define H_KAO2AR_COLLISIONCTRL

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eCollisionCtrl interface
    // <kao2.005CEB48> (vptr)
    ////////////////////////////////////////////////////////////////

    class eCollisionCtrl : public Gadget
    {

        /*** Methods ***/

        public:

            eCollisionCtrl();
            ~eCollisionCtrl();

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eCollisionCtrl TypeInfo
    // <kao2.00432F00> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_COLLISIONCTRL_ID = 0x38F55765;

    extern TypeInfo E_COLLISIONCTRL_TYPEINFO;

}

#endif
