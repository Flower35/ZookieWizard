#ifndef H_KAO2AR_COLLISION
#define H_KAO2AR_COLLISION

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eCollision interface
    ////////////////////////////////////////////////////////////////

    class eCollision : public Gadget
    {

        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*[0x11]*/ bool enabled;
            /*[0x14]*/

        /*** Methods ***/

        public:

            eCollision();
            ~eCollision();

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eCollision TypeInfo
    // <kao2.00598140> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_COLLISION_ID = 0x0002FCFF;

    extern TypeInfo E_COLLISION_TYPEINFO;

}

#endif
