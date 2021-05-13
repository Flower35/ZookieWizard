#ifndef H_KAO2AR_COLLISIONCTRL
#define H_KAO2AR_COLLISIONCTRL

#include <ElephantEngine/Gadget.h>

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

        private:

            void createFromOtherObject(const eCollisionCtrl &other);

        public:

            eCollisionCtrl(const eCollisionCtrl &other);
            eCollisionCtrl& operator = (const eCollisionCtrl &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eCollisionCtrl TypeInfo
    // <kao2.00432ED0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_COLLISIONCTRL_ID = 0x38F55765;

    extern TypeInfo E_COLLISIONCTRL_TYPEINFO;

}

#endif
