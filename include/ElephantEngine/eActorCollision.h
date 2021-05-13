#ifndef H_KAO2AR_ACTORCOLLISION
#define H_KAO2AR_ACTORCOLLISION

#include <ElephantEngine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eActorCollision interface
    // <kao2.005D7A20> (vptr)
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

        private:

            void createFromOtherObject(const eActorCollision &other);

        public:

            eActorCollision(const eActorCollision &other);
            eActorCollision& operator = (const eActorCollision &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eActorCollision TypeInfo
    // <kao2.00599EB0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_ACTORCOLLISION_ID = 0x0002FCCA;

    extern TypeInfo E_ACTORCOLLISION_TYPEINFO;

}

#endif
