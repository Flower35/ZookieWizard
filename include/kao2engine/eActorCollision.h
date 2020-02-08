#ifndef H_KAO2AR_ACTORCOLLISION
#define H_KAO2AR_ACTORCOLLISION

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eActorCollision interface
    ////////////////////////////////////////////////////////////////

    class eActorCollision : public Gadget
    {

        /*** Properties ***/

        protected:

            /*[0x10-0x18] (unused group) */

        /*** Methods ***/

        public:

            eActorCollision();
            ~eActorCollision();

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eActorCollision TypeInfo
    // <kao2.00599EE0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_ACTORCOLLISION_ID = 0x0002FCCA;

    extern TypeInfo E_ACTORCOLLISION_TYPEINFO;

}

#endif
